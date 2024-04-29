// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("CAN Sender");

  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {

  Serial.print("Sending packet ... ");

  // Send message with higher priority
  CAN.beginPacket(0x00);
  CAN.write(0);
  CAN.endPacket();

  delay(1000);
}

