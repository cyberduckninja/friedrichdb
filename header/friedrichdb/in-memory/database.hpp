#pragma once

#include <algorithm>
#include <list>
#include <map>
#include <memory>
#include <iostream>
#include <unordered_map>

#include <boost/interprocess/smart_ptr/unique_ptr.hpp>

#include <friedrichdb/core/basic_field.hpp>
#include <friedrichdb/core/collection.hpp>
#include <friedrichdb/core/options.hpp>


namespace friedrichdb { namespace in_memory {

template<class T, class D = boost::movelib::default_delete<T> >
using unique_ptr_t =  boost::interprocess::unique_ptr<T, D>;

using collection = core::collection<std::allocator,unique_ptr_t>;

using empty_schema_t = core::empty_basic_schema_t<std::allocator,unique_ptr_t>;

struct view_collection final {
  view_collection(collection *ptr) : ptr_(ptr) {}

private:
  collection *ptr_;
};

class database final {
public:
  database(const core::database_constructor_options &options) {}
  database() = delete;
  database(const database &) = delete;

  auto remove(const core::collection_remove_options &options) -> bool {
    auto it = name_to_idx_.find(options.name_);
    if (it == name_to_idx_.end()) {
      return false;
    } else {
      auto result = storage_.begin();
      std::advance(result, it->second);
      storage_.erase(result);
      name_to_idx_.erase(it);
      return true;
    }
  }

  template <typename... Args>
  auto create(const core::collection_constructor_options &options, Args... args) -> view_collection {
    storage_.emplace_back(new collection(std::forward<Args>(args)...));
    auto result = name_to_idx_.emplace(options.name_, storage_.size()-1);
    auto it = storage_.begin();
    std::advance(it, result.first->second);
    return it->get();
  }

  auto create(const core::collection_constructor_options &options) -> view_collection {
    storage_.emplace_back(new collection(empty_schema_t()));
    auto result = name_to_idx_.emplace(options.name_, storage_.size()-1);
    auto it = storage_.begin();
    std::advance(it, result.first->second);
    return it->get();
  }

  auto find(const core::collection_find_options &options) -> view_collection {

    auto it = name_to_idx_.find(options.name_);

    if (it == name_to_idx_.end()) {
      std::cerr << "not collection" << std::endl;
      return nullptr;
    } else {
      auto result = storage_.begin();
      std::advance(result, it->second);
      return result->get();
    }
  }

  auto all_names() const -> std::set<std::string> {
    std::set<std::string> tmp;

    for (const auto &i : name_to_idx_) {
      tmp.emplace(i.first);
    }

    return tmp;
  }

  auto size() const -> std::size_t { return storage_.size(); }

private:
  std::list<std::unique_ptr<collection>> storage_;
  std::map<std::string, std::size_t> name_to_idx_;
};

}}
