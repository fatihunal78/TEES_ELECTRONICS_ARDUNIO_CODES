//SA38 - Piano with keypad

#include <Keypad.h> // Keypad Library added

int speakerPin = 3; // Define the pin number to which the speaker is connected

const byte ROW = 4;    // Specify how many rows the keypad consists of
const byte COLUMN = 4; // Specify how many columns the keypad consists of

// Define the position and order of the keys in the row and column
char keys[ROW][COLUMN] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

// Define the keys on the keypad
byte rowPins[ROW] = {13, 12, 11, 10};   // Define the pins to which the row connections are connected on the Arduino board
byte columnPins[COLUMN] = {9, 8, 7, 6}; // Define pins to which column connections are connected on the Arduino board

Keypad key_pad = Keypad(makeKeymap(keys), rowPins, columnPins, ROW, COLUMN); // Create the keypad

char key; // Define the variable to store the keys pressed from the Keypad

// Define notes
#define do     262 // do
#define re     294 // re
#define mi     330 // mi
#define fa     349 // fa
#define so     392 // so
#define la     440 // la
#define ti     494 // ti
#define soft_do 512 // soft do

void setup() {
  pinMode(speakerPin, OUTPUT); // Set the pin to which the Speaker is connected as output
}

void loop() {
  key = key_pad.getKey(); // Save the keys pressed from the keypad to the key variable
  if (key != NO_KEY) { // If any key is pressed
    switch (key) { // Go to the case in the switch case structure that corresponds to which key was pressed
      case '1': // If key 1 is pressed
        tone(speakerPin, do); // Play do on the Speaker
        delay(200); // Wait for 200ms
        noTone(speakerPin); // Mute the Speaker
        break; // Finish case '1'
      case '2':
        tone(speakerPin, re); // Play re on the Speaker
        delay(200); // Wait for 200ms
        noTone(speakerPin);
        break; // Finish case '2'
      case '3':
        tone(speakerPin, mi); // Play mi on the Speaker
        delay(200); // Wait for 200ms
        noTone(speakerPin); // Mute the Speaker
        break; // Finish case '3'
      case 'A':
        tone(speakerPin, fa); // Play fa on the Speaker
        delay(200); // Wait for 200ms
        noTone(speakerPin); // Mute the Speaker
        break; // Finish case 'A'
      case '4':
        tone(speakerPin, so); // Play so on the Speaker
        delay(200); // Wait for 200ms
        noTone(speakerPin); // Mute the Speaker
        break; // Finish case '4'
      case '5':
        tone(speakerPin, la); // Play la on the Speaker
        delay(200); // Wait for 200ms
        noTone(speakerPin); // Mute the Speaker
        break; // Finish case '5'
      case '6':
        tone(speakerPin, ti); // Play ti on the Speaker
        delay(200); // Wait for 200ms
        noTone(speakerPin); // Mute the Speaker
        break; // Finish case '6'
      case 'B':
        tone(speakerPin, soft_do); // Play soft do on the Speaker
        delay(200); // Wait for 200ms
        noTone(speakerPin); // Mute the Speaker
        break; // Finish case 'B'
      default: // If another key other than the above cases is received
        noTone(speakerPin); // Mute the Speaker
    }
  }
  delay(10);
}