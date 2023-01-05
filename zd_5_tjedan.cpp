
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

void parseData(byte data[8], int startIndex, float factor, float offset, int length) {
 
  int value = 0;
  for (int i = 0; i < length; i++) {
    value |= data[startIndex + i] << (8 * i);
  }
  
  float realValue = value * factor + offset;
  
  Serial.println(realValue);
}

void loop() {
  
  if (CAN.checkReceive()) {
    long unsigned int id;
    byte data[8];
    byte len;
    byte flag;
    if (CAN.readMsgBuf(&id, &flag, &len, data) == CAN_OK) {
      parseData(data, 0, 1.0, 0.0, 4); 

    }
  }
}

