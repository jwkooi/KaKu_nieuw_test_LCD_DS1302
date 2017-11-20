void menu() {



  delay(500); // Knob was pushed, wait a little
  knobPushed = false; // reset Knob pushed

  const String menuTxt[] = {"set time        ", "set date        ",
                            "set light level ", "time lights off ",
                            "morning light on", "exit            ",
                           };

  // (sizeof(menuTxt1)/sizeof(menuTxt1[0])) is number of strings in array
  int menu_len = sizeof(menuTxt) / sizeof(menuTxt[0]);

  // reset index to start position
  int menu_index = 0;
  boolean menuExit = false;

  // *** menuTxt ***
  //First 2 lines on LCD
  lcd.setCursor(0, 0);                  // first line LCD
  lcd.print(menuTxt[0]);
  lcd.setCursor(0, 1);                  // second line LCD
  lcd.print(menuTxt[1]);

  // **************************************
  // **** Main menu loop

  while (menuExit == false) {              // Loop until exit is chosen

    // *****************************
    // **** Choose menu item
    while (knobPushed == false) {
      delay(100);

      if (knobTurned == 1) {
        menu_index++;
        if (menu_index >= (menu_len)) {               //reset after last item in array
          menu_index = 0;
        }
        knobTurned = 0;
      }

      if (knobTurned == -1) {
        menu_index--;
        if (menu_index <= 0) {               //set to end of array if first item is passed
          menu_index = menu_len - 1;
        }
        knobTurned = 0;
      }

      //update LCD
      lcd.setCursor(0, 0);                  // first line LCD
      lcd.print(menuTxt[menu_index]);

      lcd.setCursor(0, 1);                  // second line LCD

      if (menu_index < (menu_len - 1)) {             // check end of array
        lcd.print(menuTxt[menu_index + 1]);
      }
      else {
        lcd.print(menuTxt[0]); // Last menu item is passed so print first of array
      }

    }
    delay(200);
    knobPushed = false;


    //**************************************
    // **** A menu item has been chosen



    // *********************************
    // *** set time ***
    if (menu_index == 0) {

      setTime(currentHour, currentMinute); //output variables setHour, setMinute

      DS1302module.updateTime();

      currentDay = DS1302module.dayofmonth;
      currentMonth = DS1302module.month;
      currentYear = DS1302module.year;

      // Set the current date, and time in the following format:
      // seconds, minutes, hours, day of the week, day of the month, month, year
      DS1302module.setDS1302Time(0, setMinute, setHour, 1, currentDay, currentMonth, currentYear);
      currentMinute = setMinute;
      currentHour = setHour;

      knobPushed = false; // reset Knob pushed
      delay(500);
      lcd.clear();
    }

    // *********************************
    // *** set date
    if (menu_index == 1) {
      setDate(); //output variables setDate, setMonht, setYear

      DS1302module.updateTime();

      currentHour = DS1302module.hours;
      currentMinute = DS1302module.minutes;

      // Set the current date, and time in the following format:
      // seconds, minutes, hours, day of the week, day of the month, month, year
      DS1302module.setDS1302Time(0, currentMinute, currentHour, 1, setDay, setMonth, setYear);

      currentDay = setDay;
      currentMonth = setMonth;
      currentYear = setYear;

      knobPushed = false; // reset Knob pushed
      delay(500);
      lcd.clear();

    }

    // *********************************
    // *** set light level
    if (menu_index == 2) {
      setLightLevel(); //output variables lightLevel

      knobPushed = false; // reset Knob pushed
      delay(500);
      lcd.clear();


    }

    // *********************************
    // *** set time lights off
    if (menu_index == 3) {

      setTime(offHour, offMinute);
      offHour = setHour;
      offMinute = setMinute;

      EEPROM.update(1, offHour); // update EEPROM only if differ
      EEPROM.update(2, offMinute); // update EEPROM only if differ

      knobPushed = false; // reset Knob pushed
      delay(500);
      lcd.clear();

    }

    // *********************************
    // *** set time lights off
    if (menu_index == 4) {

      setTime(morningHour, morningMinute);
      morningHour = setHour;
      morningMinute = setMinute;

      EEPROM.update(3, morningHour); // update EEPROM only if differ
      EEPROM.update(4, morningMinute); // update EEPROM only if differ

      knobPushed = false; // reset Knob pushed
      delay(500);
      lcd.clear();

    }



    // *********************************
    //  *** exit menu
    if (menu_index == 5) {
      menuExit = true;
    }
  }
}





