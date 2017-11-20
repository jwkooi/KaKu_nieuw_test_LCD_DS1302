// Interrupt Service Routine (ISR) 0 (connected to pin D2 of Arduino Nano)
// Called every time the rotaryknob is pushed

void rotPushed() {
//Serial.println("Interrupt Knop is ingedrukt !!!");

  knobPushed = true;
  Serial.println("Knop is ingedrukt");

}

