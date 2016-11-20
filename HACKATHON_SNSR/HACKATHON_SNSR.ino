#include <SPI.h>
#include <SD.h>
#include <DHT11.h>
#define DHTPIN1 5
#define DHTPIN2 6

#define TIME 500

int adc_MQ1=0;
int adc_MQ2=1;
float voltage1=0.0,Rs1=0.0,voltage2=0.0,Rs2=0.0;
double gas1=0.0,gas2=0.0;

DHT11 dht1(DHTPIN1);
DHT11 dht2(DHTPIN2);
int err;

const int chipSelect = 4;
String dataString = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    return;
  }
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("START");
  writeSD();
  delay(TIME);
}
double readGas1(){
  adc_MQ1 = analogRead(A0);
  voltage1 = adc_MQ1 * (5.0 / 1023.0);
  Rs1=1000*((5-voltage1)/voltage1);
  gas1=0.4091*pow(Rs1/5463, -1.497);
  return gas1;
}
double readGas2(){
  adc_MQ2 = analogRead(A1);
  voltage2 = adc_MQ2 * (5.0 / 1023.0);
  Rs2=1000*((5-voltage2)/voltage2);
  gas2=0.4091*pow(Rs2/5463, -1.497);
  return gas2;
}
float* readHT1(){
  float th[2];
  if((err=dht1.read(th[0],th[1]))==0){
    return th;
  }
}
float* readHT2(){
  float th[2];
  if((err=dht2.read(th[0],th[1]))==0){
    return th;
  }
}
void writeSD(){
  dataString = "";
  float* th1;
  float* th2;
  dataString += String(readGas1());
  dataString += ",";
  Serial.println("1");
  dataString += String(readGas2());
  dataString += ",";
  Serial.println("2");
  th1=readHT1();
  th2=readHT2();
  dataString += String(th1[0]);
  Serial.println(th1[0]);
  Serial.println("3");
  dataString += ",";
  dataString += String(th1[1]);
//  Serial.println(th1[1]);
  dataString += ",";
  Serial.println("5");
  dataString += String(th2[0]);
  dataString += ",";
  Serial.println("5");
  dataString += String(th2[1]);
//  Serial.println(dataString);
  File dataFile = SD.open("data.txt", FILE_WRITE);
  if (dataFile) {
    Serial.println("10");
    dataFile.println(dataString);
    dataFile.close();
  }
}

