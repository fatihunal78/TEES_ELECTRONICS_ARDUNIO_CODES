// SA53 - Fruit automation

#include <LiquidCrystal_I2C.h> // Add I2C LCD library
#include <Servo.h>             // Add the servo motor library

LiquidCrystal_I2C lcd(0x27, 16, 2); // Define 1602 LCD display
Servo servo;                        // Define the servo motor

int buttonPin = 2;  // Define the pin number to which the Button is connected
int red_LED = 5;    // Define the pin to which the RGB Red LED is connected
int green_LED = 6;  // Define the pin to which the RGB Green LED is connected
int blue_LED = 8;   // Define the pin to which the RGB Blue LED is connected
int servoPin = 3;   // Define the pin number to which the servo motor is connected
int LDR_pin = A0;   // Define the pin number to which the LDR is connected

// Define the variables to keep the colour values read
int red_read;
int green_read;
int blue_read;

void setup() {
  pinMode(red_LED, OUTPUT);       // Set the pin to which the Red LED is connected as output
  pinMode(green_LED, OUTPUT);     // Set the pin to which the Green LED is connected as output
  pinMode(blue_LED, OUTPUT);      // Set the pin to which the Blue LED is connected as output
  pinMode(buttonPin, INPUT_PULLUP); // Set the pin to which the Button is connected as input

  servo.attach(servoPin);         // Set the pin to which the servo motor is connected

  lcd.begin();      // Start the LCD display
  lcd.backlight();  // Turn ON the LCD backlights
  lcd.clear();      // Clear the LCD display

  lcd.setCursor(0, 0); // Switch to the first row
  lcd.print("TEES ELECTRONICS"); // Write "TEES ELECTRONICS" on the first row
  lcd.setCursor(0, 1); // Switch to the second row
  lcd.print("COLOUR DETECTION"); // Write "COLOUR DETECTION" to the LCD display
  delay(2000); // Wait for 2 seconds

  servo.write(90); // Initialize servo motor to 90-degree position
}

void loop() {
  if (digitalRead(buttonPin) == LOW) { // If the button is pressed, start colour detection
    lcd.clear(); // Clear the LCD display

    // To read the red value
    // Enter 100 PWM in the Red LED with the analogWrite command and turn OFF the other LEDs
    analogWrite(red_LED, 100);
    digitalWrite(green_LED, HIGH);
    digitalWrite(blue_LED, HIGH);
    delay(50); // Wait for 50ms
    red_read = analogRead(LDR_pin); // Read the red value and save it to the red_read variable
    delay(50);

    // Turn ON the Blue LED to turn OFF the others to read blue
    digitalWrite(red_LED, HIGH);
    digitalWrite(green_LED, HIGH);
    digitalWrite(blue_LED, LOW);
    delay(50);
    blue_read = analogRead(LDR_pin); // Read the blue value and save it to blue_read variable
    delay(50);

    // Turn ON the green LED to 100 PWM with the analogWrite command to read green, turn OFF the other LEDs
    digitalWrite(red_LED, HIGH);
    analogWrite(green_LED, 100);
    digitalWrite(blue_LED, HIGH);
    delay(50);
    green_read = analogRead(LDR_pin); // Read green value and save it to green_read variable
    delay(50);

    // Turn OFF the RGB LED
    digitalWrite(red_LED, HIGH);
    digitalWrite(green_LED, HIGH);
    digitalWrite(blue_LED, HIGH);

    // Determine the perceived colour based on the highest value
    if (red_read > green_read && red_read > blue_read) { // If red is the highest
      lcd.print("RED COLOUR"); // Print "RED COLOUR" on the LCD display
      servo.write(30);         // Set servo to 30 degrees to show red colour
    } else if (green_read > red_read && green_read > blue_read) { // If green is the highest
      lcd.print("GREEN COLOUR"); // Print "GREEN COLOUR" on the LCD display
      servo.write(90);           // Move servo to 90 degrees to show green colour
    } else if (blue_read > red_read && blue_read > green_read) { // If blue is the highest
      lcd.print("BLUE COLOUR"); // Print "BLUE COLOUR" on the LCD display
      servo.write(150);         // Set servo to 150 degrees to show blue colour
    }
  }
}