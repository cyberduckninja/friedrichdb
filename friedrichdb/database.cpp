#include "include/friedrichdb/database.hpp"
namespace friedrichdb {
    response database::find(where f) const {
        return memory->find(f);
    }

    bool database::update(where_generator f) {
        file->update(f);
        return memory->update(f);
    }

    bool database::erase(where f) {
        file->erase(f);
        return memory->erase(f);
    }

    bool database::insert(generator f) {
        file->insert(f);
        return memory->insert(f);
    }
}
