// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef MODULE_LED_INCLUDE_LED_HPP_
#define MODULE_LED_INCLUDE_LED_HPP_

#include "hal/gpio/include/digital_output.hpp"

namespace robarm {
namespace module {
namespace led {

class Simple_LED : protected hal::gpio::DigitalOutput {
 public:
  explicit Simple_LED(uint32_t gpio_number, bool active_low = false,
                      bool on_by_default = false);
  virtual ~Simple_LED() = default;
  bool isOn() const noexcept {
    return parseLevel(getLevel()) == hal::gpio::DigitalLevel::kHigh;
  }
  void turnOn() { setLevel(parseLevel(hal::gpio::DigitalLevel::kHigh)); }
  void turnOff() { setLevel(parseLevel(hal::gpio::DigitalLevel::kLow)); }
  void toggle() { DigitalOutput::toggleLevel(); }

 private:
  hal::gpio::DigitalLevel parseLevel(
      hal::gpio::DigitalLevel level) const noexcept {
    return (active_low_) ? DigitalOutput::invertDigitalLevel(level) : level;
  }

 private:
  bool active_low_;
};

}  // namespace led
}  // namespace module
}  // namespace robarm

#endif  // MODULE_LED_INCLUDE_LED_HPP_
