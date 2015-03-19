void separateData(String message) {
  int i,j,start;
  start = 0;
  Serial.println(message);
  String test = "";
  String test2 = "";
  for (i=0;i<=message.length();i++) 
    { //check entire string 
    if (message[i]!=',') {
      test += message[i];
    }
    if (message[i]==',') {//if comma found 
      Serial.println("found comma");
      Serial.println(test);
      
      
      for(j=i+1;j<message.length();j++) {
        //Serial.print(message[j]);
        test2 += message[j];
      }
      Serial.println(test2);
      setTone(test.toInt());
      int pin1 = test2[0]-48;
      int pin2 = test2[1]-48;
      int pin3 = test2[2]-48;
      setLED(pin1,pin2,pin3,4,200);
    }
  }
          Serial.println(); 
  //Serial.println(message[strLength]);
  //Serial.println(c1);
  //Serial.println(c2);
}
