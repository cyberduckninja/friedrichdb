#include <stdexcept>
#include <fstream>
#include <zconf.h>
#include "friedrichdb/object_id.hpp"
#include <friedrichdb/error.hpp>
namespace friedrichdb {

        namespace implement {

            uint64_t urandom() {
                std::ifstream f;
                f.rdbuf()->pubsetbuf(0, 0);
                f.open("/dev/urandom");

                uint64_t ret;
                if (f.read(reinterpret_cast<char *>(&ret), sizeof(ret)))
                    return ret;
                else
                    throw std::runtime_error("cannot read a number from /dev/urandom");
            }

            uint64_t counter() {
                static std::atomic<uint64_t> x(urandom());
                static std::atomic<pid_t> pid(getpid());

                if (pid != getpid()) {
                    x = urandom();
                    pid = getpid();
                }
                return ++x;
            }

        }

        namespace {
            struct TzSetter {
                TzSetter() { ::tzset(); }
            };

            static TzSetter tz_setter;

            static const char DIGITS[] = "0123456789abcdef";

            unsigned char byteOfHexDigit(char c) {
                if (c >= '0' && c <= '9') {
                    return c - '0';
                }
                if (c >= 'a' && c <= 'f') {
                    return 10u + (c - 'a');
                }
                if (c >= 'A' && c <= 'F') {
                    return 10u + (c - 'A');
                }
                throw error("Invalid ObjectId: unknown character");
            }

            inline unsigned char byteOfHex(char msb, char lsb) {
                return byteOfHexDigit(msb) << 4 | byteOfHexDigit(lsb);
            }

            void puthex(std::ostream &out, unsigned char ch) {
                out << DIGITS[ch & 0x0F] << DIGITS[ch >> 4];
            }

        } // namespace

        object_id::object_id(const char *hex) {
            if (std::strlen(hex) != DataSize * 2) {
                throw error("Invalid object_t id: bad size");
            }
            for (size_t i = 0; i < DataSize; ++i) {
                data_[i] = byteOfHex(hex[2 * i], hex[2 * i + 1]);
            }
        }

        object_id::object_id(const std::string &hex) {
            if (hex.size() != DataSize * 2) {
                throw error("Invalid object_t id: bad size");
            }
            for (size_t i = 0; i < DataSize; ++i) {
                data_[i] = byteOfHex(hex[2 * i], hex[2 * i + 1]);
            }
        }

        object_id::object_id(uint32_t time, uint64_t counter)
                : time_(htonl(time)), counter_(counter) {
        }

        object_id object_id::generate() {
            return object_id(static_cast<uint32_t>(::time(0)), implement::counter());
        }

        object_id object_id::min_id_for_timestamp(time_t t) {
            return object_id(t, 0);
        }

        object_id object_id::max_id_for_timestamp(time_t t) {
            return object_id(t, std::numeric_limits<uint64_t>::max());
        }

        std::string object_id::to_string() const {
            std::string out(DataSize * 2, 0);
            for (size_t i = 0; i < DataSize; ++i) {
                unsigned char byte = static_cast<unsigned char>(data_[i]);
                out[2 * i] = DIGITS[byte >> 4];
                out[2 * i + 1] = DIGITS[byte & 0x0F];
            }
            return out;
        }

        time_t object_id::get_timestamp() const {
            return static_cast<time_t>(ntohl(time_));
        }

        std::ostream &operator<<(std::ostream &out, const object_id &id) {
            out << "object_id_t(\"";
            for (size_t i = 0; i != object_id::DataSize; ++i)
                puthex(out, id.data_[i]);
            return out << "\")";
        }
}