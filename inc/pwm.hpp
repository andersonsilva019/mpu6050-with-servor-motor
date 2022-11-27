#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void set_pwm_period(const char *period, const char *path);

void set_pwm_duty(const char *duty, const char *path);

void set_pwm_enable(const char *enable, const char *path);