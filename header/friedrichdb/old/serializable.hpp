#pragma once

#include <string>

namespace friedrichdb {

    using binary_data = std::string;

    struct serializable {

        virtual binary_data serialization_json() const = 0;

        virtual void deserialization_json(binary_data) = 0;

        virtual ~serializable() = default;

    };
}


