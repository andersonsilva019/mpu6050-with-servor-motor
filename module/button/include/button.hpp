// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef MODULE_BUTTON_INCLUDE_BUTTON_HPP_
#define MODULE_BUTTON_INCLUDE_BUTTON_HPP_

#include "hal/gpio/include/digital_input.hpp"

namespace robarm {
namespace module {
namespace button {

class Button : protected hal::gpio::DigitalInput {
 public:
  explicit Button(uint32_t gpio_number);
  virtual ~Button() = default;
  bool isPressed() const {
    return getLevel() == hal::gpio::DigitalLevel::kHigh;
  }
  operator bool() const { return isPressed(); }
};

}  // namespace button
}  // namespace module
}  // namespace robarm

#endif  // MODULE_BUTTON_INCLUDE_BUTTON_HPP_
