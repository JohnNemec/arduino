int red=3;
int voltvalue;

void setup() {
  Serial.begin(9600);
  pinMode(red,OUTPUT);
}

void loop() {
  Serial.println("What voltage do you want to apply to the Red LED? 1-255");
  while(Serial.available()==0) {}
  voltvalue = Serial.parseInt();

  if (voltvalue > 102) {
    Serial.println("That may burn out the LED, try something lower.");
  } else {
    analogWrite(red,voltvalue);
    Serial.print("WOW! ");
    Serial.print( voltvalue );
    Serial.println( " was a nice pick" );
    delay(5000);
    
  }

  analogWrite(red,0);
}
