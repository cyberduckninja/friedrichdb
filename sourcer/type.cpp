#include <string>
#include "friedrichdb/type.hpp"

namespace friedrichdb {

    namespace run_time_type {

        std::string to_string(const meta_type& t) {
            switch(t.id){
                case object_type::NILL:
                    return "null";
                case object_type::BOOLEAN:
                    return "bool";
                case object_type::POSITIVE_INTEGER:
                    return "POSITIVE_INTEGER";
                case object_type::NEGATIVE_INTEGER:
                    return "NEGATIVE_INTEGER";
                case object_type::FLOAT32:
                    return "float32";
                case object_type::FLOAT64:
                    return "float64";
                case object_type::STR:
                    return "str";
                case object_type::ARRAY:
                    return "array";
                case object_type::MAP:
                    return "map";
                case object_type::BIN:
                    return "bin";
                case object_type::EXT:
                    return "ext";
            }
        }


    }
}