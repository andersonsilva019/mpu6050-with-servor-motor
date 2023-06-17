// Copyright (c) 2023 Robarm
// All rights reserved

#include "module/accelerometer/include/accelerometer_tilt_angle.hpp"

#include <stdexcept>

#include "utils/common/include/common.hpp"

constexpr int16_t kAccelerometerTiltAngleMinAcceleration = -17000;
constexpr int16_t kAccelerometerTiltAngleMaxAcceleration = 17000;
constexpr double kAccelerometerTiltAngleMinAngle = 0.0;
constexpr double kAccelerometerTiltAngleMaxAngle = 180.0;
constexpr char kAccelerometerNullptrErrorString[] =
    "Accelerometer shared pointer cannot be null.";

robarm::module::accelerometer::AccelerometerTiltAngle::AccelerometerTiltAngle(
    std::shared_ptr<Accelerometer> accelerometer)
    : accelerometer_(accelerometer) {
  if (!accelerometer) {
    throw std::invalid_argument(kAccelerometerNullptrErrorString);
  }
}

robarm::module::accelerometer::TiltAngle const&
robarm::module::accelerometer::AccelerometerTiltAngle::getTiltAngles() {
  AxisAcceleration const& axis_acceleration = accelerometer_->getAcceleration();
  angles_.x = robarm::utils::common::map(
      axis_acceleration.y, kAccelerometerTiltAngleMinAcceleration,
      kAccelerometerTiltAngleMaxAcceleration, kAccelerometerTiltAngleMaxAngle,
      kAccelerometerTiltAngleMinAngle);
  angles_.y = robarm::utils::common::map(
      axis_acceleration.x, kAccelerometerTiltAngleMinAcceleration,
      kAccelerometerTiltAngleMaxAcceleration, kAccelerometerTiltAngleMinAngle,
      kAccelerometerTiltAngleMaxAngle);
  return angles_;
}
