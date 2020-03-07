#pragma once

#include <utility>
#include <memory>
#include <algorithm>

#include <boost/container/static_vector.hpp>

#include "friedrichdb/core/basic_field.hpp"
#include "friedrichdb/core/field.hpp"
#include "friedrichdb/core/schema.hpp"
#include "friedrichdb/core/join.hpp"

namespace friedrichdb { namespace core {

        template<
            template<typename P> class Allocator,
            template <typename P,class D> class UniquePtr
        >
        using basic_row_t = basic_vector_t<field_t<Allocator,UniquePtr>, Allocator>;

        template<
            template<typename P> class Allocator,
            template <typename P,class D> class UniquePtr
        >
        using basic_storage_base_t = basic_vector_t<basic_row_t<Allocator,UniquePtr>, Allocator>;


        template<
            template<typename A> class Allocator,
            template <typename P,class D> class UniquePtr
        >
        class collection final {
        public:
            using schema_t  = basic_schema_t<Allocator,UniquePtr>;
            using row_t = basic_row_t<Allocator,UniquePtr>;
            using storage_base_t = basic_storage_base_t<Allocator,UniquePtr>;

            template<
                template<typename A> class OtherAllocator,
                template <typename P,class D> class OtherUniquePtr
            >
            collection(const basic_schema_t<OtherAllocator,OtherUniquePtr>& current_schema)
                : schema_(current_schema.begin(), current_schema.end()) {}

            template<
                template<typename A> class OtherAllocator,
                template <typename P,class D> class OtherUniquePtr
            >
            void update(
                    const collection<OtherAllocator,OtherUniquePtr> &other,
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

                for(;;){

                }


            }


            row_t &row(std::size_t index) {
                return storage_.at(index);
            }

            const row_t &row(std::size_t index) const {
                return storage_.at(index);
            }

            const schema_t &schema() const { return schema_; }

            std::size_t size() const {
              return storage_.size();
            }

        private:
            schema_t schema_;
            storage_base_t storage_;
        };

}}