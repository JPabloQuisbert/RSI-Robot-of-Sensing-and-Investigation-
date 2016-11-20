#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

int set_jy1_1;
int set_jy1_2;
int jy1_in1=0;
int jy1_in2=1;
int but=22;

int set_jy2_1;
int set_jy2_2;
int jy2_in1=2;
int jy2_in2=3;

int msg[16];
RF24 radio(9,10);
const uint64_t pipe = 0xABCDABCD71LL;

void setup() {
  // put your setup code here, to run once:
  pinMode(but,INPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe);
  
  set_jy1_1=analogRead(jy1_in1);
  set_jy1_2=analogRead(jy1_in2);
  
  set_jy2_1=analogRead(jy1_in1);
  set_jy2_2=analogRead(jy2_in2);
}
void loop() {
  // put your main code here, to run repeatedly:
  moveMotor();
  moveSM();
  //ifbut()
  bool ok=radio.write(msg, sizeof(msg));
  if (ok){
    Serial.println("ok...");
    for(int i=0;i<6;i++)  Serial.println(msg[i]);  
  }        
  else
    Serial.println("failed");
  delay(500);
}
void moveMotor(){
  int p1=constrain(analogRead(0),set_jy1_1,1023);
  int p2=constrain(analogRead(0),0,set_jy1_1);
  int p3=constrain(analogRead(1),set_jy1_2,1023);
  int p4=constrain(analogRead(1),0,set_jy1_2);
  msg[0]=map(p1,set_jy1_1,1023,0,200);
  msg[1]=map(p2,set_jy1_1,0,0,200);
  msg[2]=map(p3,set_jy1_2,1023,0,200);
  msg[3]=map(p4,set_jy1_2,0,0,200);
}
void moveSM(){
  msg[4]=map(analogRead(2),0,1023,0,180);
  msg[5]=map(analogRead(3)+10,0,1023,0,180);
}
void ifbut(){
  if(digitalRead(but)==1) msg[6]=1;
  else msg[6]=0;    
}  
