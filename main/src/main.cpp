// Copyright (c) 2023 Robarm
// All rights reserved

#include <unistd.h>

#include <iostream>
#include <memory>
#include <stdexcept>

#include "module/accelerometer/include/accelerometer.hpp"
#include "module/accelerometer/include/accelerometer_exception.hpp"
#include "module/accelerometer/include/accelerometer_tilt_angle.hpp"
#include "module/button/include/button.hpp"
#include "module/led/include/led.hpp"
#include "module/roboticarm/include/roboticarm.hpp"

constexpr uint32_t kRobarmTouchSensorGpioNumber = 66;
constexpr uint32_t kRobarmPowerLedGpioNumber = 67;
constexpr uint32_t kRobarmTouchLedGpioNumber = 68;

std::unique_ptr<robarm::module::roboticarm::RoboticArm> robotic_arm;
std::shared_ptr<robarm::module::accelerometer::Accelerometer> accelerometer;
std::unique_ptr<robarm::module::button::Button> touch_sensor;
std::unique_ptr<robarm::module::led::Simple_LED> power_led;
std::unique_ptr<robarm::module::led::Simple_LED> touch_led;

static void accelerometerDisconnectedErrorFlux() {
  try {
    while (!accelerometer->isConnected()) {
      power_led->toggle();
      usleep(500);
    }
    power_led->turnOn();
  } catch (...) {
  }
}

int main() {
  try {
    robotic_arm = std::make_unique<robarm::module::roboticarm::RoboticArm>(
        robarm::hal::pwm::PWM_ChannelId::kPwm1Channel_0,
        robarm::hal::pwm::PWM_ChannelId::kPwm1Channel_1,
        robarm::hal::pwm::PWM_ChannelId::kPwm4Channel_0,
        robarm::hal::pwm::PWM_ChannelId::kPwm4Channel_1);
    accelerometer =
        std::make_shared<robarm::module::accelerometer::Accelerometer>(
            robarm::hal::i2c::I2C_Bus::kBus2);
    touch_sensor = std::make_unique<robarm::module::button::Button>(
        kRobarmTouchSensorGpioNumber);
    power_led = std::make_unique<robarm::module::led::Simple_LED>(
        kRobarmPowerLedGpioNumber, false, true);
    touch_led = std::make_unique<robarm::module::led::Simple_LED>(
        kRobarmTouchLedGpioNumber);
  } catch (std::exception const& e) {
    std::cout << e.what();
    return 1;
  }

  robarm::module::accelerometer::AccelerometerTiltAngle
      accelerometer_tilt_angle(accelerometer);

  while (true) {
    try {
      robarm::module::accelerometer::TiltAngle const& angles =
          accelerometer_tilt_angle.getTiltAngles();

      robotic_arm->setApproximationAngle(angles.x);
      robotic_arm->setRotationAngle(angles.y);

      if (touch_sensor->isPressed()) {
        touch_led->turnOn();
        robotic_arm->closeClaw();
      } else {
        touch_led->turnOff();
        robotic_arm->openClaw();
      }
    } catch (robarm::module::accelerometer::AccelerometerException const& e) {
      std::cout << "[error] An error has ocurred in the ACCELEROMETER:\n\t"
                << e.what() << "\nPlease, reconnect the ACCELEROMETER.\n";
      accelerometerDisconnectedErrorFlux();
    } catch (std::exception const& e) {
      std::cout << e.what();
      return 1;
    }
  }
}
