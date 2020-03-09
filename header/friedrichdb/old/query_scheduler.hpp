#pragma once

#include <queue>
#include <unordered_map>

#include <friedrichdb/query.hpp>

namespace friedrichdb {

    struct dummy_analyzer final {
        using queue =  std::queue<query>;
    };

    template <typename Analyzer>
    struct query_scheduler final {
        using queue = typename Analyzer::queue;
        ~query_scheduler() = default;
        template<typename... Args>
        void emplace(Args&&... args){
            queue_.emplace(std::forward<Args>(args)...);

        }
    private:

        queue queue_;
        std::unordered_map<id_t, query> index;


    };



}