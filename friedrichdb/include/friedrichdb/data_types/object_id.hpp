#ifndef OBJECT_ID_HPP
#define OBJECT_ID_HPP

#include "ordering.h"

namespace friedrichdb {

    namespace data_types {

        class object_id final : public implement::ordered<object_id> {
        public:
            object_id() { ::memset(data_, 0, DataSize); }

            object_id(const char *hex);

            object_id(const std::string &hex);

            std::string to_string() const;

            time_t get_timestamp() const;

            static object_id generate();

            static object_id min_id_for_timestamp(time_t);

            static object_id max_id_for_timestamp(time_t);

        private:
            object_id(uint32_t time, uint64_t counter);

            enum {
                DataSize = 12
            };

            union {
                struct {
                    uint32_t time_;
                    uint64_t counter_;
                } __attribute__((packed));
                char data_[DataSize];
            };

            friend class implement::ordered_base;

            template<template<class> class Cmp>
            static bool cmp(const object_id &a, const object_id &b) {
                return Cmp<int>()(::memcmp(a.data_, b.data_, DataSize), 0);
            }

            friend std::ostream &operator<<(std::ostream &out, const object_id &);
        };

    }
}
namespace std {

    template <>
    struct hash<friedrichdb::data_types::object_id>{
        std::size_t operator()(friedrichdb::data_types::object_id id) const {
            return std::hash<std::string>{}(id.to_string());
        }
    };

}

#endif //OBJECT_ID_HPP
