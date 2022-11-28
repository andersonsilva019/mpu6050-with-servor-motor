#include "pwm.hpp"

#include <fstream>

Pwm::Pwm(PwmId pwmOutput) {
     /* ID Setting */
     if(pwmOutput > kPWM6_CHANNEL_1 || pwmOutput < kPWM1_CHANNEL_0) {
          return;
     }
     this->pwmOutput = pwmOutput;

     /* Path Setting */
     this->pwmPath = "/sys/class/pwm/pwmchip";
     switch(pwmOutput) {
          case kPWM1_CHANNEL_0: 
               this->pwmPath += "1/pwm-1:0/";
               break;
          case kPWM1_CHANNEL_1:
               this->pwmPath += "1/pwm-1:1/";
               break;
          case kPWM3_CHANNEL_0:
               this->pwmPath += "3/pwm-3:0/";
               break;
          case kPWM3_CHANNEL_1:
               this->pwmPath += "3/pwm-3:1/";
               break;
          case kPWM6_CHANNEL_0:
               this->pwmPath += "6/pwm-6:0/";
               break;
          case kPWM6_CHANNEL_1:
               this->pwmPath += "6/pwm-6:0/";
               break;
     }
}

Pwm::Pwm(PwmId pwmOutput, long period, long dutyCycle, bool enabledStatus = true) : Pwm(pwmOutput) {
     this->setPeriod(period);
     this->setDutyCycle(dutyCycle);
     this->setEnabledStatus(enabledStatus);
}

Pwm::~Pwm(void) {
     this->setEnabledStatus(false);
}


/* Setters */
void Pwm::setEnabledStatus(bool enabledStatus) {
     std::fstream pwmEnableFile;
     pwmEnableFile.open(this->pwmPath + "enable", std::ios::out);
     if(pwmEnableFile) {
          pwmEnableFile << std::to_string(enabledStatus);
          pwmEnableFile.close();
     }
}

void Pwm::setPeriod(long period) {
     std::fstream pwmPeriodFile;
     pwmPeriodFile.open(this->pwmPath + "period", std::ios::out);
     if(pwmPeriodFile) {
          pwmPeriodFile << std::to_string(period);
          pwmPeriodFile.close();
     }
}

void Pwm::setDutyCycle(long dutyCycle) {
     std::fstream pwmDutyCycleFile;
     pwmDutyCycleFile.open(this->pwmPath + "duty_cyle", std::ios::out);
     if(pwmDutyCycleFile) {
          pwmDutyCycleFile << std::to_string(dutyCycle);
          pwmDutyCycleFile.close();
     }
}


/* Getters */
bool Pwm::getEnabledStatus(void) {
     bool returnEnabledStatus = false;
     std::fstream pwmEnableFile;
     pwmEnableFile.open(this->pwmPath + "enable", std::ios::out);
     if(pwmEnableFile) {
          pwmEnableFile >> returnEnabledStatus;
          pwmEnableFile.close();
     }
     return returnEnabledStatus;
}

long Pwm::getPeriod(void) {
     long returnPeriod = 0;
     std::fstream pwmEnableFile;
     pwmEnableFile.open(this->pwmPath + "period", std::ios::out);
     if(pwmEnableFile) {
          pwmEnableFile >> returnPeriod;
          pwmEnableFile.close();
     }
     return returnPeriod;
}

long Pwm::getDutyCycle(void) {
     long returnDutyCyle = 0;
     std::fstream pwmEnableFile;
     pwmEnableFile.open(this->pwmPath + "duty_cyle", std::ios::out);
     if(pwmEnableFile) {
          pwmEnableFile >> returnDutyCyle;
          pwmEnableFile.close();
     }
     return returnDutyCyle;
}

PwmId Pwm::getOutputChannel(void) {
     return this->pwmOutput;
}
