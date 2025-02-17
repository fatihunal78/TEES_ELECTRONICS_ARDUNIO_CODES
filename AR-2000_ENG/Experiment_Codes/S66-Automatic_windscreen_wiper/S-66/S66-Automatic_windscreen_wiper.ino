//S66 - Automatic windscreen wiper

//Add servo motor library
#include <Servo.h>
Servo myservo;    //Add servo object to control servo motor

int sensorPin = 2;    //Define the pin number to which the rain sensor is connected
int LEDPin = 12;    //Define the digital pin number to which the Green LED is connected

void setup() {
    pinMode(sensorPin, INPUT);    //Set the pin to which the sensor is connected as input
    pinMode(LEDPin, OUTPUT);    //Set the pin to which the LED is connected as output
    
    myservo.attach(5);    //Set the pin to which the servo motor is connected
    myservo.write(0);    //Set the starting position of the servo motor to zero (0)
}

void loop() {
    if(digitalRead(sensorPin) == HIGH) {    //Read value from rain sensor
                                           //If the sensor value is 1, that is, if it is raining
        digitalWrite(LEDPin, HIGH);    //Turn ON the LED
        for(int i = 0; i <= 180; i++) {    //An incremental for loop to rotate the servo motor between 0 and 180 degrees
            myservo.write(i);    //Transfer each degree in the for loop to the servo motor
            delay(10);    //Wait for 10ms
        }
        for(int i = 180; i >= 0; i--) {    //A decremental for loop to rotate the servo between 180 and 0 degrees
            myservo.write(i);    //Transfer each degree in the for loop to the servo motor
            delay(10);    //Wait for 10ms
        }
    }
    else {    //If it is not raining
        myservo.write(0);    //Send servo motor to its initial position
        digitalWrite(LEDPin, LOW);    //Turn OFF the LED
    }
}
