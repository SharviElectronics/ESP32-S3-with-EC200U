#define EC200U_RX   18
#define EC200U_TX   17
#define PW_KEY  10  

void setup() {
  pinMode(PW_KEY, OUTPUT);  // Output for Power Key
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, EC200U_RX, EC200U_TX);  // Connect through UART
  digitalWrite(PW_KEY, LOW); // Enable the EC200U by Power Key

}

void loop() {
  if (Serial.available()) {
    Serial2.write(Serial.read());
  }

  if (Serial2.available()) {
    Serial.write(Serial2.read());
  }
}
