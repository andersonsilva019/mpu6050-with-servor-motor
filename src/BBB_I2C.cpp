#include "BBB_I2C.hpp"

BBB_I2C::BBB_I2C() {}

BBB_I2C::BBB_I2C(std::string bus, uint8_t deviceAddress) {
    // path = "/dev/i2c-" + std::to_string(I2C_BUS);
    path = bus;
    // i2cFile = open(path.c_str(), O_RDWR);
    i2cFile = open(path.c_str(), O_RDWR);
    if (i2cFile < 0) {
        printf("Error: Could not open I2C bus %d", I2C_BUS);
    }
    if (ioctl(i2cFile, I2C_SLAVE, deviceAddress) < 0) {
        printf("Error: Could not open I2C device at address %d", busAddr);
    }
}

BBB_I2C::~BBB_I2C(void) {
    close(i2cFile);
}

void BBB_I2C::writeI2C(uint8_t registerAddress, uint8_t data) {
    uint8_t buffer[2];
    buffer[0] = registerAddress;
    buffer[1] = data;
    int result = write(i2cFile, buffer, 2);
    if (result != 2) {
        printf("Error: Could not write to I2C device at address %d", busAddr);
    }
}

void BBB_I2C::writeBitI2C(uint8_t registerAddress, uint8_t bitNum, uint8_t data) {
    uint8_t b = readByteI2C(registerAddress);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    writeI2C(registerAddress, b);
}

void BBB_I2C::readI2C(uint8_t registerAddress, uint8_t *data, uint8_t length) {
    uint8_t buffer[1];
    buffer[0] = registerAddress;
    
    if(write(i2cFile, buffer, 1) != 1) {
        printf("Error: Could not write to I2C device");
    }

    if(read(i2cFile, data, length) != length) {
        printf("Error: Could not read from I2C device");
    }
}

uint8_t BBB_I2C::readByteI2C(uint8_t registerAddress) {
    uint8_t data;
    readI2C(registerAddress, &data, sizeof(data));
    return data;
}

uint16_t BBB_I2C::readWordI2C(uint8_t registerAddress) {
    uint8_t data[2];
    readI2C(registerAddress, data, sizeof(data));
    return (data[0] << 8) | data[1];
}

