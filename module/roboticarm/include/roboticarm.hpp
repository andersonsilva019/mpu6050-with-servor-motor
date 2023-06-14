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
     RoboticArm(hal::pwm::PWM_ChannelId rotation_servo_channel, hal::pwm::PWM_ChannelId elevation_servo_channel, hal::pwm::PWM_ChannelId approximation_servo_channel, hal::pwm::PWM_ChannelId grab_servo_channel);
     void setRotationAngle(double angle) {
          rotation_servo_.setAngle(angle);
     }
     void setElevationAngle(double angle) {
          elevation_servo_.setAngle(angle);
     }
     void setApproximationAngle(double angle) {
          approximation_servo_.setAngle(angle);
     }
     void setGripAngle(double angle) {
          grab_servo_.setAngle(angle);
     }
     double getRotationAngle() {
          return rotation_servo_.getAngle();
     }
     double getElevationAngle() {
          return elevation_servo_.getAngle();
     }
     double getApproximationAngle() {
          return approximation_servo_.getAngle();
     }
     double getGripAngle() {
          return grab_servo_.getAngle();
     }

private:
     motor::ServoMotor rotation_servo_;
     motor::ServoMotor approximation_servo_;
     motor::ServoMotor elevation_servo_;
     motor::ServoMotor grab_servo_;
};

}
}
}

#endif  // MODULE_ROBOTICARM INCLUDE_ROBOTICARM_HPP_