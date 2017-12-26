#include <SPI.h>
#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h>
//#include<adc.h>

Enrf24 radio(PE_1, PE_2, PE_3); 
const uint8_t txaddr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x01 };

void dump_radio_status_to_serialport(uint8_t);
  int potVal = 0;
  int ldrVal = 0;
  String sendstring;

void setup() {
  Serial.begin(115200);
  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  radio.begin();  // Defaults 1Mbps, channel 0, max TX power
    Serial.println("---------------TX--------------------");
  dump_radio_status_to_serialport(radio.radioState());

  radio.setTXaddress((void*)txaddr);
}

void loop() {
  potVal = analogRead(PD_2);

    ldrVal = analogRead(PD_3);
  sendstring = "&field1="+(String)ldrVal +"&field2="+ (String)potVal;
//  sendstring = "POT1=1212" + ;
  
  Serial.print("Sending packet: ");
  Serial.println(sendstring);
  radio.print(sendstring);
  radio.flush();
  delay(15000);
}

void dump_radio_status_to_serialport(uint8_t status)
{
  Serial.print("Enrf24 radio transceiver status: ");
  switch (status) {
    case ENRF24_STATE_NOTPRESENT:
      Serial.println("NO TRANSCEIVER PRESENT");
      break;

    case ENRF24_STATE_DEEPSLEEP:
      Serial.println("DEEP SLEEP <1uA power consumption");
      break;

    case ENRF24_STATE_IDLE:
      Serial.println("IDLE module powered up w/ oscillators running");
      break;

    case ENRF24_STATE_PTX:
      Serial.println("Actively Transmitting");
      break;

    case ENRF24_STATE_PRX:
      Serial.println("Receive Mode");
      break;

    default:
      Serial.println("UNKNOWN STATUS CODE");
  }
}
