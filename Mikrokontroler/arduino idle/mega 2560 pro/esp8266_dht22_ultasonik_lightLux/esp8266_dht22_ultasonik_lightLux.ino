#include <BH1750.h>
#include <SPI.h>
#include <Wire.h>

BH1750 sCahaya(0x23);

#define Buzzer      D7


void setup() {

  pinMode(Buzzer, OUTPUT);

  Wire.begin();
  Serial.begin(9600);
  sCahaya.begin();

}
void loop() {

  float lux = sCahaya.readLightLevel();
  Serial.println(lux);
  
  tone(Buzzer, 500);
  delay(500);
  noTone(Buzzer);

  
  delay(3000);

}



//=================FUNGSI=========================

//void StokABMix () {
//  long durasi;
//  digitalWrite(triggerpin, LOW);
//  delayMicroseconds(2);
//  digitalWrite(triggerpin, HIGH);
//  delayMicroseconds(2);
//  digitalWrite(triggerpin, LOW);
//
//  durasi = pulseIn(echopin, HIGH);
//  jarakABMix = (durasi / 2) / 29.1;
//}
