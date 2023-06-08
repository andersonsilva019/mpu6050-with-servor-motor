// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef MODULE_MOTOR_INCLUDE_SERVO_MOTOR_HPP_
#define MODULE_MOTOR_INCLUDE_SERVO_MOTOR_HPP_

#include <string>

#include "hal/pwm/include/pwm_component.hpp"

namespace robarm {
namespace module {
namespace motor {

class ServoMotor : protected hal::pwm::PWM_Component {
 public:
  ServoMotor(hal::pwm::PWM_ChannelId pwm_channel, double default_angle = 0.0F,
             bool is_enabled = true);
  void enable() { enableOutput(); }
  void disable() { disableOutput(); }
  void setAngle(double angle);
  double getAngle() const noexcept { return current_angle_; }
  bool isEnabled() const noexcept { return PWM_Component::isEnabled(); }

 private:
  uint32_t parseAngle(double angle);

 private:
  double current_angle_;
};

}  // namespace motor
}  // namespace module
}  // namespace robarm

#endif  // MODULE_MOTOR_INCLUDE_SERVO_MOTOR_HPP_
