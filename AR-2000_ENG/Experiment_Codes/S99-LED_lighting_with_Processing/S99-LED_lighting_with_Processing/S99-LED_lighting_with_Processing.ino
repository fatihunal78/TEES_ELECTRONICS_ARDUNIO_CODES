//S99 - LED lighting with Processing

int LEDPin = 5;  //Define the digital pin number to which the LED is connected
char Processing_LED_Status;  //Define the variable where the value that will come from Processing as 1 or 0 will be stored

void setup() {
    pinMode(LEDPin, OUTPUT);  //Set the pin to which the LED is connected as output
    Serial.begin(9600);  //Start serial communication with Processing
}

void loop() {
    if(Serial.available() > 0) {  //If there is data coming from the serial communication port
        Processing_LED_Status = Serial.read();  //Save the value read from the serial port to the Processing_LED_Status variable
        if(Processing_LED_Status == '1') {  //If the value read from the serial port is 1, that is, if the left mouse button 
                                           //is pressed on a white background in Processing
            digitalWrite(LEDPin, HIGH);  //Turn ON the LED
        }
        if(Processing_LED_Status == '0') {  //If the value read from the serial port is 0, that is, if the right mouse button 
                                           //is pressed on a yellow background in Processing
            digitalWrite(LEDPin, LOW);  //Turn OFF the LED
        }
    }
}
