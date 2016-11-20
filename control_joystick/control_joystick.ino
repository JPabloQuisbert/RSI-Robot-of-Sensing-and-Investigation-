#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

//definicion lecturas analogicas joystick
int set_jy1_1;
int set_jy1_2;
int jy1_in1=0;
int jy1_in2=1;

int set_jy2_1;
int set_jy2_2;
int jy2_in1=2;
int jy2_in2=3;

int msg[16];                             // Array a transmitir
RF24 radio(9,53);                        // Creamos un objeto radio del tipo RF2$
const uint64_t pipe = 0xE8E8F0F0E1LL;    // Usamos este canal

void setup(void){
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);           // Abrir para escribir
  
  set_jy1_1=analogRead(jy1_in1);
  set_jy1_2=analogRead(jy1_in2);
  
  set_jy2_1=analogRead(jy1_in1);
  set_jy2_2=analogRead(jy2_in2);
}
void loop(void)
{
  int p1=constrain(analogRead(0),set_jy1_1,1023);
  int p2=constrain(analogRead(0),0,set_jy1_1);
  
  int p3=constrain(analogRead(1),set_jy1_2,1023);
  int p4=constrain(analogRead(1),0,set_jy1_2);
  /*
  int p5=constrain(analogRead(2),set_jy1_1,1023);
  int p6=constrain(analogRead(2),0,set_jy1_1);
  
  int p7=constrain(analogRead(3),set_jy1_2,1023);
  int p8=constrain(analogRead(3),0,set_jy1_2);
  */
  msg[0]=map(p1,set_jy1_1,1023,0,255);
  msg[1]=map(p2,set_jy1_1,0,0,255);
  msg[2]=map(p3,set_jy1_2,1023,0,255);
  msg[3]=map(p4,set_jy1_2,0,0,255);
  
  msg[4]=map(analogRead(2),0,1023,0,180);
  msg[5]=map(analogRead(3),0,1023,0,180);
 
  Serial.print(msg[0]);
  Serial.print("   ");
  Serial.print(msg[1]);
  Serial.print("   ");
  Serial.print(msg[2]);
  Serial.print("   ");
  Serial.print(msg[3]);
  Serial.print("   ");
  Serial.print(msg[4]);
  Serial.print("   ");
  Serial.println(msg[5]);
  
  radio.write(msg, 16);
}
