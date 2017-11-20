// switch light on or off 
void lightSwitch(boolean inSwitchOn) {
  Serial.print("Schakelen: ");
  Serial.println(inSwitchOn);
  
  if (inSwitchOn == true)
  {
    transmitter.sendUnit(2, true); // lights on
    delay(50);
    transmitter.sendUnit(2, true); // lights on
    delay(50);
    transmitter.sendUnit(2, true); // lights on
  }
  else
  {
    transmitter.sendUnit(2, false); // lights off
    delay(50);
    transmitter.sendUnit(2, false); // lights off
    delay(50);
    transmitter.sendUnit(2, false); // lights off
  }
}

