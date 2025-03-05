//SA10 - LCD direction indicator

#include <LiquidCrystal_I2C.h> //Add I2C LCD library

int xPin = A0;      //Define the pin number to which the Joystick X axis is connected
int yPin = A1;      //Define the pin number to which the Joystick Y axis is connected
int buttonPin = 2;  //Define the pin number to which the Joystick button is connected

int xPosition = 0;    //Define the variable that will store the position of the Joystick X axis
int yPosition = 0;    //Define the variable that will store the position of the Joystick Y axis
int buttonStatus = 0; //Define the variable to store the Joystick button state

LiquidCrystal_I2C lcd(0x27, 16, 2); //Define 1602 LCD display

//Define direction characters for LCD
byte middleupper[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0E, 0x15};  //Define middle upper character
byte middlelower[8] = {0x15, 0x0E, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00};  //Define middle lower character

void setup() {
    pinMode(xPin, INPUT);      //Set the pin to which the Joystick X axis is connected as input 
    pinMode(yPin, INPUT);      //Set the pin to which the Joystick Y axis is connected as input 
    pinMode(buttonPin, INPUT); //Set the pin to which the Joyistick button is connected as input 
    
    digitalWrite(buttonPin, OUTPUT); //Set the pin to which the joystick button is connected as pullup
  
    lcd.begin();      //Start the LCD 
    lcd.backlight();  //Turn ON LCD backlights
    //Define added characters
    lcd.createChar(2, middleupper);
    lcd.createChar(3, middlelower);
    lcd.clear();      //Clear LCD display
    lcd.setCursor(0, 0);  //Go to the first line, first character on the LCD
    lcd.print("TEES Electronics"); //Write "TEES Electronics" on the LCD display
    lcd.setCursor(1,1);   //Select LCD lower line second character
    lcd.print("Direction Sign"); //Write on the LCD display
    delay(3000);          //Wait for 3 seconds
    lcd.clear();          //Clear the LCD display
}
 
void loop() {
    // Read the position of the Joystick X axis and save it to the xPosition variable
    xPosition = analogRead(xPin);
    // Read the position of the Joystick Y axis and save it to the yPosition variable
    yPosition = analogRead(yPin);
    // Read the status of the Joystick button and save it to the buttonStatus variable
    buttonStatus = digitalRead(buttonPin);

    if(xPosition > 900 && yPosition > 120) {  // If the direction is right, type Right on the LCD display and show -->
        lcd.setCursor(0, 0);
        lcd.print("Right  ");
        lcd.setCursor(12, 0);
        lcd.print(" ");
        lcd.setCursor(11, 1);
        lcd.print("-->");
    }
    else if(xPosition < 120 && yPosition > 120) {  // If the direction is left, type Left on the LCD display and show <--
        lcd.setCursor(0, 0);
        lcd.print("Left   ");
        lcd.setCursor(12, 0);
        lcd.print(" ");
        lcd.setCursor(11, 1);
        lcd.print("<--");
    }
    else if(xPosition > 120 && yPosition < 120) {  // If the direction is forward, type Forward on the LCD display 
        lcd.setCursor(0, 0);
        lcd.print("Forward");
        lcd.setCursor(12, 0);
        lcd.write(byte(2));
        lcd.setCursor(11, 1);
        lcd.print(" | ");
    }
    else if(xPosition > 120 && yPosition > 900) {  // If direction is backward, write Back on the LCD display 
        lcd.setCursor(0, 0);
        lcd.print("Back   ");
        lcd.setCursor(12, 0);
        lcd.print("|");
        lcd.setCursor(11, 1);
        lcd.print(" ");
        lcd.write(byte(3));
        lcd.print(" ");
    }
    else {
        if(buttonStatus == LOW) {                 // If the button is pressed, type "Button Pressed" on the LCD display
            lcd.setCursor(0, 1);
            lcd.print("Button Pressed  ");
        }
        else {                                   // If the Button is not pressed and the Joystick is in the middle
            lcd.setCursor(0, 0);
            lcd.print("Middle ");
            lcd.setCursor(12, 0);
            lcd.print(" ");
            lcd.setCursor(0, 1);
            lcd.print("           <->");
        }
    }
    delay(100);                                  // Wait for 100ms
}
