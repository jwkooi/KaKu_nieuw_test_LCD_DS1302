void setDate() {

  boolean flashOn = false;
  previousMillis = millis();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("set date");


  // *******************************
  // **** print current date

  lcd.setCursor(0, 1);
  if (currentDay < 10) {
    lcd.print("0");
  }
  lcd.print(currentDay); lcd.print(" ");

  if (currentMonth < 10) {
    lcd.print("0");
  }
  lcd.print(currentMonth); lcd.print(" ");
  lcd.print(currentYear);

  setDay = currentDay;
  setMonth = currentMonth;
  setYear = currentYear;

  // ******************************
  // **** Set day of month

  delay(500); // Knob was pushed, wait a little
  knobPushed = false; // reset Knob pushed

  while (knobPushed == false) {

    if ((millis() < (previousMillis + flashDuration)) && (flashOn == false)) {
      lcd.setCursor(0, 1);
      if (setDay < 10) {
        lcd.print("0");
      }
      lcd.print(setDay);
      flashOn = true; //print only one time at the start of flashDuration
    }

    if ((millis() > (previousMillis + flashDuration)) && (flashOn == true)) {
      lcd.setCursor(0, 1);
      lcd.print("  ");
      flashOn = false;
    }

    if (millis() > (previousMillis + (2 * flashDuration))) {
      previousMillis = millis();
    }

    // exception if millis overflows
    if (millis() < previousMillis) {
      previousMillis = millis();
      Serial.println("Millis overflow");
    }

    // increase/ decrease with check on min and max
    if (knobTurned == 1) {
      if (setDay >= 31) {
        setDay = 1;
      }
      else {
        setDay++;
      }
      knobTurned = 0;
    }


    if (knobTurned == -1) {
      if (setDay == 1) {
        setDay = 31;
      }
      else {
        setDay--;
      }
      knobTurned = 0;
    }
  }

  lcd.setCursor(0, 1); // make sure day of month is printed
  if (setDay < 10) {
    lcd.print("0");
  }
  lcd.print(setDay);

  // ********************************
  // **** set month


  delay(500); // Knob was pushed, wait a little
  knobPushed = false; // reset Knob pushed

  flashOn = false;
  previousMillis = millis();

  while (knobPushed == false) {

    if ((millis() < (previousMillis + flashDuration)) && (flashOn == false)) {
      lcd.setCursor(3, 1);
      if (setMonth < 10) {
        lcd.print("0");

      }
      lcd.print(setMonth);

      flashOn = true; //print only one time at the start of flashDuration
    }

    if ((millis() > (previousMillis + flashDuration)) && (flashOn == true)) {
      lcd.setCursor(3, 1);
      lcd.print("  ");
      flashOn = false;
    }

    if (millis() > (previousMillis + (2 * flashDuration))) {
      previousMillis = millis();
    }

    // exception if millis overflows
    if (millis() < previousMillis) {
      previousMillis = millis();
      Serial.println("Millis overflow");
    }

    // increase/ decrease with check on min and max
    if (knobTurned == 1) {
      if (setMonth >= 12) {
        setMonth = 1;
      }
      else {
        setMonth++;
      }
      knobTurned = 0;
    }

    if (knobTurned == -1) {
      if (setMonth == 1) {
        setMonth = 12;
      }
      else {
        setMonth--;
      }
      knobTurned = 0;
    }
  }
  delay(200);
  knobPushed = false;


  lcd.setCursor(3, 1); // make sure month is printed
  if (setMonth < 10) {
    lcd.print("0");
  }
  lcd.print(setMonth);


  // **********************************************
  // **** set year

  delay(500); // Knob was pushed, wait a little
  knobPushed = false; // reset Knob pushed

  flashOn = false;
  previousMillis = millis();

  while (knobPushed == false) {

    if ((millis() < (previousMillis + flashDuration)) && (flashOn == false)) {
      lcd.setCursor(6, 1);
      lcd.print(setYear);

      flashOn = true; //print only one time at the start of flashDuration
    }

    if ((millis() > (previousMillis + flashDuration)) && (flashOn == true)) {
      lcd.setCursor(6, 1);
      lcd.print("    ");
      flashOn = false;
    }

    if (millis() > (previousMillis + (2 * flashDuration))) {
      previousMillis = millis();
    }

    // exception if millis overflows
    if (millis() < previousMillis) {
      previousMillis = millis();
      Serial.println("Millis overflow");
    }

    // increase/ decrease with check on min and max
    if (knobTurned == 1) {
      if (setYear >= 2040) {
        setYear = 2010;
      }
      else {
        setYear++;
      }
      knobTurned = 0;
    }

    if (knobTurned == -1) {
      if (setYear == 2010) {
        setYear = 2040;
      }
      else {
        setYear--;
      }
      knobTurned = 0;
    }
  }
  delay(200);
  knobPushed = false;


  lcd.setCursor(6, 1); // make sure year is printed
  lcd.print(setYear);

}

