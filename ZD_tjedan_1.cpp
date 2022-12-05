int pinLed_1=7;
int pinLed_2=12;

unsigned long interval_off_1=2000;
unsigned long interval_off_2=3000;
unsigned long interval_on=500;

unsigned long prevMill[2]={millis()};


void setup() {
pinMode(pinLed_1, OUTPUT);
pinMode(pinLed_2, OUTPUT);
}

void setHigh(int pinLed){
  digitalWrite(pinLed, HIGH);
}

void setLow(int pinLed){
  digitalWrite(pinLed, LOW);
}

void blink(int diode_num,int pinLed, int interval_on,int interval_off){

  if(!digitalRead(pinLed)){
    if((long)millis()-prevMill[diode_num]>interval_off){
    prevMill[diode_num]=millis();
    setHigh(pinLed);
    }
  }

  if(digitalRead(pinLed)){
    if((long)millis()-prevMill[diode_num]>interval_on){
    prevMill[diode_num]=millis();
    setLow(pinLed);
    }
  }

}

void loop() {
  
  blink(0,pinLed_1,interval_on,interval_off_1);
  blink(1,pinLed_2,interval_on,interval_off_2);
}
