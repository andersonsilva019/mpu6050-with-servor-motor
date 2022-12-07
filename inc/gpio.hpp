#pragma once

#include <string>
#include <fstream>
class GPIO {
private:
    std::string gpioPath;
public:
    GPIO(int gpioNumber);
    std::string getGpioPath();
    void setDirection(std::string direction);
    void setValue(std::string value);
    std::string getDirection(void);
    std::string getValue(void);
};