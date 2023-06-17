// Copyright (c) 2023 Robarm
// All rights reserved

#include "module/accelerometer/include/accelerometer.hpp"

#include "hal/i2c/include/i2c_component.hpp"
#include "hal/i2c/include/i2c_peripheral_exception.hpp"
#include "module/accelerometer/include/accelerometer_exception.hpp"

constexpr int kAccelerometerPeripheralAddress = 0x68;

enum class AccelerometerRegister : uint8_t {
  kAccelConfig = 0x1C,
  kXoutH = 0x3B,
  kXoutL = 0x3C,
  kYoutH = 0x3D,
  kYoutL = 0x3E,
  kZoutH = 0x3F,
  kZoutL = 0x40,
  kPwrMgmt1 = 0x6B,
  kPwrMgmt2 = 0x6C,
  kWhoAmI = 0x75
};

constexpr uint8_t kAccelerometerDeviceId = 0x34;
constexpr uint8_t kAccelerometerRegisterAccelConfig_FullScaleStartBit = 0x03;
constexpr uint8_t kAccelerometerRegisterAccelConfig_FullScaleLength = 0x02;
constexpr uint8_t kAccelerometerRegisterPwrMgmt1_SleepBit = 0x06;
constexpr uint8_t kAccelerometerRegisterWhoAmI_StartBit = 0x01;
constexpr uint8_t kAccelerometerRegisterWhoAmI_Length = 0x06;

robarm::module::accelerometer::Accelerometer::Accelerometer(
    hal::i2c::I2C_Bus bus, FullScaleRange range, bool is_awake)
    : I2C_Component(bus, kAccelerometerPeripheralAddress),
      range_(range),
      is_awake_(is_awake) {
  if (!isConnected()) {
    throw AccelerometerException(AccelerometerError::kConnection);
  }
  if (is_awake) {
    wakeup();
  }
  setFullScaleRange(range);
}

bool robarm::module::accelerometer::Accelerometer::isConnected() {
  return readDeviceId() == kAccelerometerDeviceId;
}

void robarm::module::accelerometer::Accelerometer::setFullScaleRange(
    FullScaleRange range) {
  range_ = range;
  scale_ = 32768 / (2 << static_cast<uint32_t>(range));
  try {
    writeBitField(static_cast<uint8_t>(AccelerometerRegister::kAccelConfig),
                  static_cast<uint8_t>(range),
                  kAccelerometerRegisterAccelConfig_FullScaleLength,
                  kAccelerometerRegisterAccelConfig_FullScaleStartBit);
  } catch (hal::i2c::I2C_PeripheralException const& e) {
    throw AccelerometerException(static_cast<AccelerometerError>(e.getError()));
  }
}

uint8_t robarm::module::accelerometer::Accelerometer::readDeviceId() {
  try {
    return readBitField(static_cast<uint8_t>(AccelerometerRegister::kWhoAmI),
                        kAccelerometerRegisterWhoAmI_Length,
                        kAccelerometerRegisterWhoAmI_StartBit);
  } catch (hal::i2c::I2C_PeripheralException const& e) {
    throw AccelerometerException(static_cast<AccelerometerError>(e.getError()));
  }
}

void robarm::module::accelerometer::Accelerometer::readAxisAcceleration() {
  uint8_t buffer[6];
  try {
    readBlock(static_cast<int8_t>(AccelerometerRegister::kXoutH), buffer,
              sizeof(buffer));
  } catch (hal::i2c::I2C_PeripheralException const& e) {
    throw AccelerometerException(static_cast<AccelerometerError>(e.getError()));
  }
  acceleration_.x = static_cast<int16_t>((buffer[0] << 8) | buffer[1]);
  acceleration_.y = static_cast<int16_t>((buffer[2] << 8) | buffer[3]);
  acceleration_.z = static_cast<int16_t>((buffer[4] << 8) | buffer[5]);
}

void robarm::module::accelerometer::Accelerometer::writeSleep(bool is_asleep) {
  try {
    writeBit(static_cast<uint8_t>(AccelerometerRegister::kPwrMgmt1), is_asleep,
             kAccelerometerRegisterPwrMgmt1_SleepBit);
  } catch (hal::i2c::I2C_PeripheralException const& e) {
    throw AccelerometerException(static_cast<AccelerometerError>(e.getError()));
  }
}
