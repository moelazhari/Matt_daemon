#ifndef SERVER_HPP
#define SERVER_HPP

#include "Tintin_reporter.hpp"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include <cstring>

#define PORT 4242
#define MAX_CLIENTS 3
#define BUFFER_SIZE 1024
class Server {
public:
    void start();
};

#endif
