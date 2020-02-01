#pragma once

#include <memory>
#include ""


using array_vector = std::vector<std::unique_ptr<Array>>;

class chunked_vector final {
    array_vector chunks_;
    int64_t length_;
    int64_t null_count_;
    std::unique_ptr<DataType> type_;
};

class table final  {

};