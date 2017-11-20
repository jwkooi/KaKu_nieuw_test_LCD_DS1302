void setTime (byte inHour, byte inMinute) {

#define flashDuration 300 //duration of flashing


  boolean flashOn = false;
  previousMillis = millis();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("set time");


  // ********************************************
  // **** print current time (without seconds)


  lcd.setCursor(0, 1);
  if (inHour < 10) {
    lcd.print("0");
  }
  lcd.print(inHour); lcd.print(":");

  if (inMinute < 10) {
    lcd.print("0");
  }
  lcd.print(inMinute);

  // ************************************
  // **** set hour

  delay(500); // Knob was pushed, wait a little
  knobPushed = false; // reset Knob pushed

  while (knobPushed == false) {

    if ((millis() < (previousMillis + flashDuration)) && (flashOn == false)) {
      lcd.setCursor(0, 1);
      if (inHour < 10) {
        lcd.print("0");
      }
      lcd.print(inHour);
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
      if (inHour >= 23) {
        inHour = 0;
      }
      else {
        inHour++;
      }
      knobTurned = 0;
    }


    if (knobTurned == -1) {
      if (inHour == 0) {
        inHour = 23;
      }
      else {
        inHour--;
      }
      knobTurned = 0;
    }
  }

  lcd.setCursor(0, 1); // make sure time is printed
  if (inHour < 10) {
    lcd.print("0");
  }
  lcd.print(inHour);

  // ******************************
  // **** set Minute

  delay(500); // Knob was pushed, wait a little
  knobPushed = false; // reset Knob pushed

  flashOn = false;
  previousMillis = millis();

  while (knobPushed == false) {

    if ((millis() < (previousMillis + flashDuration)) && (flashOn == false)) {
      lcd.setCursor(3, 1);
      if (inMinute < 10) {
        lcd.print("0");

      }
      lcd.print(inMinute);

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
      if (inMinute >= 59) {
        inMinute = 0;
      }
      else {
        inMinute++;
      }
      knobTurned = 0;
    }

    if (knobTurned == -1) {
      if (inMinute == 0) {
        inMinute = 59;
      }
      else {
        inMinute--;
      }
      knobTurned = 0;
    }
  }
  delay(200);
  knobPushed = false;


  lcd.setCursor(3, 1); // make sure time is printed
  if (inMinute < 10) {
    lcd.print("0");
  }
  lcd.print(inMinute);


  setHour = inHour;
  setMinute = inMinute;

}

