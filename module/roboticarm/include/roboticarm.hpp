// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef MODULE_ROBOTICARM_INCLUDE_ROBOTICARM_HPP_
#define MODULE_ROBOTICARM_INCLUDE_ROBOTICARM_HPP_

#include "module/motor/include/servo_motor.hpp"

namespace robarm {
namespace module {
namespace roboticarm {

class RoboticArm {
 public:
  RoboticArm(hal::pwm::PWM_ChannelId rotation_servo_channel,
             hal::pwm::PWM_ChannelId elevation_servo_channel,
             hal::pwm::PWM_ChannelId approximation_servo_channel,
             hal::pwm::PWM_ChannelId grab_servo_channel);
  virtual ~RoboticArm() = default;
  void openClaw() { setGripAngle(120.0); }
  void closeClaw() { setGripAngle(180.0); }
  void setRotationAngle(double angle) { rotation_servo_.setAngle(angle); }
  void setElevationAngle(double angle) { elevation_servo_.setAngle(angle); }
  void setApproximationAngle(double angle) {
    approximation_servo_.setAngle(angle);
  }
  void setGripAngle(double angle) { grab_servo_.setAngle(angle); }
  double getRotationAngle() const noexcept {
    return rotation_servo_.getAngle();
  }
  double getElevationAngle() const noexcept {
    return elevation_servo_.getAngle();
  }
  double getApproximationAngle() const noexcept {
    return approximation_servo_.getAngle();
  }
  double getGripAngle() const noexcept { return grab_servo_.getAngle(); }

 private:
  motor::ServoMotor rotation_servo_;
  motor::ServoMotor approximation_servo_;
  motor::ServoMotor elevation_servo_;
  motor::ServoMotor grab_servo_;
};

}  // namespace roboticarm
}  // namespace module
}  // namespace robarm

#endif  // MODULE_ROBOTICARM_INCLUDE_ROBOTICARM_HPP_
