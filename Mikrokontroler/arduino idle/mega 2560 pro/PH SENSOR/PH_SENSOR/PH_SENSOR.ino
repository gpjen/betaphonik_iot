#include <Arduino.h>

  int pHSense = A6;
  int samples = 10;
  float adc_resolution = 1024.0;

  void setup()
  {
    Serial.begin(9600);
    delay(100);
  }

  float ph (float voltage) {
    return 7 + ((2.5 - voltage) / 0.18);
  }

  void loop()
  {
    int measurings=0;

    for (int i = 0; i < samples; i++)
    {
        measurings += analogRead(pHSense);
        delay(10);

    }

    float voltage = 5 / adc_resolution * measurings/samples;
    Serial.print("pH : ");
    Serial.println(ph(voltage));
    delay(3000);
  }
