#ifndef TABLE_SCHEMA_H
#define TABLE_SCHEMA_H

#include <vector>
#include <string>
#include <initializer_list>

#include "type.hpp"
#include "meta_data_t.hpp"

namespace friedrichdb {

    /**
     * json
     {
        "name":"example",
        "schema":[
            {
                "name":a,
	            "type":int
            },

	        {
	            "name":b,
	            "type":bool
  	        },
	        {
	            "name":c,
	            "type":double
	        },
        ]
         "indexs":[
            {
                "rows":[],
                "constrain":[]
            }
         ]
     }
     */


    class schema final {
    public:
        ~schema() = default;

        const std::string& name() const {
            return name_;
        }

        /// |name:type:id|name:type:id|name:type:id|
        schema(const std::string&name, std::initializer_list<meta_data_t> raw_schema,std::initializer_list<std::string> constrain);

        /// compile time check
        template<typename T>
        auto check(const T &data) const -> bool {
            return hash == data.template hash();
        }

        std::pair< std::vector<meta_data_t>::const_iterator,std::vector<meta_data_t>::const_iterator> get_schema() const;

        std::pair<std::vector<std::string>::const_iterator ,std::vector<std::string>::const_iterator> get_indexs() const;

        bool hash_element_in_schema(const std::string &name) const;



    private:
        std::string name_;
        std::vector<meta_data_t> schema_;
        std::vector<std::string> constrain_;
        std::size_t hash;
    };

}

#endif //TABLE_SCHEMA_H
