#pragma once

class meta_info final {
    std::size_t pid_;
};

class document final {
    value value_;
    meta_info  meta_info_;
};

class table  final {


private:
    unordered_map_shared<std::size_t,document> storage_;
};