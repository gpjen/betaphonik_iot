#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <jefripunza.h>
#include "RTClib.h"

LiquidCrystal_I2C lcd(0x27, 20, 4);
RTC_DS1307 RTC;

volatile int MenuTampil = 1;
volatile bool lampu = false, menuSet, ISTIRAHAT = false;

unsigned long W_Sebelum = 0, W_cek1m = 0;
String Jam, tgl;
float S_Air, PHmeter;
int LUX, stokA, stokB, stokPhdown, jamOn, menitOn, jamOff, menitOff, W_cek1j;


void MENUSet();
#include "sensorGPJ.h"

void setup() {
  tone(buzLed, 400, 100); delay(200);
  tone(buzLed, 400, 100);
  bacaEEPROM();

  Serial.begin(9600);
  Serial3.begin(115200);
  lcd.begin();
  lcd.backlight();

  Wire.begin();
  RTC.begin();
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
  pinMode(PumpAirNutrisi, OUTPUT);
  pinMode(PumpPHdown, OUTPUT);
  pinMode(TrigerA, OUTPUT);
  pinMode(TrigerB, OUTPUT);
  pinMode(TrigerPhdown, OUTPUT);
  pinMode(EchoA, INPUT);
  pinMode(EchoB, INPUT);
  pinMode(EchoPhdown, INPUT);

  digitalWrite(ECGround, LOW);
  digitalWrite(PumpA, LOW);
  digitalWrite(PumpB, LOW);


  attachInterrupt(digitalPinToInterrupt(TB), pushTB, FALLING);
  attachInterrupt(digitalPinToInterrupt(TOK), pushTOK, FALLING);
  attachInterrupt(digitalPinToInterrupt(TN), pushTN, FALLING);

  lcd.setCursor(0, 1);
  lcd.print("   BETAPHONIK V1");
  delay(2000);
  
  while (isnan(dht.readHumidity()) or isnan(dht.readTemperature())) {
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("     CEK SENSOR    ");
    delay(2000);
  }

  cekAKTIF();  

}

void loop() {

  //Update waktu
  DateTime now = RTC.now(); delay(100);
  Jam = String(now.hour()) + ":" + String(now.minute()) + ":" + String(now.second());
  delay(900);
  Serial.println(Jam);


  //cek waktu ON dan OFF...... Ex : 06:30 - 18:30 .......parsing : jamOn, menitOn, jamOff, menitOff
  if (now.hour() > jamOff || now.hour() < jamOn) {
    lcd.clear();
    ISTIRAHAT = true;
    waktuIstirahat();
  } else if (now.hour() == jamOff && now.minute() > menitOff) {
    lcd.clear();
    ISTIRAHAT = true;
    waktuIstirahat();
  } else if (now.hour() == jamOn && now.minute() < menitOn) {
    lcd.clear();
    ISTIRAHAT = true;
    waktuIstirahat();
  }


  //nyalakan lampu lcd jika tombol ditekan
  if (lampu == true) {
    lcd.backlight();
    lampu = false;
    W_Sebelum = millis();
  }
  //matikan lampu lcd jika dalam waktu 2 menit tombol tidak ditekan
  if (millis() - W_Sebelum >= 120000) {
    lcd.noBacklight();
    W_Sebelum = millis();
  }



  //tambilkan menu setting jika tombol OK ditekan
  if ( menuSet == true ) {
    lcd.clear();
    MENUSet();
  }
  //Tampilkan dalam layar LCD
  if ( MenuTampil == 1) {
    Tampilin1();
  } else if (MenuTampil == 2) {
    Tampilin2();
  } else {
    Tampilin3();
  }



  //update sensor Permenit (cahaya, kelembapan, suhu udara, suhu air)
  //PH dan ppm setiap 1 jam
  if ( now.hour() == W_cek1j) {
    tone(buzLed, 500, 300);
    delay(300);
    tone(buzLed, 900, 700);

    lcd.backlight();

    String ppmStatus, phStatus;

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(" CEK AIR & NUTRISI");


    // baca ph
    PHmeter = bacaPH();

    //perbaikan PH
    if (PHmeter > phMax) {
      int pompaPHD;

      if (PHmeter >= 10) {
        pompaPHD = (Out_pumpPhd * 1000) * 5;
        pompaPHdown(pompaPHD);
      } else if (PHmeter >= 9.0) {
        pompaPHD = (Out_pumpPhd * 1000) * 4;
        pompaPHdown(pompaPHD);
      } else if (PHmeter >= 8.0) {
        pompaPHD = (Out_pumpPhd * 1000) * 3;
        pompaPHdown(pompaPHD);
      } else if (PHmeter >= 7.0) {
        pompaPHD = (Out_pumpPhd * 1000) * 2   ;
        pompaPHdown(pompaPHD);
      } else if (PHmeter >= 6.0) {
        pompaPHD = Out_pumpPhd * 1000;
        pompaPHdown(pompaPHD);
      }

      phStatus = "Penambahan%20PH%20Down";

    } else if (PHmeter < phMin) {
      tone(buzLed, 900, 3000);

      phStatus = "Ganti%20Air%20Nutrisi";
    } else {

      phStatus = "PH%20Aman";
    }



    //baca ppm
    ppm = hitungPPM(S_Air);

    //perbaikan ppm
    if (ppm >= ppmMax) {

      ppmStatus = "Ganti%20Air%20Nutrisi";

    } else if (ppm <= ppmMin && S_Air <= 38 ) {
      tambahNutrisi();

      ppmStatus = "Penambahan%20Nutrisi";

    } else if (ppm <= ppmMin && S_Air >= 38 ) {
      ppmStatus = "Suhu%20Air%20Lebih%20Dari%2038%20C";
    } else {

      ppmStatus = "PPM%20AMAN";
    }


    //update stok nutrisi dan air.
    stokA   = hitungStok('A'); delay(100);
    stokB   = hitungStok('B'); delay(100);
    stokPhdown = hitungStok('C'); delay(100);

    tone(buzLed, 900, 100);
    Serial3.println("up1jam#" +
                    String(Jam) + "#" +
                    String(ppm) + "#" +
                    String(ppmStatus) + "#" +
                    String(PHmeter) + "#" +
                    String(phStatus) + "#" +
                    String(stokA) + "#" +
                    String(stokB) + "#" +
                    String(stokPhdown));

    //update cahaya
    LUX = S_cahaya.readLightLevel();
    //update kelembapan udara
    humi = dht.readHumidity();
    //update suhu udara
    temp = dht.readTemperature();
    //update suhu air
    sensorT.requestTemperatures();
    S_Air = sensorT.getTempCByIndex(0);
    if (S_Air <= -200){
      S_Air = 25;
    }

    tone(buzLed, 900, 100);
    Serial3.println("up1m#" +
                    String(Jam) + "#" +
                    String(S_Air) + "#" +
                    String(LUX) + "#" +
                    String(humi) + "#" +
                    String(temp));

    W_cek1j = W_cek1j + 1;
    lampu = true;
  }



} //akhir void loop





//-----------------------------MENU SETTING------------------------------------------------------


void MENUSet() {
  while (digitalRead(TOK) == 0) {}

  bool JamDetikPecah = false;


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
  lcd.setCursor(0, 1);
  lcd.print("Atur PH dan Nutrisi");
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
  lcd.setCursor(0, 1);
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
    JamDetikPecah = true;
    goto jadwalOnjam;
  } else if (digitalRead(TN) == 0) {
    while (digitalRead(TN) == 0) {}
    lcd.clear();
    goto inMenu4;
  }
  lcd.setCursor(0, 0);
  lcd.print("   [ PENGATURAN ]");
  lcd.setCursor(0, 1);
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
  lcd.setCursor(0, 1);
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
  lcd.setCursor(0, 1);
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
      } lcd.setCursor(11, 0); lcd.print(String(ppmMin) + " "); delay(150);
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
      } lcd.setCursor(11, 0); lcd.print(String(ppmMin) + " "); delay(150);
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
      } lcd.setCursor(11, 1); lcd.print(ppmMax); delay(150);
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
      } lcd.setCursor(11, 1); lcd.print(ppmMax); delay(150);
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
  //pilihnilaiAfull, pilihnilaiAlow, pilihnilaiBfull, pilihnilaiBlow, pilihnilaiCfull, pilihnilaiClow

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
      } delay(150);
      lcd.setCursor(0, 1); lcd.print("   <" + String(Low_nutrisiA) + "> Cm ");
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
    pilihnilaiAlow = true;
    pilihnilaiAfull = false;
    goto tessensorA;

  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto kalibrasiAfull;
    }
    while ( digitalRead(TN) == 0 ) {
      Low_nutrisiA++; if (Low_nutrisiA >= 100) {
        Low_nutrisiA = 100;
      } delay(150);
      lcd.setCursor(0, 1); lcd.print("   <" + String(Low_nutrisiA) + "> Cm ");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("> Nutrisi A penuh");
  lcd.setCursor(0, 1);
  lcd.print("   <" + String(Low_nutrisiA) + "> Cm ");

  lcd.setCursor(0, 2);
  lcd.print("  Nutrisi A Menipis");
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
      } delay(150);
      lcd.setCursor(0, 3); lcd.print("   <" + String(Full_nutrisiA) + "> Cm ");
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
    pilihnilaiAlow = false;
    pilihnilaiAfull = true;
    goto tessensorA;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto kalibrasiBlow;
    }
    while ( digitalRead(TN) == 0 ) {
      Full_nutrisiA++; if (Full_nutrisiA >= 150) {
        Full_nutrisiA = 150;
      } delay(150);
      lcd.setCursor(0, 3); lcd.print("   <" + String(Full_nutrisiA) + "> Cm ");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("  Nutrisi A penuh");
  lcd.setCursor(0, 1);
  lcd.print("   <" + String(Low_nutrisiA) + "> Cm ");

  lcd.setCursor(0, 2);
  lcd.print("> Nutrisi A Menipis");
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
      } delay(150);
      lcd.setCursor(0, 1); lcd.print("   <" + String(Low_nutrisiB) + "> Cm ");
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
    pilihnilaiBlow = true;
    pilihnilaiBfull = false;
    goto tessensorB;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto kalibrasiBfull;
    }
    while ( digitalRead(TN) == 0 ) {
      Low_nutrisiB++; if (Low_nutrisiB >= 100) {
        Low_nutrisiB = 100;
      } delay(150);
      lcd.setCursor(0, 1); lcd.print("   <" + String(Low_nutrisiB) + "> Cm ");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("> Nutrisi B penuh");
  lcd.setCursor(0, 1);
  lcd.print("   <" + String(Low_nutrisiB) + "> Cm ");

  lcd.setCursor(0, 2);
  lcd.print("  Nutrisi B Menipis");
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
      } delay(150);
      lcd.setCursor(0, 3); lcd.print("   <" + String(Full_nutrisiB) + "> Cm ");
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
    pilihnilaiBlow = false;
    pilihnilaiBfull = true;
    goto tessensorB;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto KalibrasiPHlow;
    }
    while ( digitalRead(TN) == 0 ) {
      Full_nutrisiB++; if (Full_nutrisiB >= 150) {
        Full_nutrisiB = 150;
      } delay(150);
      lcd.setCursor(0, 3); lcd.print("   <" + String(Full_nutrisiB) + "> Cm ");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("  Nutrisi B penuh");
  lcd.setCursor(0, 1);
  lcd.print("   <" + String(Low_nutrisiB) + "> Cm ");

  lcd.setCursor(0, 2);
  lcd.print("> Nutrisi B Menipis");
  lcd.setCursor(0, 3);
  lcd.print("   <" + String(Full_nutrisiB) + "> Cm ");

  goto kalibrasiBfull;


KalibrasiPHlow:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto kalibrasiBfull;
    }
    while ( digitalRead(TB) == 0 ) {
      Low_air--; if (Low_air <= 1) {
        Low_air = 1;
      } delay(150);
      lcd.setCursor(0, 1); lcd.print("   <" + String(Low_air) + "> Cm ");
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
    pilihnilaiClow = true;
    pilihnilaiCfull = false;
    goto tessensorC;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto KalibrasiPHfull;
    }
    while ( digitalRead(TN) == 0 ) {
      Low_air++; if (Low_air >= 100) {
        Low_air = 100;
      } delay(150);
      lcd.setCursor(0, 1); lcd.print("   <" + String(Low_air) + "> Cm ");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("> PH Down Penuh");
  lcd.setCursor(0, 1);
  lcd.print("   <" + String(Low_air) + "> Cm ");

  lcd.setCursor(0, 2);
  lcd.print("  PH Down Menipis");
  lcd.setCursor(0, 3);
  lcd.print("   <" + String(Full_air) + "> Cm ");

  goto KalibrasiPHlow;

KalibrasiPHfull:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto KalibrasiPHlow;
    }
    while ( digitalRead(TB) == 0 ) {
      Full_air--; if (Full_air <= 1) {
        Full_air = 1;
      } delay(150);
      lcd.setCursor(0, 3); lcd.print("   <" + String(Full_air) + "> Cm ");
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
    pilihnilaiClow = false;
    pilihnilaiCfull = true;
    goto tessensorC;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto KalibrasiK_PPM;
    }
    while ( digitalRead(TN) == 0 ) {
      Full_air++; if (Full_air >= 150) {
        Full_air = 150;
      } delay(150);
      lcd.setCursor(0, 3); lcd.print("   <" + String(Full_air) + "> Cm ");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("  PH Down Penuh");
  lcd.setCursor(0, 1);
  lcd.print("   <" + String(Low_air) + "> Cm ");

  lcd.setCursor(0, 2);
  lcd.print("> PH Down Menipis");
  lcd.setCursor(0, 3);
  lcd.print("   <" + String(Full_air) + "> Cm ");

  goto KalibrasiPHfull;



KalibrasiK_PPM:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto KalibrasiPHfull;
    }
    while ( digitalRead(TB) == 0 ) {
      K_TDS = K_TDS - 0.01; if (K_TDS <= 0.01) {
        K_TDS = 0.01;
      } delay(150);
      lcd.setCursor(0, 1); lcd.print("   < " + String(K_TDS) + " >");
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
    goto tessensorTDS;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto KalibrasiK_PH;
    }
    while ( digitalRead(TN) == 0 ) {
      K_TDS = K_TDS + 0.01; if (K_TDS > 2.99) {
        K_TDS = 2.99;
      } delay(150);
      lcd.setCursor(0, 1); lcd.print("   < " + String(K_TDS) + " >");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("> Konstanta PPM");
  lcd.setCursor(0, 1);
  lcd.print("   < " + String(K_TDS) + " >");

  lcd.setCursor(0, 2);
  lcd.print("  Konstanta PH");
  lcd.setCursor(0, 3);
  lcd.print("   < " + String(K_PH) + " >");

  goto KalibrasiK_PPM;



KalibrasiK_PH:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto KalibrasiK_PPM;
    }
    while ( digitalRead(TB) == 0 ) {
      K_PH = K_PH - 0.01; if (K_PH < 0) {
        K_PH = 0;
      } delay(150);
      lcd.setCursor(0, 3); lcd.print("   < " + String(K_PH) + " >");
    }

  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
    goto tessensorPH;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto kalibrasiSIMPAN;
    }
    while ( digitalRead(TN) == 0 ) {
      K_PH = K_PH + 0.01; if (K_PH > 3) {
        K_PH = 3;
      } delay(150);
      lcd.setCursor(0, 3); lcd.print("   < " + String(K_PH) + " >");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print("  Konstanta PPM");
  lcd.setCursor(0, 1);
  lcd.print("   < " + String(K_TDS) + " >");

  lcd.setCursor(0, 2);
  lcd.print("> Konstanta PH");
  lcd.setCursor(0, 3);
  lcd.print("   < " + String(K_PH) + " >");

  goto KalibrasiK_PH;



kalibrasiSIMPAN:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto KalibrasiK_PH;
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
  lcd.print("   < " + String(K_TDS) + " >");

  lcd.setCursor(0, 1);
  lcd.print("  Konstanta PH");
  lcd.setCursor(0, 2);
  lcd.print("   < " + String(K_PH) + " >");

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
  lcd.print("  Konstanta PH");
  lcd.setCursor(0, 1);
  lcd.print("   < " + String(K_PH) + " >");

  lcd.setCursor(0, 2);
  lcd.print("  [ SIMPAN ]");

  lcd.setCursor(0, 3);
  lcd.print("> [ BATAL/KELUAR ]");

  goto kalibrasiBATAL;




tessensorA:

  int tesA = hitungjarak('A');

  if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    if (pilihnilaiAlow ==  true && pilihnilaiAfull ==  false) {
      Low_nutrisiA = tesA;
      pilihnilaiAfull = false;
      pilihnilaiAlow =  false;
      lcd.clear();
      goto kalibrasiAlow;
    } else if (pilihnilaiAfull == true && pilihnilaiAlow == false) {
      Full_nutrisiA = tesA;
      pilihnilaiAfull = false;
      pilihnilaiAlow =  false;
      lcd.clear();
      goto kalibrasiAfull;
    }
  }


  lcd.setCursor(0, 0);
  lcd.print("    [ TES MODE ]");
  lcd.setCursor(0, 1);
  lcd.print("   Jarak Nutrisi A");

  lcd.setCursor(0, 2);
  lcd.print("       " + String(tesA) + " cm  ");

  lcd.setCursor(0, 3);
  lcd.print("     [ Keluar ]");

  delay (1000);

  goto tessensorA;

tessensorB:
  int tesB = hitungjarak('B');

  if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    if (pilihnilaiBlow ==  true && pilihnilaiBfull ==  false) {
      Low_nutrisiB = tesB;
      pilihnilaiBfull = false;
      pilihnilaiBlow =  false;
      lcd.clear();
      goto kalibrasiBlow;
    } else if (pilihnilaiBfull == true && pilihnilaiBlow == false) {
      Full_nutrisiB = tesB;
      pilihnilaiBfull = false;
      pilihnilaiBlow =  false;
      lcd.clear();
      goto kalibrasiBfull;
    }
  }


  lcd.setCursor(0, 0);
  lcd.print("    [ TES MODE ]");
  lcd.setCursor(0, 1);
  lcd.print("   Jarak Nutrisi B");

  lcd.setCursor(0, 2);
  lcd.print("       " + String(tesB) + " cm  ");

  lcd.setCursor(0, 3);
  lcd.print("     [ Keluar ]");

  delay (1000);

  goto tessensorB;


tessensorC:
  int tesC = hitungjarak('C');

  if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    if (pilihnilaiClow ==  true && pilihnilaiCfull ==  false) {
      Low_air = tesC;
      pilihnilaiCfull = false;
      pilihnilaiClow =  false;
      lcd.clear();
      goto KalibrasiPHlow;
    } else if (pilihnilaiCfull == true && pilihnilaiClow == false) {
      Full_air = tesC;
      pilihnilaiCfull = false;
      pilihnilaiClow =  false;
      lcd.clear();
      goto KalibrasiPHfull;
    }
  }


  lcd.setCursor(0, 0);
  lcd.print("    [ TES MODE ]");
  lcd.setCursor(0, 1);
  lcd.print("   Jarak PH Down");

  lcd.setCursor(0, 2);
  lcd.print("       " + String(tesC) + " cm  ");

  lcd.setCursor(0, 3);
  lcd.print("     [ Keluar ]");

  delay (1000);

  goto tessensorC;


tessensorTDS:
  bool cekppm = true;
  int suhunya = sensorT.getTempCByIndex(0),
      ppmnya  = hitungPPM(suhunya); delay(100);

  lcd.setCursor(0, 0);
  lcd.print("      BACA PPM");
  lcd.setCursor(0, 1);
  lcd.print("  PPM = " + String(ppmnya) + " ppm  ");
  lcd.setCursor(0, 2);
  lcd.print("  Konstanta = " + String(K_TDS));
  lcd.setCursor(0, 3);
  lcd.print("     [ Keluar ]");

  while (cekppm) {
    if (digitalRead(TOK) == 0) {
      while (digitalRead(TOK) == 0) {}
      lcd.clear();
      goto KalibrasiK_PPM;
    }
  }


  goto tessensorTDS;


tessensorPH:

  bool cekph = true;
  float phnya = bacaPH();

  lcd.setCursor(0, 0);
  lcd.print("   BACA NILAI PH");

  lcd.setCursor(0, 1);
  lcd.print( "     PH = " + String(phnya));
  lcd.setCursor(0, 2);
  lcd.print( "  Konstanta = " + String(K_PH));

  lcd.setCursor(0, 3);
  lcd.print("     [ Keluar ]");

  while (cekph) {
    if (digitalRead(TOK) == 0) {
      while (digitalRead(TOK) == 0) {}
      lcd.clear();
      goto KalibrasiK_PH;
    }
  }

  goto tessensorPH;

  //...................AKHIR SUB KALIBRASI SENSOR......................................



  //===================SUB MENU JADWAL ON OFF========================================

jadwalOnjam:

  while (JamDetikPecah) {

    jamOn = string2int(splitText(JamON, ':', 0));
    menitOn = string2int(splitText(JamON, ':', 1));
    jamOff = string2int(splitText(JamOFF, ':', 0));
    menitOff = string2int(splitText(JamOFF, ':', 1));

    JamDetikPecah = false;
  }

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
      lcd.setCursor(2, 1); lcd.print("[" + String(jamOn) + "] : " + String(menitOn) + "  ");
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
      lcd.setCursor(2, 1); lcd.print("[" + String(jamOn) + "] : " + String(menitOn) + "  ");
    }

  }

  lcd.setCursor(0, 0);
  lcd.print("> Jadwal ON");
  lcd.setCursor(2 , 1);
  lcd.print("[" + String(jamOn) + "] : " + String(menitOn) + "  ");

  lcd.setCursor(0, 2);
  lcd.print("  Jadwal OFF");
  lcd.setCursor(2, 3);
  lcd.print(String(jamOff) + " : " + String(menitOff) + "  ");

  goto jadwalOnjam;


jadwalOndetik:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto jadwalOnjam;
    }
    while (digitalRead(TB) == 0) {
      if (menitOn <= 1 ) {
        menitOn = 60;
      } menitOn--; delay(300);
      lcd.setCursor(2, 1); lcd.print(String(jamOn) + " : [" + String(menitOn) + "]  ");
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
      if (menitOn >= 60 ) {
        menitOn = 1;
      } menitOn++; delay(300);
      lcd.setCursor(2, 1); lcd.print(String(jamOn) + " : [" + String(menitOn) + "]  ");
    }

  }

  lcd.setCursor(0, 0);
  lcd.print("> Jadwal ON");
  lcd.setCursor(2, 1);
  lcd.print(String(jamOn) + " : [" + String(menitOn) + "]  ");

  lcd.setCursor(0, 2);
  lcd.print("  Jadwal OFF");
  lcd.setCursor(2, 3);
  lcd.print(String(jamOff) + " : " + String(menitOff) + "  ");

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
      lcd.setCursor(2, 3); lcd.print("[" + String(jamOff) + "] : " + String(menitOff) + "  ");
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
      lcd.setCursor(2, 3); lcd.print("[" + String(jamOff) + "] : " + String(menitOff) + "  ");
    }

  }

  lcd.setCursor(0, 0);
  lcd.print("  Jadwal ON");
  lcd.setCursor(2, 1);
  lcd.print(String(jamOn) + " : " + String(menitOn) + "  ");

  lcd.setCursor(0, 2);
  lcd.print("> Jadwal OFF");
  lcd.setCursor(2, 3);
  lcd.print("[" + String(jamOff) + "] : " + String(menitOff) + "  ");

  goto jadwalOffjam;


jadwalOffdetik:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto jadwalOffjam;
    }
    while (digitalRead(TB) == 0) {
      if (menitOff <= 1 ) {
        menitOff = 60;
      } menitOff--; delay(300);
      lcd.setCursor(2, 3); lcd.print(String(jamOff) + " : [" + String(menitOff) + "]  ");
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
      if (menitOff >= 60 ) {
        menitOff = 1;
      } menitOff++; delay(300);
      lcd.setCursor(2, 3); lcd.print(String(jamOff) + " : [" + String(menitOff) + "]  ");
    }

  }

  lcd.setCursor(0, 0);
  lcd.print("  Jadwal ON");
  lcd.setCursor(2, 1);
  lcd.print(String(jamOn) + " : " + String(menitOn) + "  ");

  lcd.setCursor(0, 2);
  lcd.print("> Jadwal OFF");
  lcd.setCursor(2, 3);
  lcd.print(String(jamOff) + " : [" + String(menitOff) + "]  ");

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
    JamON = String(jamOn) + ":" + String(menitOn);
    JamOFF = String(jamOff) + ":" + String(menitOff);
    simpanEEPROM(); delay(1000); lcd.clear();
    goto inMenu3;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto jadwalBATAL;
    }
  }

  lcd.setCursor(2, 0);
  lcd.print(String(jamOn) + " : " + String(menitOn) + "  ");
  lcd.setCursor(0, 1);
  lcd.print("  Jadwal OFF");
  lcd.setCursor(2, 2);
  lcd.print(String(jamOff) + " : [" + String(menitOff) + "]  ");
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
  lcd.print(String(jamOff) + " : [" + String(menitOff) + "]  ");
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
      if (Out_pumpA <= 0 ) {
        Out_pumpA = 0; delay(150);
      }
      lcd.setCursor(0, 0); lcd.print(">PUMP A : " + String(Out_pumpA) + " /s ");
    }
  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
    goto tespumpA;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto pumpB;
    }
    while (digitalRead(TN) == 0) {
      Out_pumpA++;
      if (Out_pumpA >= 300) {
        Out_pumpA = 300; delay(150);
      }
      lcd.setCursor(0, 0); lcd.print(">PUMP A : " + String(Out_pumpA) + " /s ");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print(">PUMP A : " + String(Out_pumpA) + " /s ");
  lcd.setCursor(0, 1);
  lcd.print(" PUMP B : " + String(Out_pumpB) + " /s ");
  lcd.setCursor(0, 2);
  lcd.print(" PUMP PHD : " + String(Out_pumpPhd) + " /s ");
  lcd.setCursor(0, 3);
  lcd.print(" [ SIMPAN ]");

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
      if (Out_pumpB <= 0) {
        Out_pumpB = 0; delay(150);
      }
      lcd.setCursor(0, 1); lcd.print(">PUMP B : " + String(Out_pumpB) + " /s ");
    }
  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    lcd.clear();
    goto tespumpB;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto pumpPHdown;
    }
    while (digitalRead(TN) == 0) {
      Out_pumpB++;
      if (Out_pumpB >= 300) {
        Out_pumpB = 300; delay(150);
      }
      lcd.setCursor(0, 1); lcd.print(">PUMP B : " + String(Out_pumpB) + " /s ");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print(" PUMP A : " + String(Out_pumpA) + " /s ");
  lcd.setCursor(0, 1);
  lcd.print(">PUMP B : " + String(Out_pumpB) + " /s ");
  lcd.setCursor(0, 2);
  lcd.print(" PUMP PHD : " + String(Out_pumpPhd) + " /s ");
  lcd.setCursor(0, 3);
  lcd.print(" [ SIMPAN ]");

  goto pumpB;



pumpPHdown:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto pumpB;
    }
    while (digitalRead(TB) == 0) {
      Out_pumpPhd--;
      if (Out_pumpPhd <= 0) {
        Out_pumpPhd = 0; delay(150);
      }
      lcd.setCursor(0, 2); lcd.print(">PUMP PHD : " + String(Out_pumpPhd) + " /s ");
    }
  } else if (digitalRead(TOK) == 0) {
    while (digitalRead(TOK) == 0) {}
    goto tespumpC;
  } else if (digitalRead(TN) == 0) {
    delay(200);
    if (digitalRead(TN) == 1) {
      lcd.clear();
      goto pumpSIMPAN;
    }
    while (digitalRead(TN) == 0) {
      Out_pumpPhd++;
      if (Out_pumpPhd >= 300) {
        Out_pumpPhd = 300; delay(150);
      }
      lcd.setCursor(0, 2); lcd.print(">PUMP PHD : " + String(Out_pumpPhd) + " /s ");
    }
  }

  lcd.setCursor(0, 0);
  lcd.print(" PUMP A : " + String(Out_pumpA) + " /s ");
  lcd.setCursor(0, 1);
  lcd.print(" PUMP B : " + String(Out_pumpB) + " /s ");
  lcd.setCursor(0, 2);
  lcd.print(">PUMP PHD : " + String(Out_pumpPhd) + " /s ");
  lcd.setCursor(0, 3);
  lcd.print(" [ SIMPAN ]");

  goto pumpPHdown;


pumpSIMPAN:
  if (digitalRead(TB) == 0) {
    delay(200);
    if (digitalRead(TB) == 1) {
      lcd.clear();
      goto pumpPHdown;
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
  lcd.print(" PUMP A : " + String(Out_pumpA) + " /s ");
  lcd.setCursor(0, 1);
  lcd.print(" PUMP B : " + String(Out_pumpB) + " /s ");
  lcd.setCursor(0, 2);
  lcd.print(" PUMP PHD : " + String(Out_pumpPhd) + " /s ");
  lcd.setCursor(0, 3);
  lcd.print(">[ SIMPAN ]");

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
  lcd.print(" PUMP B : " + String(Out_pumpB) + " /s ");
  lcd.setCursor(0, 1);
  lcd.print(" PUMP PHD : " + String(Out_pumpPhd) + " /s ");
  lcd.setCursor(0, 2);
  lcd.print(" [ SIMPAN ]");
  lcd.setCursor(0, 3);
  lcd.print(">[ BATAL/Keluar ]");

  goto pumpBATAL;



tespumpA:

  lcd.setCursor(0, 0);
  lcd.print("   > TEST PUMP A <");
  lcd.setCursor(0, 2);
  lcd.print("     pompa aktif");
  lcd.setCursor(0, 3);
  lcd.print("    " + String(Out_pumpA) + " Detik  ");

  digitalWrite(PumpA, HIGH);
  delay(Out_pumpA*1000);
  digitalWrite(PumpA, LOW);
  lcd.clear();
  
  goto pumpA;

tespumpB:

  lcd.setCursor(0, 0);
  lcd.print("   > TEST PUMP B <");
  lcd.setCursor(0, 2);
  lcd.print("     pompa aktif");
  lcd.setCursor(0, 3);
  lcd.print("    " + String(Out_pumpB) + " Detik  ");

  digitalWrite(PumpB, HIGH);
  delay(Out_pumpB*1000);
  digitalWrite(PumpB, LOW);
  lcd.clear();
  
  goto pumpB;


tespumpC:

  lcd.setCursor(0, 0);
  lcd.print("  > TEST PUMP PHD <");
  lcd.setCursor(0, 2);
  lcd.print("     pompa aktif");
  lcd.setCursor(0, 3);
  lcd.print("    " + String(Out_pumpPhd) + " Detik  ");

  digitalWrite(PumpPHdown, HIGH);
  delay(Out_pumpPhd*1000);
  digitalWrite(PumpPHdown, LOW);
  lcd.clear();
  
  goto pumpPHdown;


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
  lcd.print("Nutrisi A : " + String(stokA) + " % ");

  lcd.setCursor(0, 1);
  lcd.print("Nutrisi B : " + String(stokB) + " % ");

  lcd.setCursor(0, 2);
  lcd.print("PH Down   : " + String(stokPhdown) + " % ");
}
void Tampilin3() {
  lcd.clear();

  lcd.setCursor(6, 0);
  lcd.print(Jam + "  ");

  lcd.setCursor(0, 1);
  lcd.print("  On:" + String(jamOn) + ":" + String(menitOn) + " Off:" + String(jamOff) + ":" + String(menitOff));


  lcd.setCursor(0, 3);
  lcd.print("[B]   [Seting]   [N]");


}



void bacaEEPROM() {

  //jamON#jamOFF#PPMmin#PPMmax#PHmin#PHmax#Out_pumpA#Out_pumpB#Low_nutrisiA#Full_nutrsisiA#Low_nutrisiB#Full_nutrisiB#low_AIR#Full_air#AIR_MIN#Out_pumpPhd

  Serial.println("BACA <=== " + BacaPROM);

  JamON         = splitText(BacaPROM, '#', 0);
  JamOFF        = splitText(BacaPROM, '#', 1);

  jamOn     = string2int(splitText(JamON, ':', 0));
  menitOn   = string2int(splitText(JamON, ':', 1));
  jamOff    = string2int(splitText(JamOFF, ':', 0));
  menitOff  = string2int(splitText(JamOFF, ':', 1));

  ppmMin        = string2int(splitText(BacaPROM, '#', 2));
  ppmMax        = string2int(splitText(BacaPROM, '#', 3));

  String TphMin = splitText(BacaPROM, '#', 4);
  String TphMax = splitText(BacaPROM, '#', 5);
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
  PHmin         = string2int(splitText(BacaPROM, '#', 14));
  Out_pumpPhd   = string2int(splitText(BacaPROM, '#', 15));

  String TKTDS  = splitText(BacaPROM, '#', 16);
  String TKPH   = splitText(BacaPROM, '#', 17);
  K_TDS         = TKTDS.toFloat();
  K_PH          = TKPH.toFloat();

  Serial.println("\n- Kons PPM :" + String(K_TDS) + " - Kons PH :" + String(K_PH) + "\n");


}

void simpanEEPROM() {

  //jamON#jamOFF#PPMmin#PPMmax#PHmin#PHmax#Out_pumpA#Out_pumpB#Low_nutrisiA#Full_nutrsisiA#Low_nutrisiB#Full_nutrisiB#low_AIR#Full_air#AIR_MIN#Out_pumpPhd

  lcd.setCursor(0, 1);
  lcd.print("     MENYIMPAN ");

  String Simpan = JamON + '#' +
                  JamOFF + '#' +
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
                  String(Full_air) + '#' +
                  String(PHmin) + '#' +
                  String(Out_pumpPhd) + '#' +
                  String(K_TDS) + '#' +
                  String(K_PH);

  Serial.println("SIMPAN ===> " + Simpan);

  writeStringToEEPROM(0, Simpan);
  BacaPROM = readStringFromEEPROM(0);
  bacaEEPROM();
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("      DISIMPAN "); \
  tone(buzLed, 1000, 80);
}
