#include "accelerometer.hpp"

#define ACC_FULLSCALE           (2)

#define MPU6050_ADDRESS         (int)(0x68) // address pin low (GND), default for InvenSense evaluation board

#if ACC_FULLSCALE == 2
    #define ACC_SCALE           (float)(16384.0)
#elif ACC_FULLSCALE == 4
    #define ACC_SCALE           (float)(8192.0)
#elif ACC_FULLSCALE == 8
    #define ACC_SCALE           (float)(4096.0)
#elif ACC_FULLSCALE == 16
    #define ACC_SCALE           (float)(2048.0)
#endif

Accelerometer::Accelerometer() : Accelerometer(I2C_LINUX_BUS2) {}

Accelerometer::Accelerometer(std::string bus) : i2c(bus, MPU6050_ADDRESS) {}

bool Accelerometer::init(void) {
    if (testConnection()) {
        setSleepEnabled(false);
        setFullScaleAccelRange(ACC_FULLSCALE);
        return true;
    }
    return false;
}

bool Accelerometer::testConnection(void) {
    return ((getDeviceID() == 0b110100) ? true : false);
}

void Accelerometer::setSleepEnabled(bool enabled) {
    i2c.writeBitI2C(0x6B, 6, enabled);
}

void Accelerometer::setFullScaleAccelRange(uint8_t range) {
    i2c.writeBitI2C(0x1C, 4, range);
}

uint8_t Accelerometer::getFullScaleAccelRange(void) {
    return i2c.readByteI2C(0x1C);
}

uint8_t Accelerometer::getDeviceID(void) {
    return i2c.readByteI2C(0x75) >> 1;
}

void Accelerometer::readAccelRaw(AccelerationRAW_t *accelRaw) {
    uint8_t buffer[6];
    i2c.readI2C(0x3B, buffer, 6);
    accelRaw->x = (int16_t)((buffer[0] << 8) | buffer[1]);
    accelRaw->y = (int16_t)((buffer[2] << 8) | buffer[3]);
    accelRaw->z = (int16_t)((buffer[4] << 8) | buffer[5]);
}

void Accelerometer::getAcceleration(Acceleration_t *acceleration) {
    readAccelRaw(&accelRaw);
    acceleration->x = (float)(accelRaw.x / ACC_SCALE);
    acceleration->y = (float)(accelRaw.y / ACC_SCALE);
    acceleration->z = (float)(accelRaw.z / ACC_SCALE);
}
