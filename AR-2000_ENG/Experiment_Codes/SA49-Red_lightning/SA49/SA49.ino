// SA49 - Red lightning

// Define the pin numbers to which the LEDs are connected
int LEDs[] = {3, 4, 5, 6, 7};

// Define the digital pin number to which the Button is connected
int buttonPin = 2;

// Navigation speed of LEDs
int speed = 60;

void setup() {
  // With for loop, set the pin to which the LEDs are connected as output
  for (int i = 0; i < 5; i++) {
    pinMode(LEDs[i], OUTPUT);
  }

  // Set the pin to which the Button is connected as input
  pinMode(buttonPin, INPUT);
}

void loop() {
  // Check button status
  if (digitalRead(buttonPin) == HIGH) { // If the Button is pressed
    // Number of repetitions
    for (int k = 0; k < 5; k++) {
      // Turn the LEDs ON and OFF in order from left to right
      // The LEDs defined as an array with the variable i are turned ON and OFF in sequence.
      for (int i = 0; i < 5; i++) {
        digitalWrite(LEDs[i], HIGH); // Turn ON the next LED
        delay(speed);                // Wait according to the speed value
        digitalWrite(LEDs[i], LOW);  // Turn OFF the next LED
      }

      // Turn the LEDs ON and OFF in order from right to left
      // The LEDs defined as an array with the variable j are turned ON and OFF in sequence.
      for (int j = 4; j >= 0; j--) { // Corrected the loop to start from 4 instead of 5
        digitalWrite(LEDs[j], HIGH); // Turn ON the next LED
        delay(speed);                // Wait according to the speed value
        digitalWrite(LEDs[j], LOW);  // Turn OFF the next LED
      }
    }
  }
}