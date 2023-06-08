// Copyright (c) 2023 Robarm
// All rights reserved

#include "hal/pwm/include/pwm_info.hpp"

#include <cstdio>
#include <cstdlib>

#include "utils/common/include/common.hpp"

constexpr char kPwmDevicePathFormat[] = "/sys/class/pwm/pwmchip%d/pwm-%d:%d/";
constexpr char kPwmPinConfigFormat[] = "config-pin P%d.%d pwm";

robarm::hal::pwm::PWM_Info::PWM_Info(uint32_t chip, uint32_t device,
                                     uint32_t channel, uint32_t header,
                                     uint32_t pin)
    : chip_(chip),
      device_(device),
      channel_(channel),
      header_(header),
      pin_(pin) {
  configPinAsPwm();
}

std::string robarm::hal::pwm::PWM_Info::getDeviceFilePath() const noexcept {
  return utils::common::format(kPwmDevicePathFormat, chip_, device_, channel_);
}

void robarm::hal::pwm::PWM_Info::configPinAsPwm() const noexcept {
  std::string config_pin_string =
      utils::common::format(kPwmPinConfigFormat, header_, pin_);
  std::system(config_pin_string.c_str());
}
