#pragma once

#include <functional>

namespace friedrichdb {
    namespace tuple {
        namespace implement {

            struct ordered_base {
                template<template<class> class Cmp, class T>
                static bool cmp(const T &a, const T &b) {
                    return T::template cmp<Cmp>(a, b);
                }
            };

            template<class T>
            struct ordered {
                friend bool operator==(const T &lhs, const T &rhs) {
                    return ordered_base::cmp<std::equal_to>(lhs, rhs);
                }

                friend bool operator!=(const T &lhs, const T &rhs) {
                    return ordered_base::cmp<std::not_equal_to>(lhs, rhs);
                }

                friend bool operator<(const T &lhs, const T &rhs) { return ordered_base::cmp<std::less>(lhs, rhs); }

                friend bool operator<=(const T &lhs, const T &rhs) {
                    return ordered_base::cmp<std::less_equal>(lhs, rhs);
                }

                friend bool operator>(const T &lhs, const T &rhs) { return ordered_base::cmp<std::greater>(lhs, rhs); }

                friend bool operator>=(const T &lhs, const T &rhs) {
                    return ordered_base::cmp<std::greater_equal>(lhs, rhs);
                }
            };

            template<class T>
            struct equal {
                friend bool operator==(const T &, const T &) { return true; }

                friend bool operator!=(const T &, const T &) { return false; }

                friend bool operator<(const T &, const T &) { return false; }

                friend bool operator<=(const T &, const T &) { return true; }

                friend bool operator>(const T &, const T &) { return false; }

                friend bool operator>=(const T &, const T &) { return true; }
            };
        }
    }
}
