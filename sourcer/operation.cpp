#include <friedrichdb/operation.hpp>

namespace friedrichdb {

    std::string to_string(friedrichdb::operation_type type) {
        switch (type) {

            case friedrichdb::operation_type::create:
                return "create";
            case friedrichdb::operation_type::find:
                return "find";
            case friedrichdb::operation_type::modify:
                return "modify";
            case friedrichdb::operation_type::remove:
                return "remove";
        }
    }

    operation_type from_string(std::string type) {

        switch (*type.begin()) {
            case 'c':
                return friedrichdb::operation_type::create;
            case 'f':
                return friedrichdb::operation_type::find;
            case 'm':
                return friedrichdb::operation_type::modify;
            case 'r':
                return friedrichdb::operation_type::remove;

            default:
                break;
        }

    }

}
