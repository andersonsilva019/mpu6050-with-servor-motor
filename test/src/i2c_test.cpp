// Copyright (c) 2023 Robarm
// All rights reserved

#include <iostream>
#include <memory>

#include "module/accelerometer/include/accelerometer.hpp"
#include "module/accelerometer/include/accelerometer_exception.hpp"

/**
 * Tests I2C components, such as the accelerometer,
 * to ensure that everything is working properly.
 */
int main() {
  std::unique_ptr<robarm::module::accelerometer::Accelerometer> accelerometer;
  try {
    accelerometer =
        std::make_unique<robarm::module::accelerometer::Accelerometer>(
            robarm::hal::i2c::I2C_Bus::kBus2);
  } catch (robarm::module::accelerometer::AccelerometerException const& e) {
    std::cout << e.what() << "\n";
    return 1;
  } catch (std::exception const& e) {
    std::cout << e.what() << "\n";
    return 1;
  }

  while (true) {
    try {
      robarm::module::accelerometer::AxisAcceleration const& acceleration =
          accelerometer->getAcceleration();
      std::cout << "X: " << acceleration.x << " Y: " << acceleration.y
                << " Z: " << acceleration.z << "\n";
    } catch (robarm::module::accelerometer::AccelerometerException const& e) {
      std::cout << e.what() << "\n";
      return 0;
    } catch (std::exception const& e) {
      std::cout << e.what() << "\n";
      return 1;
    }
  }
  return 0;
}
