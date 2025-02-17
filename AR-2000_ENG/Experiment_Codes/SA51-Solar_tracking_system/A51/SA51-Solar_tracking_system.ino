// SA51 - Solar tracking system

#include <Servo.h> // Add servo motor library

Servo servo_motor;  // Create object to control servo motor
int rightLDR = A4;  // Define the pin to which the LDR on the right side is connected
int leftLDR = A5;   // Define the pin to which the LDR on the left side is connected
int buttonPin = 2;  // Define the pin number to which the Button is connected

int rightLDR_value; // Define the variable to store the right LDR value
int leftLDR_value;  // Define the variable to store the left LDR value

int error = 0;      // Define the variable to store the difference of the values read from the right and left LDR

int servoposition;  // Define the variable to store the position of the servomotor

// To read the current ambient illumination value in the setup section of the Right and Left LDR
// Define variables to store calibration values
int rightLDR_Calibration = 0;
int leftLDR_Calibration = 0;

void setup() {
  servo_motor.attach(3);               // Define the pin to which the servo motor is connected
  pinMode(buttonPin, INPUT_PULLUP);    // Define the pin number to which the button is connected

  servo_motor.write(90);               // Initially set servo motor to 90-degree position

  // Read right and left LDR values and save them in calibration variables
  rightLDR_Calibration = analogRead(rightLDR);
  leftLDR_Calibration = analogRead(leftLDR);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) { // If the Button is pressed
    while (1) {                        // Enter infinite loop
      rightLDR_value = analogRead(rightLDR); // Read value on right sensor
      leftLDR_value = analogRead(leftLDR);   // Read value on left sensor

      error = rightLDR_value - leftLDR_value; // Define the difference between the two sensors and save it to the error variable

      // Proportion the data in the error variable between 180 and 0 degrees, which is the rotation angle of the servo motor
      servoposition = map(error, rightLDR_Calibration - 1023, 1023 - leftLDR_Calibration, 180, 0);

      servo_motor.write(servoposition); // Provide rotation by writing the proportion value to the servo motor
      delay(50);
    }
  }
}
