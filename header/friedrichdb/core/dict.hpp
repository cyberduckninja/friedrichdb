#pragma once

#include "type.hpp"

#include <boost/container/small_vector.hpp>

namespace friedrichdb { namespace core {

        enum struct type_t {
            INT = 0,
            BOOLEAN = 1,
            REAL = 2,
            STRING = 3,
            FLOAT = 7,
            UNSIGNED_INT = 8,
            UINT64 = 9,
            UCHAR = 11,
            SCALAR = 12
        };

        class dict_value final {
        public:

            using string = basic_string_t<char>;

            dict_value(const dict_value &r);

            dict_value(bool i);

            dict_value(int64_t i = 0);

            dict_value(int i) ;

            dict_value(unsigned p) ;

            dict_value(double p);

            dict_value(const std::string &s);

            dict_value(const char *s);

            template<typename TypeIter>
            static dict_value array_int(TypeIter begin, int size);

            template<typename TypeIter>
            static dict_value array_real(TypeIter begin, int size);

            template<typename TypeIter>
            static dict_value array_string(TypeIter begin, int size);

            template<typename T>
            T get(int idx = -1) const;

            int size() const;

            bool is_int() const;

            bool is_string() const;

            bool is_real() const;

            int getIntValue(int idx = -1) const;

            double getRealValue(int idx = -1) const;

            std::string get_string_value(int idx = -1) const;

            dict_value &operator=(const dict_value &r);

            friend std::ostream &operator<<(std::ostream &stream, const dict_value &dictv);

            ~dict_value();

        private:

            type_t type_;

            union {
                basic_vector_t<int64_t> *pi;
                basic_vector_t<double> *pd;
                basic_vector_t<string> *ps;
                void *pv;
            };

            dict_value(type_t _type, void *_p);

            void release();
        };


        class dict final {
            using string = basic_string_t<char>;
            using dict_t = basic_unordered_map_t<string, dict_value>;
            using const_iterator = dict_t::const_iterator;

        public:

            bool has(const std::string &key) const;

            dict_value *ptr(const std::string &key);

            const dict_value *ptr(const std::string &key) const;

            const dict_value &get(const std::string &key) const;

            template<typename T>
            T get(const std::string &key) const;

            template<typename T>
            T get(const std::string &key, const T &defaultValue) const;

            template<typename T>
            const T &set(const std::string &key, const T &value);

            void erase(const std::string &key);

            friend std::ostream &operator<<(std::ostream &stream, const dict &dict);

            const_iterator begin() const;

            const_iterator end() const;

        private:
            dict_t dict_;
        };

}}