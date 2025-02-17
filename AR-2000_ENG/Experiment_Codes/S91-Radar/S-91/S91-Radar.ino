//S91 - Radar

#include <Servo.h>    //Add servo motor library

const int triggerPin = 4;    //Define the pin to which the HC-SR04 Trigger leg is connected
const int echoPin = 5;       //Define the pin to which the HC-SR04 Echo pin is connected
const int LEDPin = 8;        //Define the pin to which the Red LED is connected
int speakerPin = 2;          //Define the pin number to which the Speaker is connected
int buttonPin = 9;           //Define the pin number to which the Button is connected

int buttonStatus = 0;        //Define the variable to store the button state and set its initial state to 0
//Define time and distance variables
long time;
int distance;

Servo myServo;              //Create an object named myServo for servo motor control

void setup() {
    pinMode(triggerPin, OUTPUT);         //Set the pin to which the trigger leg is connected as output
    pinMode(echoPin, INPUT);             //Set the pin to which the echo leg is connected as input
    pinMode(LEDPin, OUTPUT);             //Set the pin to which the Red LED is connected as output
    pinMode(speakerPin, OUTPUT);         //Set the pin to which the Speaker is connected as output
    pinMode(buttonPin, INPUT_PULLUP);    //Set the pin to which the Button is connected as input and activate the pull up resistor
    myServo.attach(3);                   //Define the pin to which the signal leg of the servo motor is connected
}

void loop() {
    if(digitalRead(buttonPin) == LOW && buttonStatus == 0) {
        buttonStatus = 1;
        while(1) {
            if(digitalRead(buttonPin) == LOW && buttonStatus == 0) {
                buttonStatus = 0;
                break;
            }
            //To scan the servo motor between 25-degree and 145-degree angles
            for(int i=25; i<=145; i++) {    //In the for loop, increment the value of i one by one from 25 to 145
                myServo.write(i);           //Rotate servo motor to i value
                delay(20);                  //Wait for 20ms
                //Call the measureDistance() function and save the distance value returned in measureDistance() function to the
                //distance variable. measureDistance() function returns the value calculated in the function with the return command
                distance = measureDistance();
                
                //If the measured distance value is less than 30cm. That is, if an obstacle comes 30 cm in front of the 
                //ultrasonic sensor while the servo motor is rotating
                if(distance <= 30) {
                    digitalWrite(LEDPin, HIGH);    //Turn ON the Red LED
                    tone(speakerPin, 700);        //Play audio from the Speaker
                    delay(50);                    //Wait for 50ms
                    digitalWrite(LEDPin, LOW);     //Turn OFF the Red LED
                    noTone(speakerPin);           //Mute the Speaker
                    delay(50);                    //Wait for 50ms
                }
            }
            
            //For the servo motor to scan in the opposite direction, that is, from 145 degrees to 25 degrees
            for(int i=145; i>25; i--) {    //In the for loop, decrement the value of i one by one from 145 to 25
                myServo.write(i);          //Rotate servo motor to i value
                delay(20);
                //Call the measureDistance() function and save the distance value returned in measureDistance() function to the
                //distance variable. measureDistance() function returns the value calculated in the function with the return command
                distance = measureDistance();
                
                //If the measured distance value is less than or equal to 30cm. That is, if an obstacle comes 30 cm in front of
                //the ultrasonic sensor while the servo motor is rotating
                if(distance <= 30) {
                    digitalWrite(LEDPin, HIGH);    //Turn ON the Red LED
                    tone(speakerPin, 500);        //Play audio from the Speaker
                    delay(50);                    //Wait for 50ms
                    digitalWrite(LEDPin, LOW);     //Turn OFF the Red LED
                    noTone(speakerPin);           //Mute the Speaker
                    delay(50);                    //Wait for 50ms
                }
            }
        }
    }
}

//To measure the distance with the help of ultrasonic sensor. As we saw before in the distance calculation experiment
//We measure the distance by turning the trigger and echo pins ON and OFF
int measureDistance() {    //Define the measureDistance() function
    digitalWrite(triggerPin, LOW);     //Pull the trigger pin to LOW
    delayMicroseconds(2);              //Wait for 2 microseconds
    digitalWrite(triggerPin, HIGH);     //Pull the trigger pin to HIGH 
    delayMicroseconds(10);             //Wait for 10 microseconds
    digitalWrite(triggerPin, LOW);      //Pull the trigger pin to LOW
    time = pulseIn(echoPin, HIGH);     //PULL the echo pin high and save the measured time to the time variable
    //Find the distance using the formula Path = speed * time. Here, the time is the value we read from the ultrasonic
    //sensor and the time it takes for the sound signal to go back and forth, so we divided it by 2. 0.034 is the speed
    //of sound. Sound travels 342.2 meters per second.
    distance = time * 0.034/2;
    
    return distance;    //Return the distance variable to the line calling the function
}
