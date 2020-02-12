#pragma once

#include <utility>
#include <memory>

#include <boost/container/static_vector.hpp>

#include "field_base.hpp"

template< template<typename P> class Allocator >
struct field final {
    using string_t  = basic_string_t<char,std::char_traits,Allocator>;
    string_t  uuid;
    field_base base_;
};


template< template<typename P> class Allocator >
struct field_metadata final {
    using string_t  = basic_string_t<char,std::char_traits,Allocator>;
    string_t  name_;
    field_type type_;
};

template< template<typename P> class Allocator >
using basic_row_t = basic_vector_t<field<Allocator>,Allocator>;

template< template<typename P> class Allocator >
using basic_storage_base_t = basic_vector_t<basic_row_t<Allocator>,Allocator>;

template< template<typename P> class Allocator >
class basic_schema_t final {
public:
    using storage_t = basic_vector_t<field_metadata<Allocator>,Allocator>;
    using iterator = typename storage_t::iterator;
    using name_t  = basic_string_t<char,std::char_traits,Allocator>;
    using index_t  = basic_map_t<
            name_t,
            std::size_t,
            std::less<>,
            Allocator<std::pair<const name_t,std::size_t>>
    >;

    basic_schema_t() = default;


    template<class Iterator>
    basic_schema_t(Iterator begin,Iterator end) {
        for(;begin!=end;++begin){
            push(begin()->name_,begin()->type_);
        }
    }

    const field_type& field(std::size_t index) const {
        return storage_.at(index);
    }

    const field_type& field(const std::string& index) const {
        return storage_.at(index_.at(index));
    }

    void push(const std::string&name, field_type type   ) {
        storage_.emplace_back({name,type});
        index_.emplace(name,storage_.size());
    }

    auto begin() -> iterator {
        storage_.begin();
    }

    auto end() -> iterator {
        storage_.end();
    }

private:
    storage_t storage_;
    index_t index_;
};

template< template <typename A> class Allocator>
class table_view final {

};

class column_view final {

};

class  document_view final {

};

class record_view final {

};


template< template <typename A> class Allocator>
class collection final {
public:
    using schema_t  = basic_schema_t<Allocator>;
    using row_t = basic_row_t<Allocator>;
    using storage_base_t = basic_storage_base_t<Allocator>;

    template< template <typename A> class OtherAllocator>
    collection(basic_schema_t<OtherAllocator>& current_schema) : schema_(current_schema.begin(),current_schema.end()) {}

    row_t &row(std::size_t index) {
        return storage_.at(index);
    }

    const row_t &row(std::size_t index) const {
        return storage_.at(index);
    }

    template <template <typename T> class OtherAllocator>
    void  batch_write(table_view<OtherAllocator>){

    }

    template <template <typename T> class OtherAllocator>
    void  batch_read(table_view<OtherAllocator>){

    }

    const schema_t &schema() const { return schema_; }

    const field_base& field(std::size_t i) const { return schema_.field(i); }

    ///table_view Slice(int64_t offset, int64_t length) { }

    ///table_view Slice(int64_t offset) const { return Slice(offset, num_rows_); }

    int num_columns() const { return schema_.storage_.size(); }

    int64_t num_rows() const { return num_rows_; }

private:
    schema_t schema_;
    storage_base_t storage_;
    int64_t num_rows_;
};

using in_memory_collection = collection<std::allocator>;