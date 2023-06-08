// Copyright (c) 2023 Robarm
// All rights reserved

#include "hal/gpio/include/gpio_component.hpp"

#include <fstream>

#include "hal/device/include/linux_device_access.hpp"
#include "hal/device/include/linux_device_exception.hpp"

constexpr char kGpioComponentPath[] = "/sys/class/gpio/gpio";
constexpr char kGpioComponentDirection[] = "direction";
constexpr char kGpioComponentEdge[] = "edge";
constexpr char kGpioComponentValue[] = "value";
constexpr char kGpioComponentDirectionIn[] = "in";
constexpr char kGpioComponentDirectionOut[] = "out";
constexpr char kGpioComponentInterruptEdgeNone[] = "none";
constexpr char kGpioComponentInterruptEdgeRising[] = "rising";
constexpr char kGpioComponentInterruptEdgeFalling[] = "falling";
constexpr char kGpioComponentInterruptEdgeBoth[] = "both";

robarm::hal::gpio::GPIO_Component::GPIO_Component(uint32_t number,
                                                  PinDirection direction)
    : LinuxDevice(kGpioComponentPath + std::to_string(number) + "/"),
      value_path_(getPath() + kGpioComponentValue) {
  setDirection(direction);
}

robarm::hal::gpio::DigitalLevel robarm::hal::gpio::GPIO_Component::getLevel()
    const {
  std::string level_string = device::LinuxDeviceAccess::readFile(value_path_);
  return static_cast<DigitalLevel>(std::atoi(level_string.c_str()));
}

void robarm::hal::gpio::GPIO_Component::setDirection(PinDirection direction) {
  direction_ = direction;
  device::LinuxDeviceAccess::writeFile(getPath() + kGpioComponentDirection,
                                       parseDirection(direction));
}

void robarm::hal::gpio::GPIO_Component::setLevel(DigitalLevel level) {
  device::LinuxDeviceAccess::writeFile(
      value_path_, std::to_string(static_cast<uint32_t>(level)));
}

void robarm::hal::gpio::GPIO_Component::setInterruptEdge(InterruptEdge edge) {
  device::LinuxDeviceAccess::writeFile(getPath() + kGpioComponentEdge,
                                       parseInterruptEdge(edge));
}

char const* robarm::hal::gpio::GPIO_Component::parseDirection(
    PinDirection direction) const noexcept {
  char const* direction_string;
  switch (direction) {
    case PinDirection::kIn:
      direction_string = kGpioComponentDirectionIn;
      break;
    case PinDirection::kOut:
      direction_string = kGpioComponentDirectionOut;
      break;
  }
  return direction_string;
}

char const* robarm::hal::gpio::GPIO_Component::parseInterruptEdge(
    InterruptEdge edge) const noexcept {
  char const* edge_string;
  switch (edge) {
    case InterruptEdge::kNone:
      edge_string = kGpioComponentInterruptEdgeNone;
      break;
    case InterruptEdge::kRising:
      edge_string = kGpioComponentInterruptEdgeRising;
      break;
    case InterruptEdge::kFalling:
      edge_string = kGpioComponentInterruptEdgeFalling;
      break;
    case InterruptEdge::kBoth:
      edge_string = kGpioComponentInterruptEdgeBoth;
      break;
  }
  return edge_string;
}
