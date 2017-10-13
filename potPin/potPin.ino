int LEDPin = 9;           // Assign LEDPin to 9
int potPin = A0;          // Assign potPin to A0
int readValue;            // Declare readValue var
int writeValue;           // Declare writeValue as var
float Voltage;            // Declare voltage var
float dVal;               // The delay value

void setup() {
  Serial.begin(9600);
  pinMode(LEDPin, OUTPUT);
  pinMode(potPin,INPUT);
  
}

void loop() {
  readValue = analogRead(potPin);
  Voltage = (5./1023.)*readValue;   // Calculating the real world voltage
  writeValue = (255./1023.) * readValue;
  dVal = (-900./255.) * writeValue + 1000;

  analogWrite(LEDPin, writeValue);
  delay(dVal);
  analogWrite(LEDPin, 0);
  delay(dVal);

  
  Serial.print(Voltage);
  Serial.println(" volts");
  Serial.print(dVal);
  Serial.println(" delay speed");
  Serial.print(writeValue);
  Serial.println(" power to LED");
  Serial.println("");
  delay(250);
  
  
}
