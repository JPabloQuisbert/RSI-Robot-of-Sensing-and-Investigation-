// Sketch de ejemplo para testear el famoso sensor DHT de humedad y temperatura
// Escrito por ladyada, de dominio público
// Modificado por Regata para www.tallerarduino.wordpress.com
 
#include "DHT.h"  //Añadimos la libreria con la cual trabaja nuestro sensor
 
#define DHTPIN 2     // Indicamos el pin donde conectaremos la patilla data de nuestro sensor
 
// Descomenta el tipo de sensor que vas a emplear. En este caso usamos el DHT11
#define DHTTYPE DHT11   // DHT 11 
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
 
// Conecta el pin 1 (el de la izquierda) del sensor a +5V
// Conecta el pin 2 del sensor al pin que has elegido para DHTPIN
// Conecta el pin 4 (el de la derecha) del sensor a GROUND
// Conecta una resistencia de 10K del pin 2 (data) al pin 1 (+5V) del sensor
 
DHT dht(DHTPIN, DHTTYPE);  //Indica el pin con el que trabajamos y el tipo de sensor
int maxh=0, minh=100, maxt=0, mint=100;  //Variables para ir comprobando maximos y minimos
 
void setup() 
{
  //Inicio comunicacion serie para ver los datos en el ordenador
  Serial.begin(9600); 
  //Mensaje de inicio
  Serial.println("Comprobacion sensor DHTxx:");
  //Iniciamos el sensor
  dht.begin();
}
 
void loop() 
{
  // La lectura de la temperatura o de la humedad lleva sobre 250 milisegundos  
  // La lectura del sensor tambien puede estar sobre los 2 segundos (es un sensor muy lento)
  int h = dht.readHumidity();  //Guarda la lectura de la humedad en la variable float h
  int t = dht.readTemperature();  //Guarda la lectura de la temperatura en la variable float t
 
  // Comprobamos si lo que devuelve el sensor es valido, si no son numeros algo esta fallando
  if (isnan(t) || isnan(h)) // funcion que comprueba si son numeros las variables indicadas 
  {
    Serial.println("Fallo al leer del sensor DHT"); //Mostramos mensaje de fallo si no son numeros
  } else {
    //Mostramos mensaje con valores actuales de humedad y temperatura, asi como maximos y minimos de cada uno de ellos
    Serial.print("Humedad relativa: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperatura: "); 
    Serial.print(t);
    Serial.println(" *C");
    //Comprobacion de maximos y minimos de humedad y temperatura
    if (maxh<h)
      maxh=h;
    if (h<minh)
      minh=h;
    if (maxt<t)
      maxt=t;
    if (t<mint)
      mint=t;
    Serial.print("Max: ");
    Serial.print(maxh);
    Serial.print(" % ");
    Serial.print("Min: ");
    Serial.print(minh);
    Serial.print(" %\t");
    Serial.print("Max: ");
    Serial.print(maxt);
    Serial.print(" *C ");
    Serial.print("Min: ");
    Serial.print(mint);
    Serial.println(" *C\n");
  }
  delay(1000);
}
