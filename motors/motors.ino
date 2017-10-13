int mot1 = 7;
int mot2 = 8;
int onTime = 2000;
String start;

void setup() {
  // put your setup code here, to run once:
  pinMode(mot1, OUTPUT);
  pinMode(mot2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Type YES to start.");
  while(Serial.available()==0) {};
  start = Serial.readString();

  while( start=="YES" ) {
    digitalWrite(mot1,HIGH);
    delay(onTime);
  
    digitalWrite(mot1,LOW);
    digitalWrite(mot2,HIGH);
    delay(onTime);
  
    digitalWrite(mot1,HIGH);
    delay(onTime);
  
    digitalWrite(mot1,LOW);
    digitalWrite(mot2,LOW);

    start= "NO";
  }
}
