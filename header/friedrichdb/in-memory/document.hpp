#pragma once

#include <friedrichdb/serializable.hpp>
#include <memory>
#include <atomic>
#include <map>

namespace friedrichdb { namespace in_memory {
        using object = std::string;
        using tuple_storage = std::vector<object>;
        struct manager final {
            manager()= default;
            manager(const std::string &name, size_t position) : name(name), position(position) {}
            ~manager()= default;
            std::string name;
            std::size_t position;
        };
        using vector_type = std::vector<manager>;


        class document final : public serializable {
        public:

            document() = default;

            document(const document &) = default;

            document &operator=(const document &) = default;

            document(document &&) = default;

            document &operator=(document &&) = default;

            ~document() override = default;

            std::string serialization_json() const override {

            }

            void deserialization_json(std::string) override {

            }

            template<typename... _Args>
            void emplace(const std::string &key, _Args &&... __args) {
               storage_.emplace_back((__args)...);
               index.emplace(key,manager("",storage_.size()));

            }

            auto operator[](const std::string &key) -> object & {
                return storage_[index[key].position];
            }

            auto at(const std::string &key) -> object & {
                return storage_[index.at(key).position];
            }

            auto at(const std::string &key) const -> const object & {
                return storage_[index.at(key).position];
            }

            auto operator[](std::size_t key) -> object & {
                return storage_[key];
            }

            auto at(std::size_t key) -> object & {
                return storage_.at(key);
            }

            auto at(std::size_t key) const -> const object & {
                return storage_.at(key);
            }


        private:
            std::size_t id; //TODO move to meta data in storage;
            std::map<std::string, manager> index;
            tuple_storage storage_;

        };

    }
}