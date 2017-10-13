byte redLED = 7;
byte yellowLED = 4;

int redOn = 500;
int redOff = 250;
int yellowOn = 500;
int yellowOff = 250;

int redBlink = 6;
int yellowBlink = 4;

int loopCount = 0;

void setup() {

  Serial.begin(9600);
  pinMode(redLED,OUTPUT);
  pinMode(yellowLED,OUTPUT);

}

void loop() {

  Serial.println("");
  Serial.println("RED");
  for(int x = 0; x < redBlink; x++) {
    Serial.println(x+1);
    digitalWrite(redLED,HIGH);
    delay(redOn);
    digitalWrite(redLED,LOW);
    delay(redOff);
  }

  Serial.println("");
  Serial.println("YELLOW");
  for(int j = 0; j < yellowBlink; j++) {
    Serial.println(j+1);
    digitalWrite(yellowLED,HIGH);
    delay(yellowOn);
    digitalWrite(yellowLED,LOW);
    delay(yellowOff);
  }
  loopCount++;
  Serial.println("");
  Serial.print("The program has run ");
  Serial.print(loopCount);
  Serial.println(" time!");
  Serial.println("");

}
