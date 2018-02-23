#include "friedrichdb/data_types/timestamp.hpp"
#include <ostream>
namespace friedrichdb {
        std::ostream &operator<<(std::ostream &out, const timestamp &ts) {
            return out << "timestamp_t(" << ts.first() << ", " << ts.second() << ")";
        }
}