//www.elegoo.com
//2016.12.08
/*****************************************/
const int ledPin = 13;//the led attach to
int buzzer = 12; //the pin of the active buzzer

void setup()
{ 
  pinMode(ledPin,OUTPUT);//initialize the ledPin as an output
  pinMode(2,INPUT);
  pinMode(buzzer,OUTPUT);//initialize the buzzer pin as an output
  digitalWrite(2, HIGH);
} 
/******************************************/
void loop() 
{  
  int digitalVal = digitalRead(2);
  if(HIGH == digitalVal)
  {
    digitalWrite(ledPin,LOW);//turn the led off
    digitalWrite(buzzer,LOW);
  }
  else
  {
    digitalWrite(ledPin,HIGH);//turn the led on 
    
    digitalWrite(buzzer,HIGH);
    delay(2);//wait for 1ms
    digitalWrite(buzzer,LOW);
    delay(2);//wait for 1ms
  }
}
/**********************************************/

