// Copyright (c) 2023 Robarm
// All rights reserved

#ifndef HAL_I2C_INCLUDE_I2C_PERIPHERAL_EXCEPTION_HPP_
#define HAL_I2C_INCLUDE_I2C_PERIPHERAL_EXCEPTION_HPP_

#include <stdexcept>
#include <string>

namespace robarm {
namespace hal {
namespace i2c {

enum class I2C_PeripheralError : uint32_t { kAccess, kRead, kWrite };

class I2C_PeripheralException : public std::exception {
 public:
  explicit I2C_PeripheralException(
      uint8_t peripheral_address,
      I2C_PeripheralError error = I2C_PeripheralError::kAccess);
  virtual ~I2C_PeripheralException() noexcept = default;
  char const* what() const noexcept { return message_.c_str(); }

 private:
  std::string parseErrorMessage(uint8_t peripheral_address,
                                I2C_PeripheralError error);

 private:
  std::string message_;
};

}  // namespace i2c
}  // namespace hal
}  // namespace robarm

#endif  // HAL_I2C_INCLUDE_I2C_PERIPHERAL_EXCEPTION_HPP_
