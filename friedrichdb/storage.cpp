
#include <vector>

#include "friedrichdb/tuple/storage.hpp"
namespace friedrichdb {
    namespace tuple {
        namespace implement {
            struct storage_t::Impl {
                std::atomic<std::size_t> refcount{0};
                std::vector<char> data;
            };

            void storage_t::reset(storage_t::Impl *p) {
                if (p)
                    ++p->refcount;
                if (impl_ && !--impl_->refcount)
                    delete impl_;
                impl_ = p;
            }

            storage_t::storage_t() : impl_(0) {}

            storage_t::storage_t(const storage_t &s) : impl_(0) { reset(s.impl_); }

            storage_t &storage_t::operator=(const storage_t &s) {
                reset(s.impl_);
                return *this;
            }

            storage_t::~storage_t() { reset(0); }

            const char *storage_t::data() const {
                static const char ZERO = 0;
                return impl_ ? impl_->data.data() : &ZERO;
            }

            char *storage_t::data() {
                return impl_ ? impl_->data.data() : 0;
            }

            size_t storage_t::size() const { return impl_ ? impl_->data.size() : 0; }

            void storage_t::push(const void *data, size_t size) {
                const char *p = reinterpret_cast<const char *>(data);
                if (!impl_)
                    reset(new Impl);
                impl_->data.insert(impl_->data.end(), p, p + size);
            }

            void storage_t::resize(size_t size) { impl_->data.resize(size); }

        }
    }
}
