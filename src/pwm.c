#include "pwm.h"

/*
    Servo A
*/
const char* pwm_period_p9_22 = "/sys/class/pwm/pwmchip1/pwm-1:0/period";
const char* pwm_duty_p9_22 = "/sys/class/pwm/pwmchip1/pwm-1:0/duty_cycle";
const char* pwm_enable_p9_22 = "/sys/class/pwm/pwmchip1/pwm-1:0/enable";

/*
    Servo B
*/
const char* pwm_period_p9_21 = "/sys/class/pwm/pwmchip1/pwm-1:1/period";
const char* pwm_duty_p9_21 = "/sys/class/pwm/pwmchip1/pwm-1:1/duty_cycle";
const char* pwm_enable_p9_21 = "/sys/class/pwm/pwmchip1/pwm-1:1/enable";

void set_pwm_period_p9_22(const char *period)
{
  FILE *fp = fopen(pwm_period_p9_22, "w");
  if (fp == NULL)
  {
    printf("Error opening file %s for writing period value %d");
    exit(1);
  }
  fputs(period, fp);
  fclose(fp);
}

void set_pwm_duty_p9_22(const char *duty)
{
  FILE *fp = fopen(pwm_duty_p9_22, "w");
  if (fp == NULL)
  {
    printf("Error opening file %s for writing duty value %d");
    exit(1);
  }
  fputs(duty, fp);
  fclose(fp);
}

void set_pwm_enable_p9_22(const char *enable)
{
  FILE *fp = fopen(pwm_enable_p9_22, "w");
  if (fp == NULL)
  {
    printf("Error opening file %s for writing enable value %d");
    exit(1);
  }
  fputs(enable, fp);
  fclose(fp);
}

void set_pwm_period_p9_21(const char *period)
{
  FILE *fp = fopen(pwm_period_p9_21, "w");
  if (fp == NULL)
  {
    printf("Error opening file %s for writing period value %d");
    exit(1);
  }
  fputs(period, fp);
  fclose(fp);
}

void set_pwm_duty_p9_21(const char *duty)
{
  FILE *fp = fopen(pwm_duty_p9_21, "w");
  if (fp == NULL)
  {
    printf("Error opening file %s for writing duty value %d");
    exit(1);
  }
  fputs(duty, fp);
  fclose(fp);
}

void set_pwm_enable_p9_21(const char *enable)
{
  FILE *fp = fopen(pwm_enable_p9_21, "w");
  if (fp == NULL)
  {
    printf("Error opening file %s for writing enable value %d");
    exit(1);
  }
  fputs(enable, fp);
  fclose(fp);
}