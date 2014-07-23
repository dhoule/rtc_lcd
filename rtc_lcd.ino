#include <Wire.h>
#include <LiquidCrystal.h>
#include "RTClib.h"

// RTC connections:
// SDA to Arduino pin 20(Mega)/4(Uno)
// SCL to Arduino pin 21(Mega)/5(Uno)
RTC_DS1307 RTC;
// LCD Connections:
// rs (LCD pin 4) to Arduino pin 12
// rw (LCD pin 5) to Arduino pin 11
// enable (LCD pin 6) to Arduino pin 10
// LCD pin 15 to Arduino pin 13
// LCD pins d4, d5, d6, d7 to Arduino pins 7, 6, 5, 4
LiquidCrystal lcd(12, 11, 10, 7, 6, 5, 4);
// Pin used by the Relay
// pin 13 will control the backlight
int backLight = 13; 

void setup () {
  //Initialize the serial port, wire library and RTC module
  Serial.begin(9600);
  // Set the pin for outputing.
  pinMode(backLight, OUTPUT);
  digitalWrite(backLight, HIGH); // turn backlight on. Replace 'HIGH' with 'LOW' to turn it off.
  lcd.begin(16,4);              // columns, rows.  use 16,2 for a 16x2 LCD, etc.
  lcd.clear();                  // start with a blank screen
  Wire.begin();
  RTC.begin();
  // Sets up the module time and date with the computer one
  RTC.adjust(DateTime(__DATE__, __TIME__));
}

void loop () {
    DateTime now = RTC.now();
    lcd.clear();
    lcd.setCursor(0,1);
    //We print the day
    lcd.print(now.day(), DEC);
    lcd.setCursor(2,1);
    lcd.print('/');
    lcd.setCursor(3,1);
    //We print the month
    int month = now.month();
    if(month > 9){
      lcd.print(now.month(), DEC);
    }
    else{
      lcd.print(0);
      lcd.setCursor(4,1);
      lcd.print(now.month(), DEC);
    }
    lcd.setCursor(5,1);
    lcd.print('/');
    lcd.setCursor(6,1);
    //We print the year
    lcd.print(now.year(), DEC);
    lcd.setCursor(10,1);
    lcd.print(' ');
    lcd.setCursor(11,1);
    //We print the hour
    int hour = now.hour();
    if(hour > 9){
      lcd.print(hour, DEC);
    }
    else{
      lcd.print(0);
      lcd.setCursor(12,1);
      lcd.print(hour, DEC);
    }  
    lcd.setCursor(13,1);
    lcd.print(':');
    lcd.setCursor(14,1);
    //We print the minutes
    lcd.print(now.minute(), DEC);
    lcd.setCursor(16,1);
    lcd.print(':');
    lcd.setCursor(17,1);
    //We print the seconds
    int second = now.second();
    if(second > 9){
      lcd.print(second, DEC);
    }
    else{
      lcd.print(0);
      lcd.setCursor(18,1);
      lcd.print(second, DEC);
    }  
    
    //We check the time and sent through the serial port every 3s
    delay(1000);
}
