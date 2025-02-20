//S49 - Touch sensor

int LEDPin = 7;      //Define the pin number to which the LED is connected 
int sensorPin = 3;   //Define the pin number to which the touch sensor is connected 
int LEDStatus = 0;   //Define the variable to store the LED status

void setup() {
    pinMode(LEDPin, OUTPUT);    //Set the pin to which the LED is connected as output
    pinMode(sensorPin, INPUT);  //Set the pin to which the sensor is connected as input
}

void loop() {
    if(digitalRead(sensorPin) == HIGH) {   //If the touch sensor is pressed 
        if(LEDStatus == 0) {               //If the LED is OFF 
            digitalWrite(LEDPin, HIGH);     //Turn ON the LED 
            LEDStatus = 1;                 //Save the LED status as ON 
            delay(100);                    //Wait for 100ms
        }
        else if(LEDStatus == 1) {          //If the LED is ON 
            digitalWrite(LEDPin, LOW);      //Turn OFF the LED 
            LEDStatus = 0;                 //Save the LED status as OFF 
            delay(100);                    //Wait for 100ms
        }
    }
    delay(200);                            //Wait for 200ms
}

