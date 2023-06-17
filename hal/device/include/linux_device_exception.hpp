// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef HAL_DEVICE_INCLUDE_LINUX_DEVICE_EXCEPTION_HPP_
#define HAL_DEVICE_INCLUDE_LINUX_DEVICE_EXCEPTION_HPP_

#include <stdexcept>
#include <string>

namespace robarm {
namespace hal {
namespace device {

class LinuxDeviceException : public std::exception {
 public:
  LinuxDeviceException() noexcept;
  explicit LinuxDeviceException(char const* path) noexcept;
  explicit LinuxDeviceException(std::string const& message) noexcept;
  LinuxDeviceException(char const* device, char const* path) noexcept;
  virtual ~LinuxDeviceException() = default;
  virtual char const* what() const noexcept { return message_.c_str(); }

 private:
  std::string message_;
};

}  // namespace device
}  // namespace hal
}  // namespace robarm

#endif  // HAL_DEVICE_INCLUDE_LINUX_DEVICE_EXCEPTION_HPP_
