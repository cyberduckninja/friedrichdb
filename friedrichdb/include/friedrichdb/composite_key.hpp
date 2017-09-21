#ifndef COMPOSITE_KEY_HPP
#define COMPOSITE_KEY_HPP

#include "tuple_t.hpp"
#include "object_id.hpp"

namespace friedrichdb {

    struct composite_key {
        composite_key(const object_id &id_1, const size_t id_2);
        ~composite_key()= default;
        const object_id   id_1;
        const std::size_t id_2;

        bool operator == (const composite_key &rhs) const;

        bool operator != (const composite_key &rhs) const;

        std::size_t hash() const {
            return std::hash<std::string>()(id_1.to_string()) ^ std::hash<std::size_t>()(id_2);
        }
    };

    struct hash {
        std::size_t operator()(const friedrichdb::composite_key& key) const {
            return key.hash();
        }
    };
}
#endif
