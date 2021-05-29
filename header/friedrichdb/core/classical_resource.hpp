#pragma once

#include "base_memory_resource.hpp"

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <new>

#include <boost/core/ignore_unused.hpp>


static constexpr std::size_t default_host_alignment{alignof(std::max_align_t)};

constexpr bool is_pow2(std::size_t n) { return (0 == (n & (n - 1))); }

constexpr bool is_supported_alignment(std::size_t alignment) { return is_pow2(alignment); }

template<typename Alloc>
void *aligned_allocate(std::size_t bytes, std::size_t alignment, Alloc alloc) {
    assert(is_pow2(alignment));

    std::size_t padded_allocation_size{bytes + alignment + sizeof(std::ptrdiff_t)};

    char *const original = static_cast<char *>(alloc(padded_allocation_size));

    void *aligned{original + sizeof(std::ptrdiff_t)};

    std::align(alignment, bytes, aligned, padded_allocation_size);

    std::ptrdiff_t offset = static_cast<char *>(aligned) - original;

    *(static_cast<std::ptrdiff_t *>(aligned) - 1) = offset;

    return aligned;
}


template<typename Dealloc>
void aligned_deallocate(void *p, std::size_t bytes, std::size_t alignment, Dealloc dealloc) {
    boost::ignore_unused(alignment);

    std::ptrdiff_t const offset = *(reinterpret_cast<std::ptrdiff_t *>(p) - 1);

    void *const original = static_cast<char *>(p) - offset;

    dealloc(original);
}

class classical_resource final : public memory_resource {
public:
    classical_resource() = default;

    ~classical_resource() = default;

    classical_resource(classical_resource const &) = default;

    classical_resource(classical_resource &&) = default;

    classical_resource &operator=(classical_resource const &) = default;

    classical_resource &operator=(classical_resource &&) = default;

private:

    void *do_allocate(std::size_t bytes, std::size_t alignment = default_host_alignment) override {
#if __cplusplus >= 201703L
        return ::operator new(bytes, std::align_val_t(alignment));
#else
        // If the requested alignment isn't supported, use default
    alignment =(is_supported_alignment(alignment)) ? alignment : default_host_alignment;

    return aligned_allocate(bytes, alignment, [](std::size_t size) { return ::operator new(size); });
#endif
    }


    void do_deallocate(void *p, std::size_t bytes, std::size_t alignment = default_host_alignment) override {
#if __cplusplus >= 201703L
        ::operator delete(p, bytes, std::align_val_t(alignment));
#else
        aligned_deallocate(p, bytes, alignment, [](void *p) { ::operator delete(p); });
#endif
    }
};