/*
 Lora Node1

*/
#include <SPI.h>  // include libraries
#include <LoRa.h>
#include <LowPower.h>


int UmiSensPin = A2;

String outgoing;  // outgoing message

byte msgCount = 0;  // count of outgoing messages
byte MasterNode = 0xFF;
byte Node1 = 0xBB;


void setup() {
  Serial.begin(9600);  // initialize serial
  pinMode(UmiSensPin, INPUT);
  while (!Serial)
    ;

  Serial.println("LoRa Duplex");



  if (!LoRa.begin(433E6)) {  // initialize ratio at 915 MHz
    Serial.println("LoRa init failed. Check your connections.");
    while (true)
      ;  // if failed, do nothing
  }

  Serial.println("LoRa init succeeded.");
}

void loop() {
  //mio
  // send packet modo 1
  LoRa.beginPacket();
  LoRa.print("umi % ");
  LoRa.print(analogRead(UmiSensPin));
  LoRa.endPacket();
  // send packet modo 2 (con funzione)
  outgoing = ("umi % " + analogRead(UmiSensPin));
  sendMessage(outgoing, MasterNode, Node1);
  //mio*/
}

void sendMessage(String outgoing, byte MasterNode, byte otherNode) {
  LoRa.beginPacket();             // start packet
  LoRa.write(MasterNode);         // add destination address
  LoRa.write(Node1);              // add sender address
  LoRa.write(msgCount);           // add message ID
  LoRa.write(outgoing.length());  // add payload length
  LoRa.print(outgoing);           // add payload
  LoRa.endPacket();               // finish packet and send it
  msgCount++;                     // increment message ID
}
