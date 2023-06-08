// Copyright (c) 2023 Robarm
// All rights reserved

#include "hal/gpio/include/digital_input.hpp"

robarm::hal::gpio::DigitalInput::DigitalInput(uint32_t gpio_number,
                                              InterruptEdge default_edge)
    : GPIO_Component(gpio_number, PinDirection::kIn) {
  setInterruptEdge(default_edge);
}
