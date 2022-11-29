#ifndef _MPU6050_HPP_
#define _MPU6050_HPP_

#include "BBB_I2C.hpp"

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} AccelerationRAW_t;

typedef struct {
    float x;
    float y;
    float z;
} Acceleration_t;

class MPU6050 {
private:
    BBB_I2C i2c;
    AccelerationRAW_t accelRaw;
    void readAccelRaw(AccelerationRAW_t *accelRaw);

public:
    MPU6050();
    MPU6050(std::string bus);
    ~MPU6050(void);
    void getAcceleration(Acceleration_t *acceleration);
    
    bool init(void);
    bool testConnection(void);

    void setSleepEnabled(bool enabled);

    void setFullScaleAccelRange(uint8_t range);
    uint8_t getFullScaleAccelRange(void);

    uint8_t getDeviceID(void);
};

#endif // MPU6050_HPP