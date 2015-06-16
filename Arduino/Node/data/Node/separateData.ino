void separateData(String message) {
  // Pulls apart a string that is received from the server to display audio and visual notifications
  setTone(int(message[0])-48);
  setLED((message.substring(2,5)).toInt(), (message.substring(6,9)).toInt(), (message.substring(10,13)).toInt(), int(message[14])-48, int(message[16])-48);
}