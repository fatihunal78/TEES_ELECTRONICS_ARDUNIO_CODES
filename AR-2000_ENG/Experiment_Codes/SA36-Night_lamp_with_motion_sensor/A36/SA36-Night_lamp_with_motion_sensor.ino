//SA36 - Night lamp with motion sensor

int LEDPin = 3; // Define the pin number to which the LED is connected
int sensorPin = 2; // Define the pin number to which the PIR Sensor is connected
int LDRPin = A5; // Define the pin number to which the LDR is connected

void setup() {
  pinMode(LEDPin, OUTPUT); // Set the pin to which the LED is connected as output
  pinMode(sensorPin, INPUT); // Set the pin to which the sensor is connected as input
  pinMode(LDRPin, INPUT); // Set the pin to which the LDR is connected as input
}

void loop() {
  if (analogRead(LDRPin) <= 400) { // If the value read from LDR is less than 400, that is, if the weather is dark
    if (digitalRead(sensorPin) == HIGH) { // If motion is detected
      digitalWrite(LEDPin, HIGH); // Turn ON the LED 
      delay(5000); // Wait for 5 seconds
      digitalWrite(LEDPin, LOW); // Turn OFF the LED 
    } else {
      digitalWrite(LEDPin, LOW); // If no motion is detected, turn OFF the LED
    }
  } else {
    digitalWrite(LEDPin, LOW); // If the value read from the LDR is greater than 400, that is, if the weather is bright, turn OFF the LED
  }
}