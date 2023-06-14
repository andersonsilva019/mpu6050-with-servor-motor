// Copyright (c) 2023 Robarm
// All rights reserved

#include "module/roboticarm/include/roboticarm.hpp"

#include "hal/pwm/include/pwm_component.hpp"
#include "hal/i2c/include/i2c_component.hpp"

#include "module/led/include/led.hpp"
#include "module/button/include/button.hpp"
#include "module/accelerometer/include/accelerometer.hpp"

#include "utils/common/include/common.hpp"

#include <stdexcept>
#include <iostream>
#include <cmath>
#include <memory>

#include <unistd.h>

#define POWER_GLOVE_MIN_ACCELERATION 0.5
#define PI 3.14159265359
#define RADIAN_TO_DEGREE 57.2958

int main(void) {
     std::unique_ptr<robarm::module::roboticarm::RoboticArm> robotic_arm;
     std::unique_ptr<robarm::module::accelerometer::Accelerometer> accelerometer;
     std::unique_ptr<robarm::module::button::Button> touch_sensor;
     std::unique_ptr<robarm::module::led::Simple_LED> start_led;
     std::unique_ptr<robarm::module::led::Simple_LED> touch_led;
     try {
          robotic_arm = std::make_unique<robarm::module::roboticarm::RoboticArm>(robarm::hal::pwm::PWM_ChannelId::kPwm1Channel_0, robarm::hal::pwm::PWM_ChannelId::kPwm1Channel_1, robarm::hal::pwm::PWM_ChannelId::kPwm4Channel_0, robarm::hal::pwm::PWM_ChannelId::kPwm4Channel_1);
          accelerometer = std::make_unique<robarm::module::accelerometer::Accelerometer>(robarm::hal::i2c::I2C_Bus::kBus2);
          touch_sensor = std::make_unique<robarm::module::button::Button>(66);
          start_led = std::make_unique<robarm::module::led::Simple_LED>(67, false, true);
          touch_led = std::make_unique<robarm::module::led::Simple_LED>(68);
     }
     catch(std::exception const& e) {
          std::cout << e.what();
          return 1;
     }

     bool grip_returned_to_default = true;
     while (true) {
          try {
               robarm::module::accelerometer::AxisAcceleration const& acceleration = accelerometer->getAcceleration();

               double x_angle = robarm::utils::common::map(acceleration.y, -17000, 17000, 180.0, 0.0);
               double y_angle = robarm::utils::common::map(acceleration.x, -17000, 17000, 0.0, 180.0);

               robotic_arm->setApproximationAngle(x_angle);
               robotic_arm->setRotationAngle(y_angle);

               if (touch_sensor->isPressed()) {
                    touch_led->turnOn();
                    robotic_arm->setGripAngle(180);
               }
               else {
                    touch_led->turnOff();
                    robotic_arm->setGripAngle(120);
               }
               
          }
          catch (std::exception const& e) {
               std::cout << e.what();
               return 1;
          }
     }
}
