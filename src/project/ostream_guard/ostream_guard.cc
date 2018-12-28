#include <project/ostream_guard/ostream_guard.hh>

ostream_guard::ostream_guard(std::ostream &stream) : stream_(stream)
{
    flags_ = stream.flags();
    fill_ = stream.fill();
    width_ = stream.width();
}

ostream_guard::~ostream_guard()
{
    stream_.flags(flags_);
    stream_.fill(fill_);
    stream_.width(width_);
}
