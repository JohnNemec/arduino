#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>


#define DS3231_I2C_ADDRESS 0x68
#define buz 11

DS3231 Clock;
byte ADay, AHour, AMinute, ASecond, ABits;
bool ADy, A12h, Apm;

const int btnOne = 2; // pushbutton pin, set to 2 so it can be used as an interrupt
const int setBtn = 4; // the setBtn, set to pin 4
volatile int btnOneState;
byte cancelAlarm;
byte alarmSet;
volatile byte alarmSetState;
byte alarmIsSounding;

byte alarmIcon[8] = {
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B00100,
  B00000
};

String ampm;

// set the LCD address to 0x27 for a 16 chars 2 line display
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

/* Note to self
 *  Connect SDA to A4
 *  Connect SCL to A5
 */

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val) { 
  return( (val/10*16) + (val%10) );
}

// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val) { 
  return( (val/16*10) + (val%16) );
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(buz,OUTPUT);

  pinMode(btnOne,INPUT);
  pinMode(setBtn,INPUT);
  attachInterrupt(0, pin_ISR, CHANGE);
  
  // set the initial time here:
  // DS3231 seconds, minutes, hours, day, date, month, year
  // setDS3231time(45,7,23,6,20,10,17);

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

}

void pin_ISR() {
  if (alarmIsSounding == 1) {
    btnOneState = digitalRead(btnOne);
    if (btnOneState == HIGH) {
      cancelAlarm = 1;
      stopAlarm();
    }
  } else {
    alarmSetState = digitalRead(btnOne);
    Serial.print("alarmSetState: ");
    Serial.println(alarmSetState);
    if ( alarmSetState == HIGH ) {
      if ( alarmSet == 1 ) {
        alarmSet = 0; // turn the alarm off
      } else {
        alarmSet = 1; // turn the alarm on
      }
    }
  }
}

void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year) {
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the second register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}

void readDS3231time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year) {
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set the DS3231 register pointer to 00h
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7); // Request seven bytes of data from DS3231 starting from register 00h
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}

void displayTime(String ampm) {
  //-------- Write characters on the display ------------------
  // NOTE: Cursor Position: (CHAR, LINE) start at 0
  lcd.clear();
  lcd.setCursor(0,1);
  
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // retrieve data from DS3231
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  // send it to the LCD
  if (hour>12) {
    hour = hour - 12;
    ampm = "pm";
    lcd.print(hour, DEC);
  } else {
    lcd.print(hour, DEC);
    ampm = "am";
  }

  // convert the byte variable to a decimal number when displayed
  lcd.print(":");
  if (minute<10) {
    lcd.print("0");
  }
  lcd.print(minute, DEC);
  lcd.print(ampm);

  lcd.setCursor(8,1);
  //lcd.print(" ");
  lcd.print(month, DEC);
  lcd.print("/");
  lcd.print(dayOfMonth, DEC);
  lcd.print("/");
  lcd.print(year, DEC);

  lcd.setCursor(0,0);
  switch(dayOfWeek) {
    case 1:
      lcd.print("Sunday");
      break;
    case 2:
      lcd.print("Monday");
      break;
    case 3:
      lcd.print("Tuesday");
      break;
    case 4:
      lcd.print("Wednesday");
      break;
    case 5:
      lcd.print("Thursday");
      break;
    case 6:
      lcd.print("Friday");
      break;
    case 7:
      lcd.print("Saturday");
      break;
  }

  //Serial.print("alarmSetState: ");
  //Serial.print(alarmSetState);
  //Serial.print("\talarmSet: ");
  //Serial.println(alarmSet);
  if (alarmSet == 1) {
    lcd.setCursor(15,0);
    lcd.write(7);

    soundAlarm(hour, minute, ampm);
  } else if (alarmSet != 1) {
    lcd.setCursor(15,0);
    lcd.print(" ");
  }

}

void loop() {
  displayTime(ampm);
  while (digitalRead(setBtn) == HIGH) {
    Serial.println(digitalRead(setBtn));
    displayAlarm();
  }
  delay(250); // every second
}

void Buzzer() {
  digitalWrite(buz,HIGH);
  delay(500);
  digitalWrite(buz,LOW);
  delay(500);
}

void stopAlarm() {
  digitalWrite(buz,LOW);
}

void soundAlarm(byte hour, byte minute, String ampm) {
  //Comparing the current time with the Alarm time

  if( cancelAlarm == 0 && hour == 6 && minute == 31 && ampm == "pm" ) {
    alarmIsSounding = 1;
    Buzzer();
    Buzzer();
      
    lcd.clear();
    lcd.print("Alarm ON");
    lcd.setCursor(0,1);
    lcd.print("Alarming");

    Buzzer();
    Buzzer();

  } else {
    alarmIsSounding = 0;
  }
}

void displayAlarm(){
  Clock.getA1Time(ADay, AHour, AMinute, ASecond, ABits, ADy, A12h, Apm);

  // Display Alarm 1 information  
  lcd.clear();
  lcd.print("Alarm: ");  
  lcd.setCursor(0,1);

  if (AHour > 12) {
    AHour = AHour - 12;
    ampm = "pm";
    lcd.print(AHour, DEC);
  } else {
    lcd.print(AHour, DEC);
    ampm = "am";
  }
  lcd.print(":");
  if (AMinute < 10) {
    lcd.print("0");
  }
  lcd.print(AMinute, DEC);
  lcd.print(ampm);

  if (Clock.checkAlarmEnabled(1)) {
    Serial.print("enabled");
  }
  delay(5000);
}

void setAlarm(){

    Clock.setA1Time(ADay, AHour, AMinute, ASecond, ABits, ADy, A12h, Apm);

}


