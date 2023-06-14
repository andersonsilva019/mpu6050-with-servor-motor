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
      peripheral_address_(peripheral_address) {}

robarm::hal::i2c::I2C_Bus robarm::hal::i2c::I2C_Component::getBus() const {
  return bus_;
}

uint8_t robarm::hal::i2c::I2C_Component::getPeripheralAddress() const {
  return peripheral_address_;
}

void robarm::hal::i2c::I2C_Component::writeByte(uint8_t register_address,
                                                uint8_t data) {
  I2C_Peripheral i2c_peripheral(getPath(), peripheral_address_);
  i2c_peripheral.writeRegister(register_address, data);
}

void robarm::hal::i2c::I2C_Component::writeBit(uint8_t register_address,
                                               uint8_t data, uint8_t bit_num) {
  uint8_t b = readByte(register_address);
  b = (data != 0) ? (b | (1 << bit_num)) : (b & ~(1 << bit_num));
  writeByte(register_address, b);
}

void robarm::hal::i2c::I2C_Component::writeBits(uint8_t register_address,
                                                uint8_t data, uint8_t length,
                                                uint8_t start_bit) {
  int8_t b = readByte(register_address);
  uint8_t bits = 1;
  uint8_t i = 0;

  while (i < length - 1) {
    bits = (bits << 1);
    ++bits;
    ++i;
  }

  b &= ~(bits << start_bit);
  b |= (data << start_bit);
  writeByte(register_address, b);
}

void robarm::hal::i2c::I2C_Component::readBlock(uint8_t register_address,
                                                uint8_t* data, uint8_t length) {
  I2C_Peripheral i2c_peripheral(getPath(), peripheral_address_);
  i2c_peripheral.readRegister(register_address, data, length);
}

uint8_t robarm::hal::i2c::I2C_Component::readBit(uint8_t register_address,
                                                 uint8_t bit_num) {
  uint8_t b = readByte(register_address);
  return (b >> bit_num) & 0x01;
}

uint8_t robarm::hal::i2c::I2C_Component::readBits(uint8_t register_address,
                                                  uint8_t length,
                                                  uint8_t start_bit) {
  int8_t temp = readByte(register_address);
  if ((length + start_bit) > 8) {
    // [TODO] Find a better way to deal with this.
    // std::cout << "Error: readBitsI2C cannot read more than 8 bits" <<
    // std::endl;
    exit(1);
  } else if (length == 8) {
    return temp;
  }
  return (temp >> start_bit) & 0xFF;
}

uint8_t robarm::hal::i2c::I2C_Component::readByte(uint8_t register_address) {
  uint8_t data;
  readBlock(register_address, &data, sizeof(data));
  return data;
}

uint16_t robarm::hal::i2c::I2C_Component::readWord(uint8_t register_address) {
  uint8_t data[2];
  readBlock(register_address, data, sizeof(data));
  return (data[0] << 8) | data[1];
}
