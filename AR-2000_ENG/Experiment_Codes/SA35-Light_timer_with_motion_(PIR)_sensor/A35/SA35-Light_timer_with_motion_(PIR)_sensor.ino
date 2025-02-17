//SA35 - Light timer with motion (PIR) sensor

// Define the digital pin numbers to which the LEDs are connected
int blueLED = 4;
int redLED = 5;
int greenLED = 6;
int yellowLED = 7;

// Define the digital pin number to which the PIR sensor is connected
int sensorPin = 2;
// Define the variable to store the state of the PIR Sensor
int sensorStatus = 0;

void setup() {
  // Set the pin to which the LED is connected as output
  pinMode(blueLED, OUTPUT);
  pinMode(yellowLED, OUTPUT); 
  pinMode(redLED, OUTPUT); 
  pinMode(greenLED, OUTPUT); 
  // Set the pin to which the PIR Sensor is connected as input
  pinMode(sensorPin, INPUT);
}

void loop() {
  // Query the status of the PIR sensor and save it in the sensorStatus variable
  sensorStatus = digitalRead(sensorPin);
  // Set the status of the LED according to the status of the PIR Sensor
  if (sensorStatus == HIGH) { // If the sensor is triggered
    // Turn ON the LEDs
    digitalWrite(blueLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, HIGH);

    delay(5000); // Wait for 5 seconds 
    digitalWrite(blueLED, LOW); // Turn OFF the Blue LED 
    delay(5000); // Wait for 5 seconds 
    digitalWrite(redLED, LOW); // Turn OFF the Red LED 
    delay(5000); // Wait for 5 seconds 
    digitalWrite(greenLED, LOW); // Turn OFF the Green LED 
    delay(5000); // Wait for 5 seconds 
    digitalWrite(yellowLED, LOW); // Turn OFF the Yellow LED
  }
}