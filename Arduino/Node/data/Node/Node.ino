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
// buffers for receiving and sending data
char  bootBuffer[] = "DE:AD:BE:EF:FE:EF";       // a string to send back
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEF };
IPAddress ip(192, 168, 1, 178);     // Arduino IP address
IPAddress server(255, 255, 255, 255);  // Server IP address
unsigned int localPort = 8888;      // local port to listen on

int temp_pin = 0;        // the analog pin for LM34 temp sensor - Cannot use pin 0 as it is used for something by DRobotics LCD shield
int motion_pin = 2;
int alarm_pin = A2;    // select the input pin for the potentiometer
int leds[] = {5, 3, 6}; 
float sensor_reading = 0.0;        // variable to store the value coming from the sensor
float vref = 1.04;        // variable to store the voltage reference used (check for validity with a DMM)
float fahrenheit = 0.0;        // variable to store the actual temperature
float centigrade = 0.0;
boolean debug = true;
boolean boot = true;

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;
//ChipTemp chipTemp;

void setup() {
  for(int i = 0; i < 3; i++){   
    pinMode(leds[i], OUTPUT);   //Set the three LED pins as outputs   
  } 
  pinMode( temp_pin, INPUT );        // set LM34 temp sensor pin as an input
  pinMode( motion_pin, INPUT );      // set PIR sensor pin as an input
  analogReference(INTERNAL);         // set the analog reference to the 1.1V internal reference
  Ethernet.begin(mac,ip);            // Start Ethernet connection
  Udp.begin(localPort);              // Start UDP server
  Serial.begin(9600);                // Serial Output init
  Serial.print(mac[0]);
  while(boot) {
Udp.flush();
    sendPacket(bootBuffer,8888);
    
     int packetSize = Udp.parsePacket();
  if(packetSize)
  {
    IPAddress remote = Udp.remoteIP();

    // read the packet into packetBufffer
    char* msg = (char*)malloc(packetSize+1);
    int len = Udp.read(msg,packetSize+1);
    msg[len]=0;
      if(String(msg) == "booting") {
                boot = false;
                server = Udp.remoteIP();
      }
    }
    Udp.stop();
        Serial.print("restart connection: ");
    Serial.println (Udp.begin(localPort) ? "success" : "failed");
    Udp.flush();
    //delay(2000);
  }
}

void loop() {  
  //getLux();
  //delay(1000);
  receivePacket();

}










