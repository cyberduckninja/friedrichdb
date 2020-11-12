#pragma once

#include <cassert>
#include <stdexcept>
#include <utility>

class buffer {
public:
    buffer() = delete;
    explicit buffer(std::size_t size,
                    mr::device_memory_resource *mr = mr::get_current_device_resource())
            :  _mr{mr} {
        allocate(size);
    }


    buffer(void const *source_data,
           std::size_t size,
           mr::device_memory_resource *mr = mr::get_current_device_resource())
            :  _mr{mr} {
        allocate(size);
        copy(source_data, size);
    }


    buffer(buffer const &other,
           rmm::mr::device_memory_resource *mr = rmm::mr::get_current_device_resource())
            : device_buffer{other.data(), other.size(), stream, mr} {
    }


    buffer(buffer &&other) noexcept
            : _data{other._data},
              _size{other._size},
              _capacity{other._capacity},
              _mr{other._mr} {
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }


    buffer &operator=(buffer const &other) {
        if (&other != this) {
            // If the current capacity is large enough and the resources are
            // compatible, just reuse the existing memory
            if ((capacity() > other.size()) and _mr->is_equal(*other._mr)) {
                resize(other.size());
                copy(other.data(), other.size());
            } else {
                // Otherwise, need to deallocate and allocate new memory
                deallocate();
                _mr = other._mr;
                allocate(other.size());
                copy(other.data(), other.size());
            }
        }
        return *this;
    }


    buffer &operator=(buffer &&other) noexcept {
        if (&other != this) {
            deallocate();

            _data = other._data;
            _size = other._size;
            _capacity = other._capacity;
            _mr = other._mr;

            other._data = nullptr;
            other._size = 0;
            other._capacity = 0;
        }
        return *this;
    }


    ~buffer() noexcept {
        deallocate();
        _mr = nullptr;
    }


    void resize(std::size_t new_size) {
        // If the requested size is smaller than the current capacity, just update
        // the size without any allocations
        if (new_size <= capacity()) {
            _size = new_size;
        } else {
            void *const new_data = _mr->allocate(new_size);
            RMM_CUDA_TRY(cudaMemcpyAsync(new_data, data(), size(), cudaMemcpyDefault, this->stream().value()));
            deallocate();
            _data = new_data;
            _size = new_size;
            _capacity = new_size;
        }
    }


    void shrink_to_fit() {
        if (size() != capacity()) {
            // Invoke copy ctor on self which only copies `[0, size())` and swap it
            // with self. The temporary `device_buffer` will hold the old contents
            // which will then be destroyed
            auto tmp = buffer{*this, _mr};
            std::swap(tmp, *this);
        }
    }


    void const *data() const noexcept { return _data; }

    void *data() noexcept { return _data; }

    std::size_t size() const noexcept { return _size; }

    bool is_empty() const noexcept { return 0 == size(); }

    std::size_t capacity() const noexcept { return _capacity; }

    mr::device_memory_resource *memory_resource() const noexcept { return _mr; }

private:
    void *_data{nullptr};
    std::size_t _size{};
    std::size_t _capacity{};
    mr::device_memory_resource *_mr{mr::get_current_device_resource()};

    void allocate(std::size_t bytes) {
        _size = bytes;
        _capacity = bytes;
        _data = (bytes > 0) ? _mr->allocate(bytes, stream()) : nullptr;
    }


    void deallocate() noexcept {
        if (capacity() > 0) { _mr->deallocate(data(), capacity(), stream()); }
        _size = 0;
        _capacity = 0;
        _data = nullptr;
    }


    void copy(void const *source, std::size_t bytes) {
        if (bytes > 0) {
            RMM_EXPECTS(nullptr != source, "Invalid copy from nullptr.");
            RMM_CUDA_TRY(cudaMemcpyAsync(_data, source, bytes, cudaMemcpyDefault, stream().value()));
        }
    }
};