#ifndef DAEMON_HPP
#define DAEMON_HPP

#include "Daemon.hpp"
#include "Tintin_reporter.hpp"
#include "Server.hpp"
#include <csignal>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/types.h>
class Daemon {
public:
    static void run();
};

#endif
