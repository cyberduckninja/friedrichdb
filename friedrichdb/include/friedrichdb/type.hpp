#ifndef TYPE_HPP
#define TYPE_HPP

#include <cstdint>
#include <cstdint>
#include <memory>
#include <unordered_map>

namespace friedrichdb {
    namespace tuple {
        namespace type {

            enum class object_type {
                NILL = 0x00,
                BOOLEAN = 0x01,
                POSITIVE_INTEGER = 0x02,
                NEGATIVE_INTEGER = 0x03,
                FLOAT32 = 0x0a,
                FLOAT64 = 0x04,
                FLOAT = 0x04,
                STR = 0x05,
                ARRAY = 0x06,
                MAP = 0x07,
                BIN = 0x08,
                EXT = 0x09
            };

            struct meta_type final {
                constexpr meta_type(object_type id, bool fixed, bool inner_bson)
                        :
                        inner(inner_bson),
                        fixed(fixed),
                        id(id) {}

                constexpr bool operator==(const meta_type &rhs) const {
                    return fixed == rhs.fixed && inner == rhs.inner && id == rhs.id;
                }

                constexpr bool operator!=(const meta_type &rhs) const {
                    return !(rhs == *this);
                }

                const bool fixed;
                const bool inner;
                const object_type id;
            };
        }
    }

    constexpr const tuple::type::meta_type positive_integer_t(tuple::type::object_type::POSITIVE_INTEGER,true,false);
    constexpr const tuple::type::meta_type string_t(tuple::type::object_type::STR,false,false);
    constexpr const tuple::type::meta_type double_t(tuple::type::object_type::FLOAT64,true,false);
    constexpr const tuple::type::meta_type boolean_t(tuple::type::object_type::FLOAT64,true,false);

}
#endif //PROJECT_TYPE_HPP
