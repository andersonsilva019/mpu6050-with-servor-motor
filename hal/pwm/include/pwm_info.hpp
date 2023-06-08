// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef HAL_PWM_INCLUDE_PWM_INFO_HPP_
#define HAL_PWM_INCLUDE_PWM_INFO_HPP_

#include <cstdint>
#include <string>

namespace robarm {
namespace hal {
namespace pwm {

struct PWM_Info {
 public:
  PWM_Info(uint32_t chip, uint32_t device, uint32_t channel, uint32_t header,
           uint32_t pin);
  std::string getDeviceFilePath() const noexcept;

 private:
  void configPinAsPwm() const noexcept;

 public:
  const uint32_t chip_ = 0;
  const uint32_t device_ = 0;
  const uint32_t channel_ = 0;
  const uint32_t header_ = 0;
  const uint32_t pin_ = 0;
};

}  // namespace pwm
}  // namespace hal
}  // namespace robarm

#endif  // HAL_PWM_INCLUDE_PWM_INFO_HPP_
