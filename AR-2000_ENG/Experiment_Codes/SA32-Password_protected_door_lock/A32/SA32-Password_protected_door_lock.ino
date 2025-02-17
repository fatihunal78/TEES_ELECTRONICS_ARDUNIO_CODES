//SA32 - Password protected door lock

#include <Servo.h>               // Add servo library
#include <LiquidCrystal_I2C.h>   // Add I2C LCD library
#include <Keypad.h>              // Add Keypad Library

// Define how many rows and columns are on the keypad we use
// The keypad on the panel is 4x4, that is, there are 4 rows and 4 columns
const byte ROW = 4; 
const byte COLUMN = 4;

// We specified the location and order of the keys in the row and column
char keys[ROW][COLUMN] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Define the pins to which the row and column pins of the keypad are connected
byte rowPins[ROW] = {7, 6, 5, 4};       // Define the pins to which the row connections are connected on the Arduino
byte columnPins[COLUMN] = {3, 2, 1, 0}; // Define the pins to which column connections are connected on the Arduino

Keypad keyPad = Keypad(makeKeymap(keys), rowPins, columnPins, ROW, COLUMN); // Start the keypad

LiquidCrystal_I2C lcd(0x27, 16, 2); // Define 1602 LCD display
                  
Servo servo; // We created a Servo object named servo 

/* string is a type of variable that stores multiple characters in the memory. String
   Features such as string splitting, merging, finding/deleting/changing the desired letter are used frequently. */

String enteredPassword = ""; // Define the variable to store the entered password
String password = "1234";    // Define the variable that will store the current door password
int servo_position;          // Define the variable that will store the servo angular value
int servoPin = 11;           // Define the pin number to which the servo motor is connected

void setup() {  
  servo.attach(servoPin);   // Set the pin to which the servo motor is connected
  servo.write(0);           // Set servo start position to zero (0) degree
  
  lcd.begin();              // Start the LCD display
  lcd.backlight();          // Turn ON the LCD backlights
  lcd.clear();              // Clear the LCD display
  lcd.setCursor(0, 0);      // Switch to the first row 
  lcd.print("TEES ELECTRONICS"); // Write "TEES ELECTRONICS" 
  lcd.setCursor(0, 1);      // Switch to the lower row
  lcd.print("Password Protected Lock"); 
  delay(2000);              // Wait for 2 seconds
  lcd.clear();              // Clear the LCD display
  
  lcd.print("Enter Password and"); // Write "Enter Password and" on the LCD display
  lcd.setCursor(0, 1);      // Switch to the lower row
  lcd.print("Press # Key"); // Write "Press # Key" on the LCD display
  delay(3000);              // Wait for 3 seconds
  lcd.clear();              // Clear the LCD display
  lcd.print("Password:");
}

void loop() {   
  char key = keyPad.getKey(); // Save the key pressed from the keypad
  if (key != NO_KEY) { // If any key is pressed 
    switch (key) { // With switch case structure, perform the action on the key that is pressed 
      case '#':
        lcd.setCursor(0, 0); 
        if (enteredPassword == password) { // If the password entered is the same as the door password
          for (servo_position = 0; servo_position <= 90; servo_position++) { // Increment servo angle one by one from 0 to 90
            servo.write(servo_position); // Write servo_position variable to servo
            delay(30); // Wait for 30ms
          }
          // Write "Door is Open Close It with * Key" on the LCD display 
          lcd.print("Door is Open ");
          lcd.setCursor(0, 1);
          lcd.print("Close it with * Key");
        } else { // If the password entered is not the same as the door password
          lcd.print("Invalid Password"); // Print "Invalid Password" on the LCD display
        }
        enteredPassword = ""; // Reset the password entered
        break; // End the case #
      
      case '*': // If the star key is pressed
        lcd.clear(); // Clear LCD display
        enteredPassword = ""; // Reset the password entered 
        if (servo_position == 0) { // If the servo motor is in 0 degree position
          servo.write(0); // Keep the servo motor at 0 degree position
        } else { // If the servo motor is at 90-degree position 
          for (servo_position = 90; servo_position > 0; servo_position--) { // Move the servo motor to 0-degree position
            servo.write(servo_position); 
            delay(30); 
          }
        }
        lcd.print("Door is Locked!"); // Write "Door is Locked!" on the LCD display
        lcd.setCursor(0, 1); // Switch to the lower row 
        lcd.print("Enter Password"); // Write "Enter Password" on the LCD display
        break; // End the case *
      
      default: // If there is no case
        lcd.clear(); // Clear the LCD display 
        lcd.print("Password:"); // Write "Password" on the LCD display
        enteredPassword += key; // Write the entered password side by side
        for (int i = 0; i < enteredPassword.length(); i++) { // Write the password entered on the LCD display using for loop
          lcd.setCursor(9 + i, 0);
          lcd.print(enteredPassword[i]); // Show the password entered on the LCD display 
        }              
        break;
    }
  }
}