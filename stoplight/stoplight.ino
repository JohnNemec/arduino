int trigPin = 13;
int echoPin = 11;
int redLED = 3;
int yellowLED = 4;
int greenLED = 5;
float pingTime;     // Time for ping to travel to target and return
float distance;     // Distance from sensor to target
float speedOfSound = 776.5;   // Speed of Sound in Miles per hour


void setup() {

  Serial.begin(9600);

  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

  pinMode(redLED,OUTPUT);
  pinMode(yellowLED,OUTPUT);
  pinMode(greenLED,OUTPUT);

}

void loop() {

  digitalWrite(trigPin,LOW);
  delayMicroseconds(500);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(20);
  digitalWrite(trigPin,LOW);

  pingTime = pulseIn(echoPin, HIGH);
  pingTime = pingTime/1000000./3600; // Converts ping time to hours
  distance = speedOfSound * pingTime/2*63360; // Calculates round trip distance in inches

  // Red Light
  if (distance < 7) {
    digitalWrite(greenLED,LOW);
    digitalWrite(yellowLED,LOW);
    digitalWrite(redLED,HIGH);
  }
  // Yellow Light
  else if (distance >= 7 && distance < 14) {
    digitalWrite(greenLED,LOW);
    digitalWrite(yellowLED,HIGH);
    digitalWrite(redLED,LOW);
  } 
  // Green Light
  else {
    digitalWrite(greenLED,HIGH);
    digitalWrite(yellowLED,LOW);
    digitalWrite(redLED,LOW);
  }
  
  Serial.print("The distance to the target is: ");
  Serial.print(distance);
  Serial.println(" inches");
  delay(500);

}
