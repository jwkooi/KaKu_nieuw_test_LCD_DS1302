// 17 sep 2016: Test LCD via I2C + Nano386
// 25 sep 2016: Test DS1302 (OK), Test 433 transmitter (OK), Test LCD (OK), Test LDR (OK)
// 26 sep 2016: Test interrupt with rotary switch (OK), test rotary routine (OK)
// 06 nov 2016: Menu upto set Light level. Trying to use EEPROM functions. Problem with setLight.
// 07 dec 2016: All Menu items are finished. EEPROM is working.
// 14 dec 2016: Backlight automatic switch off after 3 minutes
// 30 dec 2016: Bug set date solved
// 14 jan 2017: morning on if dark implemented
// 15 jan 2017: evening on if dark (version Arduino 1.8.0)
//#include <Arduino.h>  //in combination with tabs to be used but causing trouble compiling

// LCD 16x2 with I2C
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address

//Kaku  Klik-Aan-Klik-Uit
#include <NewRemoteTransmitter.h>
// Create a transmitter on address 18649618, using digital pin 11 to transmit,
// with a period duration of 270ms (default), repeating the transmitted
// code 2^3=8 times.
NewRemoteTransmitter transmitter(18649618, 11, 270, 3);

//DS1302 Module time
#include <virtuabotixRTC.h>
//(CLK, I/O (DAT) , CE (RST)
virtuabotixRTC DS1302module(10, 9, 8);

//EEPROM library
#include <EEPROM.h>

//LDR connected to A0 
#define LDR A0
int currentLight = 65; // start value day light
int lightLevel; // 0-99 stored in EEPROM (0), good switch level is 52

// Rolling avarage for measuring light
#define Rolling_Max 10 // Max for rolling average (60)
int Rolling_Array[Rolling_Max]; //Used in Rolling_Average procedure
int oldSecond = 0;

//Rotary switch
#define rotPush 2 //normally HIGH
#define rot1 3    //normally HIGH
#define rot2 5    //normally HIGH

int rot = 0;

// set in Interrupt Service Routine
volatile boolean knobPushed = false; // volatile since this is used in ISR
volatile int knobTurned = 0; // volatile since this is used in ISR


//Menu

#define flashDuration 300 //duration of flashing to indicate editting a menu item

unsigned long previousMillis;    // used for various functions as time stamp


byte currentHour = 0;
byte currentMinute = 0;
byte currentDay= 0;
byte currentMonth = 0;
int currentYear = 0;

byte setHour = 0;    // used as output parameter in setTime
byte setMinute = 0;  // used as output parameter in setTime

byte setDay = 0;     // used as output parameter in setDate
byte setMonth = 0;   // used as output parameter in setDate
int setYear = 0;     // used as output parameter in setDate


byte offHour;     // time light go off at night
byte offMinute;   // time light go off at night

byte morningHour;    // time lights go on in the morning
byte morningMinute;  // time lights go on in the morning

//switching
boolean lightOn = false;   // current status of lights
byte lightHysteresis = 10; // delay time in minutes between switch events

// backlight off
byte backlightTime = 3;      // time in minutes, that backlight is on
byte backlightMinuteOff;     // uses to switch off backlight
boolean backlightOn = false; // status backlight

