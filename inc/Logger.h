#pragma once
#include <iostream>
#include <string>
#include <sstream>

namespace Logger {
    inline void log(const std::string& message) {
        std::cout << message << std::endl;
    }

    template <typename... Args>
    inline void log(Args&&... args) {
        std::ostringstream oss;
        (oss << ... << args);
        std::cout << oss.str() << std::endl;
    }

    inline void logerr(const std::string& message) {
        std::cerr << message << std::endl;
    }

    template <typename... Args>
    inline void logerr(Args&&... args) {
        std::ostringstream oss;
        (oss << ... << args);
        std::cerr << oss.str() << std::endl;
    }
}
