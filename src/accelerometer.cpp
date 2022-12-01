#include "accelerometer.hpp"

#define ACC_FULLSCALE           (2)

#define MPU6050_ADDRESS         (int)(0x68) // address pin low (GND), default for InvenSense evaluation board

#if ACC_FULLSCALE == 2
    #define ACC_SCALE           (float)(16384.0)
    #define AFS_SEL             (int)(0x00)
#elif ACC_FULLSCALE == 4
    #define ACC_SCALE           (float)(8192.0)
    #define AFS_SEL             (int)(0x01)
#elif ACC_FULLSCALE == 8
    #define ACC_SCALE           (float)(4096.0)
    #define AFS_SEL             (int)(0x02)
#elif ACC_FULLSCALE == 16
    #define ACC_SCALE           (float)(2048.0)
    #define AFS_SEL             (int)(0x03)
#endif

#define MPU6050_ACCEL_CONFIG    (int)(0x1C)

#define MPU6050_ACCEL_XOUT_H    (int)(0x3B)
#define MPU6050_ACCEL_XOUT_L    (int)(0x3C)

#define MPU6050_ACCEL_YOUT_H    (int)(0x3D)
#define MPU6050_ACCEL_YOUT_L    (int)(0x3E)

#define MPU6050_ACCEL_ZOUT_H    (int)(0x3F)
#define MPU6050_ACCEL_ZOUT_L    (int)(0x40)

#define MPU6050_PWR_MGMT_1      (int)(0x6B)
#define MPU6050_WHO_AM_I        (int)(0x75)

Accelerometer::Accelerometer() : Accelerometer(I2C_LINUX_BUS2) {}

Accelerometer::Accelerometer(std::string bus) : i2c(bus, MPU6050_ADDRESS) {}

bool Accelerometer::init(void) {
    if (testConnection()) {
        setSleepEnabled(false);
        setFullScaleAccelRange(AFS_SEL);
        return true;
    }
    return false;
}

bool Accelerometer::testConnection(void) {
    return ((getDeviceID() == 0b110100) ? true : false);
}

void Accelerometer::setSleepEnabled(bool enabled) {
    i2c.writeBitI2C(MPU6050_PWR_MGMT_1, enabled, 6);
}

void Accelerometer::setFullScaleAccelRange(uint8_t range) {
    i2c.writeBitsI2C(MPU6050_ACCEL_CONFIG, range, 2, 3);
}

uint8_t Accelerometer::getFullScaleAccelRange(void) {
    uint8_t temp = i2c.readByteI2C(MPU6050_ACCEL_CONFIG);
    temp = (temp >> 3) & 0b11;
    switch(temp) {
        case 0:
            return 2;
        case 1:
            return 4;
        case 2:
            return 8;
        case 3:
            return 16;
        default:
            return 0;
    }
}

uint8_t Accelerometer::getDeviceID(void) {
    return i2c.readByteI2C(MPU6050_WHO_AM_I) >> 1;
}

void Accelerometer::readAccelRaw(AccelerationRAW_t *accelRaw) {
    uint8_t buffer[6];
    i2c.readI2C(MPU6050_ACCEL_XOUT_H, buffer, 6);
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
