// S52 - Random colour capture

// Define the digital pin numbers where LEDs are connected
int redLEDPin = 6;              // Red LED pin
int greenLEDPin = 5;            // Green LED pin  
int blueLEDPin = 3;             // Blue LED pin

// Define the digital pin number where button is connected
int buttonPin = 2;              // Button pin

// Define the pin number where speaker is connected
int speakerPin = 9;             // Speaker pin

// Define the variable to store button state
int buttonState = 0;            // Button state

// Define variables to store LED states
int redState = 0;               // Red LED state
int greenState = 0;             // Green LED state
int blueState = 0;              // Blue LED state

void setup() {
    // Set LED pins as output
    pinMode(redLEDPin, OUTPUT);
    pinMode(greenLEDPin, OUTPUT);
    pinMode(blueLEDPin, OUTPUT);
    
    // Set button pin as input
    pinMode(buttonPin, INPUT);
    
    // Set speaker pin as output
    pinMode(speakerPin, OUTPUT);
    
    // Turn off all LEDs at startup
    digitalWrite(redLEDPin, HIGH);
    digitalWrite(greenLEDPin, HIGH);
    digitalWrite(blueLEDPin, HIGH);
}

void loop() {
    // Read button state and assign to buttonState variable
    buttonState = digitalRead(buttonPin);

    // Adjust RGB LED state based on button state
    if(buttonState == HIGH) {    // If button is pressed
        // Create 3 second animation
        for(int i = 0; i < 15; i++) {
            // Select random LED states between 0-255
            redState = random(0, 256);
            greenState = random(0, 256);
            blueState = random(0, 256);
            
            // Generate sound from speaker based on LED states
            tone(speakerPin, (redState + greenState + blueState) / 3);
            
            // Light up RGB LED according to state variable levels
            analogWrite(redLEDPin, redState);
            analogWrite(greenLEDPin, greenState);
            analogWrite(blueLEDPin, blueState);
            
            delay(200);              // Wait for 200ms
            noTone(speakerPin);      // Return speakerPin to normal pin state
        }
        delay(500);                  // Wait for 500ms
    }
}
