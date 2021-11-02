int R1 = 1000; // Value of resistor for EC probe
int EC_Read = A1;
int ECPower = A0;
int Temp_pin = 33;

float Temp_C; // Do not change
float Temp_F; // Do not change
float Temp1_Value = 0;
float Temp_Coef = 0.019; // You can leave as it is
/////////////////This part needs your attention during calibration only///////////////
float Calibration_PPM = 1080 ; //Change to PPM reading measured with a separate meter
float K = 1.89; //You must change this constant once for your probe(see video)
float PPM_Con = 0.5; //You must change this only if your meter uses a different factor
/////////////////////////////////////////////////////////////////////////////////////
float CalibrationEC = (Calibration_PPM * 2) / 1000;
float Temperature;
float EC;
float EC_at_25;
int ppm;
float A_to_D = 0;
float Vin = 5;
float Vdrop = 0;
float R_Water;
float Value = 0;


///////////////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(9600);
  pinMode(EC_Read, INPUT);
  pinMode(ECPower, OUTPUT);
  //////////////////////////////////////////////////////////////////////////////////////////
  //Calibrate (); // After calibration put two forward slashes before this line of code
  //////////////////////////////////////////////////////////////////////////////////////////
}

void loop(){
  GetEC();
  delay(6000);
}

  ////////////////////////////////////////////////////////////////////////////////////
  void Calibrate (){
    Serial.println("Calibration routine started");
    float Temperature_end = 0;
    float Temperature_begin = 0;
    int val;
    double Temp;
    val = analogRead(Temp_pin);
    Temp = log(((10240000 / val) - 10000));
    Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp);
    Temp_C = Temp - 273.15; // Kelvin to CelsiusTemp_F = (Temp_C * 9.0)/ 5.0 + 32.0; // Celsius to Fahrenheit
    Temp1_Value = Temp_C;
    Temperature_begin = Temp_C;
    Value = 0;
    int i = 1;
    while (i <= 10) {
      digitalWrite(ECPower, HIGH);
      A_to_D = analogRead(EC_Read);
      A_to_D = analogRead(EC_Read);
      digitalWrite(ECPower, LOW);
      Value = Value + A_to_D;
      i++;
      delay(6000);
    };
    A_to_D = (Value / 10);
    val = analogRead(Temp_pin);
    Temp = log(((10240000 / val) - 10000));
    Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp);
    Temp_C = Temp - 273.15; // Kelvin to Celsius
    Temp_F = (Temp_C * 9.0) / 5.0 + 32.0; // Celsius to Fahrenheit
    Temp1_Value = Temp_C;
    Temperature_end = Temp_C;
    EC = CalibrationEC * (1 + (Temp_Coef * (Temperature_end - 25.0)));
    Vdrop = (((Vin) * (A_to_D)) / 1024.0);
    R_Water = (Vdrop * R1) / (Vin - Vdrop);
    float K_cal = 1000 / (R_Water * EC);
    Serial.print("Replace K in line 23 of code with K = ");
    Serial.println(K_cal);
    Serial.print("Temperature difference start to end were = ");
    Temp_C = Temperature_end - Temperature_begin;
    Serial.print(Temp_C);
    Serial.println("*C");
    Serial.println("Temperature difference start to end must be smaller than 0.15*C");
    Serial.println("");
    Calibrate ();
  }


  ////////////////////////////////////////////////////////////////////////////////////
void GetEC() {
  int val;
  double Temp;
  val = analogRead(Temp_pin);
  Temp = log(((10240000 / val) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp);
  Temp_C = Temp - 273.15; // Kelvin to Celsius
  Temp_F = (Temp_C * 9.0) / 5.0 + 32.0; // Celsius to Fahrenheit
  Temp1_Value = Temp_C;
  Temperature = Temp_C;
  digitalWrite(ECPower, HIGH);
  A_to_D = analogRead(EC_Read);
  A_to_D = analogRead(EC_Read);
  digitalWrite(ECPower, LOW);
  Vdrop = (Vin * A_to_D) / 1024.0;
  R_Water = (Vdrop * R1) / (Vin - Vdrop);
  EC = 1000 / (R_Water * K);
  EC_at_25 = EC / (1 + Temp_Coef * (Temperature - 25.0));
  ppm = (EC_at_25) * (PPM_Con * 1000);
  Serial.print(" EC: ");
  Serial.print(EC_at_25);
  Serial.print(" milliSiemens(mS/cm) ");
  Serial.print(ppm);
  Serial.print(" ppm ");
  Serial.print(Temperature);
  Serial.println(" *C ");
}
