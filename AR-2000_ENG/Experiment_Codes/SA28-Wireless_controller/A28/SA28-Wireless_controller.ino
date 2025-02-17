//SA28 - Wireless controller

int sensorPin = A5;  // Define the pin number to which the infrared sensor is connected
int LEDPin = 7;      // Define the pin to which the LED is connected

void setup() {
  pinMode(sensorPin, INPUT);   // Set the pin to which the infrared sensor is connected as input
  pinMode(LEDPin, OUTPUT);     // Set the pin to which the LED is connected as output
}

void loop() {
  if (analogRead(sensorPin) >= 1000) { // If the sensor value in the analog pin is greater than or equal to 1000
                                       // That is, if a factor other than the average value (pressing the button) triggers the sensor
    digitalWrite(LEDPin, HIGH);        // Turn ON the LED 
  } 
  else {                               // If the sensor value read from the analog pin does not trigger the sensor
    digitalWrite(LEDPin, LOW);         // Turn OFF the LED
  }
}