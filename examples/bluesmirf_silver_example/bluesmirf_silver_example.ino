/**
 * BlueSmirf Bluetooth silver tester
 * 
 * This test simply sets the BT module
 * to a 9600 baud rate (default powerup
 * is 115200) and passes data between the
 * serial command window and the bluetooth
 * module.
 */

void setup() {
  Serial.begin(9600);
  arduinoBtSetup();
}

void loop() {
  // If the bluetooth sent any characters
  if (Serial1.available()) {
    Serial.print((char)Serial1.read());
  }

  // If stuff was type in the serial monitor
  if (Serial.available()) {
    // Send any characters the Serial monitor prints to the bluetooth
    Serial1.write((char)Serial.read());
  }
}

void arduinoBtSetup() {
  // THIS BAUD RATE HAS PROBLEMS TRANSMITTING
  // The Bluetooth Mate defaults to 115200bps
  Serial1.begin(115200);
  delay(10);

  // Put module into CMD mode
  Serial1.write("$$$");
  // Give some time for BT to send back CMD
  delay(100);

  // Set baud to a lower rate of 9600
  Serial1.write("SU,9600\r");
  delay(100);

  // Clear the BT buffer of junk
  while (Serial1.available()) {
    Serial1.read();
  }

  // Set new baud for Arduino
  Serial1.begin(9600);
}
