String getMotion() {
  // Obtains the state of the motion sensor
  String temp;
  temp += "motion"; temp += ','; temp += digitalRead(motion_pin); temp += ',';
  return temp;
}
