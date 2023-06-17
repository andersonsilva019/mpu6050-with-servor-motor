// Copyright (c) 2023 Robarm
// All rights reserved

#include "module/accelerometer/include/accelerometer_exception.hpp"

constexpr char kAccelerometerExceptionConnection[] =
    "Accelerometer is not connected.";
constexpr char kAccelerometerExceptionRead[] =
    "Could not read from the accelerometer.";
constexpr char kAccelerometerExceptionWrite[] =
    "Could not write to the accelerometer.";

robarm::module::accelerometer::AccelerometerException::AccelerometerException(
    AccelerometerError error) noexcept
    : error_(error) {}

const char*
robarm::module::accelerometer::AccelerometerException::parseErrorMessage()
    const noexcept {
  const char* error_string = nullptr;
  switch (error_) {
    default:
    case AccelerometerError::kConnection:
      error_string = kAccelerometerExceptionConnection;
      break;
    case AccelerometerError::kRead:
      error_string = kAccelerometerExceptionRead;
      break;
    case AccelerometerError::kWrite:
      error_string = kAccelerometerExceptionWrite;
      break;
  }
  return error_string;
}
