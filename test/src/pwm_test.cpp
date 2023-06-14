// Copyright (c) 2023 Robarm
// All rights reserved

#include <unistd.h>

#include <iostream>
#include <memory>

#include "hal/device/include/linux_device_exception.hpp"
#include "module/motor/include/servo_motor.hpp"

/**
 * Tests PWM components, such as the servo motors,
 * to ensure that everything is working properly.
 */

int main() {
  std::unique_ptr<robarm::module::motor::ServoMotor> motor;
  try {
    motor = std::make_unique<robarm::module::motor::ServoMotor>(
        robarm::hal::pwm::PWM_ChannelId::kPwm1Channel_0);
  } catch (robarm::hal::device::LinuxDeviceException const& e) {
    std::cout << e.what() << "\n";
    return 0;
  }
  float angle = 0.0;
  bool ascending_count = true;
  while (true) {
    try {
      if (ascending_count) {
        angle += 0.01;
        if (angle >= 180.0) {
          ascending_count = false;
        }
      } else {
        angle -= 0.01;
        if (angle <= 0.0) {
          ascending_count = true;
        }
      }
      motor->setAngle(angle);
      usleep(25);
    } catch (robarm::hal::device::LinuxDeviceException const& e) {
      std::cout << e.what() << "\n";
      return 0;
    }
  }
 while(true);
}
