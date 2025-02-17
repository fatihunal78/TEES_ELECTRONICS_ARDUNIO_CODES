//SA13 - Let's learn IR remote control keys

#include <IRremote.h>          //Add IR receiver library
#include <LiquidCrystal_I2C.h> //Add I2C LCD library

int IRPin = 2;                 //Define the pin to which the IR receiver signal leg is connected

LiquidCrystal_I2C lcd(0x27, 16, 2); //Define 1602 LCD display

IRrecv IRReceive(IRPin);       //Define an IR Receiver named IRReceive
decode_results result;         //Define variable to store values from IR receiver

void setup() {
    lcd.begin();              //Start the LCD display
    lcd.backlight();          //Turn ON LCD backlights
    lcd.clear();              //Clear the LCD display 
    
    IRReceive.enableIRIn();   //Start IR receiver

    //Write "TEES ELECTRONICS" on the first row of the LCD display and "IR CONTROL" on the second 
    //line.
    lcd.setCursor(0, 0);
    lcd.print("TEES ELECTRONICS");
    lcd.setCursor(0, 1);
    lcd.print("  IR CONTROL  ");
    delay(3000);
    lcd.clear();
}

void loop() {
    //Check if there is any information coming from IR receiver
    if(IRReceive.decode(&result)) { //If data has arrived from the IR receiver
        lcd.clear();
        lcd.print("0x");
        lcd.print(result.value, HEX); //Print incoming data on the LCD display in HEX format
        delay(500);                   //Wait for 500ms
        IRReceive.resume();           //Reset IR receiver to get other values
    }
}
