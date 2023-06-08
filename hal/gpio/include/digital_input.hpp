// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef HAL_GPIO_INCLUDE_DIGITAL_INPUT_HPP_
#define HAL_GPIO_INCLUDE_DIGITAL_INPUT_HPP_

#include <cstdint>
#include <string>

#include "hal/gpio/include/gpio_component.hpp"

namespace robarm {
namespace hal {
namespace gpio {

class DigitalInput : protected GPIO_Component {
 public:
  explicit DigitalInput(uint32_t gpio_number,
                        InterruptEdge default_edge = InterruptEdge::kNone);
  virtual ~DigitalInput() = default;
  DigitalLevel getLevel() const { return GPIO_Component::getLevel(); }
};

}  // namespace gpio
}  // namespace hal
}  // namespace robarm

#endif  // HAL_GPIO_INCLUDE_DIGITAL_INPUT_HPP_
