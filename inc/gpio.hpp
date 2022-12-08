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
    void setEdge(std::string edge);
    std::string getDirection(void);
    int getValue(void);

};