void setup() {
  Serial.begin(9600);

}

void loop() {
  int j=0; // Declare that j is an int and set it to 2

  while( j<=100 ) {
    Serial.print("You are on Loop Number ");
    Serial.println(j);
    delay(250);
    j=j+5;
  }
  Serial.println(" ");
}
