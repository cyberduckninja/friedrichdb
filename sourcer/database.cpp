
#include <friedrichdb/database.hpp>
#include <string>
#include <friedrichdb/query.hpp>

namespace friedrichdb {

    database::database(
            const std::string &name,
            abstract_database *memory_,
            abstract_database *file_
    ) :
        abstract_database(name, storge_t::instance),
        journal_(new dummy_journal) {
        assert(memory_->type() == storge_t::memory);
        assert(file_->type() == storge_t::disk);
        memory.reset(memory_);
        file.reset(file_);
    }

    auto database::apply(query&& query_) -> output_query {
        auto outpyt_ = memory->apply(std::move(query_));
        return outpyt_;
    }



}