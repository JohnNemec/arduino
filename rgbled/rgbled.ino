int red=11;         // Set red LED pin to 11
int green=10;       // Set green LED pin to 10
int blue=6;         // Set blue LED pin to 6
int on=150;  // Set brightness to 75
int off=0;          // Turn off

void setup() {
  Serial.begin(9600);   // Turn on Serial Port
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(blue,OUTPUT);

}

void loop() {
  analogWrite(red,on);
  analogWrite(green,on);
  analogWrite(blue,on);

}
