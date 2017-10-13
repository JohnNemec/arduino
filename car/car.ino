// Motor A
int enA = 9;
int in1 = 8;
int in2 = 7;

// Motor B
int enB = 3;
int in3 = 5;
int in4 = 4;

int carSpeed;
int farSpeed = 200;
int closeSpeed = 100;
int slowSpeed = 50;


// Distance Sensor
int trigPin = 13;
int echoPin = 11;
float pingTime;     // Time for ping to travel to target and return
float distance;     // Distance from sensor to target
float speedOfSound = 776.5;   // Speed of Sound in Miles per hour

void setup() {
  Serial.begin(9600);

  // Motor control pins
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Distance Sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
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

  Serial.print("The distance to the target is: ");
  Serial.print(distance);
  Serial.println(" inches");
  delay(500);
  

  if (distance > 24) {
    carSpeed = farSpeed;
    moveForward(carSpeed);
  }
  else if (distance > 12 && distance <= 24) {
    carSpeed = closeSpeed;
    moveForward(carSpeed);
  }
  else if (distance > 5 && distance <= 12) {
    carSpeed = slowSpeed;
    stopCar();
    reverse(carSpeed);
    turnRight(carSpeed);
  } 
  else {
    stopCar();
  }
    
}


void moveForward(int carSpeed) {
  /* Move forward */

  // Motor A
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // Set Speed
  analogWrite(enA, carSpeed);

  // Motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // Set Speed
  analogWrite(enB, carSpeed);

}

void stopCar() {
  // Turn motors off
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(1000);
}

void reverse(int carSpeed) {
  /* Move Backward */

  // Motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // Set Speed
  analogWrite(enA, carSpeed);

  // Motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  // Set Speed
  analogWrite(enB, carSpeed);

  delay(2000);
}

void turnRight(int carSpeed){
  /* Turn right by stopping reversing right and move forward left */

  // Motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // Set Speed
  analogWrite(enA, carSpeed);

  // Motor B
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  // Set Speed
  analogWrite(enB, carSpeed);

  delay(2000);

}
