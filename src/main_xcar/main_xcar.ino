#include <Arduino.h>
#include "PinDefinitionsAndMore.h" // Part of the IRremote library
#include <IRremote.hpp>



void setup() {

    Serial.begin(115200);
    // Start the receiver
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(6,OUTPUT);
}

void loop() {
    if (IrReceiver.decode()) {
        
        uint16_t command = IrReceiver.decodedIRData.command;

        switch (command)
        {
          case 0x18:
            Serial.print("UP");
            break;
          case 0x52:
            Serial.print("DOWN");
            break;
          case 
        }

        

        // Print the full raw data
        //IrReceiver.printIRResultShort(&Serial); 
        
        IrReceiver.resume(); // Enable receiving of the next value
    }
}