#ifndef TINTIN_REPORTER_HPP
#define TINTIN_REPORTER_HPP

#include <string>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

#define LOG_PATH "/var/log/matt_daemon/"
#define LOG_FILE "/var/log/matt_daemon/matt_daemon.log"

class Tintin_reporter {
public:
    static Tintin_reporter& getInstance();
    void log(const std::string& level, const std::string& message);

private:
    Tintin_reporter();
    ~Tintin_reporter();
    Tintin_reporter(const Tintin_reporter&) = delete;
    Tintin_reporter& operator=(const Tintin_reporter&) = delete;

    int log_fd;
    void openLogFile();
    void closeLogFile();
};

#endif
