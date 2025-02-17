//SA99 - Audible rain alarm

int LEDPin = 8;     // Defines the digital pin number to which the LED is connected
int sensorPin = 2;  // Define the pin number to which the humidity sensor is connected
int rainStatus = 0; // Define the variable to store the status of the humidity sensor

void setup() {
    pinMode(LEDPin, OUTPUT);    // Set the pin to which the LED is connected as output
    pinMode(sensorPin, INPUT);  // Set the pin to which the sensor is connected as input
    Serial.begin(9600);         // Start serial communication
}

void loop() {
    // Query rain status and assign it to the variable
    rainStatus = digitalRead(sensorPin);

    // Check the rain status
    if(rainStatus == HIGH) {    // If it is raining
        Serial.println(1);      // Send value 1 to inform Processing that it is raining 
        
        // Flash the LED
        digitalWrite(LEDPin, HIGH); 
        delay(200);             // Wait for 200ms
        digitalWrite(LEDPin, LOW);  // Turn OFF the LED
        delay(200);             // Wait for 200ms
    }
    else {                      // If it is not raining
        // Turn OFF the LED
        digitalWrite(LEDPin, LOW);
        Serial.println(0);      // Send 0 to inform Processing that it is not raining 
    }
}
