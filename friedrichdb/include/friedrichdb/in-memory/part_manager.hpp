#ifndef PART_MANAGER_HPP
#define PART_MANAGER_HPP

#include <cstddef>
#include <friedrichdb/abstract_table.hpp>
#include <list>

namespace friedrichdb {
    namespace in_memory {
        class part_manager final {
        public:
            part_manager() : current_part(0) {
                part.emplace_back(std::vector<row>());
            }

            std::vector<row> &part_number(std::size_t index) {
                return *part.begin();
            }

            row &current_row(const address __address__) {
                return part.begin()->at(__address__.number);
            }

            address push_back(row&& data) {
                address tmp;
                part.begin()->emplace_back(std::move(data));
                tmp.part_number = current_part;
                tmp.number = part.begin()->size();
                return tmp;
            }

        private:
            std::size_t current_part;
            std::list<std::vector<row>> part;
        };
    }
}
#endif //PROJECT_PART_MANAGER_HPP
