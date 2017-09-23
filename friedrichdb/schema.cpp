#include "friedrichdb/schema.hpp"

namespace friedrichdb {

    schema::schema(std::initializer_list<meta_data_t> raw_schema) {
        std::string tmp;

        for (const auto &i: raw_schema) {
            tmp.append("|");
            auto number = types.size();
            types.emplace_back(i.name, number, i.type);
            tmp.append(i.name).append(":").append(std::to_string(number)).append(":").append(run_time_type::to_string(i.type));
            tmp.append("|");
        }

        hash = std::hash<std::string>()(tmp);
    }

    std::size_t schema::size() const {
        return types.size();
    }

    auto schema::begin() -> type_type::iterator{
        return types.begin();
    }

    auto schema::end() -> type_type::iterator{
        return types.end();
    }

    schema::__element__::__element__(const std::string &name, std::size_t id, run_time_type::meta_type type)
            :
            id(id),
            type(name,type)

    {}
}