// Define Pins
int bluePin = 3;
int greenPin = 5;
int redPin = 6;
int stoptime = 1000;

#define COMMON_ANODE

// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);

}

// the loop function runs over and over again forever
void loop() {
  setColor(255, 0, 0); // red
  delay(stoptime);
  setColor(0, 255, 0); // green
  delay(stoptime);
  setColor(0, 0, 255); // blue
  delay(stoptime);
  setColor(255, 255, 0); // yellow
  delay(stoptime);
  setColor(80, 0, 80); // purple
  delay(stoptime);
  setColor(0, 255, 255); // aqua
  delay(stoptime);
}

void setColor(int red, int green, int blue) {
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}


