String getLux (){
	// Gets the voltage levels of the photocell and converts the reading into lux
  String temp;
  double Vout=analogRead(1)*0.0048828125;
  int lux=500/(10*((5-Vout)/Vout));// Used if the LDR is in the upper part of the divider
  //int lux=(2500/Vout-500)/10; // Used if the LDR is in the lower part of the divider
  temp += "lux"; temp += ','; temp += lux; temp += ',';
  return temp;
}
