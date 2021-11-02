
#include <Arduino.h>
#include <Wire.h>
#include <BH1750.h>
#include <DHT.h>


#define DHTPIN 32
#define TipeDHT DHT22
#define E_Pin 34 //Echo Pin
#define T_Pin 35 //Trigger Pin

DHT dht(DHTPIN, TipeDHT);
BH1750 S_cahaya;

float LUX, humi, temp;
long Durasi, Jarak, adc_resolution = 1024.0;;
int pHSense = A0, samples = 10;

#include "Sensor.h"
void setup( ) {
  Serial.begin(9600);
  Serial1.begin(115200);

  pinMode(T_Pin, OUTPUT);
  pinMode(E_Pin, INPUT);

  Wire.begin();
  S_cahaya.begin();
  while (isnan(dht.readHumidity()) or isnan(dht.readTemperature())) {
    Serial.println("DHT22 Belum Terhubung");
    delay(2000);
  }

}

void loop() {
  Serial.print(">>");
  Sensor_hcsr04();
  delay(1000);


}
