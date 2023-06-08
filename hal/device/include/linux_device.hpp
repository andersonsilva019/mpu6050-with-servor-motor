// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef HAL_DEVICE_INCLUDE_LINUX_DEVICE_HPP_
#define HAL_DEVICE_INCLUDE_LINUX_DEVICE_HPP_

#include <string>

namespace robarm {
namespace hal {
namespace device {

/**
 * Maps a device at Linux filesystem, with a
 * path to the device handler file.
 */
class LinuxDevice {
 public:
  explicit LinuxDevice(std::string const& path) noexcept;
  virtual ~LinuxDevice() = default;
  std::string const& getPath() const noexcept { return path_; }

 private:
  const std::string path_;
};

}  // namespace device
}  // namespace hal
}  // namespace robarm

#endif  // HAL_DEVICE_INCLUDE_LINUX_DEVICE_HPP_
