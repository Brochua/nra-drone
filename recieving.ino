#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

Servo ESC;     // create servo object to control the ESC
Servo ESC2;     // create servo object to control the ESC
Servo ESC3;     // create servo object to control the ESC
Servo ESC4;     // create servo object to control the ESC
RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

int potValue;  // value from the analog pin

void setup() {
  // Reciever setup
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  // Attach the ESC on pin 9
  ESC.attach(3,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  ESC2.attach(4,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  ESC3.attach(5,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
  ESC4.attach(6,1000,2000); // (pin, min pulse width, max pulse width in microseconds) 
}

void loop() {
  if (radio.available()) {
    radio.read(&potValue, sizeof(potValue));

    ESC.write(potValue);    // Send the signal to the ESC
    ESC2.write(potValue);    // Send the signal to the ESC
    ESC3.write(potValue);    // Send the signal to the ESC
    ESC4.write(potValue);    // Send the signal to the ESC
  }  
}