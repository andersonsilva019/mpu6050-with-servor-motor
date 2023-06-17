// Copyright (c) 2023 Robarm
// All rights reserved

#include "hal/device/include/linux_device_exception.hpp"

#include "utils/common/include/common.hpp"

constexpr char kLinuxDeviceExceptionDefaultString[] =
    "Could not access the device.";
constexpr char kLinuxDeviceExceptionFormatStringOne[] =
    "Could not access the device in the path %s.";
constexpr char kLinuxDeviceExceptionFormatStringTwo[] =
    "Could not access the device %s through the given path %s.";

robarm::hal::device::LinuxDeviceException::LinuxDeviceException() noexcept
    : message_(kLinuxDeviceExceptionDefaultString) {}

robarm::hal::device::LinuxDeviceException::LinuxDeviceException(
    char const* path) noexcept
    : message_(
          utils::common::format(kLinuxDeviceExceptionFormatStringOne, path)) {}

robarm::hal::device::LinuxDeviceException::LinuxDeviceException(
    std::string const& message) noexcept
    : message_(message) {}

robarm::hal::device::LinuxDeviceException::LinuxDeviceException(
    char const* device, char const* path) noexcept
    : message_(utils::common::format(kLinuxDeviceExceptionFormatStringTwo,
                                     device, path)) {}
