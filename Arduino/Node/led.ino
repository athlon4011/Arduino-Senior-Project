/*void setLED(int pin1,int pin2,int pin3,int loops, int interval) {
  int i;
  for(i=0;i<loops;i++) {
    if(pin1 != 0) {analogWrite(red, 255);  } // turn the LED on (HIGH is the voltage level)
    if(pin2 != 0) {analogWrite(green, 255); }  // turn the LED on (HIGH is the voltage level)
    if(pin3 != 0) {analogWrite(blue, 255); }  // turn the LED on (HIGH is the voltage level)
    delay(interval);
    if(pin1 != 0) {analogWrite(red, 0);  }  // turn the LED off by making the voltage LOW
    if(pin2 != 0) {analogWrite(green, 0);  }  // turn the LED off by making the voltage LOW
    if(pin3 != 0) {analogWrite(blue, 0);  } // turn the LED on (HIGH is the voltage level)
    delay(interval);
  }
}*/

void setLED(int red, int green, int blue, int glow, int loops, int interval) {
  Serial.print("interval: ");
  Serial.println(interval);
    byte on[] = {red,green,blue}; //the RGB (red, gren blue) value for a color to display  
    byte off[] = {0,0,0}; //the RGB (red, gren blue) value for a color to display  
    //setColor(leds, on);  
    int i;
  for(i=0;i<loops;i++) {
    //setColor(leds, on);
    fadeToColor(leds, off, on, interval);  
    //delay(interval);
    fadeToColor(leds, on, off, interval);  
    //delay(interval);
  }
}

void setColor(int* led, byte* color){ 
  for(int i = 0; i < 3; i++){
    analogWrite(led[i], color[i]);  
  }
}

void fadeToColor(int* led, byte* startColor, byte* endColor, int fadeSpeed){  
  int changeRed = endColor[0] - startColor[0];                            //the difference in the two colors for the red channel  
  int changeGreen = endColor[1] - startColor[1];                          //the difference in the two colors for the green channel   
  int changeBlue = endColor[2] - startColor[2];                           //the difference in the two colors for the blue channel  
  int steps = max(abs(changeRed),max(abs(changeGreen), abs(changeBlue))); //make the number of change steps the maximum channel change    
  for(int i = 0 ; i < steps; i++){                                        //iterate for the channel with the maximum change   
    byte newRed = startColor[0] + (i * changeRed / steps);                 //the newRed intensity dependant on the start intensity and the change determined above   
    byte newGreen = startColor[1] + (i * changeGreen / steps);             //the newGreen intensity   
    byte newBlue = startColor[2] + (i * changeBlue / steps);               //the newBlue intensity   
    byte newColor[] = {newRed, newGreen, newBlue};                         //Define an RGB color array for the new color   
    setColor(led, newColor);                                               //Set the LED to the calculated value   
    delay(fadeSpeed);                                                      //Delay fadeSpeed milliseconds before going on to the next color  
  }  
  setColor(led, endColor);                                                //The LED should be at the endColor but set to endColor to avoid rounding errors
}
