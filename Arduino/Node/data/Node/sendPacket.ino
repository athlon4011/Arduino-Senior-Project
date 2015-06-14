void sendPacket(char message[], int port) {
  Udp.beginPacket(server, port);
  Udp.print(message);
  Udp.endPacket();
  Udp.stop();
      //  Serial.print("restart connection: ");
          Udp.begin(localPort);
//    Serial.println (Udp.begin(localPort) ? "success" : "failed");
}
