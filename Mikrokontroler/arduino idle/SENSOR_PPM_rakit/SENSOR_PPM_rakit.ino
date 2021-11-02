#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 33

int R1        = 1000;
int R_Air     = 25;
int ECPin     = A0;
int ECGround  = A1;
int ECPower   = A4;

const unsigned long jarakWaktu = 3000;
unsigned long waktuSebelum = 0;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensorT(&oneWire);

float ppm_konfersi  = 0.5;
float Temp_Coef     = 0.019;
float K   = 0.551;
float temp;
float Temperature = 27;
float EC    = 0;
float EC25  = 0;
int ppm     = 0;

int ppm_input;

float voltage = 0;
float Vin     = 5;
float Vdrop   = 0;
float Rc      = 0;


void setup() {
  Serial.begin(9600);

  sensorT.begin();

  pinMode(ECPin, INPUT);
  pinMode(ECPower, OUTPUT);
  pinMode(ECGround, OUTPUT);
  digitalWrite(ECGround,LOW);

  delay(100);

  R1 = (R1 + R_Air);
}

void loop() {

  unsigned long waktuNow = millis();

  if (waktuNow - waktuSebelum >= jarakWaktu){
    sensorT.requestTemperatures();
    temp= sensorT.getTempCByIndex(0);

    digitalWrite(ECPower, HIGH);
    voltage = analogRead(ECPin);
    voltage = analogRead(ECPin);
    digitalWrite(ECPower, LOW);
    
    //rubah ke EC
    Vdrop   = (Vin * voltage) / 1024.0;
    Rc      = (Vdrop * R1) / (Vin - Vdrop);
    Rc      = Rc-R_Air;
    EC      = (1/(Rc * K)) * 1000;

    //Kompensasi EC dengan Temperatur 25 derajat
    EC25    = EC / (1+ Temp_Coef * (temp - 25.0));
    ppm = (EC25) * (ppm_konfersi * 1000);

    Serial.print("EC : " + String(EC25) + " mS/cm TDS : " + String(ppm) + " ppm - Temp : " + String(temp) + "*C");
    Serial.println();
    //update waktu

    waktuSebelum = waktuNow;
    
  }

}
