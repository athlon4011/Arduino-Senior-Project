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
#include "ChipTemp.h"


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);     // Arduino IP address
IPAddress server(192, 168, 1, 39);  // Server IP address
unsigned int localPort = 8888;      // local port to listen on

int temp_pin = 0;        // the analog pin for LM34 temp sensor - Cannot use pin 0 as it is used for something by DRobotics LCD shield
int motion_pin = 2;
float sensor_reading = 0.0;        // variable to store the value coming from the sensor
float vref = 1.04;        // variable to store the voltage reference used (check for validity with a DMM)
float fahrenheit = 0.0;        // variable to store the actual temperature
float centigrade = 0.0;
boolean debug = true;


// buffers for receiving and sending data
char  ReplyBuffer[] = "acknowledged";       // a string to send back

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;
ChipTemp chipTemp;

void setup() {
  pinMode( temp_pin, INPUT );        // set LM34 temp sensor pin as an input
  pinMode( motion_pin, INPUT );      // set PIR sensor pin as an input
  analogReference(INTERNAL);         // set the analog reference to the 1.1V internal reference
  Ethernet.begin(mac,ip);            // Start Ethernet connection
  Udp.begin(localPort);              // Start UDP server
  Serial.begin(9600);                // Serial Output init
}

void loop() {
  receivePacket();
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






