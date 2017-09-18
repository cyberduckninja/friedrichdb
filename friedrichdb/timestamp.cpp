#include "friedrichdb/tuple/timestamp.hpp"
#include <ostream>
namespace friedrichdb {
    namespace tuple {
        std::ostream &operator<<(std::ostream &out, const timestamp &ts) {
            return out << "timestamp_t(" << ts.first() << ", " << ts.second() << ")";
        }
    }
}