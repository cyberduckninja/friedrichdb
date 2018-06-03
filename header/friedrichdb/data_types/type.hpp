#pragma once

#include <cstdint>
#include <cstdint>
#include <memory>
#include <unordered_map>

namespace friedrichdb {

    struct null {};

    using uint8  = uint8_t ;
    using uint16 = uint16_t;
    using uint32 = uint32_t;
    using uint64 = uint64_t;

    using int8  = int8_t ;
    using Int16 = int16_t;
    using Int32 = int32_t;
    using Int64 = int64_t;

    using float32 = float;
    using float64 = double;

    using string = std::string;
/*
    template <typename T> bool is_number = false;
    template <>  bool is_number<uint8>   = true;
    template <>  bool is_number<uint16>  = true;
    template <>  bool is_number<uint32>  = true;
    template <>  bool is_number<uint64>  = true;
    template <>  bool is_number<int8>    = true;
    template <>  bool is_number<Int16>   = true;
    template <>  bool is_number<Int32>   = true;
    template <>  bool is_number<Int64>   = true;
    template <>  bool is_number<float32> = true;
    template <>  bool is_number<float64> = true;
*/
    template <typename T> struct type_name;

    template <> struct type_name<uint8>   { static const char * get() { return "uint8";   } };
    template <> struct type_name<uint16>  { static const char * get() { return "uint16";  } };
    template <> struct type_name<uint32>  { static const char * get() { return "uint32";  } };
    template <> struct type_name<uint64>  { static const char * get() { return "uint64";  } };
    template <> struct type_name<int8>    { static const char * get() { return "int8";    } };
    template <> struct type_name<Int16>   { static const char * get() { return "Int16";   } };
    template <> struct type_name<Int32>   { static const char * get() { return "Int32";   } };
    template <> struct type_name<Int64>   { static const char * get() { return "Int64";   } };
    template <> struct type_name<float32> { static const char * get() { return "float32"; } };
    template <> struct type_name<float64> { static const char * get() { return "float64"; } };
    template <> struct type_name<string>  { static const char * get() { return "string";  } };

}
