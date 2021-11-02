


#include <Wire.h>
#include <BH1750.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);


BH1750 S_cahaya;

float LUX;

void setup()
{
  Serial.begin(9600);
  lcd.begin();
  Wire.begin();
  S_cahaya.begin();
  Serial.println(F("BH1750 TESTIIING"));
}

void loop()
{
  LUX = S_cahaya.readLightLevel();
  Serial.print("Cahaya: ");
  Serial.print(LUX);
  Serial.println(" LUX");
  delay(2000);

  lcd.setCursor(0,0);
  lcd.print("   CAHAYA : " + String(LUX));
}
