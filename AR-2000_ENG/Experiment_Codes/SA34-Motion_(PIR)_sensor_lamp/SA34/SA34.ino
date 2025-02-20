//SA34 - Motion (PIR) sensor lamp
int sensorPin = 2; // Define the pin number to which the PIR Sensor is connected
int WhiteLED = 7;  // Define the pin number to which the white LED is connected

void setup() {
  pinMode(sensorPin, INPUT);  // Define the pin to which the PIR Sensor is connected as input
  pinMode(WhiteLED, OUTPUT);  // Set the pin to which the White LED is connected as output 
}

void loop() {
  // Check the sensor status
  if (digitalRead(sensorPin) == HIGH) { // If the sensor is triggered
    digitalWrite(WhiteLED, HIGH); // Turn ON the White LED
  } else { // If the sensor is not triggered 
    digitalWrite(WhiteLED, LOW); // Turn OFF the White LED
  }
}