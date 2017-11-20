// lightLevel is triggerpoint where lights switch on (afternoon/evenin) of off (during winter in the morning)
void setLightLevel() {
  boolean flashOn = false;
  int lastLight = 50; //used to prevent ugly flashing when printing current light without rolling avarage

  previousMillis = millis();
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("set light level");

  // *******************************
  // **** print current set light level

  lcd.setCursor(0, 1);
  lcd.print(lightLevel); lcd.print(" ");

  // ******************************
  // **** Set light level

  delay(500); // Knob was pushed, wait a little
  knobPushed = false; // reset Knob pushed

  while (knobPushed == false) {

    // print current light
    currentLight = analogRead(LDR);
    currentLight = map(currentLight, 0, 1023, 0, 99);

    if ((currentLight > (lastLight + 2)) || (currentLight < (lastLight - 2))) { //prevent ugly flasing
      lastLight = currentLight;
      lcd.setCursor(14, 1);
      if (currentLight < 10) {
        lcd.print(" ");
      }
      lcd.print(currentLight);

    }

    if ((millis() < (previousMillis + flashDuration)) && (flashOn == false)) {
      lcd.setCursor(0, 1);
      lcd.print(lightLevel);
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
      if (lightLevel >= 99) {
        lightLevel = 0;
      }
      else {
        lightLevel++;
      }
      knobTurned = 0;
    }


    if (knobTurned == -1) {
      if (lightLevel == 0) {
        lightLevel = 99;
      }
      else {
        lightLevel--;
      }
      knobTurned = 0;
    }
  }
  delay(200);
  knobPushed = false;

  lcd.setCursor(0, 1); // make sure light level is printed
  lcd.print(lightLevel);

  EEPROM.update(0, lightLevel); // update EEPROM only if differ


}

