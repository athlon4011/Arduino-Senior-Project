#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = {  
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xAD };
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
  // start the Ethernet and UDP:
  Ethernet.begin(mac);
  Udp.begin(localPort);
  Serial.begin(9600);
  pinMode(light, OUTPUT);  
  pinMode(fan, OUTPUT);  
  while(boot) {
    sendPacket(bootBuffer);
    if(receivePacket() == "booting") {
      boot = false;
      server = Udp.remoteIP();
    }
  }
}

void loop() {
  sendPacket("Hello");
  digitalWrite(light, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(light, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
  digitalWrite(fan, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(fan, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);
}

void sendPacket(char message[]) {
  Udp.beginPacket(server, localPort);
  Udp.write(message);
  Udp.endPacket();
}

String receivePacket() {
  int packetSize = Udp.parsePacket();
  if(packetSize)
  {
    Serial.print("Received packet of size ");
    Serial.println(packetSize);
    Serial.print("From ");
    IPAddress remote = Udp.remoteIP();
    for (int i =0; i < 4; i++)
    {
      Serial.print(remote[i], DEC);
      if (i < 3)
      {
        Serial.print(".");
      }
    }
    Serial.print(", port ");
    Serial.println(Udp.remotePort());

    // read the packet into packetBufffer
    Udp.read(packetBuffer,UDP_TX_PACKET_MAX_SIZE);
    Serial.println("packetsize:");
    Serial.print(packetSize);
    Serial.println("Contents:");
    Serial.println(packetBuffer);
    return String(packetBuffer);
  }
}
