#include "TintinReporter.hpp"
#include <ctime>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define LOG_PATH "/var/log/matt_daemon/"
#define LOG_FILE "/var/log/matt_daemon/matt_daemon.log"

TintinReporter::TintinReporter() {
    mkdir(LOG_PATH, 0755);
    openLogFile();

}

TintinReporter::~TintinReporter() {
    closeLogFile();
}

void TintinReporter::openLogFile() {
    log_fd = open(LOG_FILE, O_WRONLY | O_CREAT | O_APPEND, 0777);
}

void TintinReporter::closeLogFile() {
    if (log_fd != -1) close(log_fd);
}

TintinReporter& TintinReporter::getInstance() {
    static TintinReporter instance;
    return instance;
}

void TintinReporter::log(const std::string& level, const std::string& message) {
    time_t now = time(nullptr);
    struct tm* t = localtime(&now);
    char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "[%d/%m/%Y-%H:%M:%S]", t);

    std::string final = std::string(timestamp) + " [ " + level + " ] - Matt_daemon: " + message + "\n";
    write(log_fd, final.c_str(), final.length());
}
