void setLED(int pin1,int pin2,int pin3,int loops, int interval) {
  int i;
  for(i=0;i<loops;i++) {
    if(pin1 != 0) {digitalWrite(red, HIGH);  } // turn the LED on (HIGH is the voltage level)
    if(pin2 != 0) {digitalWrite(green, HIGH); }  // turn the LED on (HIGH is the voltage level)
    if(pin3 != 0) {digitalWrite(blue, HIGH); }  // turn the LED on (HIGH is the voltage level)
    delay(interval);
    if(pin1 != 0) {digitalWrite(red, LOW);  }  // turn the LED off by making the voltage LOW
    if(pin2 != 0) {digitalWrite(green, LOW);  }  // turn the LED off by making the voltage LOW
    if(pin3 != 0) {digitalWrite(blue, LOW);  } // turn the LED on (HIGH is the voltage level)
    delay(interval);
  }
}
