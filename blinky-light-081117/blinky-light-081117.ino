int red=2;
int blue=4;
int green=6;
int white=8;
int yellow=10;

int waitTime=100;
int medTime=250;
int longTime=1000;

int howManyRuns;
int howManyFlashes;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(red,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(white,OUTPUT);
  pinMode(yellow,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println("How Many Runs?");
  while(Serial.available()==0) {};
  howManyRuns = Serial.parseInt();
  Serial.println("How Many Flashes");
  while(Serial.available()==0) {};
  howManyFlashes = Serial.parseInt();

  for (int i=1; i<=howManyRuns; i=i+1) {

    digitalWrite(red,HIGH);
    digitalWrite(blue,LOW);
    digitalWrite(green,LOW);
    digitalWrite(white,LOW);
    digitalWrite(yellow,LOW);
    delay(waitTime);

    digitalWrite(red,LOW);
    digitalWrite(blue,HIGH);
    digitalWrite(green,LOW);
    digitalWrite(white,LOW);
    digitalWrite(yellow,LOW);
    delay(waitTime);

    digitalWrite(red,LOW);
    digitalWrite(blue,LOW);
    digitalWrite(green,HIGH);
    digitalWrite(white,LOW);
    digitalWrite(yellow,LOW);
    delay(waitTime);

    digitalWrite(red,LOW);
    digitalWrite(blue,LOW);
    digitalWrite(green,LOW);
    digitalWrite(white,HIGH);
    digitalWrite(yellow,LOW);
    delay(waitTime);

    digitalWrite(red,LOW);
    digitalWrite(blue,LOW);
    digitalWrite(green,LOW);
    digitalWrite(white,LOW);
    digitalWrite(yellow,HIGH);
    delay(waitTime);
  }
  

  digitalWrite(red,HIGH);
  digitalWrite(blue,HIGH);
  digitalWrite(green,HIGH);
  digitalWrite(white,HIGH);
  digitalWrite(yellow,HIGH);
  delay(longTime);

  digitalWrite(red,LOW);
  digitalWrite(blue,LOW);
  digitalWrite(green,LOW);
  digitalWrite(white,LOW);
  digitalWrite(yellow,LOW);
  delay(medTime);

  digitalWrite(red,HIGH);
  digitalWrite(blue,HIGH);
  digitalWrite(green,HIGH);
  digitalWrite(white,HIGH);
  digitalWrite(yellow,HIGH);
  delay(longTime);

  digitalWrite(red,LOW);
  digitalWrite(blue,LOW);
  digitalWrite(green,LOW);
  digitalWrite(white,LOW);
  digitalWrite(yellow,LOW);
  delay(medTime);

  for (int j; j<=howManyFlashes; j=j+1) {
    digitalWrite(red,HIGH);
    digitalWrite(blue,HIGH);
    digitalWrite(green,HIGH);
    digitalWrite(white,HIGH);
    digitalWrite(yellow,HIGH);
    delay(waitTime);

    digitalWrite(red,LOW);
    digitalWrite(blue,LOW);
    digitalWrite(green,LOW);
    digitalWrite(white,LOW);
    digitalWrite(yellow,LOW);
    delay(waitTime);
  }

  digitalWrite(red,LOW);
  digitalWrite(blue,LOW);
  digitalWrite(green,LOW);
  digitalWrite(white,LOW);
  digitalWrite(yellow,LOW);

/*  
  digitalWrite(red,LOW);
  digitalWrite(blue,LOW);
  digitalWrite(green,LOW);
  digitalWrite(white,LOW);
  digitalWrite(yellow,LOW);
*/
}
