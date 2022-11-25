#include "pwm.h"

int main()
{
  // CONFIG-PIN P9.22 pwm
  system("config-pin P9.22 pwm");
  set_pwm_period_p9_22("20000000");
  set_pwm_enable_p9_22("1");

  while (1)
  {
    // Set 90 step (RIGHT)
    set_pwm_duty_p9_22("600000");

    usleep(1000000);

    // Set 0 step (middle)
    set_pwm_duty_p9_22("1500000");

    usleep(1000000);

    // Set 180 (-90) step (LEFT)
    set_pwm_duty_p9_22("2600000");

    usleep(1000000);
  }

  return (0);
}