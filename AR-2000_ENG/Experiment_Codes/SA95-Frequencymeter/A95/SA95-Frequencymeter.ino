//SA95 - Frequencymeter

#include <FreqCount.h>         //Add library required to measure frequency 
#include <LiquidCrystal_I2C.h> //Add I2C LCD library
LiquidCrystal_I2C lcd(0x27, 16, 2);  //Define 1602 LCD display

double frequency;

void setup() {
    lcd.begin();              //Start the LCD display
    lcd.backlight();          //Turn ON the LCD backlights
    lcd.clear();              //Clear the LCD display
    FreqCount.begin(1000);    //Start the frequency measurement

    lcd.setCursor(0, 0);      //Switch to the first row on the LCD display
    lcd.print("TEES ELECTRONICS");  //Write "TEES ELECTRONICS" on the LCD display
    lcd.setCursor(0, 1);      //Switch to the lower row 
    lcd.print("FREQUENCY METER");   //Print "FREQUENCY METER" on the LCD display
    delay(2000);              //Wait for 2 seconds
    lcd.clear();              //Clear the LCD display 
}

void loop() {
    if(FreqCount.available()) {  //If the system is working and the values are coming in the frequency measurement
        frequency = FreqCount.read();  //Assign the measured value to the frequency variable
        float period = (1 / frequency);  //It is calculated with period = 1/frequency formula. Period is the time elapsed 
                                        //between two frequencies. We find the period value for the frequency value we 
                                        //obtain with the 1/frequency formula.

        lcd.setCursor(4, 0);     //Go to column 4 on the first row on the LCD display
        lcd.print("Frequency");   //Print "Frequency" on the first row of the LCD display
        lcd.setCursor(0, 1);      //Switch to 2nd row on the LCD display
        lcd.print("      ");
        lcd.print(frequency);     //Write the measured frequency value on the LCD display
        lcd.print(" Hz          "); //Write "Hz"
        
        if(frequency >= 1000) {   //If the frequency value is greater than 1000
            lcd.setCursor(4, 0);   //Go to column 4 on the first row on the LCD display
            lcd.print("Frequency"); //Print "Frequency" on the first row of the LCD display
            lcd.setCursor(4, 1);   //Go to column 4 on the second row on the LCD display
            lcd.print(frequency / 1000);  //Divide the measured frequency value by 1000 and write it on the LCD display
            lcd.print(" KHz         "); //Write KHz
        }
        
        if(frequency >= 1000000) { //If the frequency value is greater than 1000000
            lcd.setCursor(4, 0);    //Go to column 4 on the first row on the LCD display
            lcd.print("Frequency");  //Print "Frequency" on the first row of the LCD display
            lcd.setCursor(4, 1);    //Go to column 4 on the second row on the LCD display
            lcd.print(frequency / 1000000); //Divide the measured frequency value by 1000000 and write it on LCD display
            lcd.print(" MHz         "); //Write MHz
        }
    }
}
