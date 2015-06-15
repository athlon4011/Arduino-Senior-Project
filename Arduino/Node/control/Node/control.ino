void control(int lightIn, int fanIn) {
  Serial.print("values: ");
  Serial.print(fanIn);
  Serial.print(" ");
  Serial.println(lightIn);
  if(fanIn == 1) {
      digitalWrite(fan, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
      digitalWrite(fan, LOW);   // turn the LED on (HIGH is the voltage level)
  }
  if(lightIn == 1) {
      digitalWrite(light, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
      digitalWrite(light, LOW);   // turn the LED on (HIGH is the voltage level)
  }
}
