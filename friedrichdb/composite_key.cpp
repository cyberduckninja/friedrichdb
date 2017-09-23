#include "friedrichdb/composite_key.hpp"
namespace friedrichdb {

    composite_key::composite_key(const data_types::object_id &id_1, const size_t id_2) : id_1(id_1), id_2(id_2) {}

    bool composite_key::operator==(const composite_key &rhs) const {
        return id_1 == rhs.id_1 &&
               id_2 == rhs.id_2;
    }

    bool composite_key::operator!=(const composite_key &rhs) const {
        return !(rhs == *this);
    }

    auto composite_key::hash() const -> std::size_t {
        return std::hash<std::string>()(id_1.to_string()) ^ std::hash<std::size_t>()(id_2);
    }

    std::size_t hash::operator()(const friedrichdb::composite_key &key) const {
        return key.hash();
    }

}