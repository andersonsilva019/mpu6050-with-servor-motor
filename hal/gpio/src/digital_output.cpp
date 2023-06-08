// Copyright (c) 2023 Robarm
// All rights reserved

#include "hal/gpio/include/digital_output.hpp"

robarm::hal::gpio::DigitalOutput::DigitalOutput(uint32_t gpio_number,
                                                DigitalLevel default_level)
    : GPIO_Component(gpio_number), level_(default_level) {
  GPIO_Component::setLevel(default_level);
}

robarm::hal::gpio::DigitalLevel
robarm::hal::gpio::DigitalOutput::toggleLevel() {
  setLevel(DigitalOutput::invertDigitalLevel(level_));
  return level_;
}
