String getSmoke() {
String temp;
  /*if(debug) {
    Serial.print("Smoke Alarm state: ");
    //Serial.println(digitalRead(motion_pin));
  }*/
  int state = 0;
 /* Serial.println();  Serial.println();  Serial.println();
  Serial.print("ALARM VALUE: ");
    Serial.println(analogRead(alarm_pin));*/
  if(analogRead(alarm_pin) > 900) {
    state = 1;
  }
  //temp += "motion"; temp += ','; temp += digitalRead(motion_pin); temp += ',';
  temp += "smoke"; temp += ','; temp += state; temp += ',';
  return temp;
}
