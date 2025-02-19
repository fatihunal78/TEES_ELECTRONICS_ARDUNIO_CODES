//SA70 - Fully automatic ventilation system

int whiteLED = 2;     //Define the pin number to which the White LED is connected
int sensorPin = 5;    //Define the pin number to which the PIR Sensor is connected  
int motorPin = 4;     //Define the pin number to which the Motor is connected

void setup() {
    pinMode(whiteLED, OUTPUT);    //Set the pin to which the White LED is connected as output
    pinMode(sensorPin, INPUT);    //Set the pin to which the Sensor is connected as input
    pinMode(motorPin, OUTPUT);    //Set the pin to which the Motor is connected as output
}

void loop() {
    //Check the sensor status
    if(digitalRead(sensorPin) == HIGH) {    //If the sensor is triggered
        digitalWrite(whiteLED, HIGH);        //Turn ON the White LED
        digitalWrite(motorPin, HIGH);        //Start the Motor
        delay(5000);                        //Wait for 5 second
    }
    else {
        digitalWrite(whiteLED, LOW);         //Turn OFF the White LED
        digitalWrite(motorPin, LOW);         //Stop the Motor
    }
}
