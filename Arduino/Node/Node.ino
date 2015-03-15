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
int blue = 7;
int green = 6;
int red = 5;
float sensor_reading = 0.0;        // variable to store the value coming from the sensor
float vref = 1.04;        // variable to store the voltage reference used (check for validity with a DMM)
float fahrenheit = 0.0;        // variable to store the actual temperature
float centigrade = 0.0;
boolean debug = false;


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
/*Udp.flush();
    char  test[] = "acknowledged";
    sendPacket(test,8888);
    delay(2000);
    //boot = false;
    Serial.println("Sent Message!!!!!!!!!!!!");*/
}



void testString(String message) {
  int i,j,start;
  start = 0;
  Serial.println(message);
  String test = "";
  String test2 = "";
  for (i=0;i<=message.length();i++) 
    { //check entire string 
    if (message[i]!=',') {
      test += message[i];
    }
    if (message[i]==',') {//if comma found 
      Serial.println("found comma");
      Serial.println(test);
      
      
      for(j=i+1;j<message.length();j++) {
        //Serial.print(message[j]);
        test2 += message[j];
      }
      Serial.println(test2);
      audio(test.toInt());
      int pin1 = test2[0]-48;
      int pin2 = test2[1]-48;
      int pin3 = test2[2]-48;
      blinkLED(pin1,pin2,pin3,4,200);
    }
  }
          Serial.println(); 
  //Serial.println(message[strLength]);
  //Serial.println(c1);
  //Serial.println(c2);
}






