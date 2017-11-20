void loop() {

  // Menu
  if (knobPushed) {

    lcd.backlight();    // turn on backlight
    backlightOn = true; //

    menu();

    // set backlight timer
    backlightMinuteOff = currentMinute + backlightTime;

  }

  // *** turn backlight off after backlightTime
  // **********************************
  if (backlightMinuteOff > 59) {
    backlightMinuteOff = backlightMinuteOff - 60;
  }
  if ((currentMinute == backlightMinuteOff) && (backlightOn == true )) {
    lcd.noBacklight();   // turn Backlight off
    backlightOn = false;
  }


  general_Display(); //measure light, update time and print all data to lcd (time, data, lightlevels)

  // *** manual light switching
  // ***************************
  if (knobTurned == 1) {                 //if knob is turned right, switch on lights
    lightOn = true;
    lightSwitch(lightOn);
    knobTurned = 0;
  }
  if (knobTurned == -1) {                // if knob is turned left, switch off lights
    lightOn = false;
    lightSwitch(lightOn);
    knobTurned = 0;
  }



  // *** switch morning lights on/off (max 10:00 hour)
  // *******************************

  if (currentHour < 10) {                                                     // before 9:59?
    if ((currentHour == morningHour) && (currentMinute == morningMinute)) {   //is it time for lights on?
      if (currentLight < lightLevel) {                                       // is it still dark?
        if (lightOn == false ) {                                             // are lights off?
          lightOn = true;
          lightSwitch(lightOn);                                              // switch lights on
        }
      }
    }
    if (currentLight >= lightLevel) {                                        // is it already daylight?
      if (lightOn == true) {                                                 // are light on?
        lightOn = false;
        lightSwitch(lightOn);                                                // switch light off
      }
    }



  }
  // *** switch evening lights on/off (max 24:00 hour)
  // *******************************

  Serial.print("currentHour ");
  Serial.print(currentHour);
  Serial.print(" || currentMinute ");
  Serial.print(currentMinute);
  Serial.print(" || currentLight ");
  Serial.println(currentLight);

  Serial.print("offHour ");
  Serial.print(offHour);
  Serial.print(" || offMinute ");
  Serial.print(offMinute);
  Serial.print(" || lightLevel ");
  Serial.println(lightLevel);

  Serial.println("==============================");


  /*
    if (currentHour > 14) {                                                  // after 14:59?
      if (currentLight <= lightLevel ) {                                     // is it dark?
        if (lightOn == false) {                                              // are light off?
          if ((currentHour == offHour) && (currentMinute == offMinute)) {    // time to switch off?
            Serial.println("Nu even niet");
          }
          else {
            lightOn = true;
            lightSwitch(lightOn);                                            // switch light on
            Serial.println("LICHTEN AAN");
          }
        }

      }
      if ((currentHour == offHour) && (currentMinute == offMinute)) {         //is it time for lights off?
        if (lightOn == true) {                                                // are light on?
          lightOn = false;
          lightSwitch(lightOn);                                               // switch light off
          Serial.println("LICHTEN UIT");
        }
      }


    }
  */

  if (currentHour > 14) {                                                  // after 14:59?
    if (lightOn == true) {                                                 // are lights on?

      if ((currentHour == offHour) && (currentMinute == offMinute)) {      //is it time for lights off?
        lightOn = false;
        lightSwitch(lightOn);                                              // switch light off
        Serial.println("LICHTEN UIT");
      }
    }
    else {                                                                 // lights are off
      if (currentHour < offHour) {                                         // it is earlier than off time?
        Serial.println("Lichten meten om aan te doen (uur)");
        if (currentLight <= lightLevel ) {
          lightOn = true;
          lightSwitch(lightOn);                                            // switch lights on
          Serial.println("LICHTEN AAN");
        }

      }
      else {
        if ((currentMinute < offMinute)&& (currentHour == offHour))  {      // it is earlier than off time?
          Serial.println("Lichten meten om aan te doen (min)");
          if (currentLight <= lightLevel ) {
            lightOn = true;
            lightSwitch(lightOn);                                            // switch lights on
            Serial.println("LICHTEN AAN");
          }        
        }

      }
    }
  }





} //*** end loop
