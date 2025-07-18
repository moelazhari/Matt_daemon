#include "Tintin_reporter.hpp"


Tintin_reporter::Tintin_reporter() {
    mkdir(LOG_PATH, 0755);
    openLogFile();
}

Tintin_reporter::~Tintin_reporter() {
    closeLogFile();
}

void Tintin_reporter::openLogFile() {
    log_fd = open(LOG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0777);
}

void Tintin_reporter::closeLogFile() {
    if (log_fd != -1) close(log_fd);
}

Tintin_reporter& Tintin_reporter::getInstance() {
    static Tintin_reporter instance;
    return instance;
}

void Tintin_reporter::log(const std::string& level, const std::string& message) {
    time_t now = time(nullptr);
    struct tm* t = localtime(&now);
    char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "[%d/%m/%Y-%H:%M:%S]", t);

    std::string final = std::string(timestamp) + " [ " + level + " ] - Matt_daemon: " + message + "\n";
    write(log_fd, final.c_str(), final.length());
}
