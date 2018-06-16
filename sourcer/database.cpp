
#include <friedrichdb/database.hpp>
#include <string>

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
        //journal_.push(query_);
        auto outpyt_ = file->apply(std::move(query_));
        //journal_.push(query_);
        //auto outpyt_ =  memory->apply(query_);
        //journal_.push(query_);
        return outpyt_;
    }



}