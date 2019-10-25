#pragma once

#include <utility>
#include <memory>
#include <string>
#include <set>
#include <unordered_map>

#include <friedrichdb/serializable.hpp>
#include <friedrichdb/document/field.hpp>

namespace friedrichdb {

    struct flat_document final : public serializable {

        flat_document() = default;

        flat_document(const flat_document &) = default;

        flat_document &operator=(const flat_document &) = default;

        flat_document(flat_document &&) = default;

        flat_document &operator=(flat_document &&) = default;

        ~flat_document() override = default;

        std::string serialization_json() const override {}

        void deserialization_json(binary_data) override {}

        using storage = std::unordered_map<std::string, field>;

        template<typename Key, typename Value>
        void emplace(Key &&key, Value &&value) {
            fields.emplace(std::forward<Key>(key), std::forward<Value>(value));
            keys.emplace(std::forward<Key>(key));
        }

        std::string document_id;
        storage fields;
        std::set<std::string> keys;
    };

    using document = flat_document;

}