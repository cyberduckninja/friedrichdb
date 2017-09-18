#include "friedrichdb/composite_key.hpp"
namespace friedrichdb {

    composite_key::composite_key(const tuple::object_id &id_1, const size_t id_2) : id_1(id_1), id_2(id_2) {}

    bool composite_key::operator==(const composite_key &rhs) const {
        return id_1 == rhs.id_1 &&
               id_2 == rhs.id_2;
    }

    bool composite_key::operator!=(const composite_key &rhs) const {
        return !(rhs == *this);
    }

}