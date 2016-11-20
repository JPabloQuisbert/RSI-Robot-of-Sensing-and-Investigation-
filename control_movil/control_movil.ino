#include <Servo.h>

#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

//iniciando el mensaje
int msg[16];

RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

//definicion de pines drivers motores
int PWA=2, enA1=22, enA2=23, PWB=3, enB1=24, enB2=25;
int PWC=4, enC1=26, enC2=27, PWD=5, enD1=28, enD2=29;
//deficion de servomotores
Servo servo1;
Servo servo2;
int pin_servo1=6;
int pin_servo2=7;
//definicion lecturas analogicas joystick
int set_jy1_1;
int set_jy1_2;
int jy1_in1=0;
int jy1_in2=1;

int set_jy2_1;
int set_jy2_2;
int jy2_in1=2;
int jy2_in2=3;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  
  servo1.attach(pin_servo1);
  servo2.attach(pin_servo2);
  /*
  set_jy1_1=analogRead(jy1_in1);
  set_jy1_2=analogRead(jy1_in2);
  
  set_jy2_1=analogRead(jy1_in1);
  set_jy2_2=analogRead(jy2_in2);
  
  pinMode(PWA,OUTPUT);
  pinMode(enA1,OUTPUT);
  pinMode(enA2,OUTPUT);
  
  pinMode(PWB,OUTPUT);
  pinMode(enB1,OUTPUT);
  pinMode(enB2,OUTPUT);
  
  pinMode(PWC,OUTPUT);
  pinMode(enC1,OUTPUT);
  pinMode(enC2,OUTPUT);
  
  pinMode(PWD,OUTPUT);
  pinMode(enD1,OUTPUT);
  pinMode(enD2,OUTPUT);
  */
}

void loop() {
  if (radio.available())
  {
    // bool done = false;  
    int done = radio.read(msg, 16); 
    // lastmsg = msg[0];
    servo1.write(msg[5]);                  
    delay(15); 
  }
}
/*
void sentido_motor1(char direccion, float velocidad){
  switch(direccion){
    case('a'):{
      digitalWrite(enA1,1);
      digitalWrite(enA2,0);
      analogWrite(PWA,velocidad);
      break;
    }
    case('r'):{
      digitalWrite(enA1,0);
      digitalWrite(enA2,1);
      analogWrite(PWA,velocidad);
      break;
    }
  }
}
void sentido_motor2(char direccion, float velocidad){
  switch(direccion){
    case('a'):{
      digitalWrite(enB1,1);
      digitalWrite(enB2,0);
      analogWrite(PWB,velocidad);
      break;
    }
    case('r'):{
      digitalWrite(enB1,0);
      digitalWrite(enB2,1);
      analogWrite(PWB,velocidad);
      break;
    }
  }
}
void sentido_motor3(char direccion, float velocidad){
  switch(direccion){
    case('a'):{
      digitalWrite(enC1,1);
      digitalWrite(enC2,0);
      analogWrite(PWC,velocidad);
      break;
    }
    case('r'):{
      digitalWrite(enC1,0);
      digitalWrite(enC2,1);
      analogWrite(PWC,velocidad);
      break;
    }
  }
}
void sentido_motor4(char direccion, float velocidad){
  switch(direccion){
    case('a'):{
      digitalWrite(enD1,1);
      digitalWrite(enD2,0);
      analogWrite(PWD,velocidad);
      break;
    }
    case('r'):{
      digitalWrite(enD1,0);
      digitalWrite(enD2,1);
      analogWrite(PWD,velocidad);
      break;
    }
  }
}
void control_servo1(int val){    
  servo1.write(val);                  
  delay(15);                           
}
void control_servo2(int val){   
  servo2.write(val);                  
  delay(15);                           
}
*/
