//SA7 - Character creation on LCD screen

//Add relevant libraries
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); //Define 1602 LCD display

uint8_t character0[8] = {0x0,0x4,0xE,0x1F,0x4,0x4,0x4,0x0}; //up arrow character
uint8_t character1[8] = {0x0,0x4,0x4,0x4,0x1F,0xE,0x4,0x0}; //down arrow character
uint8_t character2[8] = {0x0,0x4,0x8,0x1F,0x1F,0x8,0x4,0x0}; //left arrow character
uint8_t character3[8] = {0x0,0x4,0x2,0x1F,0x1F,0x2,0x4,0x0}; //right arrow character
uint8_t character4[8] = {0x0,0xC,0x12,0x12,0xC,0x0,0x0,0x0}; //Character to show degree symbol
uint8_t character5[8] = {0x0,0x0,0xA,0x1F,0x1F,0xE,0x4,0x0}; //heart character

void setup() {
    lcd.begin(); //Start the LCD
    lcd.backlight(); //Turn ON LCD backlights
    lcd.createChar(0, character0); //Create up arrow and define it to address 0
    lcd.createChar(1, character1); //Create down arrow and define it to address 1
    lcd.createChar(2, character2); //Create left arrow and define it to address 2
    lcd.createChar(3, character3); //Create right arrow and define it to address 3
    lcd.createChar(4, character4); //Create degree character and define it to address 4
    lcd.createChar(5, character5); //Create heart character and define it to address 5
}

void loop() {
    lcd.setCursor(4,0); //Move cursor to row 0, column 4 on the LCD

    for(int i=0; i<=6; i++) { //With for loop
        lcd.print((char)i); //Print characters on the screen
    }
}
