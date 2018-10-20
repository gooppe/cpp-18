#include "line_number_buffer.hh"

LineNumberBuffer::LineNumberBuffer(std::streambuf *buffer) : old(buffer) {}

void LineNumberBuffer::put_ind()
{
    std::string line_prefix = std::to_string(index) + " ";
    old->sputn(line_prefix.data(), line_prefix.length());
}

int LineNumberBuffer::overflow(int c)
{
    if (print_index_flag)
    {
        index++;
        put_ind();
    }

    print_index_flag = c == '\n';

    return old->sputc(c);
}

std::streamsize LineNumberBuffer::xsputn(const char *s, std::streamsize n)
{
    std::string str = std::string(s, n);
    std::istringstream str_stream = std::istringstream(str);
    std::string token;
    std::string str_numerated;

    while (std::getline(str_stream, token))
    {
        str_numerated += std::to_string(++index) + " " + token + "\n";
    }

    print_index_flag = *(str_numerated.end() - 1) == '\n';

    return old->sputn(str_numerated.data(), str_numerated.length());
}
