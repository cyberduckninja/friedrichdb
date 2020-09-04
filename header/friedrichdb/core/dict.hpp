#include <map>
#include <ostream>

#pragma once

namespace friedrichdb { namespace core {

        enum struct type_t {
            INT = 0, BOOLEAN = 1, REAL = 2, STRING = 3, FLOAT = 7,
            UNSIGNED_INT = 8, UINT64 = 9, UCHAR = 11, SCALAR = 12
        };


        template<typename Tp, size_t fixed_size = 1024 / sizeof(Tp) + 8>
        class AutoBuffer {
        public:
            typedef Tp value_type;

            AutoBuffer();

            explicit AutoBuffer(size_t _size);

            AutoBuffer(const AutoBuffer<Tp, fixed_size> &buf);

            AutoBuffer<Tp, fixed_size> &operator=(const AutoBuffer<Tp, fixed_size> &buf);

            ~AutoBuffer();

            void allocate(size_t _size);

            void deallocate();

            void resize(size_t _size);

            size_t size() const;

             Tp *data() { return ptr; }

             const Tp *data() const { return ptr; }

#if !defined(OPENCV_DISABLE_DEPRECATED_COMPATIBILITY) // use to .data() calls instead

            operator Tp *() { return ptr; }

            operator const Tp *() const { return ptr; }

#else
     _Tp& operator[] (size_t i) { CV_DbgCheckLT(i, sz, "out of range"); return ptr[i]; }

     const _Tp& operator[] (size_t i) const { CV_DbgCheckLT(i, sz, "out of range"); return ptr[i]; }
#endif

        protected:
            Tp *ptr;
            size_t sz;
            Tp buf[(fixed_size > 0) ? fixed_size : 1];
        };

        template<typename _Tp, size_t fixed_size>
        AutoBuffer<_Tp, fixed_size>::AutoBuffer() {
            ptr = buf;
            sz = fixed_size;
        }

        template<typename _Tp, size_t fixed_size>
        AutoBuffer<_Tp, fixed_size>::AutoBuffer(size_t _size) {
            ptr = buf;
            sz = fixed_size;
            allocate(_size);
        }

        template<typename _Tp, size_t fixed_size>
        AutoBuffer<_Tp, fixed_size>::AutoBuffer(const AutoBuffer<_Tp, fixed_size> &abuf) {
            ptr = buf;
            sz = fixed_size;
            allocate(abuf.size());
            for (size_t i = 0; i < sz; i++)
                ptr[i] = abuf.ptr[i];
        }

        template<typename _Tp, size_t fixed_size>
         AutoBuffer<_Tp, fixed_size> & AutoBuffer<_Tp, fixed_size>::operator=(const AutoBuffer<_Tp, fixed_size> &abuf) {
            if (this != &abuf) {
                deallocate();
                allocate(abuf.size());
                for (size_t i = 0; i < sz; i++)
                    ptr[i] = abuf.ptr[i];
            }
            return *this;
        }

        template<typename _Tp, size_t fixed_size>
        AutoBuffer<_Tp, fixed_size>::~AutoBuffer() { deallocate(); }

        template<typename _Tp, size_t fixed_size>
         void AutoBuffer<_Tp, fixed_size>::allocate(size_t _size) {
            if (_size <= sz) {
                sz = _size;
                return;
            }
            deallocate();
            if (_size > fixed_size) {
                ptr = new _Tp[_size];
                sz = _size;
            }
        }

        template<typename _Tp, size_t fixed_size>
         void AutoBuffer<_Tp, fixed_size>::deallocate() {
            if (ptr != buf) {
                delete[] ptr;
                ptr = buf;
                sz = fixed_size;
            }
        }

        template<typename _Tp, size_t fixed_size>
         void AutoBuffer<_Tp, fixed_size>::resize(size_t _size) {
            if (_size <= sz) {
                sz = _size;
                return;
            }
            size_t i, prevsize = sz, minsize = std::min(prevsize, _size);
            _Tp *prevptr = ptr;

            ptr = _size > fixed_size ? new _Tp[_size] : buf;
            sz = _size;

            if (ptr != prevptr)
                for (i = 0; i < minsize; i++)
                    ptr[i] = prevptr[i];
            for (i = prevsize; i < _size; i++)
                ptr[i] = _Tp();

            if (prevptr != buf)
                delete[] prevptr;
        }

        template<typename _Tp, size_t fixed_size>
         size_t AutoBuffer<_Tp, fixed_size>::size() const { return sz; }


        class dict_value final {
        public:

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

            std::string getStringValue(int idx = -1) const;

            dict_value &operator=(const dict_value &r);

            friend std::ostream &operator<<(std::ostream &stream, const dict_value &dictv);

            ~dict_value();

        private:

            type_t type_;

            union {
                AutoBuffer<int64_t, 1> *pi;
                AutoBuffer<double, 1> *pd;
                AutoBuffer<std::string, 1> *ps;
                void *pv;
            };

            dict_value(type_t _type, void *_p);

            void release();
        };


        class dict final {
            using dict_t = std::map<std::string, dict_value>;
            using const_iterator = dict_t::const_iterator;
            dict_t dict_;

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
        };

}}