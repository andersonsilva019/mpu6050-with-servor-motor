// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef MODULE_ACCELEROMETER_INCLUDE_ACCELEROMETER_HPP_
#define MODULE_ACCELEROMETER_INCLUDE_ACCELEROMETER_HPP_

#include <cstdint>

#include "hal/i2c/include/i2c_component.hpp"

namespace robarm {
namespace module {
namespace accelerometer {

struct AxisAcceleration {
  int16_t x;
  int16_t y;
  int16_t z;
  AxisAcceleration() noexcept : AxisAcceleration(0, 0, 0) {}
  AxisAcceleration(int16_t x, int16_t y, int16_t z) noexcept
      : x(x), y(y), z(z) {}
};

enum class FullScaleRange : uint32_t { kRange2, kRange4, kRange8, kRange16 };

class Accelerometer : protected hal::i2c::I2C_Component {
 public:
  explicit Accelerometer(hal::i2c::I2C_Bus bus,
                         FullScaleRange range = FullScaleRange::kRange2,
                         bool is_awake = true);
  virtual ~Accelerometer() = default;
  FullScaleRange getFullScaleRange() const noexcept { return range_; }
  AxisAcceleration const& getAcceleration() {
    readAxisAcceleration();
    return acceleration_;
  }
  bool isConnected();
  bool isAwake() const noexcept { return is_awake_; }
  void setFullScaleRange(FullScaleRange range);
  void sleep() {
    writeSleep(true);
    is_awake_ = false;
  }
  void wakeup() {
    writeSleep(false);
    is_awake_ = true;
  }

 private:
  uint8_t readDeviceId();
  void readAxisAcceleration();
  void writeSleep(bool is_asleep);

 private:
  AxisAcceleration acceleration_;
  FullScaleRange range_;
  double scale_;
  bool is_awake_;
};

}  // namespace accelerometer
}  // namespace module
}  // namespace robarm

#endif  // MODULE_ACCELEROMETER_INCLUDE_ACCELEROMETER_HPP_
