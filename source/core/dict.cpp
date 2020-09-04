#include <friedrichdb/core/dict.hpp>
#include <friedrichdb/core/dict.ipp>

namespace friedrichdb { namespace core {

        dict_value::dict_value(bool i)
                : type_(type_t::INT), pi(new AutoBuffer<int64_t, 1>) {
            (*pi)[0] = i ? 1 : 0;
        }

        dict_value::dict_value(int64_t i)
                : type_(type_t::INT), pi(new AutoBuffer<int64_t, 1>) { (*pi)[0] = i; }

        dict_value::dict_value(int i)
                : type_(type_t::INT),
                  pi(new AutoBuffer<int64_t, 1>) { (*pi)[0] = i; }

        dict_value::dict_value(unsigned p)
                : type_(type_t::INT),
                  pi(new AutoBuffer<int64_t, 1>) { (*pi)[0] = p; }

        dict_value::dict_value(double p)
                : type_(type_t::REAL),
                  pd(new AutoBuffer<double, 1>) { (*pd)[0] = p; }

        dict_value::dict_value(const std::string &s)
                : type_(type_t::STRING),
                  ps(new AutoBuffer<std::string, 1>) { (*ps)[0] = s; }

        dict_value::dict_value(const char *s)
                : type_(type_t::STRING),
                  ps(new AutoBuffer<std::string, 1>) { (*ps)[0] = s; }

        int dict_value::getIntValue(int idx) const {
            return (int) get<int64_t>(idx);
        }

        double dict_value::getRealValue(int idx) const {
            return get<double>(idx);
        }

        std::string dict_value::getStringValue(int idx) const {
            return get<std::string>(idx);
        }

        void dict_value::release() {
            switch (type_) {
                case type_t::INT:
                    delete pi;
                    break;
                case type_t::STRING:
                    delete ps;
                    break;
                case type_t::REAL:
                    delete pd;
                    break;
                case type_t::BOOLEAN:
                case type_t::FLOAT:
                case type_t::UNSIGNED_INT:
                case type_t::UINT64:
                case type_t::UCHAR:
                case type_t::SCALAR:
                    break; // unhandled
            }
        }

        dict_value::~dict_value() {
            release();
        }

        dict_value &dict_value::operator=(const dict_value &r) {
            if (&r == this)
                return *this;

            if (r.type_ == type_t::INT) {
                auto *tmp = new AutoBuffer<int64_t, 1>(*r.pi);
                release();
                pi = tmp;
            } else if (r.type_ == type_t::STRING) {
                auto *tmp = new AutoBuffer<std::string, 1>(*r.ps);
                release();
                ps = tmp;
            } else if (r.type_ == type_t::REAL) {
                auto *tmp = new AutoBuffer<double, 1>(*r.pd);
                release();
                pd = tmp;
            }

            type_ = r.type_;

            return *this;
        }

        dict_value::dict_value(const dict_value &r) {
            type_ = r.type_;

            if (r.type_ == type_t::INT)
                pi = new AutoBuffer<int64_t, 1>(*r.pi);
            else if (r.type_ == type_t::STRING)
                ps = new AutoBuffer<std::string, 1>(*r.ps);
            else if (r.type_ == type_t::REAL)
                pd = new AutoBuffer<double, 1>(*r.pd);
        }

        bool dict_value::is_string() const {
            return (type_ == type_t::STRING);
        }

        bool dict_value::is_int() const {
            return (type_ == type_t::INT);
        }

        bool dict_value::is_real() const {
            return (type_ == type_t::REAL || type_ == type_t::INT);
        }

        int dict_value::size() const {
            switch (type_) {
                case type_t::INT:
                    return (int) pi->size();
                case type_t::STRING:
                    return (int) ps->size();
                case type_t::REAL:
                    return (int) pd->size();
                case type_t::BOOLEAN:
                case type_t::FLOAT:
                case type_t::UNSIGNED_INT:
                case type_t::UINT64:
                case type_t::UCHAR:
                case type_t::SCALAR:
                    break; // unhandled
            }
            throw std::runtime_error(std::string("Unhandled type_ ").append(std::to_string(static_cast<int>(type_))));
        }

        std::ostream &operator<<(std::ostream &stream, const dict_value &dictv) {
            int i;

            if (dictv.is_int()) {
                for (i = 0; i < dictv.size() - 1; i++)
                    stream << dictv.get<int64_t>(i) << ", ";
                stream << dictv.get<int64_t>(i);
            } else if (dictv.is_real()) {
                for (i = 0; i < dictv.size() - 1; i++)
                    stream << dictv.get<double>(i) << ", ";
                stream << dictv.get<double>(i);
            } else if (dictv.is_string()) {
                for (i = 0; i < dictv.size() - 1; i++)
                    stream << "\"" << dictv.get<std::string>(i) << "\", ";
                stream << dictv.get<std::string>(i);
            }

            return stream;
        }

        dict_value::dict_value(type_t _type, void *_p) : type_(_type), pv(_p) {}

        bool dict::has(const std::string &key) const {
            return dict_.count(key) != 0;
        }

        dict_value *dict::ptr(const std::string &key) {
            auto i = dict_.find(key);
            return (i == dict_.end()) ? nullptr : &i->second;
        }

        const dict_value *dict::ptr(const std::string &key) const {
            auto i = dict_.find(key);
            return (i == dict_.end()) ? nullptr : &i->second;
        }

        const dict_value &dict::get(const std::string &key) const {
            auto i = dict_.find(key);
            if (i == dict_.end()) {
                throw std::runtime_error(std::string("Required argument \"").append(key).append("\" not found into dictionary"));
            }
            return i->second;
        }

        void dict::erase(const std::string &key) {
            dict_.erase(key);
        }

        std::ostream &operator<<(std::ostream &stream, const dict &dict) {
            dict::const_iterator it;
            for (it = dict.begin(); it != dict.end(); it++)
                stream << it->first << " : " << it->second << "\n";

            return stream;
        }

        dict::const_iterator dict::begin() const {
            return dict_.begin();
        }

        dict::const_iterator dict::end() const {
            return dict_.end();
        }
    }
}