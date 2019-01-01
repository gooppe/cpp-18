#ifndef SERVER_HH
#define SERVER_HH

#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <strings.h>
#include <vector>
#include <sys/epoll.h>

#define MAX_EVENTS 10

#define handle_error(msg) \
  do                      \
  {                       \
    perror(msg);          \
    exit(EXIT_FAILURE);   \
  } while (0)

class EchoServer
{
  int conn_fd;

public:
  ~EchoServer();
  void run(uint host = INADDR_LOOPBACK, uint port = 42742);
};

class NonBlockingEchoServer
{
  int conn_fd;

public:
  ~NonBlockingEchoServer();
  void run(uint host = INADDR_LOOPBACK, uint port = 42742);
};

bool echo(int client_fd);
bool send(int trg_fd, const char *buffer, ssize_t buffer_size);
bool receive(int trg_fd, char *buffer, ssize_t buffer_size);

#endif