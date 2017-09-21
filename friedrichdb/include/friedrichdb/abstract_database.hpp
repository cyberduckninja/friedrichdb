#ifndef ABSTRACT_DATABASE_HPP
#define ABSTRACT_DATABASE_HPP

#include <functional>
#include <friedrichdb/tuple_t.hpp>
#import "array"

namespace friedrichdb {

    using row             = tuple_t;
    using response        = std::vector<row>;
    using where           = std::function<bool(row)>;
    using generator       = std::function<response()>;
    using where_generator = std::function<row(row)>;

    struct abstract_database {
        enum class storge_t : uint8_t {
            memory = 0,
            disk,
            instance
        };

        explicit abstract_database(storge_t t) : type_(t) {}

        virtual response find(where) const = 0;

        virtual bool update(where_generator) = 0;

        virtual bool erase(where) = 0;

        virtual bool insert(generator) = 0;

        virtual ~abstract_database() = default;

        storge_t type() const {
            return type_;
        }

    private:
        storge_t type_;
    };
}
#endif //VERSIONS_ABSTRACT_DATABASE_HPP
