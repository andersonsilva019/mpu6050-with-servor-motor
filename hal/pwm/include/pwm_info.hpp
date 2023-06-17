// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef HAL_PWM_INCLUDE_PWM_INFO_HPP_
#define HAL_PWM_INCLUDE_PWM_INFO_HPP_

#include <cstdint>
#include <string>

namespace robarm {
namespace hal {
namespace pwm {

enum class BoardHeader : uint32_t { kHeaderP8 = 8, kHeaderP9 = 9 };

struct PWM_Info {
 public:
  PWM_Info(uint32_t chip, uint32_t device, uint32_t channel, BoardHeader header,
           uint32_t pin) noexcept;
  virtual ~PWM_Info() = default;
  std::string getDeviceFilePath() const noexcept;

 private:
  void configPinAsPwm() const noexcept;

 public:
  const uint32_t chip_;
  const uint32_t device_;
  const uint32_t channel_;
  const BoardHeader header_;
  const uint32_t pin_;
};

}  // namespace pwm
}  // namespace hal
}  // namespace robarm

#endif  // HAL_PWM_INCLUDE_PWM_INFO_HPP_
