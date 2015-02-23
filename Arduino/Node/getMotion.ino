String getMotion() {
  String temp;
  Serial.print("Motion state: ");
  Serial.println(digitalRead(motion_pin));
  temp += digitalRead(motion_pin); temp += ',';
  return temp;
}
