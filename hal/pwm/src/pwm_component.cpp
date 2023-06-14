// Copyright (c) 2023 Robarm
// All rights reserved

#include "hal/pwm/include/pwm_component.hpp"

#include <cstdio>
#include <fstream>

#include "hal/device/include/linux_device_access.hpp"
#include "hal/pwm/include/pwm_info.hpp"

constexpr char kPwmEnable[] = "enable";
constexpr char kPwmPeriod[] = "period";
constexpr char kPwmDutyCycle[] = "duty_cycle";

robarm::hal::pwm::PWM_Component::PWM_Component(PWM_ChannelId channel)
    : PWM_Component(channel, 0, 0, false) {}

robarm::hal::pwm::PWM_Component::PWM_Component(PWM_ChannelId channel,
                                               uint32_t period,
                                               uint32_t duty_cycle,
                                               bool is_enabled)
    : channel_(channel),
      LinuxDevice(constructPath()),
      enable_file_path_(getPath() + kPwmEnable),
      duty_cycle_file_path_(getPath() + kPwmDutyCycle) {
  setPeriod(period);
  setDutyCycle(duty_cycle);
  setOutputStatus(is_enabled);
}

robarm::hal::pwm::PWM_Component::~PWM_Component() { disableOutput(); }

void robarm::hal::pwm::PWM_Component::setPeriod(uint32_t period) {
  period_ = period;
  device::LinuxDeviceAccess::writeFile((getPath() + kPwmPeriod).c_str(),
                                       std::to_string(period).c_str());
}

void robarm::hal::pwm::PWM_Component::setDutyCycle(uint32_t duty_cycle) {
  duty_cycle_ = duty_cycle;
  device::LinuxDeviceAccess::writeFile(duty_cycle_file_path_.c_str(),
                                       std::to_string(duty_cycle).c_str());
}

void robarm::hal::pwm::PWM_Component::setDutyCyclePercentage(float percentage) {
  if (percentage < 0.01F && percentage > 1.0F) {
    return;
  }
  uint32_t duty_cycle = static_cast<uint32_t>(percentage * period_);
  setDutyCycle(duty_cycle);
}

std::string robarm::hal::pwm::PWM_Component::constructPath() const noexcept {
  switch (channel_) {
    case PWM_ChannelId::kPwm1Channel_0: {
      PWM_Info pwm_info(1, 1, 0, 9, 22);
      return pwm_info.getDeviceFilePath();
    }
    case PWM_ChannelId::kPwm1Channel_1: {
      PWM_Info pwm_info(1, 1, 1, 9, 21);
      return pwm_info.getDeviceFilePath();
    }
    case PWM_ChannelId::kPwm4Channel_0: {
      PWM_Info pwm_info(4, 4, 0, 9, 14);
      return pwm_info.getDeviceFilePath();
    }
    case PWM_ChannelId::kPwm4Channel_1: {
      PWM_Info pwm_info(4, 4, 1, 9, 16);
      return pwm_info.getDeviceFilePath();
    }
    case PWM_ChannelId::kPwm7Channel_0: {
      PWM_Info pwm_info(7, 7, 0, 8, 19);
      return pwm_info.getDeviceFilePath();
    }
    case PWM_ChannelId::kPwm7Channel_1: {
      PWM_Info pwm_info(7, 7, 1, 8, 13);
      return pwm_info.getDeviceFilePath();
    }
  }
  return "";  // [TODO] Could throw an exception here...
}

void robarm::hal::pwm::PWM_Component::setOutputStatus(bool output_status) {
  is_enabled_ = output_status;
  device::LinuxDeviceAccess::writeFile(enable_file_path_.c_str(),
                                       std::to_string(output_status).c_str());
}
