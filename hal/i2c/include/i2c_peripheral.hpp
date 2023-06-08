// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef HAL_I2C_INCLUDE_I2C_PERIPHERAL_HPP_
#define HAL_I2C_INCLUDE_I2C_PERIPHERAL_HPP_

#include <stdexcept>
#include <string>

namespace robarm {
namespace hal {
namespace i2c {

class I2C_Peripheral {
 public:
  I2C_Peripheral(std::string const& i2c_path, uint8_t peripheral_address);
  ~I2C_Peripheral();
  void writeRegister(uint8_t register_address, uint8_t data);
  void readRegister(uint8_t register_address, uint8_t* data, uint32_t lenght);

 private:
  const uint32_t i2c_file_descriptor_;
  const uint8_t peripheral_address_;
};

}  // namespace i2c
}  // namespace hal
}  // namespace robarm

#endif  // HAL_I2C_INCLUDE_I2C_PERIPHERAL_HPP_
