// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef UTILS_LOGGER_INCLUDE_LOGGER_HPP_
#define UTILS_LOGGER_INCLUDE_LOGGER_HPP_

#include <iostream>
#include <string>

void LOG(std::string const& message) noexcept { LOG(message.c_str()); }

void LOG(char const* message) noexcept { std::cout << message << "\n"; }

#endif  // UTILS_LOGGER_INCLUDE_LOGGER_HPP_
