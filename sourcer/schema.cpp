#include "friedrichdb/schema.hpp"

namespace friedrichdb {

    schema::schema(const std::string& name,std::initializer_list<meta_data_t> raw_schema,std::initializer_list<std::string> constrain):name_(name) {
        std::string tmp;

        for (const auto &i: raw_schema) {
            tmp.append("|");
            auto number = schema_.size();
            schema_.emplace_back(i.name, number, i.type);
            tmp.append(i.name).append(":").append(std::to_string(number)).append(":").append(run_time_type::to_string(i.type));
            tmp.append("|");
        }

        hash = std::hash<std::string>()(tmp);
    }

    bool schema::hash_element_in_schema(const std::string &name) const {
        bool tmp;

        for (const auto &i:schema_) {
            if (i.name == name) {
                tmp = true;
                break;
            }
        }

        return tmp;
    }

    std::pair<std::vector<meta_data_t>::const_iterator,std::vector<meta_data_t>::const_iterator> schema::get_schema() const {
        auto tmp = std::make_pair(schema_.cbegin(),schema_.cend());
        return tmp;
    }

    std::pair<std::vector<std::string>::const_iterator, std::vector<std::string>::const_iterator> schema::get_indexs() const {
        auto tmp = std::make_pair(constrain_.cbegin(),constrain_.cend());
        return tmp;
    }

}