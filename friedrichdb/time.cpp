#include "friedrichdb/time.hpp"
#include <ostream>
#include <time.h>
namespace friedrichdb {

        time::time(time_t t) : milli_(t * 1000) {}

        time::time(const struct timeval &tv) : milli_(tv.tv_sec * 1000 + tv.tv_usec / 1000) {}

        std::ostream &operator<<(std::ostream &out, const time &t) {
                int tz = abs(::timezone);
                char buf[64];
                struct tm tm;
                time_t time = t.milliseconds() / 1000;
                strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime_r(&time, &tm));
                char *p = buf + strlen(buf);
                snprintf(p, buf + sizeof(buf) - p, ".%03d %c%02d%02d",
                         (int) (t.milliseconds() % 1000),
                         (::timezone <= 0) ? '+' : '-',
                         tz / 3600, (tz % 3600) / 60
                );
                return out << buf;
        }
}