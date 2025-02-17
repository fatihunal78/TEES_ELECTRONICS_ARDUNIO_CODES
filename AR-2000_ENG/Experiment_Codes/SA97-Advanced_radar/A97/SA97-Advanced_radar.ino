//SA97 - Advanced radar

#include <Servo.h>                                  //Add servo motor library 

const int triggerPin = 3;                          //Define the pin to which the trigger pin of the ultrasonic sensor is connected
const int echoPin = 4;                             //Define the pin to which the echo pin of the ultrasonic sensor is connected
int buzzerPin = 9;                                 //Define the pin number to which the buzzer is connected

long duration;                                      //Define the duration variable to which the time measurement will be stored
int distance;                                      //Define the distance variable to store the distance measurement
int buttonPin = 2;                                 //Define the pin number to which the Button is connected
int buttonStatus = 0;                              //Define the variable to store the button state and set its initial state to 0

Servo servo_control;                               //Create servo_control object to control servo motor

unsigned long newTime = 0;
unsigned long oldTime = 0;

void setup() {
    pinMode(triggerPin, OUTPUT);                   //Set the pin to which the Trigger leg is connected as output
    pinMode(echoPin, INPUT);                       //Set the pin to which the Echo leg is connected as input
    pinMode(buttonPin, INPUT);                     //Set the pin to which the Button is connected as input
    pinMode(buzzerPin, OUTPUT);                    //Set the pin to which the Buzzer is connected as output
    Serial.begin(9600);                           //Start serial communication
    servo_control.attach(8);                      //Define the pin to which the trigger pin of the servo motor is connected
}

void loop() {
    if(digitalRead(buttonPin) == HIGH && buttonStatus == 0) {
        buttonStatus = 1;
        while(1) {
            if(digitalRead(buttonPin) == HIGH && buttonStatus == 1) {
                buttonStatus = 0;
                break;
            }
            
            for(int i=25; i<=145; i++) {          //For loop is used for the movement of the servo motor from 25 to 145 degree angle
                servo_control.write(i);            //Moving servo motor from 25 degrees to 145 degrees
                delay(30);
                distance = calculate_distance();    //Call the calculate_distance() function and save the value there to the distance variable
        
                Serial.print(i);                   //Send the current angle of the servo motor to the serial port
                Serial.print(",");                 //Send "," to the serial port
                Serial.print(distance);            //Send the distance variable to the serial port
                Serial.print(".");                 //Send a "." sign to the serial port to let it know that the data is finished
        
                newTime = millis();
                if(newTime - oldTime >= 2000) {
                    digitalWrite(buzzerPin, HIGH);
                    delay(100);
                    digitalWrite(buzzerPin, LOW);
                    delay(100);
                    oldTime = newTime; 
                }
            }
            
            for(int i=145; i>25; i--) {           //We use for loop for the servo motor to scan in the opposite direction, that is, 
                                                  //from 145 degrees to 25 degrees
                servo_control.write(i);            //Move the servo motor
                delay(30);
                distance = calculate_distance();    //Call the calculate_distance() function and save the value there to the distance variable
                Serial.print(i);                   //Send the current angle of the servo motor to the serial port
                Serial.print(",");                 //Send "," to the serial port
                Serial.print(distance);            //Send the distance variable to the serial port
                Serial.print(".");                 //Send a "." sign to the serial port to let it know that the data is finished
        
                newTime = millis();
                if(newTime - oldTime >= 2000) {
                    digitalWrite(buzzerPin, HIGH);
                    delay(100);
                    digitalWrite(buzzerPin, LOW);
                    delay(100);
                    oldTime = newTime; 
                }
            }
        }
    }
}

int calculate_distance() {                         //Create calculate_distance() function to calculate distance
    digitalWrite(triggerPin, LOW);                //Pull the trigger pin of the ultrasonic sensor to LOW
    delayMicroseconds(2);                         //Wait for 2 microseconds
    digitalWrite(triggerPin, HIGH);               //Pull the trigger pin of the ultrasonic sensor to HIGH
    delayMicroseconds(10);                        //Wait for 10 microseconds
    digitalWrite(triggerPin, LOW);                //Pull the trigger pin to LOW
    duration = pulseIn(echoPin, HIGH);            //Read the value in the echo pin, and calculate the round trip time and save this 
                                                 //time to the duration variable
    distance = duration * 0.034 / 2;              //To calculate the distance, divide by two as the round trip is the total time and 
                                                 //multiply it by the speed of sound 0.034
    return distance;                              //Return the distance variable
}
