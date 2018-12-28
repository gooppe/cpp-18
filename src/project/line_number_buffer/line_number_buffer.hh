#ifndef LINE_NUMBER_BUFFER_H
#define LINE_NUMBER_BUFFER_H

#include <ios>
#include <string>
#include <sstream>

class LineNumberBuffer : public std::streambuf
{
  std::streambuf *old;
  int index = 0;
  bool print_index_flag = true;

  std::string get_prefix();
  void put_ind();

public:
  LineNumberBuffer(std::streambuf *buffer);

protected:
  int overflow(int c) override;
  std::streamsize xsputn(const char *s, std::streamsize n) override;
};

struct StreamBuffGuard
{
  std::ostream &stream_;
  std::streambuf *buff_;

  StreamBuffGuard(std::ostream &stream) : stream_(stream), buff_(stream.rdbuf()) {}

  ~StreamBuffGuard() { stream_.rdbuf(buff_); }

  StreamBuffGuard(const StreamBuffGuard &) = delete;
  StreamBuffGuard &operator=(const StreamBuffGuard &) = delete;
};

#endif