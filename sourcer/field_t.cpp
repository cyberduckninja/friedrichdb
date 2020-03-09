#include "friedrichdb/field_t.hpp"

namespace friedrichdb {

    void field_t::set(const byte *data, std::size_t size) {
            data_.resize(size);
            for (std::size_t i = 0; i < size; ++i) {
                data_[i] = data[i];
            }
    }

    byte *field_t::data() {
        return data_.data();
    }

    const byte *field_t::data() const {
        return data_.data();
    }

    std::size_t field_t::size() const {
        return data_.size();
    }

    void field_t::push_back(const char *data, std::size_t size) {
        const byte *p = reinterpret_cast<const byte *>(data);
        data_.insert(data_.end(), p, p + size);
    }
}