void receivePacket() {
  int packetSize = Udp.parsePacket();
  if(packetSize)
  {
    IPAddress remote = Udp.remoteIP();
    if(server == remote) {
    if(debug) {
      Serial.print("Received packet from ");
      
      for (int i =0; i < 4; i++)
      {
        Serial.print(remote[i], DEC);
        if (i < 3)
        {
          Serial.print(".");
        }
      }
      Serial.print(", port ");
      Serial.print(Udp.remotePort());
      Serial.print(", size ");
      Serial.println(packetSize);
    }
    // read the packet into packetBufffer
    char* msg = (char*)malloc(packetSize+1);
    int len = Udp.read(msg,packetSize+1);
    msg[len]=0;
    if(debug) {
      Serial.print("Contents: ");
      Serial.println(msg);
      //Serial.print('|');
    }
    //String test = msg;
    //test.trim();
    //char compare[] = "hello";
    //Serial.print("Compare: ");
    //Serial.println(test.length());
    //Serial.println(test);
    Udp.flush();
    if(String(msg).startsWith("pull")) {
      //Serial.println("TRUE"); 
      // Gather data to send to server
      String dataString;
      dataString += extTemp(); // Load external temperature into data string
      //dataString += intTemp(); // Load internal temperature into data string
      dataString += getMotion();
      dataString += getLux();
      dataString += getSmoke();
      char message[dataString.length()]; 
      dataString.toCharArray(message,dataString.length()); // convert string to char array
      sendPacket(message,Udp.remotePort());
    } else if(String(msg).startsWith("send")) {
      String test = String(msg);
      test.remove(0,5);
      separateData(test);
      Udp.stop();
        Serial.print("restart connection: ");
    Serial.println (Udp.begin(localPort) ? "success" : "failed");
    } else {
      Udp.stop();
        Serial.print("restart connection: ");
    Serial.println (Udp.begin(localPort) ? "success" : "failed");
    }
    //testString(msg, (packetSize-2));
    free(msg);
    } else {
      Serial.println("Invalid Server!");
      Udp.stop();
        Serial.print("restart connection: ");
    Serial.println (Udp.begin(localPort) ? "success" : "failed");
    }
  }
}
