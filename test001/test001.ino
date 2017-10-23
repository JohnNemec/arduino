#include <ps2.h>

/*
 * this is a modification to the original ps2 mouse sketch, it requires ps2 library,
 * can be found on arduino website.
 * Modified by Jabbar Ali.
 * Feel free to use or modify.
 * an arduino sketch to interface with a   mouse ( optical, ball, ps2 and usb).
 * it measures the distance the mouse travels.
 * a button is used to zero the reading.
 * one side of the button is connected to pin 7 other to ground. 
 * it writes the results to the serial port.
 */

/*
 * Pin 5 is the mouse data pin, pin 6 is the clock pin
 * Feel free to use whatever pins are convenient.
 */
PS2 mouse(6, 10);
int newmx=0;
int newmy=0;
int zeroPin=7; // to zero the counter
 
/*
 * initialize the mouse. Reset it, and place it into remote
 * mode, so we can get the encoder data on demand.
 */
void mouse_init() {
  mouse.write(0xff);  // reset
  mouse.read();  // ack byte
  mouse.read();  // blank */
  mouse.read();  // blank */
  mouse.write(0xf0);  // remote mode
  mouse.read();  // ack
  delayMicroseconds(100);
}

void setup() {
  pinMode(zeroPin, INPUT_PULLUP);
  Serial.begin(9600);
  mouse_init();
}
/*
* get a reading from the mouse and report it back to the
* host via the serial line.
*/
void loop() {
  char mstat;
  char mx;
  char my;
 
  /* get a reading from the mouse */
  mouse.write(0xeb);  // give me data!
  mouse.read();      // ignore ack
  mstat = mouse.read();
  //Serial.print("mstat: ");
  //Serial.println(mstat);
  mx = mouse.read();
  //Serial.print("mx: ");
  //Serial.println(mx);
  my = mouse.read();
  //Serial.print("my: ");
  //Serial.println(my, OCT);
  //delay(500);
  
  if ( digitalRead(zeroPin) == LOW) {
    newmy=0;
    newmx=0;
  }
  else {
    newmx=newmx+ mx;
    newmy=newmy+my;    

    Serial.print("\tX=");
    Serial.print(newmx/(18.500));// gives mm reading for my  mouse
    Serial.print("\tY=");
    Serial.print(newmy/(18.500));//  gives mm reading for my  mouse
    Serial.println();

  }
}
