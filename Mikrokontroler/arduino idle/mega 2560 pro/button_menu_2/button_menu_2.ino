#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SPI.h>
#include <jefripunza.h>
#include "RTClib.h"
#include "sensorGPJ.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);
RTC_DS1307 RTC;

#define TB 18
#define TOK 19
#define TN 3
#define buzLed 31


volatile int MenuTampil = 3;
volatile bool lampu = false, menuSet = false;
unsigned long W_Sebelum = 0, W_now, W_cek1m = 0;
String Jam, tgl, jamCek;
float S_Air, PHmeter;
int LUX;

//----------EEPROM----------------------------------------------
String JamON, JamOFF, BacaPROM = readStringFromEEPROM(0);
int ppmMin, ppmMax, Out_pumpA, Out_pumpB, Low_nutrisiA, Full_nutrisiA, Low_nutrisiB, Full_nutrisiB, Low_air, Full_air;
float phMin, phMax;
//--------------------------------------------------------------

void setup() {
  tone(buzLed, 400, 100); delay(200);
  tone(buzLed, 400, 100);
  bacaEEPROM();

  Serial.begin(115200);
  Serial3.begin(9600);
  lcd.begin();
  lcd.backlight();

  Wire.begin();
  RTC.begin();
  RTC.adjust(DateTime(__DATE__, __TIME__));
  S_cahaya.begin();
  sensorT.begin();


  pinMode(TB, INPUT_PULLUP);
  pinMode(TOK, INPUT_PULLUP);
  pinMode(TN, INPUT_PULLUP);
  pinMode(buzLed, OUTPUT);
  pinMode(ECPin, INPUT);
  pinMode(ECPower, OUTPUT);
  pinMode(ECGround, OUTPUT);
  pinMode(PumpA, OUTPUT);
  pinMode(PumpB, OUTPUT);


  digitalWrite(ECGround, LOW);
  digitalWrite(PumpA, LOW);
  digitalWrite(PumpB, LOW);

  attachInterrupt(digitalPinToInterrupt(TB), pushTB, FALLING);
  attachInterrupt(digitalPinToInterrupt(TOK), pushTOK, FALLING);
  attachInterrupt(digitalPinToInterrupt(TN), pushTN, FALLING);

  while (isnan(dht.readHumidity()) or isnan(dht.readTemperature())) {
    lcd.setCursor(0, 0);
    lcd.print("     CEK DHT22");
    delay(2000);
  }

  LUX = S_cahaya.readLightLevel();
  humi = dht.readHumidity();
  temp = dht.readTemperature();
  sensorT.requestTemperatures();
  S_Air = sensorT.getTempCByIndex(0);
  PHmeter = bacaPH();

  R1 = (R1 + R_Air);
  ppm = hitungPPM(S_Air); delay(100);
  ppm = hitungPPM(S_Air);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("   MEMULAI PROGRAM");
  delay(2000);
  lcd.clear();

}

void loop() {


  W_now = millis();
  DateTime now = RTC.now();
  Jam = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
  jamCek = String(now.hour()) + ":" + String(now.minute());
  tgl = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year());


  if (jamCek == "22:35") {

    if (ppm <= ppmMin) {
      tone(buzLed, 1000, 500);
      tambahNutrisi();
    }
  }


  if (lampu == true) {
    lcd.backlight();
    lampu = false;
    W_Sebelum = W_now;
  }
  if (W_now - W_Sebelum >= 120000) {
    lcd.noBacklight();
    W_Sebelum = W_now;
  }


  if ( menuSet == true ) {
    lcd.clear();
    MENUSet();
  }

  if ( MenuTampil == 1) {
    Tampilin1();

  } else if (MenuTampil == 2) {
    Tampilin2();

  } else {
    Tampilin3();

  }

  if (W_now - W_cek1m >= 60000) {
    LUX = S_cahaya.readLightLevel();
    humi = dht.readHumidity();
    temp = dht.readTemperature();

    sensorT.requestTemperatures();
    S_Air = sensorT.getTempCByIndex(0);

    ppm = hitungPPM(S_Air);
    PHmeter = bacaPH();

    tone(buzLed, 900, 100);
    W_cek1m = W_now;
  }

  delay(1000);
}






//-----------------------------MENU SETTING------------------------------------------------------


void MENUSet() {
  while (digitalRead(TOK) == 0) {}
  String OnJam = "", OnDet = "", OffJam = "", OffDet = "";

  for (int i = 0; i <= 2 ; i++) {
    OnJam += JamON[i];
  }
  for (int i = 3; i <= 4 ; i++) {
    OnDet += JamON[i];
  }
  for (int i = 0; i <= 2 ; i++) {
    OffJam += JamOFF[i];
  }
  for (int i = 3; i <= 4 ; i++) {
    OffDet += JamOFF[i];
  }

  int jamOn = string2int(OnJam), detikOn = string2int(OnDet), jamOff = string2int(OffJam), detikOff = string2int(OffDet);



inMenu1:
  if (digitalRead(TB) == 0) {
    while (digitalRead(TB) == 0) {}
    lcd.clear();
    goto inMenu5;
  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
    goto menuPPMmin;
  } else if (digitalRead(TN) == 0) {
    while (digitalRead(TN) == 0) {}
    lcd.clear();
    goto inMenu2;
  }

  lcd.setCursor(0, 0);
  lcd.print("   [ PENGATURAN ]");
  lcd.setCursor(0, 2);
  lcd.print(" Atur Nilai Nutrisi");
  lcd.setCursor(0, 3);
  lcd.print("<B       OK       N>");
  goto inMenu1;

inMenu2:

  if (digitalRead(TB) == 0) {
    while (digitalRead(TB) == 0) {}
    lcd.clear();
    goto inMenu1;
  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
    goto kalibrasiAlow;
  } else if (digitalRead(TN) == 0) {
    while (digitalRead(TN) == 0) {}
    lcd.clear();
    goto inMenu3;
  }
  lcd.setCursor(0, 0);
  lcd.print("   [ PENGATURAN ]");
  lcd.setCursor(0, 2);
  lcd.print("  Kalibrasi Sensor");
  lcd.setCursor(0, 3);
  lcd.print("<B       OK       N>");
  goto inMenu2;

inMenu3:

  if (digitalRead(TB) == 0) {
    while (digitalRead(TB) == 0) {}
    lcd.clear();
    goto inMenu2;
  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
    goto jadwalOnjam;
  } else if (digitalRead(TN) == 0) {
    while (digitalRead(TN) == 0) {}
    lcd.clear();
    goto inMenu4;
  }
  lcd.setCursor(0, 0);
  lcd.print("   [ PENGATURAN ]");
  lcd.setCursor(0, 2);
  lcd.print(" Atur Jadwal On/Off");
  lcd.setCursor(0, 3);
  lcd.print("<B       OK       N>");
  goto inMenu3;

inMenu4:

  if (digitalRead(TB) == 0) {
    while (digitalRead(TB) == 0) {}
    lcd.clear();
    goto inMenu3;
  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
    goto pumpA;
  } else if (digitalRead(TN) == 0) {
    while (digitalRead(TN) == 0) {}
    lcd.clear();
    goto inMenu5;
  }
  lcd.setCursor(0, 0);
  lcd.print("   [ PENGATURAN ]");
  lcd.setCursor(0, 2);
  lcd.print("  Atur Output Pump");
  lcd.setCursor(0, 3);
  lcd.print("<B       OK       N>");
  goto inMenu4;


inMenu5:

  if (digitalRead(TB) == 0) {
    while (digitalRead(TB) == 0) {}
    lcd.clear();
    goto inMenu4;
  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
    goto Keluar;
  } else if (digitalRead(TN) == 0) {
    while (digitalRead(TN) == 0) {}
    lcd.clear();
    goto inMenu1;
  }
  lcd.setCursor(0, 0);
  lcd.print("   [ PENGATURAN ]");
  lcd.setCursor(0, 2);
  lcd.print("     > KELUAR <");
  lcd.setCursor(0, 3);
  lcd.print("<B       OK       N>");
  goto inMenu5;

  //===================SUB MENU NUTRISI==========================================

menuPPMmin:

  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto nutrisiBATAL;
    }

    while (digitalRead(TB) == 0) {
      ppmMin--; if (ppmMin <= 700) {
        ppmMin = 700;
      } lcd.setCursor(11, 0); lcd.print(String(ppmMin) + " "); delay(50);
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    //    lcd.clear();

  } else if (digitalRead(TN) == 0) {
    delay(250);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto menuPPMmax;
    }
    while (digitalRead(TN) == 0) {
      ppmMin++; if (ppmMin >= 1200) {
        ppmMin = 1200;
      } lcd.setCursor(11, 0); lcd.print(String(ppmMin) + " "); delay(50);
    }
  }

  lcd.setCursor(0, 0);
  lcd.print(">PPM MIN : ");
  lcd.setCursor(11, 0);
  lcd.print(ppmMin);

  lcd.setCursor(0, 1);
  lcd.print(" PPM MAX : ");
  lcd.setCursor(11, 1);
  lcd.print(ppmMax);

  lcd.setCursor(0, 2);
  lcd.print(" PH MIN  : ");
  lcd.setCursor(11, 2);
  lcd.print(phMin);

  lcd.setCursor(0, 3);
  lcd.print(" PH MAX  : ");
  lcd.setCursor(11, 3);
  lcd.print(phMax);

  goto menuPPMmin;



menuPPMmax:

  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto menuPPMmin;
    }
    while (digitalRead(TB) == 0) {
      ppmMax--; if (ppmMax <= 1000) {
        ppmMax = 1000;
      } lcd.setCursor(11, 1); lcd.print(ppmMax); delay(50);
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    //    lcd.clear();

  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto menuPHmin;
    }

    while (digitalRead(TN) == 0) {
      ppmMax++; if (ppmMax >= 1700) {
        ppmMax = 1700;
      } lcd.setCursor(11, 1); lcd.print(ppmMax); delay(50);
    }
  }

  lcd.setCursor(0, 0);
  lcd.print(" PPM MIN : ");
  lcd.setCursor(11, 0);
  lcd.print(ppmMin);

  lcd.setCursor(0, 1);
  lcd.print(">PPM MAX : ");
  lcd.setCursor(11, 1);
  lcd.print(ppmMax);

  lcd.setCursor(0, 2);
  lcd.print(" PH MIN  : ");
  lcd.setCursor(11, 2);
  lcd.print(phMin);

  lcd.setCursor(0, 3);
  lcd.print(" PH MAX  : ");
  lcd.setCursor(11, 3);
  lcd.print(phMax);

  goto menuPPMmax;



menuPHmin:

  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto menuPPMmax;
    }
    while (digitalRead(TB) == 0) {
      phMin = phMin - 0.1; if (phMin <= 0.0) {
        phMin = 0.0;
      } lcd.setCursor(11, 2); lcd.print(phMin); delay(150);
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    //    lcd.clear();

  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto menuPHmax;
    }

    while (digitalRead(TN) == 0) {
      phMin = phMin + 0.1; if (phMin >= 5.9) {
        phMin = 5.9;
      } lcd.setCursor(11, 2); lcd.print(phMin); delay(150);
    }
  }

  lcd.setCursor(0, 0);
  lcd.print(" PPM MIN : ");
  lcd.setCursor(11, 0);
  lcd.print(ppmMin);

  lcd.setCursor(0, 1);
  lcd.print(" PPM MAX : ");
  lcd.setCursor(11, 1);
  lcd.print(ppmMax);

  lcd.setCursor(0, 2);
  lcd.print(">PH MIN  : ");
  lcd.setCursor(11, 2);
  lcd.print(phMin);

  lcd.setCursor(0, 3);
  lcd.print(" PH MAX  : ");
  lcd.setCursor(11, 3);
  lcd.print(phMax);

  goto menuPHmin;

menuPHmax:

  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto menuPHmin;
    }
    while (digitalRead(TB) == 0) {
      phMax = phMax - 0.1; if (phMax <= 6.0) {
        phMax = 6.0;
      } lcd.setCursor(11, 3); lcd.print(phMax); delay(150);
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    //    lcd.clear();

  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto nutrisiSIMPAN;
    }

    while (digitalRead(TN) == 0) {
      phMax = phMax + 0.1; if (phMax >= 9.9) {
        phMax = 9.9;
      } lcd.setCursor(11, 3); lcd.print(phMax); delay(150);
    }
  }

  lcd.setCursor(0, 0);
  lcd.print(" PPM MIN : ");
  lcd.setCursor(11, 0);
  lcd.print(ppmMin);

  lcd.setCursor(0, 1);
  lcd.print(" PPM MAX : ");
  lcd.setCursor(11, 1);
  lcd.print(ppmMax);

  lcd.setCursor(0, 2);
  lcd.print(" PH MIN  : ");
  lcd.setCursor(11, 2);
  lcd.print(phMin);

  lcd.setCursor(0, 3);
  lcd.print(">PH MAX  : ");
  lcd.setCursor(11, 3);
  lcd.print(phMax);

  goto menuPHmax;

nutrisiSIMPAN:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto menuPHmax;
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
    simpanEEPROM(); delay(2000);
    lcd.clear();
    goto inMenu1;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto nutrisiBATAL;
    }
  }

  lcd.setCursor(0, 0);
  lcd.print(" PPM MAX : ");
  lcd.setCursor(11, 0);
  lcd.print(ppmMax);

  lcd.setCursor(0, 1);
  lcd.print(" PH MIN  : ");
  lcd.setCursor(11, 1);
  lcd.print(phMin);

  lcd.setCursor(0, 2);
  lcd.print(" PH MAX  : ");
  lcd.setCursor(11, 2);
  lcd.print(phMax);

  lcd.setCursor(0, 3);
  lcd.print(">[ SIMPAN ]");

  goto nutrisiSIMPAN;



nutrisiBATAL:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto nutrisiSIMPAN;
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    bacaEEPROM();
    lcd.clear();
    goto inMenu1;

  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto menuPPMmin;
    }
  }

  lcd.setCursor(0, 0);
  lcd.print(" PH MIN  : ");
  lcd.setCursor(11, 0);
  lcd.print(phMin);

  lcd.setCursor(0, 1);
  lcd.print(" PH MAX  : ");
  lcd.setCursor(11, 1);
  lcd.print(phMax);

  lcd.setCursor(0, 2);
  lcd.print(" [ SIMPAN ]");

  lcd.setCursor(0, 3);
  lcd.print(">[ BATAL/KELUAR ]");

  goto nutrisiBATAL;


  //.......................AKHIR SUB MENU NUTRISI......................................

  //===================SUB MENU KALIBRASI SENSOR========================================
  //Low_nutrisiA , Full_nutrisiA, Low_nutrisiB , Full_nutrisiB, Low_air, Full_air
kalibrasiAlow:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto kalibrasiBATAL;
    }
    while (digitalRead(TB) == 0) {
      Low_nutrisiA--; if (Low_nutrisiA <= 1) {
        Low_nutrisiA = 1;
      } delay(100);
      lcd.setCursor(0, 1); lcd.print("   <" + String(Low_nutrisiA) + "> Cm ");
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}


    lcd.clear();
    goto kalibrasiAfull;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto kalibrasiAfull;
    }
    while ( digitalRead(TN) == 0 ) {
      Low_nutrisiA++; if (Low_nutrisiA >= 40) {
        Low_nutrisiA = 40;
      } delay(100);
      lcd.setCursor(0, 1); lcd.print("   <" + String(Low_nutrisiA) + "> Cm ");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("> Nutrisi A Low");
  lcd.setCursor(0, 1);
  lcd.print("   <" + String(Low_nutrisiA) + "> Cm ");

  lcd.setCursor(0, 2);
  lcd.print("  Nutrisi A Full");
  lcd.setCursor(0, 3);
  lcd.print("   <" + String(Full_nutrisiA) + "> Cm ");

  goto kalibrasiAlow;

kalibrasiAfull:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto kalibrasiAlow;
    }
    while ( digitalRead(TB) == 0 ) {
      Full_nutrisiA--; if (Full_nutrisiA <= 1) {
        Full_nutrisiA = 1;
      } delay(100);
      lcd.setCursor(0, 3); lcd.print("   <" + String(Full_nutrisiA) + "> Cm ");
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}


    lcd.clear();
    goto kalibrasiBlow;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto kalibrasiBlow;
    }
    while ( digitalRead(TN) == 0 ) {
      Full_nutrisiA++; if (Full_nutrisiA >= 40) {
        Full_nutrisiA = 40;
      } delay(100);
      lcd.setCursor(0, 3); lcd.print("   <" + String(Full_nutrisiA) + "> Cm ");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("  Nutrisi A Low");
  lcd.setCursor(0, 1);
  lcd.print("   <" + String(Low_nutrisiA) + "> Cm ");

  lcd.setCursor(0, 2);
  lcd.print("> Nutrisi A Full");
  lcd.setCursor(0, 3);
  lcd.print("   <" + String(Full_nutrisiA) + "> Cm ");

  goto kalibrasiAfull;


kalibrasiBlow:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto kalibrasiAfull;
    }
    while ( digitalRead(TB) == 0 ) {
      Low_nutrisiB--; if (Low_nutrisiB <= 1) {
        Low_nutrisiB = 1;
      } delay(100);
      lcd.setCursor(0, 1); lcd.print("   <" + String(Low_nutrisiB) + "> Cm ");
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}


    lcd.clear();
    goto kalibrasiBfull;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto kalibrasiBfull;
    }
    while ( digitalRead(TN) == 0 ) {
      Low_nutrisiB++; if (Low_nutrisiB >= 40) {
        Low_nutrisiB = 40;
      } delay(100);
      lcd.setCursor(0, 1); lcd.print("   <" + String(Low_nutrisiB) + "> Cm ");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("> Nutrisi B Low");
  lcd.setCursor(0, 1);
  lcd.print("   <" + String(Low_nutrisiB) + "> Cm ");

  lcd.setCursor(0, 2);
  lcd.print("  Nutrisi B Full");
  lcd.setCursor(0, 3);
  lcd.print("   <" + String(Full_nutrisiB) + "> Cm ");

  goto kalibrasiBlow;

kalibrasiBfull:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto kalibrasiBlow;
    }
    while ( digitalRead(TB) == 0 ) {
      Full_nutrisiB--; if (Full_nutrisiB <= 1) {
        Full_nutrisiB = 1;
      } delay(100);
      lcd.setCursor(0, 3); lcd.print("   <" + String(Full_nutrisiB) + "> Cm ");
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}


    lcd.clear();
    goto kalibrasiAirlow;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto kalibrasiAirlow;
    }
    while ( digitalRead(TN) == 0 ) {
      Full_nutrisiB++; if (Full_nutrisiB >= 40) {
        Full_nutrisiB = 40;
      } delay(100);
      lcd.setCursor(0, 3); lcd.print("   <" + String(Full_nutrisiB) + "> Cm ");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("  Nutrisi B Low");
  lcd.setCursor(0, 1);
  lcd.print("   <" + String(Low_nutrisiB) + "> Cm ");

  lcd.setCursor(0, 2);
  lcd.print("> Nutrisi B Full");
  lcd.setCursor(0, 3);
  lcd.print("   <" + String(Full_nutrisiB) + "> Cm ");

  goto kalibrasiBfull;


kalibrasiAirlow:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto kalibrasiBfull;
    }
    while ( digitalRead(TB) == 0 ) {
      Low_air--; if (Low_air <= 1) {
        Low_air = 1;
      } delay(100);
      lcd.setCursor(0, 1); lcd.print("   <" + String(Low_air) + "> Cm ");
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
    goto kalibrasiAirfull;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto kalibrasiAirfull;
    }
    while ( digitalRead(TN) == 0 ) {
      Low_air++; if (Low_air >= 50) {
        Low_air = 50;
      } delay(100);
      lcd.setCursor(0, 1); lcd.print("   <" + String(Low_air) + "> Cm ");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("> Air tandon Low");
  lcd.setCursor(0, 1);
  lcd.print("   <" + String(Low_air) + "> Cm ");

  lcd.setCursor(0, 2);
  lcd.print("  Air tandon Full");
  lcd.setCursor(0, 3);
  lcd.print("   <" + String(Full_air) + "> Cm ");

  goto kalibrasiAirlow;

kalibrasiAirfull:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto kalibrasiAirlow;
    }
    while ( digitalRead(TB) == 0 ) {
      Full_air--; if (Full_air <= 1) {
        Full_air = 1;
      } delay(100);
      lcd.setCursor(0, 3); lcd.print("   <" + String(Full_air) + "> Cm ");
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
    goto kalibrasiSIMPAN;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto kalibrasiSIMPAN;
    }
    while ( digitalRead(TN) == 0 ) {
      Full_air++; if (Full_air >= 50) {
        Full_air = 50;
      } delay(100);
      lcd.setCursor(0, 3); lcd.print("   <" + String(Full_air) + "> Cm ");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("  Air tandon Low");
  lcd.setCursor(0, 1);
  lcd.print("   <" + String(Low_air) + "> Cm ");

  lcd.setCursor(0, 2);
  lcd.print("> Air tandon Full");
  lcd.setCursor(0, 3);
  lcd.print("   <" + String(Full_air) + "> Cm ");

  goto kalibrasiAirfull;



kalibrasiSIMPAN:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto kalibrasiAirfull;
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
    simpanEEPROM();
    lcd.clear();
    goto inMenu2;

  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto kalibrasiBATAL;
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("   <" + String(Low_air) + "> Cm ");

  lcd.setCursor(0, 1);
  lcd.print("  Air tandon Full");
  lcd.setCursor(0, 2);
  lcd.print("   <" + String(Full_air) + "> Cm ");

  lcd.setCursor(0, 3);
  lcd.print("> [ SIMPAN ]");

  goto kalibrasiSIMPAN;



kalibrasiBATAL:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto kalibrasiSIMPAN;
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    bacaEEPROM();
    lcd.clear();
    goto inMenu2;

  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto kalibrasiAlow;
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("  Air tandon Full");
  lcd.setCursor(0, 1);
  lcd.print("   <" + String(Full_air) + "> Cm ");

  lcd.setCursor(0, 2);
  lcd.print("  [ SIMPAN ]");

  lcd.setCursor(0, 3);
  lcd.print("> [ BATAL/KELUAR ]");

  goto kalibrasiBATAL;





  //...................AKHIR SUB KALIBRASI SENSOR......................................



  //===================SUB MENU JADWAL ON OFF========================================

jadwalOnjam:

  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto jadwalBATAL;
    }
    while (digitalRead(TB) == 0) {
      if (jamOn <= 1 ) {
        jamOn = 24;
      } jamOn--; delay(300);
      lcd.setCursor(2, 1); lcd.print("[" + String(jamOn) + "] : " + String(detikOn) + "  ");
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto jadwalOndetik;
    }
    while (digitalRead(TN) == 0) {
      if (jamOn >= 24 ) {
        jamOn = 1;
      } jamOn++; delay(300);
      lcd.setCursor(2, 1); lcd.print("[" + String(jamOn) + "] : " + String(detikOn) + "  ");
    }

  }

  lcd.setCursor(0, 0);
  lcd.print("> Jadwal ON");
  lcd.setCursor(2 , 1);
  lcd.print("[" + String(jamOn) + "] : " + String(detikOn) + "  ");

  lcd.setCursor(0, 2);
  lcd.print("  Jadwal OFF");
  lcd.setCursor(2, 3);
  lcd.print(String(jamOff) + " : " + String(detikOff) + "  ");

  goto jadwalOnjam;


jadwalOndetik:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto jadwalOnjam;
    }
    while (digitalRead(TB) == 0) {
      if (detikOn <= 1 ) {
        detikOn = 60;
      } detikOn--; delay(300);
      lcd.setCursor(2, 1); lcd.print(String(jamOn) + " : [" + String(detikOn) + "]  ");
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}


    lcd.clear();
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto jadwalOffjam;
    }
    while (digitalRead(TN) == 0) {
      if (detikOn >= 60 ) {
        detikOn = 1;
      } detikOn++; delay(300);
      lcd.setCursor(2, 1); lcd.print(String(jamOn) + " : [" + String(detikOn) + "]  ");
    }

  }

  lcd.setCursor(0, 0);
  lcd.print("> Jadwal ON");
  lcd.setCursor(2, 1);
  lcd.print(String(jamOn) + " : [" + String(detikOn) + "]  ");

  lcd.setCursor(0, 2);
  lcd.print("  Jadwal OFF");
  lcd.setCursor(2, 3);
  lcd.print(String(jamOff) + " : " + String(detikOff) + "  ");

  goto jadwalOndetik;


jadwalOffjam:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto jadwalOndetik;
    }
    while (digitalRead(TB) == 0) {
      if (jamOff <= 1 ) {
        jamOff = 24;
      } jamOff--; delay(300);
      lcd.setCursor(2, 3); lcd.print("[" + String(jamOff) + "] : " + String(detikOff) + "  ");
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto jadwalOffdetik;
    }
    while (digitalRead(TN) == 0) {
      if (jamOff >= 24 ) {
        jamOff = 1;
      } jamOff++; delay(300);
      lcd.setCursor(2, 3); lcd.print("[" + String(jamOff) + "] : " + String(detikOff) + "  ");
    }

  }

  lcd.setCursor(0, 0);
  lcd.print("  Jadwal ON");
  lcd.setCursor(2, 1);
  lcd.print(String(jamOn) + " : " + String(detikOn) + "  ");

  lcd.setCursor(0, 2);
  lcd.print("> Jadwal OFF");
  lcd.setCursor(2, 3);
  lcd.print("[" + String(jamOff) + "] : " + String(detikOff) + "  ");

  goto jadwalOffjam;



jadwalOffdetik:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto jadwalOffjam;
    }
    while (digitalRead(TB) == 0) {
      if (detikOff <= 1 ) {
        detikOff = 60;
      } detikOff--; delay(300);
      lcd.setCursor(2, 3); lcd.print(String(jamOff) + " : [" + String(detikOff) + "]  ");
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto jadwalSIMPAN;
    }
    while (digitalRead(TN) == 0) {
      if (detikOff >= 60 ) {
        detikOff = 1;
      } detikOff++; delay(300);
      lcd.setCursor(2, 3); lcd.print(String(jamOff) + " : [" + String(detikOff) + "]  ");
    }

  }

  lcd.setCursor(0, 0);
  lcd.print("  Jadwal ON");
  lcd.setCursor(2, 1);
  lcd.print(String(jamOn) + " : " + String(detikOn) + "  ");

  lcd.setCursor(0, 2);
  lcd.print("> Jadwal OFF");
  lcd.setCursor(2, 3);
  lcd.print(String(jamOff) + " : [" + String(detikOff) + "]  ");

  goto jadwalOffdetik;


jadwalSIMPAN:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto jadwalOffdetik;
    }
  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {} lcd.clear();
    JamON = String(jamOn) + ":" + String(detikOn);
    JamOFF = String(jamOff) + ":" + String(detikOff);
    simpanEEPROM(); delay(2000); lcd.clear();
    goto inMenu3;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto jadwalBATAL;
    }
  }

  lcd.setCursor(2, 0);
  lcd.print(String(jamOn) + " : " + String(detikOn) + "  ");
  lcd.setCursor(0, 1);
  lcd.print("  Jadwal OFF");
  lcd.setCursor(2, 2);
  lcd.print(String(jamOff) + " : [" + String(detikOff) + "]  ");
  lcd.setCursor(0, 3);
  lcd.print("> [ SIMPAN ]");

  goto jadwalSIMPAN;


jadwalBATAL:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto jadwalSIMPAN;
    }
  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {} bacaEEPROM(); lcd.clear();
    goto inMenu3;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto jadwalOnjam;
    }
  }
  lcd.setCursor(0, 0);
  lcd.print("  Jadwal OFF");
  lcd.setCursor(2, 1);
  lcd.print(String(jamOff) + " : [" + String(detikOff) + "]  ");
  lcd.setCursor(0, 2);
  lcd.print("  [ SIMPAN ]");
  lcd.setCursor(0, 3);
  lcd.print("> [ BATAL/Keluar ]");

  goto jadwalBATAL;


  //...................AKHIR SUB MENU JADWAL ON OFF......................................


  //===================SUB MENU ATUR PUMP========================================


pumpA:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto pumpBATAL;
    }
    while (digitalRead(TB) == 0) {
      Out_pumpA--;
      if (Out_pumpA <= 200) {
        Out_pumpA = 200; delay(100);
      }
      lcd.setCursor(0, 0); lcd.print(">PUMP A : " + String(Out_pumpA) + " detik ");
    }
  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto pumpB;
    }
    while (digitalRead(TN) == 0) {
      Out_pumpA++;
      if (Out_pumpA >= 999) {
        Out_pumpA = 999; delay(100);
      }
      lcd.setCursor(0, 0); lcd.print(">PUMP A : " + String(Out_pumpA) + " detik ");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print(">PUMP A : " + String(Out_pumpA) + " detik ");
  lcd.setCursor(0, 1);
  lcd.print(" PUMP B : " + String(Out_pumpB) + " detik ");

  lcd.setCursor(0, 2);
  lcd.print(" [ SIMPAN ]");
  lcd.setCursor(0, 3);
  lcd.print(" [ BATAL/Keluar ]");

  goto pumpA;

pumpB:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto pumpA;
    }
    while (digitalRead(TB) == 0) {
      Out_pumpB--;
      if (Out_pumpB <= 200) {
        Out_pumpB = 200; delay(100);
      }
      lcd.setCursor(0, 1); lcd.print(">PUMP B : " + String(Out_pumpB) + " detik ");
    }
  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto pumpSIMPAN;
    }
    while (digitalRead(TN) == 0) {
      Out_pumpB++;
      if (Out_pumpB >= 999) {
        Out_pumpB = 999; delay(100);
      }
      lcd.setCursor(0, 1); lcd.print(">PUMP B : " + String(Out_pumpB) + " detik ");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print(" PUMP A : " + String(Out_pumpA) + " detik ");
  lcd.setCursor(0, 1);
  lcd.print(">PUMP B : " + String(Out_pumpB) + " detik ");

  lcd.setCursor(0, 2);
  lcd.print(" [ SIMPAN ]");
  lcd.setCursor(0, 3);
  lcd.print(" [ BATAL/Keluar ]");

  goto pumpB;





pumpSIMPAN:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto pumpB;
    }
  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {} lcd.clear();
    simpanEEPROM(); delay(2000); lcd.clear();
    goto inMenu4;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto pumpBATAL;
    }
  }
  lcd.setCursor(0, 0);
  lcd.print(" PUMP A : " + String(Out_pumpA) + " detik ");
  lcd.setCursor(0, 1);
  lcd.print(" PUMP B : " + String(Out_pumpB) + " detik ");

  lcd.setCursor(0, 2);
  lcd.print(">[ SIMPAN ]");
  lcd.setCursor(0, 3);
  lcd.print(" [ BATAL/Keluar ]");

  goto pumpSIMPAN;


pumpBATAL:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto pumpSIMPAN;
    }
  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    bacaEEPROM(); lcd.clear();
    goto inMenu4;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto pumpA;
    }
  }
  lcd.setCursor(0, 0);
  lcd.print(" PUMP A : " + String(Out_pumpA) + " detik ");
  lcd.setCursor(0, 1);
  lcd.print(" PUMP B : " + String(Out_pumpB) + " detik ");

  lcd.setCursor(0, 2);
  lcd.print(" [ SIMPAN ]");
  lcd.setCursor(0, 3);
  lcd.print(">[ BATAL/Keluar ]");

  goto pumpBATAL;


  //...................AKHIR SUB MENU ATUR PUMP......................................




Keluar:
  //  interrupts();
  delay(100);
  menuSet = false;

}



//------------------------------TOMBOL INTERUP--------------------------------------------

void pushTB() {
  lampu = true;
  if (MenuTampil == 3) {
    MenuTampil = 2;
  } else if (MenuTampil == 2) {
    MenuTampil = 1;
  } else if (MenuTampil == 1) {
    MenuTampil = 3;
  }
}

void pushTOK() {
  lampu = true;
  menuSet = true;
}

void pushTN() {
  lampu = true;
  if (MenuTampil == 3) {
    MenuTampil = 1;
  } else if (MenuTampil == 1) {
    MenuTampil = 2;
  } else if (MenuTampil == 2) {
    MenuTampil = 3;
  }
}

//-----------------------------------MENU TAMPIL----------------------------------------------------


void Tampilin1() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("     [ SENSOR ]");

  lcd.setCursor(0, 1);
  lcd.print("Ppm:" + String(ppm));
  lcd.setCursor(11, 1);
  lcd.print("Ph :" + String(PHmeter));

  lcd.setCursor(0, 2);
  lcd.print("S a:" + String(S_Air));
  lcd.setCursor(11, 2);
  lcd.print("Lux:" + String(LUX));

  lcd.setCursor(0, 3);
  lcd.print("S u:" + String(temp));
  lcd.setCursor(11, 3);
  lcd.print("Kel:" + String(humi) );

}
void Tampilin2() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nutrisi A : 30 % ");

  lcd.setCursor(0, 1);
  lcd.print("Nutrisi B : 30 % ");

  lcd.setCursor(0, 2);
  lcd.print("Air Tandon : 80 % ");
}
void Tampilin3() {
  lcd.clear();

  lcd.setCursor(5, 0);
  lcd.print(tgl + "  ");
  lcd.setCursor(6, 1);
  lcd.print(Jam + "  ");

  lcd.setCursor(0, 3);
  lcd.print("[B]   [Seting]   [N]");


}



void bacaEEPROM() {

  //11#22#33#44#55#66#77#88#99#1010#1111#1212#1313#1414

  JamON         = splitText(BacaPROM, '#', 0);
  JamOFF        = splitText(BacaPROM, '#', 1);
  ppmMin        = string2int(splitText(BacaPROM, '#', 2));
  ppmMax        = string2int(splitText(BacaPROM, '#', 3));

  String TphMin         = splitText(BacaPROM, '#', 4);
  String TphMax         = splitText(BacaPROM, '#', 5);

  phMin         = TphMin.toFloat();
  phMax         = TphMax.toFloat();
  Out_pumpA     = string2int(splitText(BacaPROM, '#', 6));
  Out_pumpB     = string2int(splitText(BacaPROM, '#', 7));
  Low_nutrisiA  = string2int(splitText(BacaPROM, '#', 8));
  Full_nutrisiA = string2int(splitText(BacaPROM, '#', 9));
  Low_nutrisiB  = string2int(splitText(BacaPROM, '#', 10));
  Full_nutrisiB = string2int(splitText(BacaPROM, '#', 11));
  Low_air       = string2int(splitText(BacaPROM, '#', 12));
  Full_air      = string2int(splitText(BacaPROM, '#', 13));

}

void simpanEEPROM() {

  //11#22#33#44#55#66#77#88#99#1010#1111#1212#1313#1414

  lcd.setCursor(0, 2);
  lcd.print("      MENYIMPAN ");

  String Simpan = String(JamON) + '#' +
                  String(JamOFF) + '#' +
                  String(ppmMin) + '#' +
                  String(ppmMax) + '#' +
                  String(phMin) + '#' +
                  String(phMax) + '#' +
                  String(Out_pumpA) + '#' +
                  String(Out_pumpB) + '#' +
                  String(Low_nutrisiA) + '#' +
                  String(Full_nutrisiA) + '#' +
                  String(Low_nutrisiB) + '#' +
                  String(Full_nutrisiB) + '#' +
                  String(Low_air) + '#' +
                  String(Full_air);

  writeStringToEEPROM(0, Simpan);
  BacaPROM = readStringFromEEPROM(0);
  bacaEEPROM();
  lcd.clear();
  lcd.setCursor(0, 2);
  lcd.print("      DISIMPAN "); \
  tone(buzLed, 1000, 80);


}




void tambahNutrisi() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" BOOSTING NUTRISISI");
  bool cek = true;

  while (cek) {
    if (ppm < 500) {
      lcd.setCursor(0, 2);
      lcd.print("     KATEGORI 4");
      digitalWrite(PumpA, HIGH); delay(Out_pumpA * 4);
      digitalWrite(PumpA, LOW);
      digitalWrite(PumpB, HIGH); delay(Out_pumpB * 4);
      digitalWrite(PumpB, LOW);
    } else if (ppm < 700) {
      lcd.setCursor(0, 2);
      lcd.print("     KATEGORI 3");
      digitalWrite(PumpA, HIGH); delay(Out_pumpA * 3);
      digitalWrite(PumpA, LOW);
      digitalWrite(PumpB, HIGH); delay(Out_pumpB * 3);
      digitalWrite(PumpB, LOW);
    } else if (ppm < 900) {
      lcd.setCursor(0, 2);
      lcd.print("     KATEGORI 2");
      digitalWrite(PumpA, HIGH); delay(Out_pumpA * 2);
      digitalWrite(PumpA, LOW);
      digitalWrite(PumpB, HIGH); delay(Out_pumpB * 2);
      digitalWrite(PumpB, LOW);
    } else if (ppm < 1000) {
      lcd.setCursor(0, 2);
      lcd.print("     KATEGORI 1");
      digitalWrite(PumpA, HIGH); delay(Out_pumpA);
      digitalWrite(PumpA, LOW);
      digitalWrite(PumpB, HIGH); delay(Out_pumpB);
      digitalWrite(PumpB, LOW);
    }

    lcd.setCursor(0, 1);
    lcd.print("CEK ULANG 5 MNT LAGI");

    for (int i = 1; i <= 600000; i++) {
      lcd.setCursor(9, 3);
      lcd.print(i); delay(1000);
    }
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("     CEK NUTRISI");
    ppm = hitungPPM(S_Air); delay(1000);
    ppm = hitungPPM(S_Air);

    if (ppm >= ppmMin) {
      cek = false;
    }
  }

  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("  BOOSTING SELESAI");
  tone(buzLed, 600, 100); delay(100); tone(buzLed, 1000, 100);
}
