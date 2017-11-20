void general_Display() {

  
  DS1302module.updateTime();

  currentHour = DS1302module.hours;
  currentMinute = DS1302module.minutes;
  currentDay = DS1302module.dayofmonth;
  currentMonth = DS1302module.month;
  currentYear = DS1302module.year;


  // **********************************************************************
  // print time
  lcd.setCursor(0, 0);
  if (currentHour < 10) {
    lcd.print("0");
  }
  lcd.print(currentHour); lcd.print(":");

  if (currentMinute < 10) {
    lcd.print("0");
  }
  lcd.print(currentMinute); lcd.print(":");

  if (DS1302module.seconds < 10) {
    lcd.print("0");
  }
  lcd.print(DS1302module.seconds);



  // **********************************************************************
  // print date
  lcd.setCursor(0, 1);
  if (currentDay < 10) {
    lcd.print("0");
  }
  lcd.print(currentDay); lcd.print(" ");

  if (currentMonth == 1) {
    lcd.print("jan");
  }
  if (currentMonth == 2) {
    lcd.print("feb");
  }
  if (currentMonth == 3) {
    lcd.print("mrt");
  }
  if (currentMonth == 4) {
    lcd.print("apr");
  }
  if (currentMonth == 5) {
    lcd.print("mei");
  }
  if (currentMonth == 6) {
    lcd.print("jun");
  }
  if (currentMonth == 7) {
    lcd.print("jul");
  }
  if (currentMonth == 8) {
    lcd.print("aug");
  }
  if (currentMonth == 9) {
    lcd.print("sep");
  }
  if (currentMonth == 10) {
    lcd.print("okt");
  }
  if (currentMonth == 11) {
    lcd.print("nov");
  }
  if (currentMonth == 12) {
    lcd.print("dec");
  }

  lcd.print (" ");
  lcd.print(currentYear);

  // **********************************************************************
  // print Current Light level (per second)

  if (DS1302module.seconds != oldSecond) {
    oldSecond = DS1302module.seconds;

    currentLight = analogRead(LDR);
    currentLight = Rolling_Average(currentLight);

    currentLight = map(currentLight, 0, 1023, 0, 99);

    lcd.setCursor(14, 0);
    if (currentLight < 10) {
      lcd.print(" ");
    }
    lcd.print(currentLight);
  }


  // **********************************************************************
  // print Set Light Level
  lcd.setCursor(14, 1);
  if (lightLevel < 10) {
    lcd.print(" ");
  }
  lcd.print(lightLevel);
  //   Serial.println(lightLevel); // strange: statement is needed, otherwise lightLevel is behaving strange
  delay(300);
}
