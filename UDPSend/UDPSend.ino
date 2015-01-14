/*
  UDPSendReceive.pde:
 This sketch receives UDP message strings, prints them to the serial port
 and sends an "acknowledge" string back to the sender
 
 A Processing sketch is included at the end of file that can be used to send 
 and received messages for testing with a computer.
 
 created 21 Aug 2010
 by Michael Margolis
 
 This code is in the public domain.
 */


#include <SPI.h>         // needed for Arduino versions later than 0018
#include <Ethernet.h>
#include <EthernetUdp.h>         // UDP library from: bjoern@cs.stanford.edu 12/30/2008
#include <avr/pgmspace.h>
#include "ChipTemp.h"


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);     // Arduino IP address
IPAddress server(192, 168, 1, 39);  // Server IP address
unsigned int localPort = 8888;      // local port to listen on

int temp_pin = 0;        // the analog pin for LM34 temp sensor - Cannot use pin 0 as it is used for something by DRobotics LCD shield
float sensor_reading = 0.0;        // variable to store the value coming from the sensor
float vref = 1.08;        // variable to store the voltage reference used (check for validity with a DMM)
float fahrenheit = 0.0;        // variable to store the actual temperature
float centigrade = 0.0;

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE]; //buffer to hold incoming packet,
char  ReplyBuffer[] = "acknowledged";       // a string to send back

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;
ChipTemp chipTemp;

void setup() {
  // start the Ethernet and UDP:
    pinMode( sensor_pin, INPUT );        // set LM34 temp sensor pin as an input
 analogReference(INTERNAL);        // set the analog reference to the 1.1V internal reference
  Ethernet.begin(mac,ip);
  Udp.begin(localPort);

  Serial.begin(9600);
}

void loop() {
  // if there's data available, read a packet
  //int packetSize = Udp.parsePacket();
 
  // send a reply, to the IP address and port that sent us the packet we received
  receivePacket();
  sendPacket("Hello");
  extTemp();
  intTemp();
  //Serial.print("test: ");
  //Serial.println(server);
  
  delay(1000);
}

void sendPacket(char message[]) {
  Udp.beginPacket(server, localPort);
  Udp.write(message);
  Udp.endPacket();
}

void receivePacket() {
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
    Serial.println("Contents:");
    Serial.println(packetBuffer);
    testString(packetBuffer, (packetSize-2));
  }
}

void testString(char message[], int strLength) {
  int i,j,start;
  start = 0;
  for (i=0;i<=strLength;i++) 
    { //check entire string 
    if (message[i]==',') {//if comma found 
      /*for (j=0;j=i-1;j++)//for the beginning to the current position - 1 for the comma symbol 
      {
        temp[j]=message[j];//transfer the chars to temp string 
      }
      Serial.println(temp);
      for(j=i+1;j==strLength;j++)//the remaining after comma symbol
      {
        temp[j]=message[j];//transfer the remain chars
      }
      Serial.println(temp);*/
      for(j=start;j<i;j++) {
        Serial.print(message[j]);
        
      }
      Serial.println(); 
                Serial.println(); 
      start = i+1;
      //Serial.println("Found Comma!");
      //c1 = i;
      /*if(c1 == NULL) {
        c1 = i;
      } else {
         c2 = i;
      }*/
    } 
  }
          Serial.println(); 
  Serial.println(message[strLength]);
  //Serial.println(c1);
  //Serial.println(c2);
}

void extTemp() {
   //sensor_reading = analogRead(sensor_pin);         // stores the digitized (0 - 1023) analog reading from the LM34
   fahrenheit = (100.0 * analogRead(temp_pin) * vref)/1023;   // calculates the actual fahrenheit temperature
   centigrade = (((5.0/9.0))*(fahrenheit-32.0)); //conversion to degrees C
   
   Serial.print (centigrade); Serial.print("C "); 
   Serial.print(fahrenheit); Serial.print("F ");
}

void intTemp() {
  Serial.print (chipTemp.celsius()); Serial.print("C "); 
  Serial.print(chipTemp.fahrenheit()); Serial.println("F "); 
}
