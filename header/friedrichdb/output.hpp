#pragma once

#include <vector>
#include <friedrichdb/serializable.hpp>

namespace friedrichdb {

    class output_operation final : public serializable {
    public:
        output_operation() = default;

        ~output_operation() override = default;

        void deserialization_json(std::string) {

        }

        std::string serialization_json() const {

        }

        operation_type operation;
        std::string table;
        std::string output_;
    };

    class output_transaction final : public serializable {
    public:
        output_transaction() = default;

        ~output_transaction() override = default;

        std::string serialization_json() const override {

        }

        void deserialization_json(std::string) override {

        }

        template<typename... Args>
        void emplace_back(Args &&... args) {
            outputs_.emplace_back(std::forward<Args>(args)...);
        }

        std::vector<output_operation> outputs_;
    };


    class output_query final : public serializable {
    public:
        output_query() = default;

        ~output_query() override = default;

        std::string serialization_json() const {

        }

        void deserialization_json(std::string) {

        }

        template<typename... Args>
        void emplace_back(Args &&... args) {
            outputs_.emplace_back(std::forward<Args>(args)...);
        }

        std::vector<output_transaction> outputs_;
    };


}