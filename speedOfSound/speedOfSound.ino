/*
 * Speed of Sound = Distance / Time
 */

int trigPin = 13;
int echoPin = 11;
float pingTime;       // Time for ping to hit target and return
float speedOfSound;   // Calculate the Speed of Sound
float distance = 8.5; // Measure the distance to the sensor 

void setup() {

  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  
}

void loop() {

  // Send the ping 
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2000);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the ping
  pingTime = pulseIn(echoPin, HIGH);

  // Calculate the Speed of Sound
  speedOfSound = 2 * distance / pingTime; // Speed in inches per microseconds

  // Convert to miles per hour
  speedOfSound = speedOfSound/63360.*1000000.*3600.;

  Serial.print("The Speed of Sound is: ");
  Serial.print(speedOfSound);
  Serial.println(" miles per hour.");
  delay(3000);
}
