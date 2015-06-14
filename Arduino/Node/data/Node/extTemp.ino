String extTemp() {
  String temp;
   //sensor_reading = analogRead(sensor_pin);         // stores the digitized (0 - 1023) analog reading from the LM34
   fahrenheit = (100.0 * analogRead(temp_pin) * vref)/1023;   // calculates the actual fahrenheit temperature
   //centigrade = (((5.0/9.0))*(fahrenheit-32.0)); //conversion to degrees C
   //temp += centigrade; temp += ',';
   temp += "temp"; temp += ','; temp += fahrenheit; temp += ',';
   /*if(debug) {
     Serial.print("External Temperature: ");
     Serial.print (centigrade); Serial.print("C "); 
     Serial.print(fahrenheit); Serial.println("F ");
   }*/
   return temp;
}
