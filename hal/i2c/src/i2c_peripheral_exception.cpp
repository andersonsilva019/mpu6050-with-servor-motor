// Copyright (c) 2023 Robarm
// All rights reserved

#include "hal/i2c/include/i2c_peripheral_exception.hpp"

constexpr char kI2C_PeripheralExceptionFormatAccess[] = "access";
constexpr char kI2C_PeripheralExceptionFormatRead[] = "read from";
constexpr char kI2C_PeripheralExceptionFormatWrite[] = "write to";
constexpr char kI2C_PeripheralExceptionFormatString[] =
    "Could not %s the I2C peripheral in address %02X.";

#include "utils/common/include/common.hpp"

robarm::hal::i2c::I2C_PeripheralException::I2C_PeripheralException(
    uint8_t peripheral_address, I2C_PeripheralError error)
    : message_(parseErrorMessage(peripheral_address, error)) {}

std::string robarm::hal::i2c::I2C_PeripheralException::parseErrorMessage(
    uint8_t peripheral_address, I2C_PeripheralError error) {
  const char* error_string = nullptr;
  switch (error) {
    default:
    case I2C_PeripheralError::kAccess:
      error_string = kI2C_PeripheralExceptionFormatAccess;
      break;
    case I2C_PeripheralError::kRead:
      error_string = kI2C_PeripheralExceptionFormatRead;
      break;
    case I2C_PeripheralError::kWrite:
      error_string = kI2C_PeripheralExceptionFormatWrite;
      break;
  }
  return utils::common::format(kI2C_PeripheralExceptionFormatString,
                               error_string, peripheral_address);
}
