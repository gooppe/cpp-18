#ifndef CUSTOM_OSTREAM_ITERATOR_HH
#define CUSTOM_OSTREAM_ITERATOR_HH

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
    ostream_iterator(ostream_type &stream);
    ostream_iterator(ostream_type &stream, const char_type *ch);
    ostream_iterator(ostream_type &stream, const size_t n);
    ostream_iterator(ostream_type &stream, const char_type *ch, const size_t n);
    ostream_iterator(const ostream_iterator &iter);
    ostream_iterator &operator=(const _T &value);
    ostream_iterator &operator*();
    ostream_iterator &operator++();
    ostream_iterator &operator++(int);
};

#endif