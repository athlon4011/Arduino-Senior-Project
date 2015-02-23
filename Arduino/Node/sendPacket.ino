void sendPacket(char message[]) {
  Udp.beginPacket(server, Udp.remotePort());
  Udp.print(message);
  Udp.endPacket();
  Udp.stop();
        Serial.print("restart connection: ");
    Serial.println (Udp.begin(localPort) ? "success" : "failed");
}
