#pragma once

#include <cmath>
#include <cassert>
#include "dict.hpp"

namespace friedrichdb {
    namespace core {

        template<typename TypeIter>
        dict_value dict_value::array_int(TypeIter begin, int size) {
            dict_value res(type_t::INT, new boost::container::small_vector<int64_t, 1>(size));
            for (int j = 0; j < size; begin++, j++) {
                (*res.pi)[j] = *begin;
            }
            return res;
        }

        template<typename TypeIter>
        dict_value dict_value::array_real(TypeIter begin, int size) {
            dict_value res(type_t::REAL, new boost::container::small_vector<double, 1>(size));
            for (int j = 0; j < size; begin++, j++) {
                (*res.pd)[j] = *begin;
            }
            return res;
        }

        template<typename TypeIter>
        dict_value dict_value::array_string(TypeIter begin, int size) {
            dict_value res(type_t::STRING, new boost::container::small_vector<std::string, 1>(size));
            for (int j = 0; j < size; begin++, j++) {
                (*res.ps)[j] = *begin;
            }
            return res;
        }

        template<>
        dict_value dict_value::get<dict_value>(int idx) const {
            assert(idx == -1);
            return *this;
        }

        template<>
        int64_t dict_value::get<int64_t>(int idx) const {
            assert((idx == -1 && size() == 1) || (idx >= 0 && idx < size()));
            idx = (idx == -1) ? 0 : idx;

            if (type_ == type_t::INT) {
                return (*pi)[idx];
            } else if (type_ == type_t::REAL) {
                double doubleValue = (*pd)[idx];
                double fracpart, intpart;
                fracpart = std::modf(doubleValue, &intpart);
                assert(fracpart == 0.0);
                return (int64_t) doubleValue;
            } else if (type_ == type_t::STRING) {
                return std::atoi((*ps)[idx].c_str());
            } else {
                assert(is_int() || is_real() || is_string());
                return 0;
            }
        }

        template<>
        int dict_value::get<int>(int idx) const {
            return (int) get < int64_t > (idx);
        }


        template<>
        unsigned dict_value::get<unsigned>(int idx) const {
            return (unsigned) get < int64_t > (idx);
        }

        template<>
        bool dict_value::get<bool>(int idx) const {
            return (get < int64_t > (idx) != 0);
        }

        template<>
        double dict_value::get<double>(int idx) const {
            assert((idx == -1 && size() == 1) || (idx >= 0 && idx < size()));
            idx = (idx == -1) ? 0 : idx;

            if (type_ == type_t::REAL) {
                return (*pd)[idx];
            } else if (type_ == type_t::INT) {
                return (double) (*pi)[idx];
            } else if (type_ == type_t::STRING) {
                return std::atof((*ps)[idx].c_str());
            } else {
                assert(is_real() || is_int() || is_string());
                return 0;
            }
        }


        template<>
        float dict_value::get<float>(int idx) const {
            return (float) get < double > (idx);
        }

        template<>
        std::string dict_value::get<std::string>(int idx) const {
            assert(is_string());
            assert((idx == -1 && ps->size() == 1) || (idx >= 0 && idx < (int) ps->size()));
            return (*ps)[(idx == -1) ? 0 : idx];
        }


        template<typename T>
        T dict::get(const std::string &key) const {
            return this->get(key).get<T>();
        }

        template<typename T>
        T dict::get(const std::string &key, const T &defaultValue) const {
            auto i = dict_.find(key);

            if (i != dict_.end())
                return i->second.get<T>();
            else
                return defaultValue;
        }

        template<typename T>
        const T &dict::set(const std::string &key, const T &value) {
            auto i = dict_.find(key);

            if (i != dict_.end())
                i->second = dict_value(value);
            else
                dict_.insert(std::make_pair(key, dict_value(value)));

            return value;
        }
}}