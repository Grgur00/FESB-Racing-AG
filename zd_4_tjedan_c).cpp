#include <SPI.h>
#include <mcp_can.h>

MCP_CAN CAN(10); // Create an MCP_CAN object and specify the slave select pin

void setup() {
  // Initialize the MCP_CAN object
  if (CAN.begin(MCP_ANY,CAN_500KBPS,MCP_16MHZ) == CAN_OK) {
    Serial.println("MCP2515 initialized successfully");
  } else {
    Serial.println("Error initializing MCP2515");
  }
}

void loop() {
  // Set up the CAN message
  long unsigned int id = 0x123; // Set the ID of the message
  byte data[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; // Set the data of the message
  byte length = 8; // Set the length of the message
  byte flag = 0; // Set the flag for the message (0 for standard message, 1 for extended message)
  
  // Send the message using the MCP_CAN library
  if (CAN.sendMsgBuf(id, flag, length, data) == CAN_OK) {
    Serial.println("Message sent successfully");
  } else {
    Serial.println("Error sending message");
  }
  
  delay(1000); // Delay for 1 second before sending the next message
}
