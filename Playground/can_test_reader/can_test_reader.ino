/*
 * @brief: Teensy 3.2 code to just output whats on the CAN bus to serial
 *
 */

#include "SAB_readings_rear.h"
#include "HyTech_FlexCAN.h"
#include "CAN_ID.h"

FlexCAN CAN(500000);

static CAN_message_t msg_rx;
//static CAN_message_t msg_tx;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  CAN.begin();
  Serial.println("CAN reader active");
}

void loop() {
  // put your main code here, to run repeatedly:
  while(CAN.read(msg_rx)) {
    Serial.print("ID: ");
    Serial.println(msg_rx.id, HEX);
    Serial.print("MSG: ");
    for(int i = 0; i < msg_rx.len; i++) {
      Serial.print(msg_rx.buf[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}
