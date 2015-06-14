#include <SPI.h>         // needed for Arduino versions later than 0018
#include <UIPEthernet.h>
//#include "ChipTemp.h"
#include <EEPROM.h>
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
//char  bootBuffer[] = "DE:AD:BE:EF:FE:EA";       // a string to send back

uint8_t  mac[6] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEA };
char macstr[18];

//IPAddress ip(192, 168, 1, 177);     // Arduino IP address
IPAddress server(255, 255, 255, 255);  // Server IP address
unsigned int localPort = 8888;      // local port to listen on

int temp_pin = 0;        // the analog pin for LM34 temp sensor
int motion_pin = 2;
int alarm_pin = A2;    // select the input pin for the alarm voltage divider
int leds[] = {5, 3, 6}; 
//float sensor_reading = 0.0;        // variable to store the value coming from the sensor
float vref = 1.04;        // variable to store the voltage reference used (check for validity with a DMM)
int fahrenheit = 0;        // variable to store the actual temperature
//float centigrade = 0.0;
boolean debug = true;
boolean boot = true;

// An EthernetUDP instance to let us send and receive packets over UDP
EthernetUDP Udp;
//ChipTemp chipTemp;

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
  
  
  for(int i = 0; i < 3; i++){   
    pinMode(leds[i], OUTPUT);   //Set the three LED pins as outputs   
  } 
  pinMode( temp_pin, INPUT );        // set LM34 temp sensor pin as an input
  pinMode( motion_pin, INPUT );      // set PIR sensor pin as an input
  analogReference(INTERNAL);         // set the analog reference to the 1.1V internal reference
  snprintf(macstr, 18, "%02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  Ethernet.begin(mac);            // Start Ethernet connection
  //Serial.print("localIP: ");
  //Serial.println(Ethernet.localIP());
  Udp.begin(localPort);              // Start UDP server
  Serial.begin(9600);                // Serial Output init
  //Serial.print(mac[0]);
  while(boot) {
Udp.flush();
    sendPacket(macstr,8888);
    
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
      //  Serial.print("restart connection: ");
      Udp.begin(localPort);
//    Serial.println (Udp.begin(localPort) ? "success" : "failed");
    Udp.flush();
    //delay(2000);
  }
}

void loop() {  
  //getLux();
  //delay(1000);
  receivePacket();

}










