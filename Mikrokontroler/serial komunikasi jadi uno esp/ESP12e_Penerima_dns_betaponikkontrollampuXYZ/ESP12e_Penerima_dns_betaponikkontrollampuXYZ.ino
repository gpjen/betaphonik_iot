#include <ESP8266WiFi.h>
#include <jefripunza.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>


String tampung;

const char* host = "betaphonik.kontrollampu.xyz";

void setup() {

  Serial.begin(115200);

  WiFiManager wifiManager;
  wifiManager.autoConnect("BETAPHONIK_IOT");

  Serial.println("\n ==> Berhasil konek Wifi...\n");

  if (MDNS.begin("betaphonik")) {
    Serial.println("MDNS dimulai...");
  }

  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("ESP8266 Aktif");
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.println("TERHUBUNG JARINGAN");

}

void loop() {

  WiFiClient client;
  Serial.println(host);
  Serial.println("/n");
  if (!client.connect(host, 80)) {
    Serial.println("Koneksi Server Bermasalah");

    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("wifi tidak tersambung");
      WiFiManager wifiManager;
      wifiManager.autoConnect("BETAPHONIK_IOT");
    }
    Serial.println("\n ==> Berhasil konek Wifi...\n");
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


      Link =  "http://" + String(host) + "/sesuatu/updatedong.php?status=" +
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

      Link =  "http://" + String(host) + "/sesuatu/updatedong.php?status=" +
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
      //Ex : up1jam#11:01#1200#PPM%20AMAN#5.6#PH%20Aman#90#80#70

      String  Ket         = "up1jam",
              waktu       = splitText(tampung, '#', 1),
              ppm         = splitText(tampung, '#', 2),
              ppmStatus   = splitText(tampung, '#', 3),
              PHmeter     = splitText(tampung, '#', 4),
              phStatus    = splitText(tampung, '#', 5),
              stokA       = splitText(tampung, '#', 6),
              stokB       = splitText(tampung, '#', 7),
              stokPhdown  = splitText(tampung, '#', 8);

      Link =  "http://" + String(host) + "/sesuatu/updatedong.php?status=" +
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

      Link =  "http://" + String(host) + "/sesuatu/updatedong.php?status=" +
              String(Ket) + "&waktu=" +
              String(waktu);

      Serial.println(Link);

      http.begin(client, Link);
      Serial.println(http.GET());

    } else if (splitText(tampung, '#', 0) == "aturppm") {
      // aturppm#nilaippm#pompaAon#pompaBon
      // Ex : aturppm#780#1000#1000
      // sesuatu/updatedong.php?status=aturppm&ppm=780&pompaA=1000&pompaB=1000


      String  Ket         = "aturppm",
              ppm         = splitText(tampung, '#', 1),
              pompaA      = splitText(tampung, '#', 2),
              pompaB      = splitText(tampung, '#', 3);

      Link =  "http://" + String(host) + "/sesuatu/updatedong.php?status=" +
              String(Ket)   + "&ppm=" +
              String(ppm) + "&pompaA=" +
              String(pompaA) + "&pompaB=" +
              String(pompaB);

      Serial.println(Link);

      http.begin(client, Link);
      Serial.println(http.GET());

    }
  }

  tampung = "";
  delay(1000);

}
