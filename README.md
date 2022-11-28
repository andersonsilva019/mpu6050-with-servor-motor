### Projeto final da disciplina de Técnicas de programação para sistemas embarcados II

### Exemplo de inicialização de uma instância do Servo
  
  ```c++
  Servo *ServoMotorBase = Servo(20000000, "/sys/class/pwm/pwmchip1/pwm-1:0")

  ServoMotorBase->init();
  
  ServoMotorBase->setAngle(90);
  ```
