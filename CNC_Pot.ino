//Incluir Biblioteca Stepper --> Controle do motor de passo
//Incluir Bibliotec Servo --> Controle Servo Motor
#include <Stepper.h>
#include <Servo.h>

//Definir os Pinos
const int X_pin = A0; // Pot em X conectado em AO
const int Y_pin = A1; // Pot em Y conectado em A1 
const int botao_pin = 51; //Pino conectado o botao para o Servo --> Pulldown
const int Servo_pin = 48; //Pino que o Servo está conectado


//Passos para dar uma volta
const int stepsPerRevolution = 20; //MOTOR DE CD

// Criar instancias de motor de Passo  e Servo
Stepper Motor_x(stepsPerRevolution, 12, 11, 10, 9); //Motor X 
Stepper Motor_y(stepsPerRevolution, 2, 3, 4, 5); //Motor Y
Servo Motor_caneta; //Motor Caneta

//Quantos passos irá dar 
int passos = 1; //MAX 250

// Variavel para amarzenar a posicao do servo
int counter = 0;


void setup() {
  Serial.begin(9600);
  Motor_caneta.attach(Servo_pin); //Liga a instancia do Servo com o pino
  pinMode(botao_pin, INPUT);
  pinMode(X_pin, INPUT);
  pinMode(Y_pin, INPUT);
}

void loop() {
  //Controle moviemnto da caneta
  //Variavel para definir o estado do botao
  int buttonState;  

  //le o estado do botao e grava isso
  buttonState = digitalRead(botao_pin);

  //Se o Botao for pressionado, adiciona isso no counter e da um delay --> "Debounce"
  if (buttonState == HIGH) // 
  {
    counter++;
    delay(150);
  }
  if(counter == 0){
    Motor_caneta.write (20);}  // Zero Graus
  else if(counter == 1){
    Motor_caneta.write(90);}
  else if(counter == 2){
    Motor_caneta.write (150); }
  else if(counter == 3){  
    Motor_caneta.write (180);}
  //Caso não for pressionado, retornar o 0 Graus.
  else{
   counter = 0;
  }
  //Controle Motor de Passo 
  int val_x = analogRead(X_pin);
  int val_y = analogRead(Y_pin);

  //Motores Parado caso Joystick esteja no meio 
  if( (val_x > 450) && (val_x < 523) && (val_y > 450) && (val_y < 523)){
    delay(20);
  }
  else{
    //Mover o motor_x em uma direcao
    while (val_x >= 523){
      // Mapear a velocidade para 60 a 120 rpm
      int speed_x = map(val_x, 523, 1023, 60, 120);
      // Define a velocidade do motor
      Motor_x.setSpeed(speed_x);
 
      // Mover o motor em 1 passo
      Motor_x.step(1);
      // Grava informação do Potenciometro
      val_x = analogRead(X_pin);
    }
   //Mover o motor_x na outra direcao
    while (val_x <= 450){
      // Mapear a velocidade para 60 a 120 rpm
      int speed_x = map(val_x, 450, 0, 60, 120);
      // Define a velocidade do motor
      Motor_x.setSpeed(speed_x);
 
      // Mover o motor em 1 passo
      Motor_x.step(-1);
      // Grava informação do Potenciometro
      val_x = analogRead(X_pin);
    }
   }
 //Mover o motor_y em uma direcao
    while (val_y >= 523){
      // Mapear a velocidade para 60 a 120 rpm
      int speed_y = map(val_y, 523, 1023, 60, 120);
      // Define a velocidade do motor
      Motor_y.setSpeed(speed_y);
 
      // Mover o motor em 1 passo
      Motor_y.step(1);
      // Grava informação do Potenciometro
      val_y = analogRead(Y_pin);
    }
   //Mover o motor_y na outra direcao
    while (val_y <= 450){
      // Mapear a velocidade para 60 a 120 rpm
      int speed_y = map(val_y, 450, 0, 60, 120);
      // Define a velocidade do motor
      Motor_y.setSpeed(speed_y);
 
      // Mover o motor em 1 passo
      Motor_y.step(-1);
      // Grava informação do Potenciometro
      val_y = analogRead(Y_pin);
    }
   }
