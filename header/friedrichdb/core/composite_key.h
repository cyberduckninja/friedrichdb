#pragma once

#include "../serializable.hpp"
namespace friedrichdb {

    /// database:collection:guid - guid document

    using composite_key = std::string;
/*
        class composite_key final : public serializable {
        public:

            composite_key(const std::string& base_):
            base_(base_),
            advasted(""){

            }

            std::string serialization_json() const override {

            }

            void deserialization_json(std::string) override  {

            }


            auto operator==(const composite_key&other) const -> bool {

            }

            std::string advasted{};
        private:
            std::string base_;


        };
        */
}