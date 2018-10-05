#include <ostream>
#include <string>
#include <iterator>

template <typename _T, typename _Tchar = char, typename _Traits = std::char_traits<_Tchar>>
class ostream_iterator : public std::iterator<std::output_iterator_tag, void, void, void, void>
{
  public:
    typedef _Tchar char_type;
    typedef _Traits traits_type;
    typedef std::basic_ostream<_Tchar, _Traits> ostream_type;

  private:
    ostream_type &_stream;
    const char_type *_char;
    size_t _n = 0;
    size_t count = 0;

  public:
    ostream_iterator(ostream_type &stream) : _stream(stream), _char(0), _n(1) {}
    ostream_iterator(ostream_type &stream, const char_type *ch) : _stream(stream), _char(ch), _n(1) {}
    ostream_iterator(ostream_type &stream, const size_t n) : _stream(stream), _char(0), _n(n) {}
    ostream_iterator(ostream_type &stream, const char_type *ch, const size_t n) : _stream(stream), _char(ch), _n(n) {}
    ostream_iterator(const ostream_iterator &iter) : _stream(iter._stream), _char(iter._char), _n(iter._n) {}

    ostream_iterator &operator=(const _T &value)
    {
        if (++count % _n == 0)
        {
            _stream << value;
            if (_char)
                _stream << _char;
        }

        return *this;
    }

    ostream_iterator &operator*()
    {
        return *this;
    }

    ostream_iterator &operator++()
    {
        return *this;
    }

    ostream_iterator &operator++(int)
    {
        return *this;
    }
};