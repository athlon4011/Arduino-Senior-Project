void setLED(int pin1,int pin2,int pin3,int loops, int interval) {
  int i;
  for(i=0;i<loops;i++) {
    if(pin1 != 0) {analogWrite(red, 255);  } // turn the LED on (HIGH is the voltage level)
    if(pin2 != 0) {analogWrite(green, 255); }  // turn the LED on (HIGH is the voltage level)
    if(pin3 != 0) {analogWrite(blue, 255); }  // turn the LED on (HIGH is the voltage level)
    delay(interval);
    if(pin1 != 0) {analogWrite(red, 0);  }  // turn the LED off by making the voltage LOW
    if(pin2 != 0) {analogWrite(green, 0);  }  // turn the LED off by making the voltage LOW
    if(pin3 != 0) {analogWrite(blue, 0);  } // turn the LED on (HIGH is the voltage level)
    delay(interval);
  }
}
