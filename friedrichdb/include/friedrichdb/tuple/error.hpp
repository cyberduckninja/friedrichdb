#ifndef ERROR_HPP
#define ERROR_HPP

#include <string>

namespace friedrichdb{
    namespace tuple{

        struct Error : public std::runtime_error {
            Error(const std::string& what):std::runtime_error(what){

            }
        };
    }
}
#endif
