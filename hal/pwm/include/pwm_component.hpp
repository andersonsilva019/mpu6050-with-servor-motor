// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef HAL_PWM_INCLUDE_PWM_COMPONENT_HPP_
#define HAL_PWM_INCLUDE_PWM_COMPONENT_HPP_

#include <cstdint>
#include <string>

#include "hal/device/include/linux_device.hpp"

namespace robarm {
namespace hal {
namespace pwm {

enum class PWM_ChannelId : uint32_t {
  kPwm1Channel_0,
  kPwm1Channel_1,
  kPwm4Channel_0,
  kPwm4Channel_1,
  kPwm7Channel_0,
  kPwm7Channel_1
};

class PWM_Component : protected device::LinuxDevice {
 public:
  explicit PWM_Component(PWM_ChannelId channel);
  PWM_Component(PWM_ChannelId channel, uint32_t period, uint32_t duty_cycle,
                bool is_enabled = true);
  virtual ~PWM_Component();
  void disableOutput() { setOutputStatus(false); }
  void enableOutput() { setOutputStatus(true); }
  void setPeriod(uint32_t period);
  void setDutyCycle(uint32_t duty_cycle);
  void setDutyCyclePercentage(double percentage);
  bool isEnabled() const noexcept { return is_enabled_; }
  uint32_t getPeriod() const noexcept { return period_; }
  uint32_t getDutyCycle() const noexcept { return duty_cycle_; }
  double getDutyCyclePercentage() const noexcept {
    return (duty_cycle_ / period_) * 100.0;
  }
  PWM_ChannelId getChannel() const noexcept { return channel_; }

 private:
  std::string constructPath(PWM_ChannelId channel) const noexcept;
  void setOutputStatus(bool output_status);

 private:
  const PWM_ChannelId channel_;
  uint32_t period_;
  uint32_t duty_cycle_;
  bool is_enabled_;
  std::string enable_file_path_;
  std::string duty_cycle_file_path_;
};

}  // namespace pwm
}  // namespace hal
}  // namespace robarm

#endif  // HAL_PWM_INCLUDE_PWM_COMPONENT_HPP_
