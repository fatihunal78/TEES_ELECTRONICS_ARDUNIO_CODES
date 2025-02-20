//SA84 - Dynamo

#include <LiquidCrystal_I2C.h>                    //Add I2C LCD display library

LiquidCrystal_I2C lcd(0x27, 16, 2);              //Define 1602 LCD display

int dynamoPin = A0;                               //Define the pin number to read the energy generated in the motor
double voltageValue;                              //Define the variable to keep the voltage value read from the dynamo

void setup() {
    pinMode(dynamoPin, INPUT);                    //Set DynamoPin as input pin
    
    lcd.backlight();                             //Turn ON LCD backlights
    lcd.begin();                                 //Start the LCD display

    lcd.setCursor(0, 0);                         //Switch to the first row on the LCD display
    lcd.print("TEES ELECTRONICS");               //Write "TEES ELECTRONICS" on the LCD display
    lcd.setCursor(0, 1);                         //Switch to the lower row
    lcd.print("     DYNAMO     ");               //Print "DYNAMO" on the screen
    delay(2000);                                 //Wait for 2 seconds
    lcd.clear();                                 //Clear the LCD display
}

void loop() {
    voltageValue = analogRead(dynamoPin) * 5/1023.0;    //Read the value from DynamoPin(A0) and multiply by 5 and divide by 1023 
                                                        //to save the voltage equivalent of it to the voltageValue variable

    lcd.setCursor(0, 0);                         //Switch to the first row on the LCD display
    lcd.print("Voltage: ");                      //Print "Voltage:" on the screen
    lcd.print(voltageValue);                     //Print the voltageValue value
    lcd.print(" V");
}
