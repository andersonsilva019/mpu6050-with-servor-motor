// Copyright (c) 2023 Robarm
// All rights reserved

/**
 * Tests GPIO components, such as LEDs and buttons,
 * to ensure that everything is working properly.
 */

#include <iostream>
#include <memory>

#include "hal/device/include/linux_device_exception.hpp"
#include "module/button/include/button.hpp"
#include "module/led/include/led.hpp"

int main() {
  std::unique_ptr<robarm::module::led::Simple_LED> led;
  std::unique_ptr<robarm::module::button::Button> button;
  try {
    led = std::make_unique<robarm::module::led::Simple_LED>(68);
    button = std::make_unique<robarm::module::button::Button>(66);
  } catch (robarm::hal::device::LinuxDeviceException const& e) {
    std::cout << e.what() << "\n";
    return 1;
  } catch (std::exception const& e) {
    std::cout << e.what() << "\n";
    return 1;
  }
  while (true) {
    try {
      if (button->isPressed()) {
        led->turnOn();
      } else {
        led->turnOff();
      }
    } catch (robarm::hal::device::LinuxDeviceException const& e) {
      std::cout << e.what() << "\n";
      return 1;
    } catch (std::exception const& e) {
      std::cout << e.what() << "\n";
      return 1;
    }
  }
}
