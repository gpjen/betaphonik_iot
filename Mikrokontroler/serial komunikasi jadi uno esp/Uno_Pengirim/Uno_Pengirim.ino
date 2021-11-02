
String tampung;

void setup() {
  Serial.begin(9600);
  Serial.println("Mega Pengirim Aktif");

}

void loop() {

  while (Serial.available()) {
    delay(10);
    char c = Serial.read();
    tampung += c;
  }
  tampung.trim();

  if (tampung == "ESP_Rikwes") {
    Serial.println("99.00#88.00#77.01#66.05#33.99#0#1#1#1#1024#2500#30000#wookey#67865g#776tygyu#776g");
  }

  tampung = "";
  Serial.println("99.00#");
  delay(10000);
}
