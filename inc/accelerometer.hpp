#pragma once

#include "i2c.hpp"

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

class Accelerometer {
private:
    I2C i2c;
    AccelerationRAW_t accelRaw;
    Acceleration_t accel;
    void readAccelRaw(AccelerationRAW_t* accelRaw);

public:
    Accelerometer();
    Accelerometer(std::string bus);
    void getAcceleration(Acceleration_t* acceleration);
    
    float getAccelerationX();
    float getAccelerationY();
    float getAccelerationZ();

    bool init(void);
    bool testConnection(void);

    void setSleepEnabled(bool enabled);

    void setFullScaleAccelRange(uint8_t range);
    uint8_t getFullScaleAccelRange(void);

    uint8_t getDeviceID(void);
};