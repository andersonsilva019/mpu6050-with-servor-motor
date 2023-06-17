// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef MODULE_ACCELEROMETER_INCLUDE_ACCELEROMETER_TILT_ANGLE_HPP_
#define MODULE_ACCELEROMETER_INCLUDE_ACCELEROMETER_TILT_ANGLE_HPP_

#include <memory>

#include "module/accelerometer/include/accelerometer.hpp"

namespace robarm {
namespace module {
namespace accelerometer {

struct TiltAngle {
  double x;
  double y;
  double z;
  TiltAngle() noexcept : TiltAngle(0, 0, 0) {}
  TiltAngle(double x, double y, double z) noexcept : x(x), y(y), z(z) {}
  virtual ~TiltAngle() = default;
};

class AccelerometerTiltAngle {
 public:
  explicit AccelerometerTiltAngle(std::shared_ptr<Accelerometer> accelerometer);
  virtual ~AccelerometerTiltAngle() = default;
  TiltAngle const& getTiltAngles();

 private:
  std::shared_ptr<Accelerometer> accelerometer_;
  TiltAngle angles_;
};

}  // namespace accelerometer
}  // namespace module
}  // namespace robarm

#endif  // MODULE_ACCELEROMETER_INCLUDE_ACCELEROMETER_TILT_ANGLE_HPP_
