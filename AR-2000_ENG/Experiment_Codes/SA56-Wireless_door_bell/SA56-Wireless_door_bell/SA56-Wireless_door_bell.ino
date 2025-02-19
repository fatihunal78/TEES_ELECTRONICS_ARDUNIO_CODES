// SA56 - Wireless door bell

int sensorPin = A5; // Define the pin number to which the infrared sensor is connected
int speakerPin = 3; // Define the pin number to which the Speaker is connected

int readValue;      // Define the variable to save the read value from ADC
int averageValue;   // Define the variable to save the average of 10 values read from ADC

// Define the frequency values corresponding to the musical notes
#define NOTE_C4  262
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247

// Define the notes to be played in sequence in an array
int melody_notes[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// Define the waiting time between notes
// Such as 4 = quarter note, 8 = eighth note
int note_strokes[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  pinMode(sensorPin, INPUT);   // Set the pin to which the infrared sensor is connected as input
  pinMode(speakerPin, OUTPUT); // Set the pin to which the Speaker is connected as output

  // Loop from 0 to 10 to get 10 values from ADC initially
  for (int i = 0; i < 10; i++) {
    readValue = analogRead(sensorPin); // Save read values from ADC to readValue variable
    averageValue += readValue;         // Add the new value to the readValue variable with the previous value
    delay(50);                         // Wait for 50ms
  }
  averageValue /= 10; // Calculate the average of 10 measured values
}

void loop() {
  // If the sensor value is 600 more than the average value or greater than 1000
  if (analogRead(sensorPin) >= averageValue + 600 || analogRead(sensorPin) >= 1000) {
    // Play doorbell music
    for (int note = 0; note < 8; note++) { // Loop through the 8 musical notes
      // Calculate the duration of the note
      // For example, 1000 / 4 = 250ms for a quarter note, 1000 / 8 = 125ms for an eighth note
      int noteTime = 1000 / note_strokes[note];
      tone(speakerPin, melody_notes[note], noteTime); // Play the note

      // The pause time between notes is 30% longer than the note time
      int note_waiting_time = noteTime * 1.30;
      delay(note_waiting_time);

      noTone(speakerPin); // Mute the music
    }
  }
}