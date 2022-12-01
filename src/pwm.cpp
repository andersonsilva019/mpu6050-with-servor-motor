#include "pwm.hpp"

#include <iostream>
#include <fstream>
#include <cstdlib>

Pwm::Pwm(PwmId pwmOutput) {
    /* ID Setting */
    if (pwmOutput > kPWM7_CHANNEL_1 || pwmOutput < kPWM1_CHANNEL_0) {
        return;
    }
    this->pwmOutput = pwmOutput;

    /* Path Setting */
    this->pwmPath = "/sys/class/pwm/pwmchip";
    switch (pwmOutput) {
    case kPWM1_CHANNEL_0:
        this->pwmPath += "1/pwm-1:0/";
        system("config-pin P9.22 pwm");
        break;
    case kPWM1_CHANNEL_1:
        this->pwmPath += "1/pwm-1:1/";
        system("config-pin P9.21 pwm");
        break;
    case kPWM4_CHANNEL_0:
        this->pwmPath += "4/pwm-4:0/";
        system("config-pin P9.14 pwm");
        break;
    case kPWM4_CHANNEL_1:
        this->pwmPath += "4/pwm-4:1/";
        system("config-pin P9.16 pwm");
        break;
    case kPWM7_CHANNEL_0:
        this->pwmPath += "7/pwm-7:0/";
        system("config-pin P8.19 pwm");
        break;
    case kPWM7_CHANNEL_1:
        this->pwmPath += "7/pwm-7:1/";
        system("config-pin P8.13 pwm");
        break;
    }
}

Pwm::Pwm(PwmId pwmOutput, long period, long dutyCycle, bool enabledStatus) : Pwm(pwmOutput) {
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
    if (pwmEnableFile) {

        std::cout << "echo " << std::to_string(enabledStatus) << " >> " << this->pwmPath << "enable" << std::endl;

        pwmEnableFile << std::to_string(enabledStatus);
        pwmEnableFile.close();
    }
}

void Pwm::setPeriod(long period) {
    std::fstream pwmPeriodFile;
    pwmPeriodFile.open(this->pwmPath + "period", std::ios::out);
    if (pwmPeriodFile) {

        std::cout << "echo " << std::to_string(period) << " >> " << this->pwmPath << "period" << std::endl;

        pwmPeriodFile << std::to_string(period);
        pwmPeriodFile.close();
    }
}

void Pwm::setDutyCycle(long dutyCycle) {
    std::fstream pwmDutyCycleFile;
    pwmDutyCycleFile.open(this->pwmPath + "duty_cycle", std::ios::out);
    if (pwmDutyCycleFile) {

        std::cout << "echo " << std::to_string(dutyCycle) << " >> " << this->pwmPath << "duty_cycle" << std::endl;

        pwmDutyCycleFile << std::to_string(dutyCycle);
        pwmDutyCycleFile.close();
    }
}


/* Getters */
bool Pwm::getEnabledStatus(void) {
    bool returnEnabledStatus = false;
    std::fstream pwmEnableFile;
    pwmEnableFile.open(this->pwmPath + "enable", std::ios::out);
    if (pwmEnableFile) {
        pwmEnableFile >> returnEnabledStatus;
        pwmEnableFile.close();
    }
    return returnEnabledStatus;
}

long Pwm::getPeriod(void) {
    long returnPeriod = 0;
    std::fstream pwmEnableFile;
    pwmEnableFile.open(this->pwmPath + "period", std::ios::out);
    if (pwmEnableFile) {
        pwmEnableFile >> returnPeriod;
        pwmEnableFile.close();
    }
    return returnPeriod;
}

long Pwm::getDutyCycle(void) {
    long returnDutyCyle = 0;
    std::fstream pwmEnableFile;
    pwmEnableFile.open(this->pwmPath + "duty_cyle", std::ios::out);
    if (pwmEnableFile) {
        pwmEnableFile >> returnDutyCyle;
        pwmEnableFile.close();
    }
    return returnDutyCyle;
}

PwmId Pwm::getOutputChannel(void) {
    return this->pwmOutput;
}
