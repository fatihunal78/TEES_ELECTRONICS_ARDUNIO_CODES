//SA37 - Patrol camera

#include <Servo.h> // Add servo library 

int buttonPin = 2; // Define the pin number to which the Joystick button is connected
int joystick_y = A5; // Define the analog pin number to which the y-axis of the joystick is connected
int servoPin = 3; // Define the pin number to which the servo motor is connected
int buttonStatus = 0; // Define the variable to store the button state

int y_axis; // Define the variable to store the values on the joystick y-axis
Servo servo; // Create an object named servo for servo motor control

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Set the pin to which the Button is connected as input
  servo.attach(servoPin); // Set the pin to which the servo motor is connected
  servo.write(90); // Initially set servo motor to 90-degree position
}

void loop() {
  if (buttonStatus == 0) { // If the buttonStatus variable is 0
    while (1) { // Enter infinite loop
      if (digitalRead(buttonPin) == LOW) { // If the button is pressed
        buttonStatus = 1; // Set the buttonStatus variable to 1
        break; // End infinite loop 
      }
      y_axis = analogRead(joystick_y); // Read value in analog pin based on joystick position
      int proportion = map(y_axis, 0, 1023, 145, 25); // Proportion the value between 0 and 1023 to between 25 and 145 degrees

      servo.write(proportion); // Transfer the proportional angular value to the servo motor.
    }
  } else if (buttonStatus == 1) { // If the buttonStatus variable is 1
    while (1) { // Enter infinite loop 
      if (digitalRead(buttonPin) == LOW || buttonStatus == 0) { // If the button is pressed or the buttonStatus variable is 0
        buttonStatus = 0; // Set the buttonStatus variable to 0
        break; // End infinite loop 
      }
      for (int i = 25; i <= 145; i++) { // For the servo motor to scan between 25 and 145 degrees
        if (digitalRead(buttonPin) == LOW) { // If the button is pressed
          buttonStatus = 0; // Set the buttonStatus variable to 0
          break; // End for loop
        }
        servo.write(i); // Write the value to servo motor
        delay(60); // 60 ms delay
      }
      for (int i = 145; i > 25; i--) { // For the servo motor to scan in the opposite direction, that is, from 145 degrees to 25 degrees
        if (digitalRead(buttonPin) == LOW) { // If the button is pressed
          buttonStatus = 0; // Set the buttonStatus variable to 0
          break; // End for loop
        }
        servo.write(i); // Write the value to servo motor
        delay(60); // 60 ms delay
      }
      delay(100);
    }
  }
}