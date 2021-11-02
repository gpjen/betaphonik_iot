
#define R1 38
#define R2 39
#define R3 40
#define R4 41
int N = 1;

void setup() {
  Serial.begin(9600);

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);

  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(R3, HIGH);
  digitalWrite(R4, HIGH);

  Serial.println("Initialize....");

  delay(3000);

}

void loop() {

  Serial.println("Tahap : " + String(N));
  delay(5000);

  for (int j = 38; j <= 41; j++) {
    digitalWrite(j, LOW);
    Serial.print(digitalRead(j));
    delay(2000);
    digitalWrite(j, HIGH);
    Serial.println(digitalRead(j));
    delay(2000);
  }
  N = N + 1;  

}
