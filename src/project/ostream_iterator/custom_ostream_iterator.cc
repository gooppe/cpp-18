#include <project/ostream_iterator/custom_ostream_iterator.hh>

template <typename _T, typename _Tchar, typename _Traits>
ostream_iterator<_T, _Tchar, _Traits>::ostream_iterator(ostream_type &stream) : _stream(stream), _char(0), _n(1) {}
template <typename _T, typename _Tchar, typename _Traits>
ostream_iterator<_T, _Tchar, _Traits>::ostream_iterator(ostream_type &stream, const char_type *ch) : _stream(stream), _char(ch), _n(1) {}
template <typename _T, typename _Tchar, typename _Traits>
ostream_iterator<_T, _Tchar, _Traits>::ostream_iterator(ostream_type &stream, const size_t n) : _stream(stream), _char(0), _n(n) {}
template <typename _T, typename _Tchar, typename _Traits>
ostream_iterator<_T, _Tchar, _Traits>::ostream_iterator(ostream_type &stream, const char_type *ch, const size_t n) : _stream(stream), _char(ch), _n(n) {}
template <typename _T, typename _Tchar, typename _Traits>
ostream_iterator<_T, _Tchar, _Traits>::ostream_iterator(const ostream_iterator &iter) : _stream(iter._stream), _char(iter._char), _n(iter._n) {}

template <typename _T, typename _Tchar, typename _Traits>
ostream_iterator<_T, _Tchar, _Traits> &ostream_iterator<_T, _Tchar, _Traits>::operator=(const _T &value)
{
    if (++count % _n == 0)
    {
        _stream << value;
        if (_char)
            _stream << _char;
    }

    return *this;
}

template <typename _T, typename _Tchar, typename _Traits>
ostream_iterator<_T, _Tchar, _Traits> &ostream_iterator<_T, _Tchar, _Traits>::operator*()
{
    return *this;
}

template <typename _T, typename _Tchar, typename _Traits>
ostream_iterator<_T, _Tchar, _Traits> &ostream_iterator<_T, _Tchar, _Traits>::operator++()
{
    return *this;
}

template <typename _T, typename _Tchar, typename _Traits>
ostream_iterator<_T, _Tchar, _Traits> &ostream_iterator<_T, _Tchar, _Traits>::operator++(int)
{
    return *this;
}