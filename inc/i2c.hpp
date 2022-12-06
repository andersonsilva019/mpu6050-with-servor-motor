#pragma once

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

#define I2C_LINUX_BUS0 "/dev/i2c-0"
#define I2C_LINUX_BUS1 "/dev/i2c-1"
#define I2C_LINUX_BUS2 "/dev/i2c-2"

class I2C {
private:
    uint8_t deviceAddress;
    std::string path;
public:
    I2C(std::string bus, uint8_t deviceAddress);
    void writeI2C(uint8_t registerAddress, uint8_t data);
    void writeBitI2C(uint8_t registerAddress, uint8_t data, uint8_t bitNum);
    void writeBitsI2C(uint8_t registerAddress, uint8_t data, uint8_t length, uint8_t startBit);
    void readI2C(uint8_t registerAddress, uint8_t* data, uint8_t length);
    uint8_t readBitI2C(uint8_t registerAddress, uint8_t bitNum);
    uint8_t readBitsI2C(uint8_t registerAddress, uint8_t length, uint8_t startBit);
    uint8_t readByteI2C(uint8_t registerAddress);
    uint16_t readWordI2C(uint8_t registerAddress);
};