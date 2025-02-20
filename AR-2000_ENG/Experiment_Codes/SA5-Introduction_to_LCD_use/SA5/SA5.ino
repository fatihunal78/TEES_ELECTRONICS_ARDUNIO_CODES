//SA5 - Introduction to LCD use

#include <LiquidCrystal_I2C.h> //Add I2C LCD library

LiquidCrystal_I2C lcd(0x27, 16, 2); //Define 1602 screen
                                    //Here 0x27 specifies LCD address. It's written on the back of the board. It may be 
                                    //different on some boards.
                                    //16 Indicates the maximum number of characters in a row on the LCD
                                    //2 indicates the maximum number of characters in a column.

void setup() {
    lcd.begin();      //Start the LCD
    lcd.backlight();  //Turn ON the LCD backlights
    lcd.clear();      //Clear LCD display
}

void loop() {
    lcd.setCursor(0, 0);
    lcd.print("TEES ELECTRONICS");
    lcd.setCursor(0, 1);
    lcd.print("  CODING SET  ");
}
