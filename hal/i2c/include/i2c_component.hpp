// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef HAL_I2C_INCLUDE_I2C_COMPONENT_HPP_
#define HAL_I2C_INCLUDE_I2C_COMPONENT_HPP_

#include <cstdint>

#include "hal/device/include/linux_device.hpp"

namespace robarm {
namespace hal {
namespace i2c {

enum class I2C_Bus : uint32_t { kBus0, kBus1, kBus2 };

class I2C_Component : protected device::LinuxDevice {
 public:
  I2C_Component(I2C_Bus bus, uint8_t peripheral_address);
  virtual ~I2C_Component() = default;
  I2C_Bus getBus() const noexcept { return bus_; }
  uint8_t getPeripheralAddress() const noexcept { return peripheral_address_; }
  void writeByte(uint8_t register_address, uint8_t data);
  void writeBit(uint8_t register_address, uint8_t bit_value,
                uint8_t bit_number);
  void writeBitField(uint8_t register_address, uint8_t bitfield_value,
                     uint8_t length, uint8_t start_bit);
  void readBlock(uint8_t register_address, uint8_t* data, uint8_t length);
  uint8_t readBit(uint8_t register_address, uint8_t bit_number);
  uint8_t readBitField(uint8_t register_address, uint8_t length,
                       uint8_t start_bit);
  uint8_t readByte(uint8_t register_address);
  std::uint16_t readWord(uint8_t register_address);

 private:
  const I2C_Bus bus_;
  const uint8_t peripheral_address_;
};

}  // namespace i2c
}  // namespace hal
}  // namespace robarm

#endif  // HAL_I2C_INCLUDE_I2C_COMPONENT_HPP_
