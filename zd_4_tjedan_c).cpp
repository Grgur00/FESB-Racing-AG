#include <SPI.h>
#include <mcp_can.h>

MCP_CAN CAN(10); 

void setup() {
  if (CAN.begin(MCP_ANY,CAN_500KBPS,MCP_16MHZ) == CAN_OK) {
    Serial.println("MCP2515 initialized successfully");
  } else {
    Serial.println("Error initializing MCP2515");
  }
}

void loop() {
 
  long unsigned int id = 0x123; 
  byte data[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
  byte length = 8; 
  byte flag = 0; 
  
  if (CAN.sendMsgBuf(id, flag, length, data) == CAN_OK) {
    Serial.println("Message sent successfully");
  } else {
    Serial.println("Error sending message");
  }
  
  delay(1000); 
}
