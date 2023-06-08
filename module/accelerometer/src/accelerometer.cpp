// Copyright (c) 2023 Robarm
// All rights reserved

#include "module/accelerometer/include/accelerometer.hpp"

#include "hal/i2c/include/i2c_component.hpp"
#include "hal/i2c/include/i2c_peripheral_exception.hpp"


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

constexpr int kAccelerometerRegister_CONFIG = 0x1C;
constexpr int kAccelerometerRegister_CONFIG_BIT = 0x03;
constexpr int kAccelerometerRegister_CONFIG_LENGTH = 0x02;

constexpr int kAccelerometerRegister_XOUT_H = 0x3B;
constexpr int kAccelerometerRegister_XOUT_L = 0x3C;

constexpr int kAccelerometerRegister_YOUT_H = 0x3D;
constexpr int kAccelerometerRegister_YOUT_L = 0x3E;

constexpr int kAccelerometerRegister_ZOUT_H = 0x3;
constexpr int kAccelerometerRegister_ZOUT_L = 0x40;

constexpr int kAccelerometerRegister_PWR_MGMT_1 = 0x6B;
constexpr int kAccelerometerRegister_SLEEP_BIT = 0x06;
constexpr int kAccelerometerRegister_SLEEP_LENGTH = 0x01;

constexpr int kAccelerometerRegister_DEVICE_ID = 0b110100;
constexpr int kAccelerometerRegister_WHO_AM_I = 0x75;
constexpr int kAccelerometerRegister_WHO_AM_I_BIT = 0x01;
constexpr int kAccelerometerRegister_WHO_AM_I_LENGTH = 0x06;

robarm::module::accelerometer::Accelerometer::Accelerometer(hal::i2c::I2C_Bus bus) :
    I2C_Component(bus, MPU6050_ADDRESS) {
    if (!isConnected()) {
        //throw hal::i2c::I2C_PeripheralException("Accelerometer not connected.");
    }
    wakeup();
    setFullScaleAccelRange(AFS_SEL);
}

bool robarm::module::accelerometer::Accelerometer::isConnected() {
    return ((getDeviceID() == kAccelerometerRegister_DEVICE_ID) ? true : false);
}

void robarm::module::accelerometer::Accelerometer::wakeup() {
    writeBit(kAccelerometerRegister_PWR_MGMT_1, false, kAccelerometerRegister_SLEEP_BIT);
}

void robarm::module::accelerometer::Accelerometer::sleep() {
    writeBit(kAccelerometerRegister_PWR_MGMT_1, true, kAccelerometerRegister_SLEEP_BIT);
}

void robarm::module::accelerometer::Accelerometer::setFullScaleAccelRange(uint8_t range) {
    writeBits(kAccelerometerRegister_CONFIG, range, kAccelerometerRegister_CONFIG_LENGTH, kAccelerometerRegister_CONFIG_BIT);
}

uint8_t robarm::module::accelerometer::Accelerometer::getFullScaleAccelRange() {
    uint8_t temp = readBits(kAccelerometerRegister_CONFIG, kAccelerometerRegister_CONFIG_LENGTH, kAccelerometerRegister_CONFIG_BIT);
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
    return readBits(kAccelerometerRegister_WHO_AM_I, kAccelerometerRegister_WHO_AM_I_LENGTH, kAccelerometerRegister_WHO_AM_I_BIT);
}

// void robarm::module::accelerometer::Accelerometer::readAccelRaw(AccelerationRAW_t* accelRaw) {
//     uint8_t buffer[6];
//     readBlock(MPU6050_ACCEL_XOUT_H, buffer, sizeof(buffer));
//     accelRaw->x = (int16_t)((buffer[0] << 8) | buffer[1]);
//     accelRaw->y = (int16_t)((buffer[2] << 8) | buffer[3]);
//     accelRaw->z = (int16_t)((buffer[4] << 8) | buffer[5]);
// }

void robarm::module::accelerometer::Accelerometer::readAxisAcceleration() {
    uint8_t buffer[6];
    readBlock(kAccelerometerRegister_XOUT_H, buffer, sizeof(buffer));
    acceleration_.x = static_cast<int16_t>((buffer[0] << 8) | buffer[1]);
    acceleration_.y = static_cast<int16_t>((buffer[2] << 8) | buffer[3]);
    acceleration_.z = static_cast<int16_t>((buffer[4] << 8) | buffer[5]);
    // acceleration_.x = (int16_t)((buffer[0] << 8) | buffer[1]);
    // acceleration_.y = (int16_t)((buffer[2] << 8) | buffer[3]);
    // acceleration_.z = (int16_t)((buffer[4] << 8) | buffer[5]);
}

robarm::module::accelerometer::AxisAcceleration const& robarm::module::accelerometer::Accelerometer::getAcceleration() {
    readAxisAcceleration();
    return acceleration_;
}