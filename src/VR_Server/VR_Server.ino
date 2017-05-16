/**
 * @author <Your name here>
 *
 * This sketch controls various electrical
 * products using your voice.
 * There is a bluetooth interface so that
 * one may see the status of powered devices.
 */

#include "Arduino.h"
#if !defined(SERIAL_PORT_MONITOR)
  #error "Arduino version not supported. Please update your IDE to the latest version."
#endif

#if defined(SERIAL_PORT_USBVIRTUAL)
  // Shield Jumper on HW (for Leonardo and Due)
  #define port SERIAL_PORT_HARDWARE
  #define pcSerial SERIAL_PORT_USBVIRTUAL
#else
  // Shield Jumper on SW (using pins 12/13 or 8/9 as RX/TX)
  #include "SoftwareSerial.h"
  SoftwareSerial port(12, 13);
  #define pcSerial SERIAL_PORT_MONITOR
#endif

#include "EasyVR.h"

EasyVR easyvr(port);

// Constant pin numbers
const int LED_PIN1 = 22;
const int LED_PIN2 = 23;
const int RELAY_PIN1 = 24;

//Groups and Commands
enum Groups
{
  GROUP_0  = 0,
  GROUP_1  = 1,
};

enum Group0 
{
  G0_MY_SD_TRIGGER = 0,
};

enum Group1 
{
  G1_TURN_ON = 0,
  G1_POWER_OFF = 1,
  G1_SAY_HI = 2,
  G1_TURN_ON_ANUJ = 3,
  G1_POWER_OFF_ANUJ = 4,
  G1_SAY_HI_ANUJ = 5,
  G1_TURN_ON_KYLE = 6,
  G1_POWER_OFF_KYLE = 7,
  G1_SAYHI_KYLE = 8,
};


int8_t group, idx;
boolean relayState = 0;

// The setup function runs only once
void setup()
{
  pinMode (LED_PIN1, OUTPUT);
  pinMode (LED_PIN2, OUTPUT);
  pinMode (RELAY_PIN1, OUTPUT);
  
  // setup PC serial port
  pcSerial.begin(9600);

  // Start bluetooth
  arduinoBtSetup();

  // bridge mode?
  int mode = easyvr.bridgeRequested(pcSerial);
  switch (mode)
  {
  case EasyVR::BRIDGE_NONE:
    // setup EasyVR serial port
    port.begin(9600);
    // run normally
    pcSerial.println(F("---"));
    pcSerial.println(F("Bridge not started!"));
    break;
    
  case EasyVR::BRIDGE_NORMAL:
    // setup EasyVR serial port (low speed)
    port.begin(9600);
    // soft-connect the two serial ports (PC and EasyVR)
    easyvr.bridgeLoop(pcSerial);
    // resume normally if aborted
    pcSerial.println(F("---"));
    pcSerial.println(F("Bridge connection aborted!"));
    break;
    
  case EasyVR::BRIDGE_BOOT:
    // setup EasyVR serial port (high speed)
    port.begin(115200);
    // soft-connect the two serial ports (PC and EasyVR)
    easyvr.bridgeLoop(pcSerial);
    // resume normally if aborted
    pcSerial.println(F("---"));
    pcSerial.println(F("Bridge connection aborted!"));
    break;
  }

  while (!easyvr.detect())
  {
    Serial.println("EasyVR not detected!");
    delay(1000);
  }
  
  easyvr.setPinOutput(EasyVR::IO1, LOW);
  Serial.println("EasyVR detected!");
  easyvr.setTimeout(5);
  easyvr.setLanguage(EasyVR::ENGLISH);
  easyvr.setKnob(EasyVR::LOOSE);

  group = EasyVR::TRIGGER; //<-- start group (customize)
}

void action();

// The loop function runs forever
void loop()
{
  easyvr.setPinOutput(EasyVR::IO1, HIGH); // LED on (listening)

  Serial.print("Say a command in Group ");
  Serial.println(group);
  easyvr.recognizeCommand(group);

  do
  {
    // can do some processing while waiting for a spoken command
  }
  while (!easyvr.hasFinished());
  
  easyvr.setPinOutput(EasyVR::IO1, LOW); // LED off

  idx = easyvr.getWord();
  if (idx >= 0)
  {
    // built-in trigger (ROBOT)
    group = GROUP_1;
    // group = GROUP_X; <-- jump to another group X
    return;
  }
  idx = easyvr.getCommand();
  if (idx >= 0)
  {
    // print debug message
    uint8_t train = 0;
    char name[32];
    Serial.print("Command: ");
    Serial.print(idx);
    if (easyvr.dumpCommand(group, idx, name, train))
    {
      Serial.print(" = ");
      Serial.println(name);
    }
    else
      Serial.println();
    easyvr.playSound(0, EasyVR::VOL_FULL);
    // perform some action
    action();
  }
  else // errors or timeout
  {
    if (easyvr.isTimeout())
      Serial.println("Timed out, try again...");
    int16_t err = easyvr.getError();
    if (err >= 0)
    {
      Serial.print("Error ");
      Serial.println(err, HEX);
    }
  }

  sendBlutoothValues(); // Update and send bluetooth status
  // TODO: HINT there's a function written
  //       below that will do this for you!
}

/**
 * Action function for reacting to
 * various trained voice commands.
 */
void action()
{
    switch (group)
    {
    case GROUP_0:
      switch (idx)
      {
      case G0_MY_SD_TRIGGER:
        Serial.println("I heard my name!");
        group = GROUP_1; // <-- jump to group 1
        break;
      }
      break;

    case GROUP_1:
      digitalWrite(RELAY_PIN1,LOW);
      if (idx == G1_SAY_HI) {
       Serial.println("Hi Abdulrahim");// Say hi on the serial console
       digitalWrite(RELAY_PIN1,HIGH);
       delay(500);
       digitalWrite(RELAY_PIN1,LOW);
       delay(500);
       digitalWrite(RELAY_PIN1,HIGH);
       delay(500);
       digitalWrite(RELAY_PIN1,LOW);
       relayState = 0;
       // and blink LED_PIN1 twice.
      } else if (idx == G1_SAY_HI_ANUJ) {
       Serial.println("Hi Anuj");// Say hi on the serial console
       digitalWrite(RELAY_PIN1,HIGH);
       delay(500);
       digitalWrite(RELAY_PIN1,LOW);
       delay(500);
       digitalWrite(RELAY_PIN1,HIGH);
       delay(500);
       digitalWrite(RELAY_PIN1,LOW);
       relayState = 0;
      } else if (idx == G1_SAYHI_KYLE) {
       Serial.println("Hi Kyle");// Say hi on the serial console
       digitalWrite(RELAY_PIN1,HIGH);
       delay(500);
       digitalWrite(RELAY_PIN1,LOW);
       delay(500);
       digitalWrite(RELAY_PIN1,HIGH);
       delay(500);
       digitalWrite(RELAY_PIN1,LOW);
       relayState = 0;
      } else if (idx == G1_TURN_ON || idx == G1_TURN_ON_ANUJ || idx == G1_TURN_ON_KYLE) {
       Serial.println("Turning on..."); // Print "Turning on..." out to the serial
       digitalWrite(RELAY_PIN1,HIGH);// console and turn RELAY_PIN1 on.
       relayState = 1; // tells relaystate it's on
      } else if (idx == G1_POWER_OFF || idx == G1_POWER_OFF_ANUJ || idx == G1_POWER_OFF_KYLE) {
       Serial.println("Powering off");// Print "Powering off" out to the serial
       digitalWrite(RELAY_PIN1,LOW); // console and turn RELAY_PIN1 off.
       relayState = 0; // tells relaystate it's off
      break;
    }
  }
}
/**
 * Setup the bluetooth module.
 */
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

/**
 * Send updated relay values over
 * Bluetooth interface.
 */
void sendBlutoothValues() {
  Serial1.write("Relay State: ");
  Serial1.write(relayState > 0 ? "ON\n" : "OFF\n");
}
