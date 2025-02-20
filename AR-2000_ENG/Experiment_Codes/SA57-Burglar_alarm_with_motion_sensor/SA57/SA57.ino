// SA57 - Burglar alarm with motion sensor

// Define the pin number to which the alarm reset button is connected
int buttonPin = 2;

// Define the digital pin numbers to which the LEDs are connected
int redPin = 4;
int greenPin = 11;

// Define the pin number to which the PIR sensor is connected
int sensorPin = 3;

// Define the pin number to which the Speaker is connected
int speakerPin = 6;

// Define the sensorStatus variable to store the sensor state
int sensorStatus = 0;

void setup() {
  // Set the pins to which the LEDs are connected as output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);

  // Set the pin to which the Speaker is connected as output
  pinMode(speakerPin, OUTPUT);

  // Set the pin to which the reset button is connected as input
  pinMode(buttonPin, INPUT);

  // Set the pin to which the PIR sensor is connected as input
  pinMode(sensorPin, INPUT);
}

void loop() {
  // Check whether the Button is pressed or not
  if (digitalRead(buttonPin) == HIGH) { // If the Button is pressed
    if (sensorStatus == 0) { // If sensor is OFF
      sensorStatus = 1;      // Save the sensor status as ON
      digitalWrite(greenPin, HIGH); // Turn ON the Green LED
    } else { // If the sensor is ON
      sensorStatus = 0;      // Save the sensor status as OFF
      digitalWrite(greenPin, LOW); // Turn OFF the Green LED
    }
    delay(200); // Wait for 200ms
  }

  // Check the sensor status
  if (digitalRead(sensorPin) == HIGH && sensorStatus == 1) { // If the sensor is triggered
    while (1) { // Enter infinite loop
      digitalWrite(greenPin, LOW); // Turn OFF the Green LED

      // Turn ON the Red LED
      digitalWrite(redPin, HIGH);

      // Activate alarm sound
      tone(speakerPin, 440);
      delay(250); // Wait for 250ms

      // Turn OFF the Red LED
      digitalWrite(redPin, LOW);
      noTone(speakerPin);
      delay(250); // Wait for 250ms

      // If the alarm reset button is pressed
      if (digitalRead(buttonPin) == HIGH) {
        delay(500); // Wait for 500ms
        noTone(speakerPin);
        sensorStatus = 0;
        digitalWrite(greenPin, LOW); // Turn OFF the Green LED
        delay(250); // Wait for 250ms
        Serial.println("Alarm Disabled");
        break; // Exit infinite loop, disable the Alarm
      }
    }
  }
}