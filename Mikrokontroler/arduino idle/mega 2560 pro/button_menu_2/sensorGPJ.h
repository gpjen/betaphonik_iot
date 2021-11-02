//dht................................................................................................

#include <DHT.h>
#define DHTPIN 32
#define TipeDHT DHT22
DHT dht(DHTPIN, TipeDHT);

float humi, temp;



//LUX................................................................................................

#include <BH1750.h>
BH1750 S_cahaya;


//SUHU AIR..........................................................................................

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 33

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensorT(&oneWire);



//TDS RAKIT.........................................................................................

#define ECPin    A0
#define ECGround A1
#define ECPower  A4

int R1        = 1000;
int R_Air     = 25;

float ppm_konfersi  = 0.5;
float Temp_Coef     = 0.019;
float K   = 0.551;
float Temperature = 27;
float EC    = 0;
float EC25  = 0;
int ppm     = 0;

int ppm_input;

float voltage = 0;
float Vin     = 5;
float Vdrop   = 0;
float Rc      = 0;

int hitungPPM( int S) {

  digitalWrite(ECPower, HIGH);
  voltage = analogRead(ECPin);
  voltage = analogRead(ECPin);
  digitalWrite(ECPower, LOW);

  //rubah ke EC
  Vdrop   = (Vin * voltage) / 1024.0;
  Rc      = (Vdrop * R1) / (Vin - Vdrop);
  Rc      = Rc - R_Air;
  EC      = (1 / (Rc * K)) * 1000;

  //Kompensasi EC dengan Temperatur 25 derajat
  EC25    = EC / (1 + Temp_Coef * (S - 25.0));
  int hasilPPM = (EC25) * (ppm_konfersi * 1000);
  return hasilPPM;
}


//Ph................................................................................................

#define PHSensor A6

int samples = 10;
float adc_resolution = 1024.0;



float bacaPH ( ) {

  int Ukur = 0;
  for (int i = 0; i < samples; i++) {
    Ukur += analogRead(PHSensor);
    delay(10);
  }
  float Voltase = 5 / adc_resolution * Ukur / samples;

  return 7 + ((2.5 - Voltase) / 0.18);
}


//PUMP..............................................................................................

#define PumpA 40
#define PumpB 41
