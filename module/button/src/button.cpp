// Copyright (c) 2023 Robarm
// All rights reserved

#include "module/button/include/button.hpp"

robarm::module::button::Button::Button(uint32_t gpio_number)
    : DigitalInput(gpio_number) {}
