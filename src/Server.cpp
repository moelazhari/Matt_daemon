#include "Server.hpp"


void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    while (true) {
        ssize_t bytes = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes <= 0) break;
        buffer[bytes] = '\0';

        std::string msg = buffer;
        if (msg == "quit\n" || msg == "quit\r\n") {
            Tintin_reporter::getInstance().log("INFO", "Matt_daemon: Request quit");
            Tintin_reporter::getInstance().log("INFO", "Quitting");
            exit(0);
        }

        Tintin_reporter::getInstance().log("LOG", "User input: " + (msg[bytes - 1] == '\n' ? msg.substr(0, bytes - 1) : msg));
    }
    close(client_socket);
}

void Server::start() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        Tintin_reporter::getInstance().log("ERROR", "Socket creation failed.");
        return;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, MAX_CLIENTS);

    Tintin_reporter::getInstance().log("INFO", "Matt_daemon: Server created.");
    Tintin_reporter::getInstance().log("INFO", "Matt_daemon: Entering Daemon mode.");
    Tintin_reporter::getInstance().log("INFO", "Matt_daemon: Starting PID: " + std::to_string(getpid()) + ".");

    std::vector<std::thread> clients;

    while (true) {
        int client_socket = accept(server_fd, nullptr, nullptr);
        if (client_socket < 0) continue;

        if (clients.size() >= MAX_CLIENTS) {
            close(client_socket);
            continue;
        }

        clients.emplace_back(handle_client, client_socket);
        clients.back().detach();
    }

    close(server_fd);
}
