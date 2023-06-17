// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef UTILS_COMMON_INCLUDE_COMMON_HPP_
#define UTILS_COMMON_INCLUDE_COMMON_HPP_

#include <cstdint>
#include <string>

namespace robarm {
namespace utils {
namespace common {

template <typename FromType, typename ToType>
ToType map(FromType value, FromType in_min, FromType in_max, ToType out_min,
           ToType out_max) noexcept {
  if (value < in_min) {
    return out_min;
  } else if (value > in_max) {
    return out_max;
  }
  return static_cast<ToType>(
      ((value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min));
}

std::string format(const char* fmt, ...) noexcept;

}  // namespace common
}  // namespace utils
}  // namespace robarm

#endif  // UTILS_COMMON_INCLUDE_COMMON_HPP_
