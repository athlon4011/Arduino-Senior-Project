void control(int lightIn, int fanIn) {
	// Sends a signal to the relay pins to turn on the equivilent device
  if(fanIn == 1) {
      digitalWrite(fan, HIGH);   // turn the fan on (HIGH is the voltage level)
  } else {
      digitalWrite(fan, LOW);   // turn the fan off (LOW is the voltage level)
  }
  if(lightIn == 1) {
      digitalWrite(light, HIGH);   // turn the light on (HIGH is the voltage level)
  } else {
      digitalWrite(light, LOW);   // turn the light off (LOW is the voltage level)
  }
}