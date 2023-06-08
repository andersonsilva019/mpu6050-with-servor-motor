// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef UTILS_LOGGER_INCLUDE_LOGGER_HPP_
#define UTILS_LOGGER_INCLUDE_LOGGER_HPP_

#include <iostream>
#include <string>

inline void LOG(std::string const& message) {
    LOG(message.c_str());
}

inline void LOG(char const* message) {
    std::cout << message << "\n";
}

#endif  // UTILS_LOGGER_INCLUDE_LOGGER_HPP_
