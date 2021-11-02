

void Sensor_LUX() {
  LUX = S_cahaya.readLightLevel();
  Serial.print("Cahaya: ");
  Serial.print(LUX);
  Serial.println(" LUX");
}

void Sensor_TempHumi () {

  humi = dht.readHumidity();
  temp = dht.readTemperature();

  Serial.println("Hum : " + String(humi) + " %  Temp : " + String(temp) + " C");
}

void Sensor_hcsr04() {
  digitalWrite(T_Pin, LOW); delayMicroseconds(2);
  digitalWrite(T_Pin, HIGH); delayMicroseconds(10);
  digitalWrite(T_Pin, LOW);
  Durasi = pulseIn(E_Pin, HIGH);
  Jarak = Durasi / 58.2;

  Serial.println("Jarak Nutrisi dengan sensor : " + String(Jarak) + " Cm");
}


float Sensor_Ph    (float voltage) {
    return 7 + ((2.5 - voltage) / 0.18);
  }
