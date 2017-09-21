#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>

namespace friedrichdb{
        struct error final : public std::runtime_error {
            error(const std::string& what):std::runtime_error(what){

            }
        };
}
#endif
