// Copyright (c) 2023 Robarm
// All rights reserved

#include "hal/device/include/linux_device.hpp"

robarm::hal::device::LinuxDevice::LinuxDevice(std::string const& path) noexcept
    : path_(path) {}
