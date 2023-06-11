// Copyright (c) 2023 Robarm
// All rights reserved

#include "module/accelerometer/include/accelerometer.hpp"

#include "hal/i2c/include/i2c_component.hpp"

#define ACC_FULLSCALE  2

constexpr int MPU6050_ADDRESS = 0x68; // address pin low (GND), default for InvenSense evaluation board

#if ACC_FULLSCALE == 2
constexpr float ACC_SCALE = 16384.0;
constexpr int AFS_SEL = 0x00;
#elif ACC_FULLSCALE == 4
constexpr float ACC_SCALE = 8192.0;
constexpr int AFS_SEL = 0x01;
#elif ACC_FULLSCALE == 8
constexpr float ACC_SCALE = 4096.0;
constexpr int AFS_SEL = 0x02;
#elif ACC_FULLSCALE == 16
constexpr float ACC_SCALE = 2048.0;
constexpr int AFS_SEL = 0x03;
#endif

constexpr int MPU6050_ACCEL_CONFIG = 0x1C;
constexpr int MPU6050_ACCEL_CONFIG_BIT = 0x03;
constexpr int MPU6050_ACCEL_CONFIG_LENGTH = 0x02;

constexpr int MPU6050_ACCEL_XOUT_H = 0x3B;
constexpr int MPU6050_ACCEL_XOUT_L = 0x3C;

constexpr int MPU6050_ACCEL_YOUT_H = 0x3D;
constexpr int MPU6050_ACCEL_YOUT_L = 0x3E;

constexpr int MPU6050_ACCEL_ZOUT_H = 0x3;
constexpr int MPU6050_ACCEL_ZOUT_L = 0x40;

constexpr int MPU6050_PWR_MGMT_1 = 0x6B;
constexpr int MPU6050_SLEEP_BIT = 0x06;
constexpr int MPU6050_SLEEP_LENGTH = 0x01;

constexpr int MPU6050_WHO_AM_I = 0x75;
constexpr int MPU6050_WHO_AM_I_BIT = 0x01;
constexpr int MPU6050_WHO_AM_I_LENGTH = 0x06;

robarm::module::accelerometer::Accelerometer::Accelerometer() : Accelerometer(hal::i2c::I2C_Bus::kBus2) {}

robarm::module::accelerometer::Accelerometer::Accelerometer(hal::i2c::I2C_Bus bus) :
    I2C_Component(bus, MPU6050_ADDRESS) {}

robarm::module::accelerometer::Accelerometer::~Accelerometer() {}

bool robarm::module::accelerometer::Accelerometer::init() {
    if (testConnection()) {
        setSleepEnabled(false);
        setFullScaleAccelRange(AFS_SEL);
        return true;
    }
    return false;
}

bool robarm::module::accelerometer::Accelerometer::testConnection() {
    return ((getDeviceID() == 0b110100) ? true : false);
}

void robarm::module::accelerometer::Accelerometer::setSleepEnabled(bool enabled) {
    writeBit(MPU6050_PWR_MGMT_1, enabled, MPU6050_SLEEP_BIT);
}

void robarm::module::accelerometer::Accelerometer::setFullScaleAccelRange(uint8_t range) {
    writeBits(MPU6050_ACCEL_CONFIG, range, MPU6050_ACCEL_CONFIG_LENGTH, MPU6050_ACCEL_CONFIG_BIT);
}

uint8_t robarm::module::accelerometer::Accelerometer::getFullScaleAccelRange() {
    uint8_t temp = readBits(MPU6050_ACCEL_CONFIG, MPU6050_ACCEL_CONFIG_LENGTH, MPU6050_ACCEL_CONFIG_BIT);
    switch (temp) {
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

uint8_t robarm::module::accelerometer::Accelerometer::getDeviceID() {
    return readBits(MPU6050_WHO_AM_I, MPU6050_WHO_AM_I_LENGTH, MPU6050_WHO_AM_I_BIT);
}

void robarm::module::accelerometer::Accelerometer::readAccelRaw(AccelerationRAW_t* accelRaw) {
    uint8_t buffer[6];
    readBlock(MPU6050_ACCEL_XOUT_H, buffer, sizeof(buffer));
    accelRaw->x = (int16_t)((buffer[0] << 8) | buffer[1]);
    accelRaw->y = (int16_t)((buffer[2] << 8) | buffer[3]);
    accelRaw->z = (int16_t)((buffer[4] << 8) | buffer[5]);
}

void robarm::module::accelerometer::Accelerometer::getAcceleration(Acceleration_t* acceleration) {
    readAccelRaw(&this->accelRaw_);
    acceleration->x = this->accelRaw_.x / ACC_SCALE;
    acceleration->y = this->accelRaw_.y / ACC_SCALE;
    acceleration->z = this->accelRaw_.z / ACC_SCALE;
}

float robarm::module::accelerometer::Accelerometer::getAccelerationX() {
    getAcceleration(&this->accel_);
    return this->accel_.x;
}

float robarm::module::accelerometer::Accelerometer::getAccelerationY() {
    getAcceleration(&this->accel_);
    return this->accel_.y;
}

float robarm::module::accelerometer::Accelerometer::getAccelerationZ() {
    getAcceleration(&this->accel_);
    return this->accel_.z;
}