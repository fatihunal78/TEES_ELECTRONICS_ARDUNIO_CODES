//SA6 - Sliding text on LCD screen

#include <LiquidCrystal_I2C.h> //Add I2C LCD library

LiquidCrystal_I2C lcd(0x27, 16, 2); //Define 1602 LCD display

int potValue; //Define the variable to store the value of the Potentiometer

void setup() {
    lcd.begin(); //Start the LCD
    lcd.backlight(); //Turn ON the LCD backlights
    lcd.clear(); //Clear LCD display
}

void loop() {
    potValue = analogRead(A0); //Read the value of the potentiometer connected to the analog A0 pin and write it to 
                              //the potValue variable

    potValue = map(potValue, 0, 1023, 50, 350); //Proportion the potValue between 0 and 1023 read from the analog pin 
                                                //to the value between 50 and 350. We will use these values in the 
                                                //delay function to change the scroll speed.
                                        
    lcd.setCursor(0, 0); //Move cursor to first line, first character 
    lcd.print("    Hello!    "); //Write Hello! to the first row
    lcd.setCursor(0, 1); //Second line, go to first character
    lcd.print("TEES ELECTRONICS"); //Write "TEES ELECTRONICS"

    delay(potValue); //Delay by potValue variable. A delay between 50 and 350 will be set according to the condition 
                     //of the Potentiometer

    lcd.scrollDisplayLeft(); //Scroll text to the left. To scroll to the right, you can use the 
                            //lcd.scrollDisplayRight(); command.
}
