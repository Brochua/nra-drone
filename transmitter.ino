/*
*           
* Library: TMRh20/RF24, https://github.com/tmrh20/RF24/
*/

/**
 * Transmitter
 * VCC --> 5V
 * GND --> GND
 * CE --> pin 7
 * CSN --> pin 8
 * SCK --> pin 13
 * M0 (MOSI) --> pin 11
 * m1 (MISO) --> pin 12
 */


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";
int potValue = 0;
bool kill = false; // For button -> shuts the motors
const int buttonPin = 2;

int buttonState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);

  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
}

void loop() {
  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    kill = true;
    Serial.write("SUICIDE\n");
  }
  potValue = analogRead(A0);   // reads the value of the potentiometer (value between 0 and 1023)
  potValue = map(potValue, 0, 1023, 0, 180);   // scale it to use it with the servo library (value between 0 and 180)
  if (kill) {
    potValue = 0;
  }
  radio.write(potValue, sizeof(potValue));
  delay(5);
}