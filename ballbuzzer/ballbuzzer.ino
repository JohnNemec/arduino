int tiltball = 2; // the pin of the Tilt Ball Switch
// for late night work, replace the Active Buzzer with an LED to not wake up the wife :)
// int buzzer = 13; // Quiet Buzzer - you can replace with the onboard LED
int buzzer = 12; // the pin of the Active Buzzer

void setup() {
  pinMode(tiltball,INPUT); // initialize the Tilt Ball Switch as an input
  pinMode(buzzer,OUTPUT); // initialize the Active Buzzer pin as an output

  // This confuses me, I'm assuming HIGH means connected but in practice it is not
  digitalWrite(tiltball, HIGH); // turn the tiltball on
}

void loop() {
  int digitalVal = digitalRead(tiltball);

  if(HIGH == digitalVal) { // so when the tiltball is pointed down turn off the buzzer. But HIGH to me means on, but in truth it is off
    digitalWrite(buzzer,LOW); // turn Active Buzzer off
  } else {
    digitalWrite(buzzer,HIGH); // turn Active Buzzer on
    delay(2); // wait for 1ms
    digitalWrite(buzzer,LOW); // turn Active Buzzer off
    delay(2); // wait for 1ms
  }
}
