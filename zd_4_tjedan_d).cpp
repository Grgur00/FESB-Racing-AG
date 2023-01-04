#include <SPI.h>
#include <mcp_can.h> 

MCP_CAN CAN(10); 

void setup() {
  if (CAN.begin(MCP_ANY,CAN_500KBPS,MCP_8MHZ) == CAN_OK) {
    Serial.println("MCP2515 initialized successfully");
  } else {
    Serial.println("Error initializing MCP2515");
  }
}

void loop() {
  if (CAN.checkReceive()) {

    long unsigned int id;
    byte data[8];
    byte len;
    byte flag;
    if (CAN.readMsgBuf(&id, &flag, &len, data) == CAN_OK) {
      Serial.print("ID: 0x");
      Serial.print(id, HEX);
      Serial.print("  Data: ");
      for (int i = 0; i < len; i++) {
        Serial.print(data[i], HEX);
        Serial.print(" ");
      }
      Serial.println();
    }
  }
}
