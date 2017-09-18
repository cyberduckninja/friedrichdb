#ifndef TIMETAMP_HPP
#define TIMETAMP_HPP

#include "ordering.h"
namespace friedrichdb{
namespace tuple {
    class timestamp : public implement::ordered<timestamp> {
    public:
        timestamp() { ts_ = 0; }

        timestamp(uint32_t a, uint32_t b) {
            first_ = a;
            second_ = b;
        }

        uint32_t first() const { return first_; }

        uint32_t second() const { return second_; }

    private:
        union {
            struct {
                uint32_t second_;
                uint32_t first_;
            } __attribute__((packed));
            uint64_t ts_;
        };

        friend class implement::ordered_base;

        template<template<class> class Cmp>
        static bool cmp(const timestamp &a, const timestamp &b) { return Cmp<uint64_t>()(a.ts_, b.ts_); }
    };

    std::ostream &operator<<(std::ostream &out, const timestamp &);
}}
#endif