#include "mcp_can.h"
#include "thermistor.h"
#include "HardwareSerial.h"

MCP_CAN CAN0(53);
// #define NUM_THERMISTORS 10
#define NUM_THERMISTORS 1
// Analog pin used to read the NTC
#define NTC_PIN0               A2
#define NTC_PIN1               A3
#define NTC_PIN2               A4
#define NTC_PIN3               A5
#define NTC_PIN4               A6
#define NTC_PIN5               A7
#define NTC_PIN6               A8
#define NTC_PIN7               A9
#define NTC_PIN8               A10
#define NTC_PIN9               A11


int pins[] = {NTC_PIN0, NTC_PIN1, NTC_PIN2, NTC_PIN3, NTC_PIN4, NTC_PIN5, NTC_PIN6, NTC_PIN7, NTC_PIN8, NTC_PIN9};

 

// THERMISTOR object

//ne postoji default constructor zato su ovako a ne odma u array

THERMISTOR thermistor0(NTC_PIN0,        // Analog pin
                      10000,          // Nominal resistance at 25 ºC
                      3950,           // thermistor's beta coefficient
                      10000);         // Value of the series resistor

THERMISTOR thermistor1(NTC_PIN1,        // Analog pin
                      10000,          // Nominal resistance at 25 ºC
                      3950,           // thermistor's beta coefficient
                      10000);         // Value of the series resistor

THERMISTOR thermistor2(NTC_PIN2,        // Analog pin
                      10000,          // Nominal resistance at 25 ºC
                      3950,           // thermistor's beta coefficient
                      10000);         // Value of the series resistor

THERMISTOR thermistor3(NTC_PIN3,        // Analog pin
                      10000,          // Nominal resistance at 25 ºC
                      3950,           // thermistor's beta coefficient
                      10000);         // Value of the series resistor

THERMISTOR thermistor4(NTC_PIN4,        // Analog pin
                      10000,          // Nominal resistance at 25 ºC
                      3950,           // thermistor's beta coefficient
                      10000);         // Value of the series resistor

THERMISTOR thermistor5(NTC_PIN5,        // Analog pin
                      10000,          // Nominal resistance at 25 ºC
                      3950,           // thermistor's beta coefficient
                      10000);         // Value of the series resistor

THERMISTOR thermistor6(NTC_PIN6,        // Analog pin
                      10000,          // Nominal resistance at 25 ºC
                      3950,           // thermistor's beta coefficient
                      10000);         // Value of the series resistor

THERMISTOR thermistor7(NTC_PIN7,        // Analog pin
                      10000,          // Nominal resistance at 25 ºC
                      3950,           // thermistor's beta coefficient
                      10000);         // Value of the series resistor

THERMISTOR thermistor8(NTC_PIN8,        // Analog pin
                      10000,          // Nominal resistance at 25 ºC
                      3950,           // thermistor's beta coefficient
                      10000);         // Value of the series resistor

THERMISTOR thermistor9(NTC_PIN9,        // Analog pin
                      10000,          // Nominal resistance at 25 ºC
                      3950,           // thermistor's beta coefficient
                      10000);         // Value of the series resistor

//THERMISTOR thermistors[] = {thermistor0, thermistor1, thermistor2, thermistor3, thermistor4, thermistor5, thermistor6, thermistor7, thermistor8, thermistor9};

THERMISTOR thermistors[] = {thermistor4};

// Global temperature reading
uint8_t temps = NULL;

uint8_t convertTemp(float *tempArray){
  
  uint8_t data[NUM_THERMISTORS*2];
  for (int i = 0; i < NUM_THERMISTORS; i++) {
    int16_t temp_data = (int16_t)(tempArray[i] * 10);
    data[i * 2] = temp_data & 0xff;
    data[i * 2 + 1] = (temp_data >> 8) & 0xff;
    
  }
  


  return *data;
}

void simulateCAN(uint32_t id, uint8_t *data, uint8_t len) {
  Serial.print("ID: ");
  Serial.print(id);
  Serial.print(" Data: ");
  for (int i = 0; i < len; i++) {
    Serial.print(data[i]);
    Serial.print(" ");
  }
  Serial.println();
}


void setup()
{
  Serial.begin(9600);
  if( CAN0.begin(MCP_ANY, CAN_500KBPS, MCP_8MHZ) == CAN_OK)
    Serial.println("Initialized");

  else
    Serial.println("Error initializing");

  CAN0.setMode(MCP_NORMAL);

}

void loop()
{

    float temperatures[NUM_THERMISTORS];
  for (int i = 0; i < NUM_THERMISTORS; i++) {
    temperatures[i] = thermistors[i].read();
    Serial.print("THERMISTOR ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(temperatures[i]);
  }

  CAN0.sendMsgBuf(0x100, 0, NUM_THERMISTORS * 2, convertTemp(temperatures));

  simulateCAN(0x100, convertTemp(temperatures),NUM_THERMISTORS * 2);

  delay(2000); //library je napravljen tako da svako ocitavanje jednog termistora traje 100ms  pa delay ne moze bit manji od 1000 za 10 termistora
}
