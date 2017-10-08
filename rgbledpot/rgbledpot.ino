int bluePin = 6;
int greenPin = 10;
int redPin = 11;

/* Pot info */
int potPin = A0;
int readValue;
int writeValue;
float Voltage;

/* brightness control variables */
int redBrightness = 0;
int greenBrightness = 0;
int blueBrightness = 0;

void setup() {

  Serial.begin(9600);
  pinMode(bluePin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(redPin,OUTPUT);
  pinMode(potPin,INPUT);
}

void loop() {

  readValue = analogRead(potPin);
  Voltage = (5./1023.)*readValue;
  writeValue = (255./1023.) * readValue;

  Serial.print("\tVolts=");
  Serial.print(Voltage);
  delay(20);

  // RED
  if(Voltage < .625) {
    Serial.println("\tRED");
    analogWrite(redPin, 0);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 255);
  }

  // PINK
  else if (Voltage >= .625 && Voltage < 1.25) {
    Serial.println("\tPINK");
    analogWrite(redPin, 0);
    analogWrite(greenPin, 205);
    analogWrite(bluePin, 205);
  }
  
  // ORANGE
  else if (Voltage >= 1.25 && Voltage < 1.875) {
    Serial.println("\tORANGE");
    analogWrite(redPin, 5);
    analogWrite(greenPin, 215);
    analogWrite(bluePin, 255);
  }

  // YELLOW
  else if (Voltage >= 1.875 && Voltage < 2.5) {
    Serial.println("\tYELLOW");
    analogWrite(redPin, 50);
    analogWrite(greenPin, 50);
    analogWrite(bluePin, 255);
  }

  // GREEN
  else if (Voltage >= 2.5 && Voltage < 3.125) {
    Serial.println("\tGREEN");
    analogWrite(redPin, 255);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 255);
  }

  // BLUE
  else if (Voltage >= 3.125 && Voltage < 3.75) {
    Serial.println("\tBLUE");
    analogWrite(redPin, 255);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
  }

  // PURPLE
  else if (Voltage >= 3.75 && Voltage < 4.375) {
    Serial.println("\tPURPLE");
    analogWrite(redPin, 50);
    analogWrite(greenPin, 255);
    analogWrite(bluePin, 0);
  }

  // WHITE
  else {
    Serial.println("\tWHITE");
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  }
}
