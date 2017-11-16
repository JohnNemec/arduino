#include <LiquidCrystal_I2C.h>
#include <DS3231.h>
#include <Wire.h>

DS3231 Clock;
DateTime dt;
RTClib RTC;

bool Century=false;
bool h12;
bool AM;
int hour;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;
byte Alarm = 2;
int temp;

byte screenState = 1;
int oldState = 1;

unsigned long currentMillis = 0;
unsigned long previousMillis = 0;        // will store last time LED was updated
int alarmDisplayInterval = 5000;


// Set Pins
const int btnOne = 2;    // pushbutton pin, set to 2 so it can be used as an interrupt
const int setBtn = 4;    // the setBtn, set to pin 4, this button changes the display options
const int actionBtn = 5; // the Action button set to pin 5, this button sets the options
const int buz = 11;      // Buzzer pin set to 11

// Custom Displays
// Alarm Icon
byte alarmIcon[8] = {
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B00100,
  B00000
};

// set the LCD address to 0x27 for a 16 chars 2 line display
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

/* Note to self
 *  Connect SDA to A4
 *  Connect SCL to A5
 */

void setup() {
  // Start the I2C interface
  Wire.begin();
  // Start the serial interface
  Serial.begin(9600);

  // Set the pins INPUT or OUTPUT
  pinMode(buz,OUTPUT);
  pinMode(btnOne,INPUT);
  pinMode(setBtn,INPUT);
  pinMode(actionBtn,INPUT);

  // Let the code know about the interrupt
  attachInterrupt(0, pin_ISR, RISING);

  Clock.setClockMode(true);

  // initialize the lcd for 16 chars 2 lines, turn on backlight
  lcd.begin(16,2);
  // ------- Quick 3 blinks of backlight  -------------
  for(int i = 0; i< 3; i++) {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); // finish with backlight on
  lcd.createChar(7, alarmIcon);

  //Clock.setA2Time(3, 12, 18, 0, 1, 1, 1);
  Clock.getA2Time(ADay, AHour, AMinute, ABits, ADy, A12h, Apm);
  currentMillis = millis();
}

void pin_ISR() {
  screenState = (screenState == 1) ? 2 : 1;
}

void loop() {
  // check to see if it's time to change the state of the LCD
  currentMillis = millis();

  switch(screenState) {
    case 1:   // Date/Time/Temp Display
      if(oldState != screenState) {
        oldState = screenState;
        lcd.clear();
        displayDoW();
        displayDate();
        displayTime();
        if(digitalRead(setBtn)) {
          toggleAlarm();
        }
        displayTempature();
        break;
      } else {
        displayDoW();
        displayDate();
        displayTime();
        if(digitalRead(setBtn)) {
          toggleAlarm();
        }
        displayTempature();
        break;
      }

    case 2:   // Alarm Display
      if(oldState != screenState) {
        oldState = screenState;
        lcd.clear();
        viewAlarmTime(); 
        break;
      } else {
        viewAlarmTime(); 
        break;
      }
      
  }
    

/*
  if(digitalRead(setBtn)) {
    lcd.clear();
    
    lcd.clear();
  }
  */
}

void displayTime() {
  lcd.setCursor(0,1);

  hour = Clock.getHour(h12, AM); //24-hr
  if(hour < 10){
    lcd.print(" ");
    lcd.print(hour);
  } else {
    lcd.print(hour);
  }
  
  lcd.print(":");
  if(Clock.getMinute() < 10) {
    lcd.print("0");
    lcd.print(Clock.getMinute(), DEC);
  } else {
    lcd.print(Clock.getMinute(), DEC);
  }
}

void displayDoW() {
  lcd.setCursor(0,0);
  switch(Clock.getDoW()) {
    case 1:
      lcd.print("Sun");
      break;
    case 2:
      lcd.print("Mon");
      break;
    case 3:
      lcd.print("Tues");
      break;
    case 4:
      lcd.print("Wed");
      break;
    case 5:
      lcd.print("Thur");
      break;
    case 6:
      lcd.print("Fri");
      break;
    case 7:
      lcd.print("Sat");
      break;
  }
}

void displayDate() {
  if(Clock.getMonth(Century) < 10){
    lcd.setCursor(9,0);
  } else {
    lcd.setCursor(8,0);
  }
  lcd.print(Clock.getMonth(Century));
  lcd.print("/");
  lcd.print(Clock.getDate());
  lcd.print("/");
  lcd.print(Clock.getYear());
}

void toggleAlarm() {
  lcd.setCursor(6,1);
  if(Clock.checkAlarmEnabled(Alarm)){
    Clock.turnOffAlarm(Alarm);
    lcd.print(" ");
  } else {
    Clock.turnOnAlarm(Alarm);
    lcd.write(7);
  }
  delay(500);
}

void displayTempature() {
  temp = (Clock.getTemperature() * 1.8 + 32), 0;
  if(temp >= 100) {
    lcd.setCursor(11,1);
  } else {
    lcd.setCursor(12,1);
  }
  lcd.print( temp );
  lcd.print((char)223);
  lcd.print("F");
}

void viewAlarmTime() {
  delay(500);
  lcd.setCursor(0,0);
  lcd.print("Alarm");
  lcd.setCursor(0,1);
  lcd.print(AHour);
  lcd.print(":");
  lcd.print(AMinute);

  if(digitalRead(actionBtn)) {
    Serial.println(digitalRead(actionBtn));
    int blinkTextState = 1;
    unsigned long currentMillis = millis();
    unsigned long futureMillis = currentMillis + 1000000;
    int blinkState = 0;

    while(blinkTextState == 1) {
      if (blinkState == 0) {
        lcd.setCursor(0,1);
        lcd.print("  ");
        blinkState = 1;
        delay(500);
      } else {
        lcd.setCursor(0,1);
        lcd.print(AHour);
        blinkState = 0;
        delay(500);
      }
      if(digitalRead(setBtn)) {
        AHour = AHour + 1;
        if (AHour > 23) {
          AHour = 00;
        }
      }
      if(digitalRead(actionBtn)) {
        blinkTextState = 2;
      }
    }

    while(blinkTextState == 2) {
      if (blinkState == 0) {
        lcd.setCursor(3,1);
        lcd.print("  ");
        blinkState = 1;
        delay(500);
      } else {
        lcd.setCursor(3,1);
        lcd.print(AMinute);
        blinkState = 0;
        delay(500);
      }
      if(digitalRead(setBtn)) {
        AMinute = AMinute + 1;
        if (AMinute > 59) {
          AMinute = 00;
        }
      }
      if(digitalRead(actionBtn)) {
        Clock.setA2Time(3, AHour, AMinute, 0, 1, 1, 1);
        viewAlarmTime();
      }
    }
    
  }
}

