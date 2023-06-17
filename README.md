# Projeto Braço Robótico 🤖

Projeto final da disciplina de "Técnicas de Programação de Sistemas Embarcados II", ou TPSE II, ministrada pelo professor Francisco Hélder Cândido (FHC), para o curso de Engenharia de Computação, na Universidade Federal do Ceará (UFC), campus de Quixadá, apresentado no dia 08 de dezembro de 2022.

O vídeo do projeto encontra-se no <a href="https://www.youtube.com/watch?v=x9LftPXqS44">YouTube</a>.

## A equipe

A equipe do projeto foi formada pelos seguintes integrantes:

- Anderson Silva: <a href="https://www.linkedin.com/in/anderson-silva-3a3883188/">LinkedIn</a> e <a href="https://github.com/andersonsilva019">Github</a>.
- Pedro Botelho: <a href="https://www.linkedin.com/in/pedrobotelho15/">LinkedIn</a> e <a href="https://github.com/pedrobotelho15">Github</a>.
- Samuel Henrique: <a href="https://www.linkedin.com/in/samuelhenrique15/">LinkedIn</a> e <a href="https://github.com/SamuelLost">Github</a>.

## O projeto

O projeto teve como proposta desenvolver um braço robótico que pudesse ser controlado por sensores (que poderiam ser acoplados em uma luva ou uma alavanca). 

## O hardware

O braço é constituído por motores servo, que são controlados pelos eixos do sensor acelerômetro (para rotação o eixo Y e para aproximação da garra o eixo X), e pelo sensor de toque (para abrir e fechar a garra). Ainda, são usados LEDs para indicar quando o braço está em funcionamento (de cor vermelho) e um para indicar quando a garra está fechada (de cor branca).

Os sensores enviam os dados para uma EVB, a Beaglebone Black com Linux, que processa os dados à nível de processo (no sistema operacional embarcado) e envia sinais PWM para os motores, e controlam ao nível dos LEDs. O sensor acelerômetro (a MPU6050) está conectado via barramento I2C, enquanto o sensor de toque capacitivo está conectado via GPIO, assim como os LEDs. Os motores estão conectados aos canais de PWM da placa.

## O software

O código foi implementado em C++17, para o sistema operacional Linux, embarcado à placa (dessa forma rodando à nível de processo). Cada entidade real (como os motores e os sensores) foram modeladas no código por meio de classes, de forma a organizar o código da melhor maneira possível.

O projeto está dividido em diretórios, de forma a separar as classes em suas funções no código. Esses diretórios são referentes a:

- **HAL (Hardware Abstraction Layer)**: Ou _camada de abstração de hardware_, é onde estão as classes que realizam acesso ao hardware, como acessar um dispositivo para realizar uma escrita ou leitura. Neste diretório estão os componentes de GPIO, I2C e PWM, todos modelados de forma a serem usados como um dispositivo do Linux.
- **Modulos**: Aqui estão os dispositivos reais do projeto modelados por meio de classes: motores servo, botões (que irá ser usado com o sensor de toque), LEDs e o sensor acelerômetro. Essas classes utilizam das classes da HAL para acessar os seus respectivos dispositivos (por meio de algum componente do hardware, como I2C e GPIO). Um módulo importante é o próprio braço robótico (classe RoboticArm), que encapsula quatro motores servo, tal como a garra real.
- **Utilitários**: Funções usadas em vários lugares do código, como funções para mapeamento de valores e para formatação de strings.
- **Testes**: Os componentes de hardware podem ser testados por meio das funções deste diretório, caso seja necessário (como por exemplo ao migrar para outra placa).

Ainda, há uma quarta pasta: a **main**, onde está o código principal da aplicação.

Além da estrutura, o código está seguindo o _code style_ da Google, bem como algumas normas internas próprias: as funções estão em **camelCase**, as classes em **PascalCase** e as variáveis em **snake_case**. Os atributos das classes tem um underline ('_') ao final.

O código está, ainda, organizado em _namespaces_, baseados nessa estrutura de diretórios. O namespace mais geral é **robarm**, então teremos os namespaces do diretório da "função" da classe  (os debatidos anteriormente), são eles: **hal**, **module** e **utils**. Por fim, para discernir entre as classes de mesma função é usado um _namespace_ para o tipo de componente/dispositivo, como **gpio** ou **button**. Seguem alguns exemplos de classes:

- **robarm::hal::i2c::I2C_Component**
- **robarm::hal::pwm::PWM_Component**
- **robarm::module::motor::ServoMotor**

Os utilitários não são classes, mas sim funções:

- **robarm::utils::common::map**
- **robarm::utils::common::format**

As classes seguem um modelo hierárquico, onde a classe **robarm::hal::device::LinuxDevice** é a super-classe. Vale a pena falar de algumas classes aqui:

## Classe ServoMotor
  
Para inicializar o motor informa-se o canal (especifica no enum **PWM_ChannelId**), o ângulo (por padrão é 0, caso não seja informado), e o estado de habilitação do motor (por padrão é true, caso não seja informado):

```c++
robarm::module::motor::ServoMotor motor(<canal>, <angulo>, <habilitado>);
```

Para inicializar um motor de rotação no canal 1 do PWM4, com ângulo de 0° e habilitado por padrão, faz-se :

```c++ 
robarm::module::motor::ServoMotor rotation_servo(robarm::hal::pwm::PWM_ChannelId::kPwm4Channel_1);
```

Para configurar um ângulo deve-se informar um valor no método setAngle().

```c++ 
elevation_servo.setAngle(<angulo>);
```

Por exemplo, para configurar um ângulo de 60° no motor de elevação :

```c++ 
elevation_servo.setAngle(60.0);
```

É perceptível que esta classe se utiliza da classe PWM_Component, da HAL de PWM.

## Classe Accelerometer

Podemos inicializar o Acelerômetro passando o barramento em que está conectado para o construtor. Assim que o construtor é chamado o acelerômetro é inicializado.

```c++
robarm::module::accelerometer::Accelerometer accelerometer(robarm::hal::i2c::I2C_Bus::kBus2);
```

Obtemos os dados por meio da função **getAcceleration**, que retorna uma referência constante à uma estrutura interna da classe: AxisAcceleration, que contém os valores das acelerações nos três eixos.

```c++
robarm::module::accelerometer::AxisAcceleration const& acceleration_values = accelerometer.getAcceleration();
```

A partir desses valores obtidos na struct, que vão de -17000 a +17000, podemos obter a angulação ou/e transcrever um ângulo no servo motor, usando a função **map**: 

```c++ 
double angle_y_ = robarm::utils::common::map(acceleration_values.x, -17000, 17000, 0.0, 180.0);
```

De forma a facilitar o processo de obter o ângulo, pode-se usar a classe invólucro **robarm::module::accelerometer::AccelerometerTiltAngle**, passando um **std::shared_ptr** para um objeto Accelerometer. Dessa forma quando  for obter o ângulo apenas chamar a função **getTiltAngles**, que retorna uma referência constante para struct atributo da classe, com os ângulos já mapeados, de 0° a 180°.

```c++
robarm::module::accelerometer::TiltAngle const& angles = accelerometer_tilt_angle.getTiltAngles();
```

Por fim, vale ressaltar que caso não seja possível ler, escrever, ou acessar o dispositivo, uma exceção será lançada.

## Classes Button e Simple_LED

A utilização de GPIO foi bastante abstraída nesse projeto, com uma grande hierarquia de classes, usada de forma a melhor organizar o código e deixá-lo simples e conciso, apesar de maior. Para inicializar um botão ou um LED, deve-se apenas informar o número do GPIO. Pode se ainda informar se o LED é ativo em baixo (falso por padrão) e se está ligado inicialmente (também falso por padrão).

```c++
robarm::module::led::Simple_LED led(<numero>);
robarm::module::button::Button button(<numero>);
```

Dessa forma podemos verificar se o botão foi pressionado e, por exemplo, ligar o LED:

```c++ 
if(button) {
    led.turnOn();
}
```

## Classe RoboticArm

Essa classe encapsula quatro motores servo. Para inicializá-lo deve apenas passar os canais dos PWM conectados aos motores. Teremos então quatro motores a nossa disposição, com funções para cada um, como as que seguem:

```c++ 
robotic_arm.setRotation(<angle>);
robotic_arm.setElevation(<angle>);
robotic_arm.setApproximation(<angle>);
robotic_arm.openClaw();
```
