//SA8 - Digital meter

#include <LiquidCrystal_I2C.h> //Add I2C LCD library
#define triggerPin 2 //Define the pin to which the HC-SR04 Trigger leg is connected
#define echoPin 3 //Define the pin to which the HC-SR04 Echo pin is connected
long time, distance; //Define time and distance variables

LiquidCrystal_I2C lcd(0x27, 16, 2); //Define 1602 LCD display

void setup() {
    pinMode(triggerPin, OUTPUT); //Set the pin to which the Trigger leg is connected as output 
    pinMode(echoPin, INPUT); //Set the pin to which the Echo leg is connected as input
    
    lcd.begin(); //Start the LCD
    lcd.backlight(); //Turn ON the LCD backlights
    
    lcd.clear(); //Clear LCD display
    lcd.setCursor(0, 0); //Go to the first line, first character on the LCD
    lcd.print("TEES ELECTRONICS"); //Write "TEES ELECTRONICS" on the LCD display
    lcd.setCursor(0, 1); //Go to the second line, first character on the LCD
    lcd.print("Digital Meter"); //Write on the LCD 
    delay(3000); //Wait for 3 seconds
    lcd.clear(); //Clear the LCD display
}

void loop() {
    digitalWrite(triggerPin, LOW); //Pull the Trigger leg to zero
    delayMicroseconds(2); //Wait for 2 microseconds 
    digitalWrite(triggerPin, HIGH); //Pull the Trigger leg to 5V
    delayMicroseconds(10); //Wait for 10 microseconds 
    digitalWrite(triggerPin, LOW); //Pull the Trigger leg to zero
    
    time = pulseIn(echoPin, HIGH); //Measure the return time of the audio waves from the Echo pin 
    distance = (time/2) * 0.034; //Calculate distance in cm by multiplying the measured time by the speed of sound
    
    lcd.setCursor(0, 0); //Go to the first line, first character on the LCD
    lcd.print("Distance:"); //Write to the LCD
    lcd.print(distance); //Write the measured distance on the LCD display
    lcd.print("cm"); //Write "cm" on the LCD 
    delay(300); //Wait for 300ms
    lcd.clear(); //Clear the LCD display
}
