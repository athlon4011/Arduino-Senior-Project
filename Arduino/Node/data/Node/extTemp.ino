String extTemp() {
  // Gets the temperature reading from the lm34 and combines it into a csv
  String temp;
  fahrenheit = (100.0 * analogRead(temp_pin) * vref)/1023;   // calculates the actual fahrenheit temperature
  temp += "temp"; temp += ','; temp += fahrenheit; temp += ',';
  return temp;
}
