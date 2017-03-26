#include <SoftwareSerial.h>

// Global variables goes here
const int BT_RX_PIN = 22; // RX-I pin of bluethooth module
const int BT_TX_PIN = 23; // TX-O pin of bluetooth module

// Delcare bluetooth serial object
SoftwareSerial bluetooth(BT_RX_PIN, BT_TX_PIN); 

// setup() function runs once
void setup() {

  // set the modes for the pins
  pinMode(BT_RX_PIN, INPUT_PULLUP);
  pinMode(BT_TX_PIN, OUTPUT);

  // call function that initializes bluetooth module
  bluetoothSetup();
}

// loop() function runs forever
void loop() {
  bluetooth.write("I'm alive!\n");
  delay(2000);
}

// the bluetooth setup function
void bluetoothSetup() {
  bluetooth.begin(115200);
  delay(10);

  // put module into command mode
  bluetooth.write("$$$");
  // give some time for module to reply
  delay(100);

  // set new baud rate to 9600
  bluetooth.write("U,9600,N\r");
  delay(100);

  // clear the bluetooth serial buffer of any junk
  while (bluetooth.available()) {
    bluetooth.read();
  }

  // set new baud rate to read from arduino
  bluetooth.begin(9600);
}
