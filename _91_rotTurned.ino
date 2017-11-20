// Interrupt Service Routine (ISR) 1 (connected to pin D3 of Arduino Nano)
// Called every time the rotaryknob is turned
// Connected to rot1 (= pin D3)

int rotTurned() {

// Serial.println("Interrupt rotTurned");

    if (digitalRead (rot2)) 
     knobTurned =1;   // Turned clockwise
  else 
     knobTurned =-1;   // Turned counter clockwise
}


