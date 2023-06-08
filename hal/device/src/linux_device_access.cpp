// Copyright (c) 2023 Robarm
// All rights reserved

#include "hal/device/include/linux_device_access.hpp"

#include <fstream>
#include <iostream>

#include "hal/device/include/linux_device_exception.hpp"
#include "utils/common/include/common.hpp"

void robarm::hal::device::LinuxDeviceAccess::writeFile(char const* file_path,
                                                       char const* value) {
  std::fstream device_file(file_path, std::ios::out);
  if (!device_file) {
    throw LinuxDeviceException();
  }
  device_file << value;
}

std::string robarm::hal::device::LinuxDeviceAccess::readFile(
    char const* file_path) {
  std::fstream device_file(file_path, std::ios::in);
  if (!device_file) {
    throw LinuxDeviceException();
  }
  std::string file_value;
  device_file >> file_value;
  return file_value;
}
