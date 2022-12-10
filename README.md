# Projeto Braço Robótico 🤖

Projeto final da disciplina de "Técnicas de Programação de Sistemas Embarcados II", ou TPSE II, ministrada pelo professor Francisco Hélder Cândido (FHC), na Universidade Federal do Ceará (UFC), campus de Quixadá, apresentado no dia 08 de dezembro de 2022.

O vídeo do projeto encontra-se no <a href="https://www.youtube.com/watch?v=x9LftPXqS44">YouTube</a>.

## O projeto

O projeto teve como proposta desenvolver um braço robótico que pudesse ser controlado por sensores (que poderiam ser acoplados em uma luva ou uma alavanca). 

## O hardware

O braço é constituído por motores servo, que são controlados pelos eixos do sensor acelerômetro (para rotação o eixo Y e para aproximação da garra o eixo X), e pelo sensor de toque (para abrir e fechar a garra). Ainda, são usados LEDs para indicar quando o braço está em funcionamento (de cor vermelho) e um para indicar quando a garra está fechada (de cor branca).

Os sensores enviam os dados para uma EVB, a Beaglebone Black com Linux, que processa os dados à nível de processo (no sistema operacional embarcado) e envia sinais PWM para os motores, e controlam ao nível dos LEDs. O sensor acelerômetro (a MPU6050) está conectado via barramento I2C, enquanto o sensor de toque capacitivo está conectado via GPIO, assim como os LEDs. Os motores estão conectados aos canais de PWM da placa.

## O software

O código foi implementado em C++, para o sistema operacional Linux, embarcado à placa (dessa forma rodando à nível de processo). Cada entidade real (como os motores e os sensores) foram replicadas no código por meio de classes, de forma a organizar o código da melhor maneira possível. 

## Classe Servo
  
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
  
Vale lembrar que esta classe se utiliza da classe PWM.
  
## Classe Accelerometer

Podemos inicializar o I2C passando o barramento desejado para o construtor, ou apenas chamar o construtor padrão, que irá definir o barramento I2C-2. Após isso a função de inicialização deve ser chamada:

```c++
Accelerometer sensor = Accelerometer();
if(!sensor.init()) { ... }
```

Para obter os dados devemos criar uma estrutura do tipo AccelerationRAW_t, onde guardaremos os valores de aceleração, que podemos ler usando a seguinte função:

```c++
AccelerationRAW_t accelerationAxis;
sensor.readAccelRaw(&accelerationAxis);
```

A partir desses valores salvos na struct, que vão de -17000 a +17000, podemos obter a angulação ou/e transcrever um ângulo no servo motor, da seguinte forma: 

```c++
int angleY = map(accelerationAxis.x, -17000, 17000, 180, 0);
```

## Classe GPIO

Para inicializar um pino como GPIO primeiro deve-se passa o número da GPIO para o construtor:

```c++
GPIO nome = GPIO(<numero>);
```

Após isso devemos definir a direção, como uma string "in" ou "out", usando a seguinte função:

```c++
touchSensor.setDirection(<direcao>);
```

Podemos então usar o pino como GPIO, ou seja, entrada ou saída:

```c++
bool touchSensorLevel = touchSensor.getValue();
touchLed.setValue(touchLedLevel);
```

Dessa forma podemos usar a classe GPIO para controlar o sensor de toque capacitivo e os LEDs.

## Classe RoboticArm

Essa classe encapsula quatro motores servo. Podemos inicializar essa classe com o construtor padrão facilmente (irá definir os canais do PWM padrões), apenas chamando:

```c++
RoboticArm roboticArm = RoboticArm();
```

Podemos tambem passar os canais desejados para o construtor, caso seja necessário.

Teremos então quatro motores a nossa disposição, com funções para cada um:

```c++
roboticArm.setRotation(<angle>);
roboticArm.setElevation(<angle>);
roboticArm.setApproximation(<angle>);
roboticArm.setGrip(<angle>);
```
