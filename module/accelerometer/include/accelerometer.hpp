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
};

class Accelerometer : protected hal::i2c::I2C_Component {
public:
    explicit Accelerometer(hal::i2c::I2C_Bus bus);
    ~Accelerometer() = default;

    uint8_t getDeviceID();
    uint8_t getFullScaleAccelRange();
    AxisAcceleration const& getAcceleration();
    bool isConnected();
    void setFullScaleAccelRange(uint8_t range);
    void sleep();
    void wakeup();

private:
    void readAxisAcceleration();

private:
    AxisAcceleration acceleration_;
};

} // namespace accelerometer
} // namespace module
} // namespace robarm

#endif // MODULE_ACCELEROMETER_INCLUDE_ACCELEROMETER_HPP_
