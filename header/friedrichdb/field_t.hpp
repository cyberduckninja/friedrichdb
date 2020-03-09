#ifndef FIELD_T_HPP
#define FIELD_T_HPP

#include "friedrichdb/data_types/ordering.h"
#include <vector>
#include <memory>

namespace friedrichdb {

        using byte = std::uint8_t;

        class field_t final : public implement::ordered<field_t> {
        public:
            field_t() = default;

            ~field_t() = default;

            void set(const byte *data, std::size_t size);

            void push_back(const char *data, std::size_t size);

            byte *data();

            const byte *data() const;;

            std::size_t size() const;;

        private:
            std::vector <byte> data_;
        };

        using field_ptr = std::shared_ptr<field_t>;
}
#endif
