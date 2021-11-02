#include <ESP8266WiFi.h>
#include <jefripunza.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


String tampung;

const char* ssid = "Tam leng clay";
const char* pass = "sawadikabong";
const char* host = "172.20.10.3";

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("ESP8266 Aktif");
  digitalWrite(LED_BUILTIN, HIGH);


  WiFi.hostname("IOT Monitoring Betaphonik");
  WiFi.begin(ssid, pass);                    //mulai melakukan koneksi ke wifi
  while (WiFi.status() != WL_CONNECTED) {    //jika status wifi tidak konek maka akan berulang di While sampai konek
    Serial.print("*");
    delay(1000);
  }

  Serial.println("TERHUBUNG JARINGAN");

}

void loop() {

  WiFiClient client;
  if (!client.connect(host, 80)) {
    Serial.println("Koneksi Server Bermasalah");
    return;
  }

  String Link;
  HTTPClient http;


  while (Serial.available()) {
    delay(10);
    char c = Serial.read();
    tampung += c;
  }
  tampung.trim();

  if (tampung != "") {
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
    digitalWrite(LED_BUILTIN, HIGH);

    if (splitText(tampung, '#', 0) == "aktif") {

      //aktif#waktu#ppm#PH#SuhuAiir#cahaya#humi#temp#stokA#stokB#stokPHDown
      //Ex : aktif#17:00#987#8.6#45#240#99#45#30#40#50

      String  Ket         = "aktif",
              waktu       = splitText(tampung, '#', 1),
              ppm         = splitText(tampung, '#', 2),
              PHmeter     = splitText(tampung, '#', 3),
              S_air       = splitText(tampung, '#', 4),
              LUX         = splitText(tampung, '#', 5),
              humi        = splitText(tampung, '#', 6),
              temp        = splitText(tampung, '#', 7),
              stokA       = splitText(tampung, '#', 8),
              stokB       = splitText(tampung, '#', 9),
              stokPhdown  = splitText(tampung, '#', 10);


      Link =  "http://" + String(host) + "/BETAPHONIK/sesuatu/updatedong.php?status=" +
              String(Ket) + "&waktu=" +
              String(waktu) + "&ppm=" +
              String(ppm) + "&ph=" +
              String(PHmeter) + "&sair=" +
              String(S_air) + "&cahaya=" +
              String(LUX) + "&kel=" +
              String(humi) + "&sudara=" +
              String(temp) + "&stoka=" +
              String(stokA) + "&stokb=" +
              String(stokB) + "&stokphdown=" +
              String(stokPhdown);

      Serial.println(Link);

      http.begin(client, Link);
      Serial.println(http.GET());

    } else if (splitText(tampung, '#', 0) == "up1m") {

      //up1m#waktu#SuhuAiir#cahaya#humi#temp
      //Ex : up1m#11:30#30#320#31#32

      String  Ket         = "up1m",
              waktu       = splitText(tampung, '#', 1),
              S_air       = splitText(tampung, '#', 2),
              LUX         = splitText(tampung, '#', 3),
              humi        = splitText(tampung, '#', 4),
              temp        = splitText(tampung, '#', 5);

      Link =  "http://" + String(host) + "/BETAPHONIK/sesuatu/updatedong.php?status=" +
              String(Ket) + "&waktu=" +
              String(waktu) + "&sair=" +
              String(S_air) + "&cahaya=" +
              String(LUX) + "&kel=" +
              String(humi) + "&sudara=" +
              String(temp);

      Serial.println(Link);

      http.begin(client, Link);
      Serial.println(http.GET());

    } else if (splitText(tampung, '#', 0) == "up1jam") {

      //up1jam#waktu#ppm#ppmStatus#PHmeter#phStatus#stokA#stokB#stokPhdown
      //Ex : up1jam#11:01#1200#MANTAP#4.6#PARAH#90#80#70

      String  Ket         = "up1jam",
              waktu       = splitText(tampung, '#', 1),
              ppm         = splitText(tampung, '#', 2),
              ppmStatus   = splitText(tampung, '#', 3),
              PHmeter     = splitText(tampung, '#', 4),
              phStatus    = splitText(tampung, '#', 5),
              stokA       = splitText(tampung, '#', 6),
              stokB       = splitText(tampung, '#', 7),
              stokPhdown  = splitText(tampung, '#', 8);

      Link =  "http://" + String(host) + "/BETAPHONIK/sesuatu/updatedong.php?status=" +
              String(Ket) + "&waktu=" +
              String(waktu) + "&ppm=" +
              String(ppm) + "&ppmStatus=" +
              String(ppmStatus) + "&ph=" +
              String(PHmeter) + "&phStatus=" +
              String(phStatus) + "&stoka=" +
              String(stokA) + "&stokb=" +
              String(stokB) + "&stokphdown=" +
              String(stokPhdown);

      Serial.println(Link);

      http.begin(client, Link);
      Serial.println(http.GET());

    } else if (splitText(tampung, '#', 0) == "deet") {

      // deet#waktu
      // Ex : deet#06:44
      // ?status=deet&waktu=1:34:3


      String  Ket         = "deet",
              waktu       = splitText(tampung, '#', 1);

      Link =  "http://" + String(host) + "/BETAPHONIK/sesuatu/updatedong.php?status=" +
              String(Ket) + "&waktu=" +
              String(waktu);

      Serial.println(Link);

      http.begin(client, Link);
      Serial.println(http.GET());
    }
  }

  tampung = "";
  delay(1000);

}
