#pragma once

#include <boost/container/stable_vector.hpp>
#include <vector>
#include "field_base.hpp"

enum class table_type {
    row = 0x00,
    document,
    tensor
};


struct field final {
    boost::interprocess::string name_;
    field_base base_;
};

using row_t = boost::interprocess::vector<field>;
using storage_base_t = boost::container::stable_vector<boost::interprocess::vector<row_t>>;


struct schema_t final {
    table_type table_type_;
    boost::interprocess::vector<field_type> storage_;
};

/// base storage in memory / shm / gpu
class table final {
public:
    using iterator = storage_base_t::iterator;

    table(const schema_t &current_schema) : schema_(current_schema) {}

    row_t &row(std::size_t index) {

    }

    auto begin() -> iterator {

    }

    auto end() -> iterator {

    }

    const schema_t &schema() const { return schema_; }

    /// \brief Return a column by index
    virtual std::shared_ptr<ChunkedArray> column(int i) const = 0;

    /// \brief Return vector of all columns for table
    std::vector<std::shared_ptr<ChunkedArray>> columns() const;

    /// Return a column's field by index
    std::shared_ptr<Field> field(int i) const { return schema_->field(i); }

    /// \brief Return vector of all fields for table
    std::vector<std::shared_ptr<Field>> fields() const;


    std::shared_ptr<Table> Slice(int64_t offset, int64_t length) const = 0;

    std::shared_ptr<Table> Slice(int64_t offset) const { return Slice(offset, num_rows_); }


    std::shared_ptr<ChunkedArray> GetColumnByName(const std::string &name) const {
        auto i = schema_->GetFieldIndex(name);
        return i == -1 ? NULLPTR : column(i);
    }


    Status RemoveColumn(int i, std::shared_ptr<Table> *out) const = 0;


    Status AddColumn(int i, std::shared_ptr<Field> field_arg,
                     std::shared_ptr<ChunkedArray> column,
                     std::shared_ptr<Table> *out) const = 0;


    Status SetColumn(int i, std::shared_ptr<Field> field_arg,
                     std::shared_ptr<ChunkedArray> column,
                     std::shared_ptr<Table> *out) const = 0;


    std::vector<std::string> ColumnNames() const;


    Status Validate() const = 0;

    Status ValidateFull() const = 0;

    int num_columns() const { return schema_.storage_.size(); }

    int64_t num_rows() const { return num_rows_; }

private:
    schema_t schema_;
    storage_base_t storage_;
    int64_t num_rows_
};