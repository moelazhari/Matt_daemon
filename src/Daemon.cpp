#include "Daemon.hpp"

static const char* LOCK_FILE = "/var/lock/matt_daemon.lock";

void handle_signal(int signum) {
    Tintin_reporter::getInstance().log("INFO", "Signal handler: Signal " + std::to_string(signum));
    Tintin_reporter::getInstance().log("INFO", "Quitting.");
    std::remove(LOCK_FILE);
    exit(0);
}

void Daemon::run() {
    if (getuid() != 0) {
        std::cerr << "Daemon must be run as root." << std::endl;
        exit(1);
    }

    int lock_fd = open(LOCK_FILE, O_CREAT | O_RDWR, 0644);
    if (lock_fd < 0 || flock(lock_fd, LOCK_EX | LOCK_NB) < 0) {
        std::cerr << "Can't open or lock " << LOCK_FILE << std::endl;
        Tintin_reporter::getInstance().log("ERROR", "Matt_daemon: Error file locked.");
        Tintin_reporter::getInstance().log("INFO", "Matt_daemon: Quitting.");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);

    umask(0);
    setsid();
    chdir("/");

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    Tintin_reporter::getInstance().log("INFO", "Matt_daemon: Started.");
    Tintin_reporter::getInstance().log("INFO", "Matt_daemon: Creating server.");

    signal(SIGTERM, handle_signal);
    signal(SIGINT, handle_signal);

    Server server;
    server.start();
}
