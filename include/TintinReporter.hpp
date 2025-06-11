#ifndef TINTIN_REPORTER_HPP
#define TINTIN_REPORTER_HPP

#include <string>

class TintinReporter {
public:
    static TintinReporter& getInstance();
    void log(const std::string& level, const std::string& message);

private:
    TintinReporter();
    ~TintinReporter();
    TintinReporter(const TintinReporter&) = delete;
    TintinReporter& operator=(const TintinReporter&) = delete;

    int log_fd;
    void openLogFile();
    void closeLogFile();
};

#endif
