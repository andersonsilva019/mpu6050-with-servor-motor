// Copyright (c) 2023 Robarm
// All rights reserved

#include "hal/i2c/include/i2c_peripheral.hpp"

#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "hal/device/include/linux_device_exception.hpp"
#include "hal/i2c/include/i2c_peripheral_exception.hpp"

robarm::hal::i2c::I2C_Peripheral::I2C_Peripheral(std::string const& i2c_path,
                                                 uint8_t peripheral_address)
    : i2c_file_descriptor_(open(i2c_path.c_str(), O_RDWR)),
      peripheral_address_(peripheral_address) {
  if (i2c_file_descriptor_ <= 0) {
    throw device::LinuxDeviceException(i2c_path.c_str());
  }
  uint32_t access_result =
      ioctl(i2c_file_descriptor_, I2C_SLAVE, peripheral_address_);
  if (access_result < 0) {
    throw I2C_PeripheralException(peripheral_address_);
  }
}

robarm::hal::i2c::I2C_Peripheral::~I2C_Peripheral() noexcept {
  close(i2c_file_descriptor_);
}

void robarm::hal::i2c::I2C_Peripheral::writeRegister(uint8_t register_address,
                                                     uint8_t data) {
  uint8_t output_buffer[2];
  output_buffer[0] = register_address;
  output_buffer[1] = data;
  uint32_t write_result =
      write(i2c_file_descriptor_, output_buffer, sizeof(output_buffer));
  if (write_result != sizeof(output_buffer)) {
    throw I2C_PeripheralException(peripheral_address_,
                                  I2C_PeripheralError::kWrite);
  }
}

void robarm::hal::i2c::I2C_Peripheral::readRegister(uint8_t register_address,
                                                    uint8_t* data,
                                                    uint32_t length) {
  uint8_t output_buffer[1];
  output_buffer[0] = register_address;
  uint32_t write_result =
      write(i2c_file_descriptor_, output_buffer, sizeof(output_buffer));
  if (write_result != sizeof(output_buffer)) {
    throw I2C_PeripheralException(peripheral_address_,
                                  I2C_PeripheralError::kWrite);
  }
  uint32_t read_result = read(i2c_file_descriptor_, data, length);
  if (read_result != length) {
    throw I2C_PeripheralException(peripheral_address_,
                                  I2C_PeripheralError::kRead);
  }
}
