// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef HAL_GPIO_INCLUDE_DIGITAL_OUTPUT_HPP_
#define HAL_GPIO_INCLUDE_DIGITAL_OUTPUT_HPP_

#include <cstdint>
#include <string>

#include "hal/gpio/include/gpio_component.hpp"

namespace robarm {
namespace hal {
namespace gpio {

class DigitalOutput : protected GPIO_Component {
 public:
  explicit DigitalOutput(uint32_t gpio_number,
                         DigitalLevel default_level = DigitalLevel::kLow);
  virtual ~DigitalOutput() = default;
  DigitalLevel getLevel() const noexcept { return level_; }
  void setLevel(DigitalLevel level) {
    level_ = level;
    GPIO_Component::setLevel(level);
  }
  DigitalLevel toggleLevel();

 public:
  static DigitalLevel invertDigitalLevel(DigitalLevel digital_level) noexcept {
    return static_cast<DigitalLevel>(!static_cast<bool>(digital_level));
  }

 private:
  DigitalLevel level_;
};

}  // namespace gpio
}  // namespace hal
}  // namespace robarm

#endif  // HAL_GPIO_INCLUDE_DIGITAL_OUTPUT_HPP_
