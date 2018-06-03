#pragma once


#include <cstdint>

enum class ff:uint8_t {
    created,
    insert,
    update,
///    delete
};


class query {

private:

    ff method;

};

class query_result;

