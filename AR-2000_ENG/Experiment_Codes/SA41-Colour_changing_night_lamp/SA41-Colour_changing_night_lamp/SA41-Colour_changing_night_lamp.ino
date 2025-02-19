//SA41 - Colour changing night lamp

#include <LiquidCrystal_I2C.h> // Add I2C LCD library
#include <Keypad.h> // Add Keypad Library
#include <stdlib.h> // Library to use the itoa function required for the integer-to-character transformation

const byte ROW = 4; // Specify how many rows the keypad consists of
const byte COLUMN = 4; // Specify how many columns the keypad consists of

// Define the keys on the keypad
char keys[ROW][COLUMN] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Define the pins to which the row and column pins of the keypad are connected
byte rowPins[ROW] = {7, 6, 5, 4}; // Define the pins to which the row connections are connected on the Arduino
byte columnPins[COLUMN] = {3, 2, 1, 0}; // Define the pins to which column connections are connected on the Arduino

// Start the keypad
Keypad key_pad = Keypad(makeKeymap(keys), rowPins, columnPins, ROW, COLUMN);

LiquidCrystal_I2C lcd(0x27, 16, 2); // Define 1602 LCD display

// Define the pin numbers to which the LEDs are connected
int RGB_Red = 11;
int RGB_Green = 10;
int RGB_Blue = 9;

char red_char[4] = {}; // Define the character variable to keep the red colour
char green_char[4] = {}; // Define the character variable to keep the green colour
char blue_char[4] = {}; // Define the character variable to keep the blue colour

char pressedKey; // Define the variable to store the key pressed on the keypad
int i = 0, j = 0, z = 0; // For R, G, B values, the variables that will define the first, second and third values of the character will be recorded in the i, j, and z variables

int Red_Value; // Define variable to store Red value of RGB LED as an integer
int Green_Value; // Define variable to store Green value of RGB LED as an integer
int Blue_Value; // Define variable to store Blue value of RGB LED as an integer

void setup() {
  pinMode(RGB_Red, OUTPUT); // Set Red (R) connection of RGB LED as output
  pinMode(RGB_Green, OUTPUT); // Set Green (G) connection of RGB LED as output
  pinMode(RGB_Blue, OUTPUT); // Set Blue (B) connection of RGB LED as output

  /*
   * Since the RGB LED is a common anode, it will be turned OFF when you make it HIGH and turn ON when you make LOW.
   * Because the common anode, that is, the common supply CA connection, is connected to +5V and is constantly energized,
   * when we make any pin (R, G, or B) LOW, it will complete the circuit and the LED will turn ON.
   */
  digitalWrite(RGB_Red, HIGH); // Make the Red connection of the RGB LED HIGH, that is, turn it OFF
  digitalWrite(RGB_Green, HIGH); // Make the Green connection of the RGB LED HIGH, that is, turn it OFF
  digitalWrite(RGB_Blue, HIGH); // Make the Blue connection of the RGB LED HIGH, that is, turn it OFF

  lcd.begin(); // Start the LCD display
  lcd.backlight(); // Turn ON the LCD backlights
  lcd.clear(); // Clear the LCD display
  lcd.setCursor(0, 0); // Switch to the first row
  lcd.print("TEES ELECTRONICS"); // Write "TEES ELECTRONICS"
  lcd.setCursor(0, 1); // Switch to the lower row
  lcd.print("COLOUR CONTRAST"); // Write "COLOUR CONTRAST" on the LCD display
  delay(2000); // Wait for 2 seconds
  lcd.clear(); // Clear the LCD display
}

void loop() {
  lcd.print("Enter RGB Values"); // Write on the LCD display
  lcd.setCursor(0, 1); // Switch to the lower row
  lcd.print("Press # Key"); // Print on the LCD display
  delay(2000); // Wait for 2 seconds
  lcd.clear(); // Clear the LCD display
  lcd.print("R(red):");
  while (1) { // Enter infinite loop
    pressedKey = key_pad.getKey(); // Save the key pressed from the keypad to the pressedKey variable
    if (pressedKey) { // If the key is pressed
      if (pressedKey == '#') { i = 0; break; } // If # is pressed, set i to zero and exit the infinite loop with the break command
      if (i < 3) { // Ensure only three characters are recorded
        red_char[i] = pressedKey; // Save the pressed key to the red_char[i] variable
        lcd.setCursor(8 + i, 0); // Go to column 8+i on the first row of the LCD display
        lcd.print(red_char[i]); // Print the values entered from the keypad to the LCD display
        i++; // Increment i value by one
      }
      Red_Value = atoi(red_char); // Convert the red_char character to integer with the atoi function and save it to the Red_Value variable
      delay(200); // Add a small delay to debounce the keypad
    }
  }

  lcd.clear(); // Clear the LCD display
  lcd.print("G(Green):");
  while (1) { // Enter infinite loop
    pressedKey = key_pad.getKey(); // Save the key pressed from the keypad to the pressedKey character
    if (pressedKey) { // If the key is pressed
      if (pressedKey == '#') { j = 0; break; } // If # is pressed, set j to zero and exit the infinite loop with the break command
      if (j < 3) { // Ensure only three characters are recorded
        green_char[j] = pressedKey; // Save the key pressed in the variable green_char[j]
        lcd.setCursor(10 + j, 0); // Go to column 10+j on the first row of the LCD display
        lcd.print(green_char[j]); // Print the values entered from the keypad to the LCD display
        j++; // Increment j value by one
      }
      Green_Value = atoi(green_char); // Convert the green_char character to integer with the atoi function and save it to the Green_Value variable
      delay(200); // Add a small delay to debounce the keypad
    }
  }

  lcd.clear(); // Clear the LCD display
  lcd.print("B(Blue):");
  while (1) { // Enter infinite loop
    pressedKey = key_pad.getKey(); // Save the key pressed from the keypad to the pressedKey character
    if (pressedKey) { // If the key is pressed
      if (pressedKey == '#') { z = 0; break; } // If # is pressed, set z to zero and exit the infinite loop with the break command
      if (z < 3) { // Ensure only three characters are recorded
        blue_char[z] = pressedKey; // Save the key pressed in the variable blue_char[z]
        lcd.setCursor(9 + z, 0); // Go to column 9+z on the first row of the LCD display
        lcd.print(blue_char[z]); // Print the values entered from the keypad to the LCD display
        z++; // Increment z value by one
      }
      Blue_Value = atoi(blue_char); // Convert the blue_char character to integer with the atoi function and save it to the Blue_Value variable
      delay(200); // Add a small delay to debounce the keypad
    }
  }

  // After assigning values to pins R, G and B, perform the following operations
  lcd.clear(); // Clear the LCD display
  lcd.print("Setting Colour"); // Write "Setting Colour" to the LCD display
  lcd.setCursor(0, 1); // Switch to the lower row
  lcd.print("R:"); lcd.print(Red_Value); lcd.print(" G:"); lcd.print(Green_Value); lcd.print(" B:"); lcd.print(Blue_Value); // Write Red, Green and Blue values to the LCD display
  analogWrite(RGB_Red, 255 - Red_Value); // Write the value 255 - Red_Value to the RGB_Red pin
  analogWrite(RGB_Green, 255 - Green_Value); // Write the value 255 - Green_Value to the RGB_Green pin
  analogWrite(RGB_Blue, 255 - Blue_Value); // Write the value 255 - Blue_Value to the RGB_Blue pin

  delay(3000); // Wait for 3 seconds
  lcd.clear(); // Clear the LCD display
  lcd.setCursor(0, 0); // Switch to first row first column
}