/*
// No longer in use
String intTemp() {
  String temp;
  //temp += chipTemp.celsius(); temp += ',';
    temp += 'temp'; temp += chipTemp.fahrenheit(); temp += ',';
  if(debug) {
    Serial.print("Internal Temperature: ");
    Serial.print (chipTemp.celsius()); Serial.print("C "); 
    Serial.print(chipTemp.fahrenheit()); Serial.println("F "); 
  }
  return temp;
}*/
