// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef MODULE_ACCELEROMETER_INCLUDE_ACCELEROMETER_HPP_
#define MODULE_ACCELEROMETER_INCLUDE_ACCELEROMETER_HPP_

#include "hal/i2c/include/i2c_component.hpp"

struct AccelerationRAW_t {
    int16_t x;
    int16_t y;
    int16_t z;
};

struct Acceleration_t {
    float x;
    float y;
    float z;
};

namespace robarm {
namespace module {
namespace accelerometer {

class Accelerometer : protected hal::i2c::I2C_Component {
private:
    //robarm::hal::i2c::I2C_Component i2c_;
    AccelerationRAW_t accelRaw_;
    Acceleration_t accel_;

public:
    Accelerometer();
    explicit Accelerometer(hal::i2c::I2C_Bus bus);
    ~Accelerometer();
    void getAcceleration(Acceleration_t* acceleration);
    void readAccelRaw(AccelerationRAW_t* accelRaw);
    
    float getAccelerationX();
    float getAccelerationY();
    float getAccelerationZ();

    bool init();
    bool testConnection();

    void setSleepEnabled(bool enabled);

    void setFullScaleAccelRange(uint8_t range);
    uint8_t getFullScaleAccelRange();

    uint8_t getDeviceID();
};

} // namespace accelerometer
} // namespace module
} // namespace robarm

#endif // MODULE_ACCELEROMETER_INCLUDE_ACCELEROMETER_HPP_