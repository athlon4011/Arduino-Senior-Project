#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008
#include <EEPROM.h>
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xAD };
  char macstr[18];
IPAddress ip(192, 168, 1, 179);
IPAddress server(255, 255, 255, 255);  // Server IP address
unsigned int localPort = 8888;      // local port to listen on
boolean boot = true;

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged";       // a string to send back
char  bootBuffer[] = "DE:AD:BE:EF:FE:ED";       // a string to send back
int light = 8;
int fan = 9;
// buffers for receiving and sending data
void setup() {
  if (EEPROM.read(1) == '#') {
    for (int i = 2; i < 6; i++) {
      mac[i] = EEPROM.read(i);
    }
  } else {
    randomSeed(analogRead(0));
    for (int i = 2; i < 6; i++) {
      mac[i] = random(0, 255);
      EEPROM.write(i, mac[i]);
    }
    EEPROM.write(1, '#');
  }
  // start the Ethernet and UDP:
    snprintf(macstr, 18, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Ethernet.begin(mac);
  Udp.begin(localPort);
  Serial.begin(9600);
  pinMode(light, OUTPUT);  
  pinMode(fan, OUTPUT);  
  while(boot) {
    sendPacket(macstr);
    int packetSize = Udp.parsePacket();
    if(packetSize)
    {
      Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
      if(String(packetBuffer) == "booting") {
        server = Udp.remoteIP();
        boot = false;
      }
    }
  }
}

void loop() {
  //Serial.print("Server said: ");
  receivePacket();
    
    
  /*sendPacket("Hello");
  digitalWrite(light, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(light, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  digitalWrite(fan, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(fan, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);*/
}




