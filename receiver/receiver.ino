#include <SPI.h>
#include <Enrf24.h>
#include <nRF24L01.h>
#include <string.h>
#include <WiFi.h>


char ssid[] = "iPhone";
char password[] = "12348765";
IPAddress hostIp(184,106,153,149);
String writeAPIKey = "Y195PCV7LMVZWEKF";
WiFiClient client;
String s;
Enrf24 radio(PE_1, PE_2, PE_3); 
const uint8_t rxaddr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x01 };

void dump_radio_status_to_serialport(uint8_t);

void setup() {
  Serial.begin(115200);

  SPI.begin();
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(MSBFIRST);
  
  radio.begin();  // Defaults 1Mbps, channel 0, max TX power
  dump_radio_status_to_serialport(radio.radioState());

  radio.setRXaddress((void*)rxaddr);
  
  pinMode(PF_1, OUTPUT);
  digitalWrite(PF_1, LOW);
  pinMode(PF_2, OUTPUT);
  digitalWrite(PF_2, LOW);
    pinMode(PF_3, OUTPUT);
  digitalWrite(PF_3, LOW);
  radio.enableRX();  // Start listening

  //webclient setup
    Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }
  
    Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");
  
  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }
    digitalWrite(PF_3, HIGH);
    delay(1000);
    digitalWrite(PF_3, LOW);
  Serial.println("\nIP Address obtained");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
//  if (client.connect(hostIp, 80)) {
//    Serial.println("Connected to ThingSpeak!");
//    Serial.println();
    
//    client.print("POST /update HTTP/1.1\n");
//    client.print("Host: api.thingspeak.com\n");
//    client.print("Connection: close\n");

    
//  }
}
//}
void loop() {
  char inbuf[33];
  
  while (!radio.available(true));
  
  if (radio.read(inbuf)) {
    Serial.print("Received packet: ");
    Serial.println(inbuf);
//    digitalWrite(PF_1, !digitalRead(PF_1));
//    digitalWrite(PF_1, HIGH);
//    delay(1000);
//    digitalWrite(PF_1, LOW);

      client.stop();
  if (client.connect(hostIp, 80)) {
    
    s = "GET https://api.thingspeak.com/update?api_key=Y195PCV7LMVZWEKF"+(String) inbuf;
    Serial.println(s);
    client.println(s);

  }
//    client.print("\n\n");
    delay(15000);
//    digitalWrite(PF_2, HIGH);
//    delay(1000);
//    digitalWrite(PF_2, LOW);
  }
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

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
