String getMotion() {
  String temp;
  Serial.print("Motion state: ");
  Serial.println(digitalRead(motion_pin));
  temp += "motion"; temp += ','; temp += digitalRead(motion_pin); temp += ',';
  return temp;
}
