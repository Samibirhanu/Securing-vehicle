void setup()
{
  // Start communication with the SIM900 on Serial3 (pins 14 and 15)
  Serial3.begin(9600);
  Serial.begin(9600);

  delay(1000); // Wait for module to initialize

  Serial.println("Initializing...");
  sendATCommand("AT"); // Check if module is ready

  sendATCommand("AT+CMGF=1"); // Set SMS mode to text

  sendATCommand("AT+CMGS=\"+251977245580\""); // Replace with recipient's phone number
  Serial3.print("Hello, this is Sam from Arduino Due!"); // Message content
  delay(100);
  Serial3.write(26); // ASCII code of CTRL+Z to send the SMS
  delay(1000); // Wait for the message to be sent

  Serial.println("Message Sent!");
}

void loop()
{
  // Not used in this example
}

void sendATCommand(String cmd)
{
  Serial3.println(cmd);
  delay(1000); // Wait for the command to be processed
  updateSerial();
}

void updateSerial()
{
  while (Serial.available())
  {
    Serial3.write(Serial.read()); // Forward data to Serial3 port
  }
  while (Serial3.available())
  {
    Serial.write(Serial3.read()); // Forward data to Serial port
  }
}
