#include <IRremote.h>
#include "DHT.h"
#define DHTPIN 12
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int val;
int tempPin = A1;
#define first_key 48703
const int RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
Serial.begin(9600);
irrecv.enableIRIn();
Serial.println(F("DHTxx test!"));
dht.begin();
}

void loop()
{
  TEmrature();
  water_sensor();
  irreceiver_sensor();
  light_sensor();
  DH_sensor();
}

void TEmrature()
{
  val = analogRead(tempPin);
  float mv = ( val/1024.0)*(5000);
  float cel = mv/10;
    float se=cel-477;
  float farh = (se*9)/5 + 32;
  Serial.print("TEMPRATURE = ");
  Serial.print(se);
  Serial.print(" C");
  Serial.println();
  delay(1000);
  }
void water_sensor(){
int sensor=analogRead(A2);
  Serial.println();
Serial.println("water level =");
Serial.print(sensor);
}

void light_sensor(){
  int analogValue = analogRead(A0);
  Serial.print("Analog reading = ");
  Serial.print(analogValue);
  if (analogValue < 10) {
    Serial.println(" - Dark");
  } else if (analogValue < 200) {
    Serial.println(" - Dim");
  } else if (analogValue < 500) {
    Serial.println(" - Light");
  } else if (analogValue < 800) {
    Serial.println(" - Bright");
  } else {
    Serial.println(" - Very bright");
  }
  delay(500);
}

void irreceiver_sensor(){
if (irrecv. decode(&results)){
Serial.println (results.value, HEX); //display EX results
irrecv.resume(); //next value
}
}

void DH_sensor(){
delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
 
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F(" Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("C "));
  Serial.print(f);
  Serial.print(F("F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("C "));
  Serial.print(hif);
  Serial.println(F("F"));
}

  
