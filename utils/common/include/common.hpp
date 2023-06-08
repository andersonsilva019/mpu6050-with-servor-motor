// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef UTILS_COMMON_INCLUDE_COMMON_HPP_
#define UTILS_COMMON_INCLUDE_COMMON_HPP_

#include <cstdint>
#include <string>

namespace robarm {
namespace utils {
namespace common {

uint32_t map(uint32_t value, uint32_t in_min, uint32_t in_max, uint32_t out_min,
             uint32_t out_max) noexcept;

std::string format(const char* fmt, ...) noexcept;

}  // namespace common
}  // namespace utils
}  // namespace robarm

#endif  // UTILS_COMMON_INCLUDE_COMMON_HPP_
