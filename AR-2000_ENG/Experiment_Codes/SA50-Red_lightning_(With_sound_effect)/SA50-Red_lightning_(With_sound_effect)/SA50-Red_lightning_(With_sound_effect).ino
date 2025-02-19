// SA50 - Red lightning (With sound effect)

// Define the pin numbers to which the LEDs are connected
int LEDs[] = {4, 5, 6, 7, 8};

// Define the digital pin number to which the Button is connected
int buttonPin = 2;

// Navigation speed of LEDs
int speed = 120;

// Define the pin number to which the Speaker is connected
int speakerPin = 3;

void setup() {
  // By means of the for loop, set the pins to which the LEDs are connected as output
  for (int i = 0; i < 5; i++) {
    pinMode(LEDs[i], OUTPUT);
  }

  // Set the pin to which the Button is connected as input
  pinMode(buttonPin, INPUT);

  // Set the pin to which the Speaker is connected as output
  pinMode(speakerPin, OUTPUT);
}

void loop() {
  // Check button status
  if (digitalRead(buttonPin) == HIGH) { // If the Button is pressed
    // Number of repetitions
    for (int k = 0; k < 5; k++) {
      // Turn the LEDs ON and OFF in order from left to right
      // The LEDs defined as an array with the variable i are turned ON and OFF in sequence.
      for (int i = 0; i < 4; i++) { // Adjusted loop to avoid out-of-bounds access
        digitalWrite(LEDs[i], HIGH);     // Turn ON the current LED
        digitalWrite(LEDs[i + 1], HIGH); // Turn ON the next LED
        tone(speakerPin, (i + 1) * 150); // Play sound effect
        delay(speed);                    // Wait according to the speed value
        digitalWrite(LEDs[i], LOW);      // Turn OFF the current LED
        noTone(speakerPin);              // Stop sound effect
      }

      // Turn the LEDs ON and OFF in order from right to left
      // The LEDs defined as an array with the variable j are turned ON and OFF in sequence.
      for (int j = 4; j > 0; j--) { // Adjusted loop to avoid out-of-bounds access
        digitalWrite(LEDs[j], HIGH);     // Turn ON the current LED
        digitalWrite(LEDs[j - 1], HIGH); // Turn ON the previous LED
        tone(speakerPin, (6 - j) * 150); // Play sound effect
        delay(speed);                    // Wait according to the speed value
        digitalWrite(LEDs[j], LOW);      // Turn OFF the current LED
        noTone(speakerPin);              // Stop sound effect
      }
    }
  }
}