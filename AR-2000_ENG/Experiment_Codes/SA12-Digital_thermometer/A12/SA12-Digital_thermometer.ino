//SA12 - Digital thermometer

#include <LiquidCrystal_I2C.h>    //Add I2C LCD library
#include <math.h>                  //Add math.h library for mathematical operations

LiquidCrystal_I2C lcd(0x27, 16, 2);   //Define 1602 LCD display

int NTCPin = A0;      //Define the analog pin number to which the NTC is connected
int analogValue;      //Define variable to store the NTC value
double temperature;   //Define the variable to store the temperature value

uint8_t character2[8] = {0xC, 0x12, 0x12, 0xC, 0x0, 0x0, 0x0, 0x0};    //Character to show degree symbol 

void setup() {  
    lcd.begin();          //Start the LCD
    lcd.backlight();      //Turn ON the LCD backlights
    lcd.clear();          //Clear LCD display

    lcd.createChar(2, character2);    //Define character to print degree symbol
  
    lcd.setCursor(0, 0);              //Go to the first line, first character on the LCD display 
    lcd.print("TEES ELECTRONICS");     //Write "TEES ELECTRONICS" on the LCD display
    lcd.setCursor(0, 1);              //Go to the second line, first character on the LCD display
    lcd.print("   THERMOMETER");       //Write THERMOMETER 
    delay(2000);                      //Wait for 2 seconds 
    lcd.clear();                      //Clear the LCD display 
}

void loop() {
    analogValue = analogRead(NTCPin);             //Read NTC value and save to analogValue variable 
    temperature = NTCCalculate(analogValue);       //Calculate temperature value with NTCCalculate function and store it
    lcd.setCursor(4, 0);                          //Go to the first line, fourth character on the LCD display 
    lcd.print("Temperature");                      //Print "Temperature" on the LCD display
    lcd.setCursor(4, 1);                          //Go to the second line, first character
    lcd.print(temperature);                       //Write the temperature value on the LCD display 
    lcd.print(char(2));                          //Write the degree symbol
    lcd.print("C");                              //Type C for Centigrade symbol
    delay(500);                                  //Wait for 500ms
    lcd.clear();                                //Clear the LCD display 
}

//Define NTCCalculate function
double NTCCalculate(int analogRead) {
    //Calculate temperature value according to NTC specifications
    temperature = log(((10240000 / analogRead) - 10000));
    temperature = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temperature * temperature)) * temperature);
    temperature = temperature - 273.15;
    //Send the calculated temperature value to the line where the function is called
    return temperature;
}
