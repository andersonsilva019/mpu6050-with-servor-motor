// Copyright (c) 2023 Robarm
// All rights reserved

#include "utils/common/include/common.hpp"

#include <cstdarg>
#include <cstdio>

constexpr uint32_t kCommonFormatterBufferSize = 2048;

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
