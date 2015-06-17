void sendPacket(char message[]) {
	// Sends a message to the server over UDP
  Udp.beginPacket(server, localPort);
  Udp.write(message);
  Udp.endPacket();
}