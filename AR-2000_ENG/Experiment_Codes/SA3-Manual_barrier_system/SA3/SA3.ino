//SA3 - Manual barrier system.ino

#include <Servo.h>  //Add the servo motor library

int servoPin = 3;      //Define the digital pin number to which the servo motor is connected
int barrierStatus = 0; //Define the variable to store the barrier status 
int buttonPin = 2;     //Define the pin number to which the Button is connected

int servoStep = 90;    //Define servo motor step count variable
int angleValue = 90;   //Define the variable to store the current angle
int triggerStatus = 0; //Define the variable that will store whether the button is pressed or not during motion

Servo servo;           //Define the servo motor

void setup() {
    pinMode(buttonPin, INPUT_PULLUP);  //Set the pin to which the Button is connected as input and activate the pull up 
                                      //resistor
    
    servo.attach(servoPin);           //Set the pin to which the servo motor is connected
    servo.write(90);                  //Move servo motor to 90-degree position
}

void loop() {
    if(digitalRead(buttonPin) == LOW) {  //Check if the button is pressed
                                        //If the Button is pressed
        barrierStatus = 1;              //Store the barrier state as open
    }
    
    if(barrierStatus == 1) {           //If barrier status is open
        //Rotate the servo motor 90 degrees and raise the barrier
        for(int i=0; i<angleValue; i++) {
            servoStep += 1;             //Rotate the servo motor in one degree steps
            servo.write(servoStep);      //Adjust the angle of the servo motor according to the servoStep variable
            delay(25);                   //Wait for 25ms
        }
        
        for(int j=0; j<100; j++) {      //5-second wait cycle
            delay(50);                   //Wait for 50ms
            //Check if a new car has arrived during the waiting time
            if(digitalRead(buttonPin) == LOW) {  //If the button is pressed within 5 seconds
                triggerStatus = 1;               //Save that it is closed with the button
                j = 100;                         //Set j to 100 to exit the loop
                delay(500);                      //Wait for 500ms
                break;                           //Exit for loop
            }
        }
        
        //Lower the barrier by rotating the servo motor 90 degrees in reverse
        for(int i=0; i<90; i++) {
            servoStep -= 1;                     //Rotate the servo motor in one degree steps
            servo.write(servoStep);             //Adjust the angle of the servo motor according to the servoStep variable
            delay(25);                          //Wait for 25ms
            
            if(digitalRead(buttonPin) == LOW) { //If the button is pressed again while the barrier is closing
                                               //To raise the barrier
                angleValue = 180 - servoStep;   //Continue the angle value from where it left off
                i = 90;                         //Set i to 90 to exit the loop
                delay(500);                     //Wait for 500ms
                break;
            }
            else {
                triggerStatus = 0;              //Reset the variable controlled by the button
                angleValue = 90;                //Store angle value as 90
            }
            
            if(servoStep == 90) {
                barrierStatus = 0;              //Store the barrier status as closed
            }
        }
    }
}
