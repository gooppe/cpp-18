#ifndef MESSAGE_H
#define MESSAGE_H

#include <ostream>
#include <stdexcept>

inline void message(std::ostream &stream, const char *str);

template <class T, class... Args>
void message(std::ostream &stream, const char *str, T &&arg, Args &&... args);

#endif