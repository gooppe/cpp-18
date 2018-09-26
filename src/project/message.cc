#include <ostream>
#include <stdexcept>

void message(std::ostream &stream, const char *str)
{
    while (*str)
    {
        if (*str == '%')
        {
            throw std::invalid_argument("not enought values for pattern");
        }
        stream << *str++;
    }
}

template <class T, class... Args>
void message(std::ostream &stream, const char *str, T &&arg, Args &&... args)
{
    while (*str)
    {
        if (*str == '%')
        {
            stream << arg;
            str++;
            message(stream, str, args...);
        }
        stream << *str++;
    }
}