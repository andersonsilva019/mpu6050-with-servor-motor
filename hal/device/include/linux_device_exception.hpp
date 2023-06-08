// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef HAL_DEVICE_INCLUDE_LINUX_DEVICE_EXCEPTION_HPP_
#define HAL_DEVICE_INCLUDE_LINUX_DEVICE_EXCEPTION_HPP_

#include <string>
#include <stdexcept>

namespace robarm {
namespace hal {
namespace device {

class LinuxDeviceException : public std::exception {
 public:
  LinuxDeviceException();
  explicit LinuxDeviceException(char const* path);
  explicit LinuxDeviceException(std::string const& message);
  LinuxDeviceException(char const* device, char const* path);
  virtual ~LinuxDeviceException() noexcept = default;
  char const* what() const noexcept { return message_.c_str(); }

 private:
  std::string message_;
};

}  // namespace device
}  // namespace hal
}  // namespace robarm

#endif  // HAL_DEVICE_INCLUDE_LINUX_DEVICE_EXCEPTION_HPP_
