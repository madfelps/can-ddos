// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>

const long attackerId = 66;
const long senderid = 67;

int attackerCounter;
int senderCounter;
int totalCounter;

void count(long id){

  if (CAN.packetId() == senderid) {
    senderCounter++;
  }
  else if (CAN.packetId() == attackerId) {
    attackerCounter++;
  }
  totalCounter++;
  
}

float percent(long a, long b){
  float percent = ((float)a / b) * 100;
  return percent;
}

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("CAN Receiver");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  attackerCounter = 0;
  senderCounter = 0;
  totalCounter = 0;
}

void loop() {
  // try to parse packet
  int packetSize = CAN.parsePacket();

  if (packetSize) {
    
    Serial.print("Received ");


    if (CAN.packetRtr()) {
      Serial.print("RTR ");
    }

    Serial.print("packet with id 0x");
    Serial.print(CAN.packetId(), HEX);

    count(CAN.packetId());

    if (CAN.packetRtr()) {
      Serial.print(" and requested length ");
      Serial.println(CAN.packetDlc());
    } else {
      Serial.print(" and length ");
      Serial.println(packetSize);

      while (CAN.available()) {
        Serial.print((char)CAN.read());
      }
      Serial.println();
    }
  }

  Serial.println("TOTAL: ");
  Serial.println(totalCounter);
  Serial.println("Attacker percent: ");
  Serial.println(percent(attackerCounter, totalCounter));
  
  
  delay(3000);
}

