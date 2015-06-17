#include <SPI.h>         	// needed for Arduino versions later than 0018
#include <Ethernet.h>		// Ethernet Library from arduino IDE
#include <EthernetUdp.h>	// UDP library from: bjoern@cs.stanford.edu 12/30/2008
#include <EEPROM.h>			// Used to access the EEPROM
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xAD };
char macstr[18];
IPAddress server(255, 255, 255, 255);	  // Server IP address
unsigned int localPort = 8888;		      // local port to listen on
boolean boot = true;

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
int light = 8;
int fan = 9;
// buffers for receiving and sending data
void setup() {
	// Check flag for MAC assignment
	// If the flag doesn't exist, generate a MAC and store it in the EEPROM
	// If the flag exists, read the MAC into a byte array
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
  // Send a broadcast throughout the network so the server can find the node
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
  receivePacket();
}




