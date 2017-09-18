#ifndef TIME_HPP
#define TIME_HPP

#include "friedrichdb/tuple/ordering.h"
#include <sys/time.h>
namespace friedrichdb{
namespace tuple {
    class time: public implement::ordered<time> {
    public:
        explicit time(time_t t);
        explicit time(const struct timeval& tv);

        int64_t milliseconds() const { return milli_; }

    private:
        int64_t milli_;

        friend class implement::ordered_base;
        template<template<class> class Cmp>
        static bool cmp(const time& a, const time& b) { return Cmp<int64_t>()(a.milliseconds(), b.milliseconds()); }
    };

    std::ostream& operator << (std::ostream& out, const time& t);
}}
#endif
