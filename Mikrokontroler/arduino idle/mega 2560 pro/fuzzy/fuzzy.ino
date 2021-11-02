
#include <jefripunza.h>
#include <Fuzzy.h>

Fuzzy *fuzzy = new Fuzzy();

String bacaEeprom = readStringFromEEPROM(0);

int ppmBahaya   = string2int(splitText(bacaEeprom, '#', 3));
int ppmKurang   = string2int(splitText(bacaEeprom, '#', 4));
int ppmIdeal    = string2int(splitText(bacaEeprom, '#', 5));
int ppmLebih    = string2int(splitText(bacaEeprom, '#', 6));

void setup() {
  Serial.begin(9600);


}

void loop() {

Serial.println(ppmMin);
Serial.println(ppmIdeal);
Serial.println(ppmMax);

delay(3000);
}
