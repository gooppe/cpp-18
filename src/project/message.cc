#include <ostream>
#include <stdexcept>

inline void message(std::ostream &stream, const char *str)
{
    while (*str)
    {
        if (*str == '%')
        {
            if (*(str + 1) == '%')
            {
                str++;
            }
            else
            {
                throw std::invalid_argument("not enought values for pattern");
            }
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
            if (*(str + 1) == '%')
            {
                str++;
            }
            else
            {
                stream << arg;
                str++;
                message(stream, str, args...);
                return;
            }
        }
        stream << *str++;
    }
}