#include <ostream>

struct ostream_guard
{
    std::ostream &stream_;
    std::ios::fmtflags flags_;
    char fill_;
    std::streamsize width_;

    ostream_guard(std::ostream &stream) : stream_(stream)
    {
        flags_ = stream.flags();
        fill_ = stream.fill();
        width_ = stream.width();
    }

    ~ostream_guard()
    {
        stream_.flags(flags_);
        stream_.fill(fill_);
        stream_.width(width_);
    }

    ostream_guard(const ostream_guard &) = delete;
    ostream_guard &operator=(const ostream_guard &) = delete;
};