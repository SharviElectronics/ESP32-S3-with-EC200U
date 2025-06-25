#include <ppposclient.h>

#define EC200U_RX   18  // ESP32 pin connected to EC200U TX
#define EC200U_TX   17  // ESP32 pin connected to EC200U RX
#define PW_KEY  	  10  


const char* APN = "internet";         // Replace with your SIM card APN
const char* USER = "";                // Username (if required)
const char* PASS = "";                // Password (if required)

PPPOSClient pppClient;

void setup() {
  pinMode(PW_KEY, OUTPUT);
  Serial.begin(115200);
  digitalWrite(PW_KEY, LOW);
  delay(2000);
  Serial.println("Starting PPPoS with EC200U...");

  // Begin PPP client on UART1
  pppClient.setSerial(1, EC200U_RX, EC200U_TX);  
  pppClient.setAPN(APN, USER, PASS);
  pppClient.setDebugStream(&Serial);

  // Optional: Set modem init sequence
  pppClient.setModemResetCommandSequence("AT+CFUN=1\r\nAT+CPIN?\r\n");

  if (pppClient.connect()) {
    Serial.println("Connected to cellular network!");
  } else {
    Serial.println("Failed to connect.");
  }
}

void loop() {
  if (pppClient.isConnected()) {
    Serial.println("IP Address: " + pppClient.getIPAddress());
  } else {
    Serial.println("Disconnected...");
  }

  delay(10000);
}
