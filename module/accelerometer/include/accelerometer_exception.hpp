// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef MODULE_ACCELEROMETER_INCLUDE_ACCELEROMETER_EXCEPTION_HPP_
#define MODULE_ACCELEROMETER_INCLUDE_ACCELEROMETER_EXCEPTION_HPP_

#include <cstdint>
#include <stdexcept>
#include <string>

namespace robarm {
namespace module {
namespace accelerometer {

enum class AccelerometerError : uint32_t { kConnection, kRead, kWrite };

class AccelerometerException : public std::exception {
 public:
  explicit AccelerometerException(
      AccelerometerError error = AccelerometerError::kConnection) noexcept;
  virtual ~AccelerometerException() = default;
  virtual char const* what() const noexcept { return parseErrorMessage(); }

 private:
  const char* parseErrorMessage() const noexcept;

 private:
  AccelerometerError error_;
};

}  // namespace accelerometer
}  // namespace module
}  // namespace robarm

#endif  // MODULE_ACCELEROMETER_INCLUDE_ACCELEROMETER_EXCEPTION_HPP_
