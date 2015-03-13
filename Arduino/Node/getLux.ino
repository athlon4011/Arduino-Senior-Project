//Lux
String getLux (){
  String temp;
  double Vout=analogRead(1)*0.0048828125;
  int lux=500/(10*((5-Vout)/Vout));//use this equation if the LDR is in the upper part of the divider
  //int lux=(2500/Vout-500)/10;
  Serial.print("Lux reading: ");
  Serial.println(lux);
  temp += "lux"; temp += ','; temp += lux; temp += ',';
  return temp;
}
