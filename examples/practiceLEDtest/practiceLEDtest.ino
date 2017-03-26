
boolean LEDon = false;
boolean pressed = false;
int ledPin = 12;
int buttonpin = 2;


void setup() {  
  pinMode(ledPin, OUTPUT);
  pinMode(buttonpin,INPUT_PULLUP);

}

void loop()
{
  pressed = digitalRead(buttonpin);
  if (pressed)
  {
    if (LEDon)
    {
      digitalWrite(12, LOW);
      LEDon = false;
    }
    else
    {
      digitalWrite (12, HIGH);
      LEDon = true;
    }
  }
  delay(200);
}
