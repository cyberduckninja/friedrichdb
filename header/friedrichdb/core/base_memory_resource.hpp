#pragma once


class memory_resource {
public:
    virtual ~memory_resource() = default;

    void *allocate(std::size_t bytes, std::size_t alignment = alignof(std::max_align_t)) {
        return do_allocate(bytes, alignment);
    }


    void deallocate(void *p, std::size_t bytes, std::size_t alignment = alignof(std::max_align_t)) {
        do_deallocate(p, bytes, alignment);
    }


    bool is_equal(memory_resource const &other) const noexcept { return do_is_equal(other); }

private:

    virtual void *do_allocate(std::size_t bytes,
                              std::size_t alignment = alignof(std::max_align_t)) = 0;


    virtual void do_deallocate(void *p,
                               std::size_t bytes,
                               std::size_t alignment = alignof(std::max_align_t)) = 0;

    virtual bool do_is_equal(memory_resource const &other) const noexcept {
        return this == &other;
    }
};