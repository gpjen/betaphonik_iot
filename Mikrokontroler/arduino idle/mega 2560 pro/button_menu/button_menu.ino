#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h>
#include "RTClib.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);
RTC_DS1307 RTC;

#define TB 18
#define TOK 19
#define TN 3

String Jam;
int W_sebelum = 0;
volatile byte Hitung = 1;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();

  Wire.begin();
  RTC.begin();
  RTC.adjust(DateTime(__DATE__, __TIME__)); 


  pinMode(TB, INPUT_PULLUP);
  pinMode(TOK, INPUT_PULLUP);
  pinMode(TN, INPUT_PULLUP);

  lcd.setCursor(0, 0);
  lcd.print("   MEMULAI PROGRAM");
  lcd.setCursor(0, 2);
  lcd.print(String(digitalRead(TB)) + String(digitalRead(TOK)) + String(digitalRead(TN)) );
  delay(5000);
  lcd.clear();

  attachInterrupt(digitalPinToInterrupt(TB), pushTB, FALLING);
  attachInterrupt(digitalPinToInterrupt(TOK), pushTOK, FALLING);
  attachInterrupt(digitalPinToInterrupt(TN), pushTN, FALLING);



}

void loop() {
  DateTime now = RTC.now();
  Jam = String(now.hour()) + ":" + String(now.minute())+ ":" + String(now.second());
  
  
  lcd.setCursor(0, 0);
  lcd.print("LOPING : " + String(Hitung) + "   ");
  Hitung++;
  lcd.setCursor(0, 1);
  lcd.print("Waktu : " + Jam);

  int W_now = millis();

  if (W_now - W_sebelum >= 60000) {
    lcd.noBacklight();
  }

  delay(1000);
}



void pushTB() {
  //  lcd.backlight();
  Hitung = 0;
}

void pushTOK() {
  //  lcd.backlight();
  Hitung = 10000;
}

void pushTN() {
  //  lcd.backlight();
  Hitung = 30000;
}
