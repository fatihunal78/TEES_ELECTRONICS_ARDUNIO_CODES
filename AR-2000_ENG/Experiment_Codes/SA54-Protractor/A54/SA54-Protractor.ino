// SA54 - Protractor

#include <Servo.h>              // Add servo library
#include <LiquidCrystal_I2C.h>  // Add I2C LCD library

LiquidCrystal_I2C lcd(0x27, 16, 2); // Define 1602 LCD display

Servo servo; // Create a Servo object named servo

int xPin = A2;          // Define the pin number to which the Joystick X axis is connected
int xPosition = 0;      // Define the variable to store the joystick X axis position
int servoAngle;         // Define the variable to store the angle value of the servo motor

uint8_t character2[8] = { 0x0C, 0x12, 0x12, 0x0C, 0x00, 0x00, 0x00, 0x00 }; // Degree symbol

void setup() {
  servo.attach(2);      // Set the pin to which the servo motor is connected
  servo.write(0);       // Move servo motor to 0-degree position

  lcd.begin();          // Start the LCD display
  lcd.backlight();      // Turn ON the LCD backlights
  lcd.clear();          // Clear the LCD display
  lcd.createChar(2, character2); // Create degree symbol
  
  // Print "TEES ELECTRONICS Protractor" to the LCD display
  lcd.setCursor(0, 0);  // Switch to the first row
  lcd.print("TEES ELECTRONICS"); // Write "TEES ELECTRONICS"
  lcd.setCursor(0, 1);  // Switch to the lower row
  lcd.print("Protractor"); // Write "Protractor"
  delay(2000);          // Wait for 2 seconds
  lcd.clear();          // Clear the LCD display
}

void loop() {
  xPosition = analogRead(xPin); // Read the position of the joystick X axis and save it to the xPosition variable

  servoAngle = map(xPosition, 1023, 0, 180, 0); // Proportion xPosition value to servo motor angle

  servo.write(180 - servoAngle); // Adjust the angle of the servo motor according to the servoAngle variable

  // Display angle value on the LCD
  lcd.print("Angle Value: "); // Write "Angle Value:" to the LCD display
  lcd.print(servoAngle);      // Print servo motor angle
  lcd.write(byte(2));         // Print degree symbol
  delay(100);                 // Wait for 100ms
  lcd.clear();                // Clear the LCD display
}