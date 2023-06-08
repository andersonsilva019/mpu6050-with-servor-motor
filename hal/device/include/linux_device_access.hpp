// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef HAL_DEVICE_INCLUDE_LINUX_DEVICE_ACCESS_HPP_
#define HAL_DEVICE_INCLUDE_LINUX_DEVICE_ACCESS_HPP_

#include <string>

namespace robarm {
namespace hal {
namespace device {

class LinuxDeviceAccess {
 public:
  static void writeFile(char const* file_path, char const* value);
  static void writeFile(std::string const& file_path,
                        std::string const& value) {
    LinuxDeviceAccess::writeFile(file_path.c_str(), value.c_str());
  }
  static void writeFile(std::string const& file_path, char const* value) {
    LinuxDeviceAccess::writeFile(file_path.c_str(), value);
  }
  static std::string readFile(char const* file_path);
  static std::string readFile(std::string const& file_path) {
    return LinuxDeviceAccess::readFile(file_path.c_str());
  }
};

}  // namespace device
}  // namespace hal
}  // namespace robarm

#endif  // HAL_DEVICE_INCLUDE_LINUX_DEVICE_ACCESS_HPP_
