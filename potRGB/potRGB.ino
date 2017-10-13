int redPin = 11;
int greenPin = 10;
int bluePin = 6;
int potPin = A0;

int readVal;
int red;
int green;
int blue;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(potPin, INPUT);
}

void loop() {
  readVal = analogRead(potPin);   // pot number 0 - 1023
  red = (255./1023.) * readVal;
  green = (255./1023.) * readVal;
  blue = (255./1023.) * readVal;

  Serial.print("Red value: ");
  Serial.println(red);
  
  Serial.print("Green value: ");
  Serial.println(green);
  
  Serial.print("Blue value: ");
  Serial.println(blue);
  Serial.println("");
  delay(250);

  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);

  Serial.print(red);
  Serial.print(", ");
  Serial.print(green);
  Serial.print(", ");
  Serial.println(blue);
  delay(500);
}
