#include <Arduino.h>
#include "PinDefinitionsAndMore.h" // Part of the IRremote library
#include <IRremote.hpp>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define  SCREEN_WIDTH 128
#define  SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);




int pos = 0;

void setup() {
    display.begin(SSD1306_SWITCHCAPVCC, 0x3c);
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(10, 10);
    display.println("car starting");
    display.display();
    delay(5000);
    display.println("car has started");
     


    Serial.begin(115200);
    // Start the receiver
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    pinMode(PIN_D3, OUTPUT);
    pinMode(PIN_D4, OUTPUT);
    pinMode(PIN_D5, OUTPUT);
    pinMode(PIN_D6, OUTPUT);

    digitalWrite(PIN_D3, LOW);
    digitalWrite(PIN_D4, LOW);
    digitalWrite(PIN_D5, LOW);
    digitalWrite(PIN_D6, LOW);
}

void stop(){
  digitalWrite(PIN_D3, LOW);
  digitalWrite(PIN_D4, LOW);
  digitalWrite(PIN_D5, LOW);
  digitalWrite(PIN_D6, LOW);

}
  
 


void driveMotor(int order)
{
  /*
    1 = Forward
    2 = Right
    3 = Backward
    4 = Left
  */

  digitalWrite(PIN_D3, LOW);
  digitalWrite(PIN_D4, LOW);
  digitalWrite(PIN_D5, LOW);
  digitalWrite(PIN_D6, LOW);

  switch (order)
  {
    case 1:
      digitalWrite(PIN_D3, HIGH);
      digitalWrite(PIN_D6, HIGH);
      delay(300);
      stop();
      break;
    case 2:
      digitalWrite(PIN_D4, HIGH);
      digitalWrite(PIN_D5, HIGH);
      delay(300);
      stop();
      break;
    case 3:
      digitalWrite(PIN_D3, HIGH);
      digitalWrite(PIN_D5, HIGH);
      delay(300);
      stop();
      break;
    case 4:
      digitalWrite(PIN_D4, HIGH);
      digitalWrite(PIN_D6, HIGH);
      delay(300);
      stop();
      break;
    case 5: 
      stop();
      break;
    default:
      break;
  }
}

void loop() {
    if (IrReceiver.decode()) {
        
        uint16_t command = IrReceiver.decodedIRData.command;

       
        switch (command)
        {
          case 0x18:
            driveMotor(1);
            display.println("forword");
            break;
          case 0x52:
            driveMotor(2);
            display.println("backword");
            break;
          case 0x8:
            driveMotor(3);
            display.println("left");
            break;
          case 0x5a:
            driveMotor(4); 
            display.println("right"); 
            break;
          case 0x1c:
            driveMotor(5);
            display.println("stop");
            break;
          default:
            driveMotor(50);
            break;

        }      
      



        // Print the full raw data
        //IrReceiver.printIRResultShort(&Serial); 
        
        IrReceiver.resume(); // Enable receiving of the next value
    }
}