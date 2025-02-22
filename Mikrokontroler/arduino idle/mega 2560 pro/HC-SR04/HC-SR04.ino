#define E_Pin D2 //Echo Pin
#define T_Pin D1 //Trigger Pin

long Durasi, Jarak; //waktu untuk kalkulasi jarak

void setup() {
  Serial.begin (9600);
  pinMode(T_Pin, OUTPUT);
  pinMode(E_Pin, INPUT);

}

void loop() {
  digitalWrite(T_Pin, LOW); delayMicroseconds(2);
  digitalWrite(T_Pin, HIGH); delayMicroseconds(10);
  digitalWrite(T_Pin, LOW);
  Durasi = pulseIn(E_Pin, HIGH);
  Jarak = Durasi / 58.2;

  Serial.println("Jarak Nutrisi dengan sensor : " + String(Jarak) + " Cm");


  delay(2000);

}
