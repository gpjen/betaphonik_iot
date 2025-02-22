
//----------EEPROM-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
String JamON, JamOFF, BacaPROM = readStringFromEEPROM(0);
int ppmMin, ppmMax, Low_nutrisiA, Full_nutrisiA, Low_nutrisiB, Full_nutrisiB, Low_air, Full_air, PHmin, Out_pumpA, Out_pumpB, Out_pumpPhd;
float phMin, phMax, K_TDS, K_PH;

//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
bool pilihnilaiAfull = false,
     pilihnilaiAlow  = false,
     pilihnilaiBfull = false,
     pilihnilaiBlow  = false,
     pilihnilaiCfull = false,
     pilihnilaiClow  = false;


//tombol............................................................................................

#define TB 18
#define TOK 19
#define TN 3
#define buzLed 31


//Ultrasonik................................................................................................................................................................................................

#define EchoA 4
#define TrigerA 5

#define EchoB 6
#define TrigerB 7

#define EchoPhdown 8
#define TrigerPhdown 9


int hitungStok(char x) {

  int Dur, Ja, T_Pin, E_Pin, low, full, hasil;

  if (x == 'A') {
    T_Pin = TrigerA;
    E_Pin = EchoA;
    low   = Low_nutrisiA;
    full  = Full_nutrisiA;
  } else if (x == 'B') {
    T_Pin = TrigerB;
    E_Pin = EchoB;
    low   = Low_nutrisiB;
    full  = Full_nutrisiB;
  } else if (x == 'C') {
    T_Pin = TrigerPhdown;
    E_Pin = EchoPhdown;
    low   = Low_air;
    full  = Full_air;
  }

  digitalWrite(T_Pin, LOW); delayMicroseconds(2);
  digitalWrite(T_Pin, HIGH); delayMicroseconds(10);
  digitalWrite(T_Pin, LOW);
  Dur = pulseIn(E_Pin, HIGH);
  Ja = Dur / 58.2;

  hasil = map(Ja, low, full, 100, 0 );

  if (hasil > 100) {
    hasil = 100;
  } else if (hasil < 1) {
    hasil = 0;
    tone(buzLed, 1000, 5000);
    MenuTampil = 2;
  }

  return hasil;
}



int hitungjarak(char x) {

  int Dur, Ja, T_Pin, E_Pin;

  if (x == 'A') {
    T_Pin = TrigerA;
    E_Pin = EchoA;
  } else if (x == 'B') {
    T_Pin = TrigerB;
    E_Pin = EchoB;
  } else if (x == 'C') {
    T_Pin = TrigerPhdown;
    E_Pin = EchoPhdown;
  }

  digitalWrite(T_Pin, LOW); delayMicroseconds(2);
  digitalWrite(T_Pin, HIGH); delayMicroseconds(10);
  digitalWrite(T_Pin, LOW);
  Dur = pulseIn(E_Pin, HIGH);
  Ja = Dur / 58.2;

  if (Ja > 2000 ){
    Ja = 0;
  }

  return Ja;
}



//PUMP.........................................................................................................

#define PumpAirNutrisi 38
#define PumpPHdown 39
#define PumpA 40
#define PumpB 41

int pompaPHdown( int x ) {

  digitalWrite(PumpPHdown, HIGH);
  delay(x);
  digitalWrite(PumpPHdown, LOW);

}



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
  EC      = (1 / (Rc * K_TDS)) * 1000;

  //Kompensasi EC dengan Temperatur 25 derajat
  EC25    = EC / (1 + Temp_Coef * (S - 25.0));
  int hasilPPM = (EC25) * (ppm_konfersi * 1000);
  return hasilPPM;
}





void tambahNutrisi() {
  int tambahA, tambahB;

  while (ppm <= ppmMin) {
    if (ppm < 500) {
      tambahA = (Out_pumpA * 1000) * 4;
      tambahB = (Out_pumpB * 1000) * 4;
      digitalWrite(PumpA, HIGH); delay(tambahA);
      digitalWrite(PumpA, LOW);delay(3000);
      digitalWrite(PumpB, HIGH); delay(tambahB);
      digitalWrite(PumpB, LOW);

    } else if (ppm < 700) {
      tambahA = (Out_pumpA * 1000) * 3;
      tambahB = (Out_pumpB * 1000) * 3;
      digitalWrite(PumpA, HIGH); delay(tambahA);
      digitalWrite(PumpA, LOW);delay(3000);
      digitalWrite(PumpB, HIGH); delay(tambahB);
      digitalWrite(PumpB, LOW);

    } else if (ppm < 900) {
      tambahA = (Out_pumpA * 1000) * 2;
      tambahB = (Out_pumpB * 1000) * 2;
      digitalWrite(PumpA, HIGH); delay(tambahA);
      digitalWrite(PumpA, LOW);delay(3000);
      digitalWrite(PumpB, HIGH); delay(tambahB);
      digitalWrite(PumpB, LOW);

    } else if (ppm < 1000) {
      tambahA = (Out_pumpA * 1000);
      tambahB = (Out_pumpB  * 1000);
      digitalWrite(PumpA, HIGH); delay(tambahA);
      digitalWrite(PumpA, LOW);delay(3000);
      digitalWrite(PumpB, HIGH); delay(tambahB);
      digitalWrite(PumpB, LOW);
    }

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("     [PPM :" + String(ppm) +"] ");
    lcd.setCursor(0, 1);
    lcd.print("CEK ULANG 3 MNT LAGI");

    for (int i = 1; i <= 300; i++) {
      lcd.setCursor(9, 3);
      lcd.print(i); delay(1000);
    }

    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("     CEK NUTRISI");

    ppm = hitungPPM(S_Air); delay(1000);
    ppm = hitungPPM(S_Air);

    // aturppm#780#1000#1000

    Serial3.println("aturppm#" +
                  String(ppm) + "#" +
                  String(tambahA) + "#" +
                  String(tambahB));

  }

  tone(buzLed, 600, 100); delay(100); tone(buzLed, 1000, 100);
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

  return 7 + ((2.5 - Voltase) / K_PH);
}


// cek aktif.............................................................................................................................................................................................

void cekAKTIF() {

  digitalWrite(PumpAirNutrisi, LOW);

  delay(3000);
  PHmeter = bacaPH();
  sensorT.requestTemperatures();
  S_Air   = sensorT.getTempCByIndex(0);
  LUX     = S_cahaya.readLightLevel();
  humi    = dht.readHumidity();
  temp    = dht.readTemperature();

  ppm     = hitungPPM(S_Air); delay(100);

  stokA   = hitungStok('A'); delay(100);
  stokB   = hitungStok('B'); delay(100);
  stokPhdown = hitungStok('C'); delay(100);


  DateTime now = RTC.now(); delay(100);
  String wkt = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());

  menuSet = false;
  W_cek1j = now.hour();

  Serial3.println("aktif#" +
                  String(wkt) + "#" +
                  String(ppm) + "#" +
                  String(PHmeter) + "#" +
                  String(S_Air) + "#" +
                  String(LUX) + "#" +
                  String(humi) + "#" +
                  String(temp) + "#" +
                  String(stokA) + "#" +
                  String(stokB) + "#" +
                  String(stokPhdown));
}


//istirahat...............................................................................................................................................................................................


void waktuIstirahat() {
  lcd.backlight();
  tone(buzLed, 900, 1000); delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("AKTIFITAS DIHENTIKAN");

  DateTime now = RTC.now(); delay(100);
  String wkt = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());


  digitalWrite(PumpAirNutrisi, HIGH);


  //deet#06:44
  Serial3.println("deet#" + String(wkt));


  for (int i = 10; i >= 0; i--) {
    lcd.setCursor(0, 1);
    lcd.print("   MEMATIKAN DAYA");
    lcd.setCursor(9, 2);
    lcd.print(String(i) + " ");
    delay(1000);
  }
  lcd.clear();



  while (ISTIRAHAT) {

Keluarin :

    DateTime now = RTC.now(); delay(100);
    Jam = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second()) + "   ";
    delay(900);

    lcd.setCursor(0, 0);
    lcd.print(" AYEM SLIPPING BOSS");
    lcd.setCursor(7, 1);
    lcd.print(Jam);
    lcd.setCursor(0, 3);
    lcd.print("On->" + String(jamOn) + ":" + String(menitOn) + " Off->" + String(jamOff) + ":" + String(menitOff));

    if (lampu == true) {
      lcd.backlight();
      lampu = false;
      W_Sebelum = millis();
    }
    if (millis() - W_Sebelum >= 60000) {
      lcd.noBacklight();
      W_Sebelum = millis();
    }
    if ( menuSet == true ) {
      lcd.clear();
      MENUSet();
    }


    //cek waktu ON dan OFF..... Ex : 06:30 - 18:30 ........jamOn, menitOn, jamOff, menitOff

    if (now.hour() > jamOff || now.hour() < jamOn) {
      goto Keluarin;
    } else if (now.hour() == jamOff && now.minute() > menitOff) {
      goto Keluarin;
    } else if (now.hour() == jamOn && now.minute() < menitOn) {
      goto Keluarin;
    } else {
      ISTIRAHAT = false;
      W_cek1j = now.hour();
    }

  }

  lcd.backlight();
  tone(buzLed, 900, 1000); delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("  AKTIFITAS DIMULAI");

  cekAKTIF();

  for (int i = 10; i >= 0; i--) {
    lcd.setCursor(0, 1);
    lcd.print("  MANGAKTIFKAN DAYA");
    lcd.setCursor(9, 2);
    lcd.print(String(i) + " ");
    delay(1000);
  }
  lcd.clear();
}
