#ifndef OSTREAM_GUARD_HH
#define OSTREAM_GUARD_HH

#include <ostream>

struct ostream_guard
{
    std::ostream &stream_;
    std::ios::fmtflags flags_;
    char fill_;
    std::streamsize width_;

    ostream_guard(std::ostream &stream);

    ~ostream_guard();

    ostream_guard(const ostream_guard &) = delete;
    ostream_guard &operator=(const ostream_guard &) = delete;
};

#endif