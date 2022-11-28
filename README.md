### Projeto final da disciplina de Técnicas de programação para sistemas embarcados II

### Exemplo de inicialização de uma instância do Servo
  
  Para inicializar o motor informa-se o canal, o ângulo (por padrão é 0, caso não seja informado), e o estado de habilitação do motor (por padrão é true, caso não seja informado):

  ```c++
  Servo nome = Servo(<canal>, <angulo>, <habilitado>);
  ```

  Para inicializar um motor de rotação no canal 1 do PWM3, com ângulo de 0º e habilitado por padrão, faz-se:

  ```c++
  Servo rotationServo = Servo(kPWM3_CHANNEL_1);
  ```

  Para configurar um ângulo deve-se informar um valor no método setAngle().

  ```c++
  elevationServo.setAngle(<angulo>);
  ```

  Por exemplo, para configurar um ângulo de 60º no motor de elevação:

  ```c++
  elevationServo.setAngle(60);
  ```