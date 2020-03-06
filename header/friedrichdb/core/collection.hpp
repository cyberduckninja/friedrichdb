#pragma once

#include <utility>
#include <memory>
#include <algorithm>

#include <boost/container/static_vector.hpp>

#include "basic_field.hpp"

namespace friedrichdb { namespace core {

        template<template<typename P> class Allocator>
        using basic_row_t = basic_vector_t<field<Allocator>, Allocator>;

        template<template<typename P> class Allocator>
        using basic_storage_base_t = basic_vector_t<basic_row_t<Allocator>, Allocator>;


        enum class join_type {
          left,
          right,
          inner,
          full_outer

        };

        template<template<typename A> class Allocator>
        class collection;

        template<
                template<typename A>class Allocator1,
                template<typename A> class Allocator2
        >
        auto left_join(
                std::vector<std::string> &keys,
                const collection<Allocator1> &c1,
                const collection<Allocator2> &c2) -> void {

          for(auto&i: c1.schema()){
            keys.push_back(i.name_);
          }

        }


        template<template<typename A> class Allocator>
        class collection final {
        public:
            using schema_t  = basic_schema_t<Allocator>;
            using row_t = basic_row_t<Allocator>;
            using storage_base_t = basic_storage_base_t<Allocator>;

            template<template<typename A> class OtherAllocator>
            collection(const basic_schema_t<OtherAllocator>& current_schema)
                : schema_(current_schema.begin(), current_schema.end()) {}

            template<template<typename A> class OtherAllocator>
            void update(
                    const collection<OtherAllocator> &other,
                    join_type join = join_type::left,
                    bool overwrite = true
            ) { ///, filter_func=None, errors='ignore'))
                std::vector<std::string> key;

                switch (join) {
                    case join_type::left:
                        left_join(key, this, other);
                        break;
                    case join_type::right:
                      break;
                    case join_type::inner:
                      break;
                    case join_type::full_outer:
                      break;
                    }

                for(){

                }


            }


            row_t &row(std::size_t index) {
                return storage_.at(index);
            }

            const row_t &row(std::size_t index) const {
                return storage_.at(index);
            }

            const schema_t &schema() const { return schema_; }

            const field_base &field(std::size_t i) const { return schema_.field(i); }

            table_view Slice(int64_t offset, int64_t length) { }

            table_view Slice(int64_t offset) const { return Slice(offset, num_rows_); }

            int num_columns() const { return schema_.storage_.size(); }

            std::size_t size() const {
              return storage_.size();
            }

        private:
            schema_t schema_;
            storage_base_t storage_;
        };

}}