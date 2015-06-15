void receivePacket() {
  int packetSize = Udp.parsePacket();
  if(packetSize)
  {
    IPAddress remote = Udp.remoteIP();
    if(server == remote) {
      // read the packet into packetBufffer
      Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
      Serial.print("packetsize:");
      Serial.println(packetSize);
      Serial.print("Contents:");
      Serial.println(packetBuffer);
      if(String(packetBuffer).startsWith("send")) {
        String test = String(packetBuffer);
        test.remove(0,5);
        Serial.print("server said: ");
        Serial.println(test);
        control(int(test[0])-48,int(test[2])-48);
      }
      //return String(packetBuffer);
    }
  }
}
