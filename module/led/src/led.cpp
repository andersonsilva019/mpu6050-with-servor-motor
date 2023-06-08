// Copyright (c) 2023 Robarm
// All rights reserved

#include "module/led/include/led.hpp"

robarm::module::led::Simple_LED::Simple_LED(uint32_t gpio_number,
                                            bool active_low, bool on_by_default)
    : active_low_(active_low),
      DigitalOutput(
          gpio_number,
          parseLevel(static_cast<hal::gpio::DigitalLevel>(on_by_default))) {}
