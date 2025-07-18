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
#include <atomic>

#define PORT 4242
#define MAX_CLIENTS 3
#define BUFFER_SIZE 1024
class Server {
public:
    void start();
    void handle_client(int client_socket);

    Server() = default;
    ~Server() = default;
    Server(const Server&) = delete;
    Server& operator=(const Server&) = delete;
private:
    std::atomic<int> active_clients{0};
};

#endif
