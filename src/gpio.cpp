#include "gpio.hpp"

#define GPIO_PATH "/sys/class/gpio/gpio"

GPIO::GPIO(int gpioNumber){
  this->gpioPath = GPIO_PATH + std::to_string(gpioNumber) + "/";
}

std::string GPIO::getGpioPath(){
  return this->gpioPath;
}

void GPIO::setDirection(std::string direction){
  std::fstream gpioDirectionFile;
  gpioDirectionFile.open(this->gpioPath + "direction", std::ios::out);
  if (gpioDirectionFile) {
    gpioDirectionFile << direction;
    gpioDirectionFile.close();
  }
}

void GPIO::setValue(std::string value){
  std::fstream gpioValueFile;
  gpioValueFile.open(this->gpioPath + "value", std::ios::out);
  if (gpioValueFile) {
    gpioValueFile << value;
    gpioValueFile.close();
  }
}

void GPIO::setEdge(std::string edge){
  std::fstream gpioEdgeFile;
  gpioEdgeFile.open(this->gpioPath + "edge", std::ios::out);
  if (gpioEdgeFile) {
    gpioEdgeFile << edge;
    gpioEdgeFile.close();
  }
}

std::string GPIO::getDirection(void){
  std::fstream gpioDirectionFile;
  std::string direction;
  gpioDirectionFile.open(this->gpioPath + "direction", std::ios::in);
  if (gpioDirectionFile) {
    gpioDirectionFile >> direction;
    gpioDirectionFile.close();
  }
  return direction;
}

int GPIO::getValue(void){
  std::fstream gpioValueFile;
  std::string value;
  gpioValueFile.open(this->gpioPath + "value", std::ios::in);
  if (gpioValueFile) {
    gpioValueFile >> value;
    gpioValueFile.close();
  }
  return atoi(value.c_str());
}