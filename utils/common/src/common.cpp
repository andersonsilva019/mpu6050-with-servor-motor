// Copyright (c) 2023 Robarm
// All rights reserved

#include "utils/common/include/common.hpp"

#include <cstdarg>
#include <cstdio>

constexpr uint32_t kCommonFormatterBufferSize = 2048;

uint32_t robarm::utils::common::map(double value, double in_min,
                                    double in_max, uint32_t out_min,
                                    uint32_t out_max) noexcept {
  /*if (value < in_min) {
    return out_min;
  } else if (value > in_max) {
    return out_max;
  }*/
  return static_cast<uint32_t>(((value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min));
}

double robarm::utils::common::map(uint32_t value, uint32_t in_min,
                                    uint32_t in_max, double out_min,
                                    double out_max) noexcept {
  /*if (value < in_min) {
    return out_min;
  } else if (value > in_max) {
    return out_max;
  }*/
  return static_cast<double>(((value - in_min) * (out_max - out_min) / (in_max - in_min) + out_min));
}

std::string robarm::utils::common::format(const char* fmt, ...) noexcept {
  if (!fmt) {
    return std::string("");
  }
  char format_buffer[kCommonFormatterBufferSize];
  va_list parameters;
  va_start(parameters, fmt);
  vsnprintf(format_buffer, kCommonFormatterBufferSize, fmt, parameters);
  va_end(parameters);
  return std::string(format_buffer);
}
