// Copyright (c) 2023 Robarm
// All rights reserved

#include <iostream>

#include <memory>

#include "module/accelerometer/include/accelerometer.hpp"
#include "hal/i2c/include/i2c_peripheral_exception.hpp"

/**
 * Tests I2C components, such as the accelerometer,
 * to ensure that everything is working properly. 
 */

int main() {
    std::unique_ptr<robarm::module::accelerometer::Accelerometer> accel;
    try {
        accel = std::make_unique<robarm::module::accelerometer::Accelerometer>(robarm::hal::i2c::I2C_Bus::kBus2);
        std::cout << "Device ID: " << accel->getDeviceID() << std::endl;
        std::cout << "Full Scale Accel Range: " << accel->getFullScaleAccelRange() << std::endl;
    }
    catch(robarm::hal::i2c::I2C_PeripheralException const& e) {
        std::cout << e.what() << std::endl;
        return 0;
    }
        
    while(1) {
        try {
            robarm::module::accelerometer::AxisAcceleration const& accel_data = accel->getAcceleration();
            std::cout << "X: " << accel_data.x << " Y: " << accel_data.y << " Z: " << accel_data.z << "\n";
        }
        catch(robarm::hal::i2c::I2C_PeripheralException const& e) {
            std::cout << e.what() << std::endl;
            return 0;
        }
    }
    return 0;
}
