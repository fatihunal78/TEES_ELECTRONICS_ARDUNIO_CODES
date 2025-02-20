//SA73 - HEX equivalents of TV remote control keys

#include <IRremote.h>                    //Add IR receiver library
#include <LiquidCrystal_I2C.h>          //Add I2C LCD library

int IRPin = 2;                          //Define the pin to which the IR receiver signal leg is connected
int buzzerPin = 5;                      //Define the pin number to which the buzzer is connected
LiquidCrystal_I2C lcd(0x27, 16, 2);    //Define 1602 LCD display

IRrecv IRReceive(IRPin);               //Define an IR Receiver named IRReceive
decode_results result;                  //Define variable to store values received from IR receiver

void setup() {
    pinMode(buzzerPin, OUTPUT);         //Set the pin to which the Buzzer is connected as output
    lcd.begin();                        //Start the LCD display
    lcd.backlight();                    //Turn ON the LCD backlights
    lcd.clear();                        //Clear the LCD display

    IRReceive.enableIRIn();            //Start IR receiver

    lcd.setCursor(0, 0);
    lcd.print("LEARNING TV");
    lcd.setCursor(0, 1);
    lcd.print("REMOTE CONTROL KEYS");
    delay(3000);
    lcd.clear();
}

void loop() {
    //Check if there is any information coming from IR receiver
    if(IRReceive.decode(&result)) {     //If data has arrived
        if(result.value != 0) {         //If any key of the remote control is pressed
            digitalWrite(buzzerPin, HIGH);  //Make a sound from the Buzzer
            delay(50);                     //Wait for 50ms
            digitalWrite(buzzerPin, LOW);   //Mute the Buzzer
        }
        
        lcd.clear();
        lcd.print("0x");
        lcd.print(result.value, HEX);   //Print incoming data on the LCD display in HEX format
        delay(500);                     //Wait for 500ms
        IRReceive.resume();             //Reset IR receiver to get other values
    }
}
