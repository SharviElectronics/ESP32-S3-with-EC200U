
#define EC200U_RX 18  // ESP32 pin connected to EC200U TX
#define EC200U_TX 17  // ESP32 pin connected to EC200U RX
#define PW_KEY  	10  


void setup() {
  pinMode(PW_KEY, OUTPUT);
  Serial.begin(115200);              // Monitor
  Serial2.begin(115200, SERIAL_8N1, EC200U_RX, EC200U_TX);  // EC200U UART
  digitalWrite(PW_KEY, LOW);
  delay(3000);
  Serial.println("Initializing EC200U...");

  sendAT("AT", "OK");
  sendAT("AT+CMGF=1", "OK");  // Set SMS to text mode
  sendAT("AT+CMGS=\"+9199XXXXXXXX\"", ">");  // Replace with your number
  Serial2.print("Hello from EC200U!\r");   // SMS content
  Serial2.write(0x1A);  // Ctrl+Z to send
  Serial.println("SMS Sent!");
}

void loop() {
  // Nothing to do in loop
}

// Function to send AT command and wait for expected response
void sendAT(String command, String expectedResponse, unsigned long timeout = 3000) {
  Serial2.println(command);
  unsigned long t = millis();
  String response = "";

  while (millis() - t < timeout) {
    while (Serial2.available()) {
      char c = Serial2.read();
      response += c;
    }
    if (response.indexOf(expectedResponse) != -1) break;
  }

  Serial.println("CMD: " + command);
  Serial.println("RESP: " + response);
}
