#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3

const uint8_t SEG_DONE[] = {
  SEG_D | SEG_E | SEG_F,
  SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
  SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
  SEG_A | SEG_D | SEG_E | SEG_F | SEG_G
};

TM1637Display display(CLK, DIO);


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  display.setBrightness(0x0f);
  display.setSegments(SEG_DONE);
}
