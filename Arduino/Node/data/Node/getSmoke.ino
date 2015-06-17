String getSmoke() {
  // Obtains the voltage level of the smoke detector's red LED to determine if the alarm is going off
  String temp;
  int state = 0;
  // Alarm fluctuates between 0 and 850 when not engaged
  if(analogRead(alarm_pin) > 900) {
    state = 1;
  }
  temp += "smoke"; temp += ','; temp += state; temp += ',';
  return temp;
}