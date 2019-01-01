#ifndef CLIENT_HH
#define CLIENT_HH

#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <strings.h>

#define handle_error(msg)   \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

class Client
{
    int fd;

  public:
    Client(uint host = INADDR_LOOPBACK, uint port = 42742);
    ~Client();
    void disconnect();
    bool send_message(const char *buffer, ssize_t buffer_size);
    bool read_message(char *buffer, ssize_t buffer_size);
};

#endif