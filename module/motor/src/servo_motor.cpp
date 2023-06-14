// Copyright (c) 2023 Robarm
// All rights reserved

#include "module/motor/include/servo_motor.hpp"

#include "utils/common/include/common.hpp"

constexpr uint32_t kServoMotorPeriodNs = 20'000'000;
constexpr double kServoMotorMinDegree = 0.0;
constexpr double kServoMotorMaxDegree = 180.0;
constexpr uint32_t kServoMotorMinDutyCycle = 500'000;
constexpr uint32_t kServoMotorMaxDutyCycle = 2'500'000;

robarm::module::motor::ServoMotor::ServoMotor(
    hal::pwm::PWM_ChannelId pwm_channel, double default_angle, bool is_enabled)
    : PWM_Component(pwm_channel, kServoMotorPeriodNs, parseAngle(default_angle),
                    is_enabled),
      current_angle_(default_angle) {
  if (static_cast<uint32_t>(default_angle) > kServoMotorMaxDegree) {
    current_angle_ = kServoMotorMaxDegree;
  } else if (static_cast<uint32_t>(default_angle) < kServoMotorMinDegree) {
    current_angle_ = kServoMotorMinDegree;
  }
}

void robarm::module::motor::ServoMotor::setAngle(double angle) {
  current_angle_ = angle;
  setDutyCycle(parseAngle(angle));
}

uint32_t robarm::module::motor::ServoMotor::parseAngle(double angle) {
  return utils::common::map(angle, kServoMotorMinDegree,
                            kServoMotorMaxDegree, kServoMotorMinDutyCycle,
                            kServoMotorMaxDutyCycle);
}
