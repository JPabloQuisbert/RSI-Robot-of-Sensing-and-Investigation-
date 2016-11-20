#include <Servo.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

int msg[16];
RF24 radio(8,10);
const uint64_t pipe = 0xABCDABCD71LL;

int pwmI=3, enI1=2,pwmD=9, enD1=4;

Servo s1;
Servo s2;
int pin_servo1=5;//arriba
int pin_servo2=6;
int poss1=0;
int possant1=0;
int poss2=0;
int possant2=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pwmI,OUTPUT);
  pinMode(enI1,OUTPUT);
  pinMode(pwmD,OUTPUT);
  pinMode(enD1,OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  s1.attach(pin_servo1);
  s2.attach(pin_servo2);
}
void loop() {
  // put your main code here, to run repeatedly:
  if(radio.available()){
    Serial.println("OK");
    radio.read(msg,16);
    for(int i=0;i<6;i++){
      Serial.println(msg[i]);
      switch(i){
        case 0:{
          if(msg[i]>10){
            avanzar(msg[i]);
          }
          break;
        }
        case 1:{
          if(msg[i]>10){
            retroceder(msg[i]);
          }
          break;
        }
        case 2:{
          break;
        }
        case 3:{
          break;
        }
        case 4:{
          moveSM1(msg[4]); 
          break;
        }
        case 5:{
          moveSM2(msg[5]);
          break;
        }
      }
    }    
  }
  delay(100);
}
void moveSM1(int posact1){
  possant1=s1.read();
  if(possant1<posact1){
    for (int i = possant1; i <= posact1; i++ ){
      s1.write(i);
      delay(20);
    }
  }
  else if(possant1>posact1){
    for (int i = possant1; i >= posact1; i-- ){
      s1.write(i);
      delay(20);
    }
  }
}
void moveSM2(int posact2){
  possant2=s2.read();
  if(possant2<posact2){
    for (int i = possant2; i <= posact2; i++ ){
      s2.write(i);
      delay(20);
    }
  }
  else if(possant2>posact2){
    for (int i = possant2; i >= posact2; i-- ){
      s2.write(i);
      delay(20);
    }
  }
}
void avanzar(int pwm){
  analogWrite(pwmI,pwm);
  analogWrite(pwmD,pwm);
  digitalWrite(enI1,HIGH);
  digitalWrite(enD1,LOW);
}
void retroceder(int pwm){
  analogWrite(pwmI,pwm);
  analogWrite(pwmD,pwm);
  digitalWrite(enI1,LOW);
  digitalWrite(enD1,HIGH);
}
