// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef HAL_GPIO_INCLUDE_GPIO_COMPONENT_HPP_
#define HAL_GPIO_INCLUDE_GPIO_COMPONENT_HPP_

#include <cstdint>
#include <string>

#include "hal/device/include/linux_device.hpp"

namespace robarm {
namespace hal {
namespace gpio {

enum class DigitalLevel : bool { kLow, kHigh };

enum class InterruptEdge : uint32_t { kNone, kRising, kFalling, kBoth };

enum class PinDirection : uint32_t { kIn, kOut };

class GPIO_Component : protected device::LinuxDevice {
 public:
  explicit GPIO_Component(uint32_t number,
                          PinDirection direction = PinDirection::kOut);
  virtual ~GPIO_Component() = default;
  PinDirection getDirection() const noexcept { return direction_; }
  DigitalLevel getLevel() const;
  void setDirection(PinDirection direction);
  void setLevel(DigitalLevel level);
  void setInterruptEdge(InterruptEdge edge);

 private:
  char const* parseDirection(PinDirection direction) const noexcept;
  char const* parseInterruptEdge(InterruptEdge edge) const noexcept;

 private:
  const std::string value_path_;
  PinDirection direction_;
};

}  // namespace gpio
}  // namespace hal
}  // namespace robarm

#endif  // HAL_GPIO_INCLUDE_GPIO_COMPONENT_HPP_
