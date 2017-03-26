#define ROBOT_NAME "RandomBot"

// If you haven't configured your device before use this
//#define BLUETOOTH_SPEED 9600
// If you are modifying your existing configuration, use this:
#define BLUETOOTH_SPEED 57600

// Swap RX/TX connections on bluetooth chip
//   Pin 10 --> Bluetooth TX
//   Pin 11 --> Bluetooth RX

unsigned int ledPin = 22;

/*
  The posible baudrates are:
    AT+BAUD1-------1200
    AT+BAUD2-------2400
    AT+BAUD3-------4800
    AT+BAUD4-------9600 - Default for hc-06
    AT+BAUD5------19200
    AT+BAUD6------38400
    AT+BAUD7------57600 - Johnny-five speed
    AT+BAUD8-----115200
    AT+BAUD9-----230400
    AT+BAUDA-----460800
    AT+BAUDB-----921600
    AT+BAUDC----1382400
*/


void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Starting config");
  Serial1.begin(BLUETOOTH_SPEED);
  delay(1000);

  // Should respond with OK
  Serial1.print("AT");
  waitForResponse();

  // Should respond with its version
  Serial1.print("AT+VERSION");
  waitForResponse();

  // Set pin to 0000
  Serial1.print("AT+PIN0000");
  waitForResponse();

  // Set the name to ROBOT_NAME
  Serial1.print("AT+NAME");
  Serial1.print(ROBOT_NAME);
  waitForResponse();

  // Set baudrate to 57600
  Serial1.print("AT+BAUD7");
  waitForResponse();

  Serial.println("Done!");

  Serial1.print("AT");
  waitForResponse();
}

void waitForResponse() {
    delay(1000);
    while (Serial1.available()) {
      Serial.write(Serial1.read());
    }
    Serial.write("\n");
}

void loop() {
  char charCmd = 0;
  
  if (Serial1.available()) {
    while (Serial1.available()) {
      charCmd = Serial1.read();
      Serial.write(charCmd);
      if (charCmd == '1')
      {
        digitalWrite (ledPin, HIGH);  
      }
    }
    Serial.write("\n");
  }
}
