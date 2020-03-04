#pragma once

#include <string>


namespace friedrichdb { namespace core {

        struct collection_create_options final {
            std::string name_;
        };

        struct collection_remove_options final {
            std::string name_;
        };

        struct collection_find_options final {
            std::string name_;
        };

        struct database_constructor_options final {};

}}