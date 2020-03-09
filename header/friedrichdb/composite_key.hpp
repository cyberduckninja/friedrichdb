#ifndef COMPOSITE_KEY_HPP
#define COMPOSITE_KEY_HPP

#include "tuple_t.hpp"
#include "friedrichdb/data_types/object_id.hpp"

namespace friedrichdb {

    struct composite_key final {
        composite_key(const data_types::object_id &id_1, size_t id_2);
        ~composite_key() = default;
        const data_types::object_id id_1;
        const std::size_t           id_2;

        bool operator == (const composite_key &rhs) const;

        bool operator != (const composite_key &rhs) const;

        auto hash() const -> std::size_t;
    };

    struct hash {
        std::size_t operator()(const friedrichdb::composite_key& key) const;
    };
}
#endif
