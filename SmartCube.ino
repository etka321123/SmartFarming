#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <WidgetLED.h>
#define BLYNK_PRINT Serial
char auth[] = "1de6eaf808f54be58373aa09ebb447ae"; // bu kodu almalisiniz
SimpleTimer timer;
#define DHTPIN D1
#define DHTTYPE DHT11

const int IN1 = 0;
const int IN2 = 2;
const int IN3 = 14;
const int IN4 = 12;
int ENA = 4;

//const int led =  2;
int humLowTrigger;
DHT dht(DHTPIN, DHTTYPE);
void updateHum(int param);
BLYNK_WRITE(V7) {
updateHum(param.asInt());
}
BLYNK_WRITE(V0)
{
  if(param.asInt()){
    digitalWrite(IN3, HIGH);
    delay(10000);
  } else {
    digitalWrite(IN3,LOW);
  }
}
void Readdata()
{
float h = dht.readHumidity();
float t = dht.readTemperature();
float th = analogRead(A0);
int gbre;
th=map(th, 400 ,1023, 100, 0);
Blynk.virtualWrite(V10, h);
Blynk.virtualWrite(V20, t);
Blynk.virtualWrite(V15, th);
Blynk.virtualWrite(V25, humLowTrigger);
Blynk.virtualWrite(V27, gbre);
//if(gbre == 1)
//{
//  digitalWrite(IN2, HIGH);
//
//Blynk.virtualWrite(V26, 255);
//} else {
//  digitalWrite(IN2, LOW);
//
//Blynk.virtualWrite(V26, 0);
//}
if(th < humLowTrigger) {
digitalWrite(IN2, HIGH);

Blynk.virtualWrite(V26, 255);
} else {
  digitalWrite(IN2, LOW);

Blynk.virtualWrite(V26, 0);
}
}
void updateHum(int param) {
humLowTrigger = param;
}
void setup()
{
Serial.begin(9600);
Blynk.begin(auth, "iPhone", "etka2003");
timer.setInterval(1000,Readdata);
//pinMode(led, 000, Readdata);
dht.begin();
//digitalWrite(led, LOW);
int humLowTrigger = 40;
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
}
void loop()
{
Blynk.run();
timer.run();
}

