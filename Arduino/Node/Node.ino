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
#include <UIPEthernet.h>
//#include "ChipTemp.h"
#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);     // Arduino IP address
IPAddress server(192, 168, 1, 39);  // Server IP address
unsigned int localPort = 8888;      // local port to listen on

int temp_pin = 0;        // the analog pin for LM34 temp sensor - Cannot use pin 0 as it is used for something by DRobotics LCD shield
int motion_pin = 2;
int blue = 6;
int green = 3;
int red = 5;
float sensor_reading = 0.0;        // variable to store the value coming from the sensor
float vref = 1.04;        // variable to store the voltage reference used (check for validity with a DMM)
float fahrenheit = 0.0;        // variable to store the actual temperature
float centigrade = 0.0;
boolean debug = true;
boolean boot = false;


// buffers for receiving and sending data
char  bootBuffer[] = "booting";       // a string to send back

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;
//ChipTemp chipTemp;

void setup() {
  pinMode(red, OUTPUT); 
  pinMode(green, OUTPUT); 
  pinMode(blue, OUTPUT); 
  pinMode( temp_pin, INPUT );        // set LM34 temp sensor pin as an input
  pinMode( motion_pin, INPUT );      // set PIR sensor pin as an input
  analogReference(INTERNAL);         // set the analog reference to the 1.1V internal reference
  Ethernet.begin(mac,ip);            // Start Ethernet connection
  Udp.begin(localPort);              // Start UDP server
  Serial.begin(9600);                // Serial Output init
  //delay(10000);
  /*Udp.flush();
  sendPacket(bootBuffer,8888);*/
}

void loop() {  

  receivePacket();
if(boot) {
Udp.flush();
    char  test[] = "acknowledged";
    sendPacket(bootBuffer,8888);
    delay(2000);
    //boot = false;
    //Serial.println("Sent Message!!!!!!!!!!!!");
    
     int packetSize = Udp.parsePacket();
  if(packetSize)
  {
    Serial.println("got message");
    IPAddress remote = Udp.remoteIP();
    boot = false;
    if(debug) {
      Serial.print("Received packet from ");
      
      for (int i =0; i < 4; i++)
      {
        Serial.print(remote[i], DEC);
        if (i < 3)
        {
          Serial.print(".");
        }
      }
      Serial.print(", port ");
      Serial.print(Udp.remotePort());
      Serial.print(", size ");
      Serial.println(packetSize);
    }
    // read the packet into packetBufffer
    char* msg = (char*)malloc(packetSize+1);
    int len = Udp.read(msg,packetSize+1);
    msg[len]=0;
    if(debug) {
      Serial.print("Contents: ");
      Serial.println(msg);
      //Serial.print('|');
    }
    }
    Udp.stop();
        Serial.print("restart connection: ");
    Serial.println (Udp.begin(localPort) ? "success" : "failed");
  }
  Udp.flush();
}










