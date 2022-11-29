#include "i2c.hpp"

I2C::I2C(std::string bus, uint8_t deviceAddress) {
    // path = "/dev/i2c-" + std::to_string(I2C_BUS);
    this->path = bus;
    this->deviceAddress = deviceAddress;
    // i2cFile = open(path.c_str(), O_RDWR);
}

void I2C::writeI2C(uint8_t registerAddress, uint8_t data) {
    int i2cFile = open(this->path.c_str(), O_RDWR);
    if (i2cFile < 0) {
        std::cout << "Error: Could not open I2C bus " << this->path << std::endl; 
    }
    if (ioctl(i2cFile, I2C_SLAVE, this->deviceAddress) < 0) {
        printf("Error: Could not open I2C device %x\n", this->deviceAddress); 
    }
    uint8_t buffer[2];
    buffer[0] = registerAddress;
    buffer[1] = data;
    int result = write(i2cFile, buffer, 2);
    if (result != 2) {
        printf("Error: Could not write to I2C device at address %x\n", this->deviceAddress); 
    }
}

void I2C::writeBitI2C(uint8_t registerAddress, uint8_t bitNum, uint8_t data) {
    uint8_t b = readByteI2C(registerAddress);
    b = (data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum));
    writeI2C(registerAddress, b);
}

void I2C::readI2C(uint8_t registerAddress, uint8_t* data, uint8_t length) {
    int i2cFile = open(this->path.c_str(), O_RDWR);
    if (i2cFile < 0) {
        std::cout << "Error: Could not open I2C bus " << this->path << std::endl; 
    }
    if (ioctl(i2cFile, I2C_SLAVE, this->deviceAddress) < 0) {
        printf("Error: Could not open I2C device %x\n", this->deviceAddress); 
    }
    uint8_t buffer[1];
    buffer[0] = registerAddress;

    if (write(i2cFile, buffer, sizeof(buffer)) != sizeof(buffer)) {
        printf("Error: Could not write to I2C device at address %x\n", this->deviceAddress); 

    }

    if (read(i2cFile, data, length) != length) {
        printf("Error: Could not read from I2C device at address %x\n", this->deviceAddress); 
    }
}

uint8_t I2C::readByteI2C(uint8_t registerAddress) {
    uint8_t data;
    readI2C(registerAddress, &data, sizeof(data));
    return data;
}

uint16_t I2C::readWordI2C(uint8_t registerAddress) {
    uint8_t data[2];
    readI2C(registerAddress, data, sizeof(data));
    return (data[0] << 8) | data[1];
}

