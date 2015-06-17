void receivePacket() {
  // Checks the UDP packet for IP and message type, then pulls or displays the data that the server has posted
  int packetSize = Udp.parsePacket();
  if(packetSize)
  {
    IPAddress remote = Udp.remoteIP();
    if(server == remote) { // Validate the source IP address against the store server IP
    // read the packet into packetBufffer
    char* msg = (char*)malloc(packetSize+1);
    int len = Udp.read(msg,packetSize+1);
    msg[len]=0;
    Udp.flush();
    if(String(msg).startsWith("pull")) { // Validate the mesage type
      // Gather data to send to server
      String dataString;
      dataString += extTemp(); // Load external temperature into data string
      //dataString += intTemp(); // Load internal temperature into data string
      dataString += getMotion();
      dataString += getLux();
      dataString += getSmoke();
      char message[dataString.length()]; 
      dataString.toCharArray(message,dataString.length()); // convert string to char array
      sendPacket(message,Udp.remotePort()); // Send the CSV of data back to the server
    } else if(String(msg).startsWith("send")) {
      String test = String(msg);
      test.remove(0,5);
      separateData(test);
      Udp.stop();
      Udp.begin(localPort); // Restart UDP Server
    } else {
      Udp.stop();
      Udp.begin(localPort); // Restart UDP Server
    }
    free(msg); // Clear the string's buffer
    } else {
		// Invalid server trying to communicate with the node
		Udp.stop();
		Udp.begin(localPort); // Restart UDP Server
    }
  }
}