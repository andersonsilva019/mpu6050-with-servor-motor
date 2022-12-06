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

public:
    Accelerometer(void);
    Accelerometer(std::string bus);
    void getAcceleration(Acceleration_t* acceleration);
    void readAccelRaw(AccelerationRAW_t* accelRaw);
    
    float getAccelerationX(void);
    float getAccelerationY(void);
    float getAccelerationZ(void);

    bool init(void);
    bool testConnection(void);

    void setSleepEnabled(bool enabled);

    void setFullScaleAccelRange(uint8_t range);
    uint8_t getFullScaleAccelRange(void);

    uint8_t getDeviceID(void);
};