#pragma once

#include <queue>
#include <unordered_map>

#include <friedrichdb/transaction.hpp>


namespace friedrichdb {

    template <typename Analyzer>
    struct query_pool final {
        ~query_pool() = default;
        template<typename... Args>
        void emplace(Args&&... args){
            queue_.emplace(std::forward<Args>(args)...);

        }
    private:
        std::queue<query> queue_;
        std::unordered_map<id_t, query> index;


    };



}