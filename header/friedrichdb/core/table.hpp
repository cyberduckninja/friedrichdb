#pragma once

#include <utility>
#include <memory>

#include <boost/container/static_vector.hpp>

#include "field_base.hpp"

struct field final {
    boost::interprocess::string  uuid;
    field_base base_;
};

using row_t = boost::interprocess::vector<field>;
using storage_base_t = boost::interprocess::vector<row_t>;

class schema_t final {
public:
    using storage_t = boost::interprocess::vector<field_type>;
    using iterator =  typename  storage_t::iterator;

    const field_type& field(std::size_t index) const {
        return storage_.at(index);
    }

    const field_type& field(const std::string& index) const {
        return storage_.at(index_.at(index));
    }

    void push(const std::string&name, field_type type   ) {
        storage_.emplace_back(type);
        index_.emplace(name,storage_.size());
    }

private:
    boost::interprocess::vector<field_type> storage_;
    boost::container::map<std::string,std::size_t> index_;
};

class table_view final {

};

class column_view final {

};

class  document_view final {

};

class record_view final {

};


template<class Allocator>
class collection {
public:
    using iterator = storage_base_t::iterator;

    collection(Allocator&allocator_t, schema_t current_schema) : schema_(std::move(current_schema)) {}

    row_t &row(std::size_t index) {
        return storage_.at(index);
    }

    const row_t &row(std::size_t index) const {
        return storage_.at(index);
    }

    const schema_t &schema() const { return schema_; }

    const field_base& field(std::size_t i) const { return schema_.field(i); }

    table_view Slice(int64_t offset, int64_t length) { }

    table_view Slice(int64_t offset) const { return Slice(offset, num_rows_); }

    int num_columns() const { return schema_.storage_.size(); }

    int64_t num_rows() const { return num_rows_; }

private:
    schema_t schema_;
    Allocator& allocator_;
    storage_base_t storage_;
    int64_t num_rows_{};
};