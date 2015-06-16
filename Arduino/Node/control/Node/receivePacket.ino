void receivePacket() {
	// Receive and process a UDP message
  int packetSize = Udp.parsePacket();
  if(packetSize)
  {
    IPAddress remote = Udp.remoteIP();
    if(server == remote) {	// Validate the IP the message is coming from
      // read the packet into packetBufffer
      Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
      Serial.print("packetsize:");
      Serial.println(packetSize);
      Serial.print("Contents:");
      Serial.println(packetBuffer);
      if(String(packetBuffer).startsWith("send")) { // Validate the message type
        // Separate the message into usable data
        String test = String(packetBuffer);
        test.remove(0,5);
        Serial.print("server said: ");
        Serial.println(test);
        control(int(test[0])-48,int(test[2])-48);
      }
    }
  }
}
