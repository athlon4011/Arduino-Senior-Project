void setLED(int red, int green, int blue, int loops, int interval) {
  // Intial function to setup the fading between the target color and black
  byte on[] = {red,green,blue}; // Loads the arguments in for the targeted color
  byte off[] = {0,0,0}; // Passes a color of black for the off state
  
  int i; 
  for(i=0;i<loops;i++) {
    fadeToColor(leds, off, on, interval);  
    fadeToColor(leds, on, off, interval);  
  }
}

void setColor(int* led, byte* color){ 
  // Sets the color for each pin on the LED's
  for(int i = 0; i < 3; i++){
    analogWrite(led[i], color[i]);  
  }
}

void fadeToColor(int* led, byte* startColor, byte* endColor, int fadeSpeed){  
  // Calculates the amount of steps between the start color and the end color, then sets the LED each step
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