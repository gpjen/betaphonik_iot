
#define R1 38
#define R2 39
#define R3 40
#define R4 41

int StatusR[4] = {0, 0, 0, 0};

#define B1 18
#define B2 19
#define B3 20
#define B4 21

int Urut = 38;

void setup() {
  Serial.begin(9600);

  pinMode(31, OUTPUT);

  while (Urut <= 41) {
    pinMode(Urut, OUTPUT);
    digitalWrite(Urut, HIGH);
    Serial.println("PIN " + String(Urut) + " Disetting");
    Urut++;
  } Urut = 18;

  while (Urut <= 21) {
    pinMode(Urut, INPUT_PULLUP);
    Serial.println("PIN " + String(Urut) + " Disetting");
    Urut++;
  } Urut = 0;

  attachInterrupt(digitalPinToInterrupt(B1), Pb_1, FALLING);
  attachInterrupt(digitalPinToInterrupt(B2), Pb_2, FALLING);
  attachInterrupt(digitalPinToInterrupt(B3), Pb_3, FALLING);
  attachInterrupt(digitalPinToInterrupt(B4), Pb_4, FALLING);

  Serial.println("Finishing. . .");
  delay(5000);
}

void loop() {

  Serial.println(" MODE STANDBY : " + String(digitalRead(B1)));
  
  delay(500);
  bunyi();

}

void Pb_1 () {
  while(digitalRead(B1) == LOW){};
    Serial.print(" STATUS R1 : ");

    if (StatusR[0] == LOW) {
      StatusR[0] = 1;
      digitalWrite(R1, LOW);
      Serial.println("  > ON <");
    } else {
      StatusR[0] = 0;
      digitalWrite(R1, HIGH);
      Serial.println("  > OFF <");
    }
}
void Pb_2 () {
  while(digitalRead(B2) == LOW){};
    Serial.print(" STATUS R2 : ");

    if (StatusR[1] == LOW) {
      StatusR[1] = 1;
      digitalWrite(R2, LOW);
      Serial.println("  > ON <");
    } else {
      StatusR[1] = 0;
      digitalWrite(R2, HIGH);
      Serial.println("  > OFF <");
    }
}
void Pb_3 () {
  while(digitalRead(B3) == LOW){};
    Serial.print(" STATUS R3 : ");

    if (StatusR[2] == LOW) {
      StatusR[2] = 1;
      digitalWrite(R3, LOW);
      Serial.println("  > ON <");
    } else {
      StatusR[2] = 0;
      digitalWrite(R3, HIGH);
      Serial.println("  > OFF <");
    }
}
void Pb_4 () {
  while(digitalRead(B4) == LOW){};
    Serial.print(" STATUS R4 : ");

    if (StatusR[3] == LOW) {
      StatusR[3] = 1;
      digitalWrite(R4, LOW);
      Serial.println("  > ON <");
    } else {
      StatusR[3] = 0;
      digitalWrite(R4, HIGH);
      Serial.println("  > OFF <");
    }
}

void bunyi() {
  tone(31, 800);
  delay(300);
  noTone(31);
}
