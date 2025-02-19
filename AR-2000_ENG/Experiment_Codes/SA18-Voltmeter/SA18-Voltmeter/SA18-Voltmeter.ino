//SA18 - Voltmeter
#include <LiquidCrystal_I2C.h> //Add I2C LCD library

LiquidCrystal_I2C lcd(0x27, 16, 2); //Define 1602 LCD display

int ADCPin = 0; //Define the pin to be measured
float Vout = 0.0; //Define the variable to store the measured calculated voltage
float Voltage = 0.0; //Define the variable to store the actual measured value
float R1 = 100000.0; //The value of the resistor connected to the + end of the probe is 100K
float R2 = 10000.0; //The value of the resistor connected to the probe-end is 10K
int readValue = 0; //Define the variable to store the measurement result

void setup() {
    lcd.begin(); //Start the LCD display
    lcd.backlight(); //Turn ON LCD backlights
    pinMode(ADCPin, INPUT); //Define ADC pin as input
    
    lcd.clear(); //Clear the LCD display
    lcd.setCursor(0, 0); //Go to the first row, first character on the LCD display
    lcd.print("TEES ELECTRONICS"); //Write "TEES ELECTRONICS" on the LCD
    lcd.setCursor(2, 1); //Select LCD lower row third character
    lcd.print("VOLTMETER"); //Write VOLTMETER to the LCD display
    delay(3000); //Wait for 3 seconds
    lcd.clear(); //Clear the LCD display
}

void loop() {
    readValue = analogRead(ADCPin); //Read the value on ADCPin and save it to the readValue variable.
    //Multiply the variable readValue by 5 and divide by 1024 to find the voltage equivalent of the measured 
    //value
    Vout = (readValue * 5.0) / 1024.0; 
    //Find the Voltage value you want to measure by proportioning the voltages on the resistors with the 
    //voltages corresponding to the voltage.
    Voltage = Vout / (R2 / (R1+R2));
    
    if(Voltage < 0.09) { //If the Voltage value is less than 0.09
        Voltage = 0.0; //Set the Voltage value to zero.
    }
    lcd.setCursor(0, 1); //Switch to 2nd line on the LCD display
    lcd.print("VOLTAGE:"); //Write VOLTAGE on the LCD display
    lcd.print(Voltage); //Write the calculated Voltage value on the LCD display
    lcd.print("V"); //Write "V" on the LCD display
    delay(500); //Wait for 500ms
}
