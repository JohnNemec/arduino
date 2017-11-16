#include <DS3231.h>
#include <TM1637Display.h>

DS3231 Clock;
#define DS3231_I2C_ADDRESS 0x68

// Module connection pins (Digital Pins)
#define CLK 8
#define DIO 9
const int modeBtn = 2;

byte screenState = 1;
int oldState = 1;

bool h12;
bool AM;
int hour;
int minute;
int clockTime;
int temp;

TM1637Display display(CLK, DIO);


/* Note to self
 *  Connect SDA to A4
 *  Connect SCL to A5
 */

const uint8_t SEG_DEGREE[] = {
  SEG_A | SEG_B | SEG_F | SEG_G            // degree symbol
};

void displayTime() {
  hour = Clock.getHour(h12, AM);
  minute = Clock.getMinute();

  String h = String(hour);
  String m = String(minute);
  if (minute < 10) {
    m = "0" + m;
  }
  String stringTime = h + m;
  clockTime = stringTime.toInt();

  display.setColon(true);
  display.showNumberDec(clockTime, false, 4, 0);
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(modeBtn,INPUT);

  // Let the code know about the interrupt
  attachInterrupt(0, pin_ISR, RISING);

  display.setBrightness(0x0f);
  Clock.setClockMode(true);
}

void pin_ISR() {
  screenState = (screenState == 1) ? 2 : 1;
}

void loop() {

  switch(screenState) {
    case 1: // show the time
      if(oldState != screenState) {
        oldState = screenState;
        displayTime();
        break;
      } else {
        displayTime();
        break;
      }

    case 2: // Alarm Display
      if(oldState != screenState) {
        oldState = screenState;
        displayTemp();
        break;
      } else {
        displayTemp();
        break;
      }
  }
}

void displayTemp() {
  temp = (Clock.getTemperature() * 1.8 + 32), 0;

  if(temp >= 100) {
    display.showNumberDec(temp, false, 3, 0);
  } else {
    display.showNumberDec(temp, false, 3, 0);
  }

  display.setSegments(SEG_DEGREE, 1, 3);

}


