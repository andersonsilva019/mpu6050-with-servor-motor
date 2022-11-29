#ifndef BBB_I2C_HPP
#define BBB_I2C_HPP

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

#define I2C_BUS 2
#define PATH_SIZE 15

class BBB_I2C {
public:
    BBB_I2C();
    BBB_I2C(std::string bus, uint8_t deviceAddress);
    ~BBB_I2C(void);
    void writeI2C(uint8_t registerAddress, uint8_t data);
    void writeBitI2C(uint8_t registerAddress, uint8_t bitNum, uint8_t data);

    void readI2C(uint8_t registerAddress, uint8_t *data, uint8_t length);
    uint8_t readByteI2C(uint8_t registerAddress);
    uint16_t readWordI2C(uint8_t registerAddress);

private:
    uint8_t busAddr;
    std::string path;
    // char* path;
    int i2cFile;
};

#endif // BBB_I2C_HPP