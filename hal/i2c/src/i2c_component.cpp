// Copyright (c) 2023 Robarm
// All rights reserved

#include "hal/i2c/include/i2c_component.hpp"

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "hal/i2c/include/i2c_peripheral.hpp"

constexpr char kI2cPath[] = "/dev/i2c-";

robarm::hal::i2c::I2C_Component::I2C_Component(I2C_Bus bus,
                                               uint8_t peripheral_address)
    : LinuxDevice(kI2cPath + std::to_string(static_cast<uint32_t>(bus))),
      bus_(bus),
      peripheral_address_(peripheral_address) {
  I2C_Peripheral i2c_peripheral_test(getPath(), peripheral_address);
}

void robarm::hal::i2c::I2C_Component::writeByte(uint8_t register_address,
                                                uint8_t data) {
  I2C_Peripheral i2c_peripheral(getPath(), peripheral_address_);
  i2c_peripheral.writeRegister(register_address, data);
}

void robarm::hal::i2c::I2C_Component::writeBit(uint8_t register_address,
                                               uint8_t bit_value,
                                               uint8_t bit_number) {
  uint8_t register_value = readByte(register_address);
  register_value = (bit_value) ? (register_value | (1 << bit_number))
                               : (register_value & ~(1 << bit_number));
  writeByte(register_address, register_value);
}

void robarm::hal::i2c::I2C_Component::writeBitField(uint8_t register_address,
                                                    uint8_t bitfield_value,
                                                    uint8_t length,
                                                    uint8_t start_bit) {
  int8_t register_value = readByte(register_address);
  uint8_t bit_mask = ((1U << length) - 1);
  register_value &= ~(bit_mask << start_bit);
  register_value |= (bitfield_value << start_bit);
  writeByte(register_address, register_value);
}

void robarm::hal::i2c::I2C_Component::readBlock(uint8_t register_address,
                                                uint8_t* data, uint8_t length) {
  I2C_Peripheral i2c_peripheral(getPath(), peripheral_address_);
  i2c_peripheral.readRegister(register_address, data, length);
}

uint8_t robarm::hal::i2c::I2C_Component::readBit(uint8_t register_address,
                                                 uint8_t bit_number) {
  uint8_t data = readByte(register_address);
  return (data >> bit_number) & 1;
}

uint8_t robarm::hal::i2c::I2C_Component::readBitField(uint8_t register_address,
                                                      uint8_t length,
                                                      uint8_t start_bit) {
  uint8_t data = readByte(register_address);
  return (data >> start_bit) & ((1U << length) - 1);
}

uint8_t robarm::hal::i2c::I2C_Component::readByte(uint8_t register_address) {
  uint8_t buffer;
  readBlock(register_address, &buffer, sizeof(buffer));
  return buffer;
}

uint16_t robarm::hal::i2c::I2C_Component::readWord(uint8_t register_address) {
  uint8_t buffer[2];
  readBlock(register_address, buffer, sizeof(buffer));
  return (buffer[0] << 8) | buffer[1];
}
