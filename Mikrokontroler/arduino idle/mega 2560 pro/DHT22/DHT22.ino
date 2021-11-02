
#include <DHT.h>                      //library DHT22
#define DHTPIN 32                     //pin data DHT22 konek ke pin 8 Arduino
#define TipeDHT DHT22                 //jenis sensor DHT22
DHT dht(DHTPIN, TipeDHT);             //setup pin dan jenis DHTT ke library

//deklarasi variabel untuk menampung pembacaan suhu & kelembaban
float humi, temp;

void setup()
{

  Serial.begin(9600);

  while (isnan(dht.readHumidity()) or isnan(dht.readTemperature())) {
    Serial.println("DHT22 Belum Terhubung");
    delay(2000);
  }
}
//============================
void loop()
{
  humi = dht.readHumidity(); //baca kelembaban
  temp = dht.readTemperature();//baca suhu

  Serial.println("Hum : " + String(humi) + " %  Temp : " + String(temp) + " C");


  delay(1000); //tunda 1 detik
}
