#include "TM1637.h"

#define CLK 3//Pins for TM1637
#define DIO 4

TM1637 DIS(CLK,DIO);

void setup() {
  DIS.init();
  DIS.set(BRIGHT_TYPICAL); //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;

  delay(1500); // Delay to let the system boot
}

void loop() {
  
  
}
