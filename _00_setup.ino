void setup() {
  Serial.begin(9600); // Enable serial printing

  //LCD
  lcd.begin(16, 2);  // initialize the lcd for 16 chars 2 lines

  //Blink backlight
  lcd.backlight();
  delay(250);
  lcd.noBacklight();
  delay(250);
  lcd.backlight(); // finish with backlight on
  lcd.clear();

  // DS1302
  // Set the current date, and time in the following format:
  // seconds, minutes, hours, day of the week, day of the month, month, year
  // DS1302module.setDS1302Time(48, 03, 21, 2, 17, 10, 2016);

  //Rotary switch
  pinMode (rotPush, INPUT); // Push knob of rotary switch, Normaly high (1), attached to interrupt
  pinMode (rot1, INPUT);    // Rotary switch clockwise,
  pinMode (rot2, INPUT);    // Rotary switch counter clockwis

  // Interrupt setup
  // Goto ISR (Interrupt Service Routine 0 when rotary switch is pushed
  attachInterrupt(0, rotPushed, CHANGE);
  // Goto ISR (Interrupt Service Routine 1 when rotary switch is turned
  attachInterrupt(1, rotTurned, FALLING);

  // EEprom, 1024 bytes on the ATmega328
  // 0 = lightLevel
  // 1 = offHour
  // 2 = offMinute
  // 3 = morningHour
  // 4 = morningMinute

  lightLevel = EEPROM.read(0);
  offHour = EEPROM.read(1);
  offMinute = EEPROM.read(2);
  morningHour = EEPROM.read(3);
  morningMinute = EEPROM.read(4);

  offHour = constrain(offHour,0,23);
  offMinute = constrain (offMinute,0,59);
  morningHour = constrain(morningHour,0,23);
  morningMinute = constrain (morningMinute,0,59);

}
