void sendPacket(char message[]) {
  Udp.beginPacket(server, localPort);
  Udp.write(message);
  Udp.endPacket();
}
