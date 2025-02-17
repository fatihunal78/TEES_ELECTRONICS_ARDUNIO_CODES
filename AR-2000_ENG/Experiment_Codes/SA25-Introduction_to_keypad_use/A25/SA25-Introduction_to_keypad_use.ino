//SA25 - Introduction to keypad use.ino

#include <LiquidCrystal_I2C.h> //Add I2C LCD library
#include <Keypad.h> //Add Keypad library

//We need to specify how many rows and columns there are on the keypad we use. 
//The keypad on the panel is 4x4, that is, there are 4 rows and 4 columns
const byte ROW = 4; 
const byte COLUMN = 4;

//We specified the location and order of the keys in the row and column.
char keys[ROW][COLUMN] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//We specified which pins the row and column pins are connected to on the Arduino board.
//Let's make our connection in order from left to right 
//The first four connections of the keypad are the connections of the ROWS
//The last four connections are the connection of the COLUMNS
//Define the connection in Arduino here
byte rowPins[ROW] = {7, 6, 5, 4}; //Define the pins to which the row connections are connected on the Arduino 
byte columnPins[COLUMN] = {3, 2, 1, 0}; //Define the pins to which column connections are connected on the Arduino

Keypad keyPad = Keypad(makeKeymap(keys), rowPins, columnPins, ROW, COLUMN); //Define Keypad for the keypad
LiquidCrystal_I2C lcd(0x27, 16, 2); //Define 1602 LCD display

void setup() {
  lcd.begin(); //Start the LCD display
  lcd.backlight(); //Turn ON the LCD backlights
  
  lcd.clear(); //Clear the LCD display
  lcd.setCursor(0, 0); //Switch to the first row 
  lcd.print("TEES ELECTRONICS"); //Write "TEES ELECTRONICS"
  lcd.setCursor(3, 1); //Switch to column 3 in the second line
  lcd.print("KEYPAD PANEL");     
  delay(1000); //Wait for 1 second 
  lcd.clear(); //Clear the LCD display 
  lcd.print("Press Any Key");
}

void loop() {
  char pressedKey = keyPad.getKey(); //Save the key pressed from the keypad to the pressedKey character.
  if (pressedKey) { //If any key is pressed
    lcd.clear(); //Clear the LCD display 
    lcd.setCursor(0, 0); //Switch to the first row 
    lcd.print("   Keypad Panel");
    lcd.setCursor(7, 1);
    lcd.print(pressedKey); //Print the key pressed from the Keypad.
  }
}