String getSmoke() {
String temp;
  if(debug) {
    Serial.print("Smoke Alarm state: ");
    //Serial.println(digitalRead(motion_pin));
  }
  //temp += "motion"; temp += ','; temp += digitalRead(motion_pin); temp += ',';
  temp += "smoke"; temp += ','; temp += '0'; temp += ',';
  return temp;
}
