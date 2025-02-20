//SA11 - Automatic barrier system

#include <Servo.h> //Add the servo motor library

int LDRPin = A5;      //Define the pin number to which the LDR is connected
int servoPin = 3;     //Define the pin number to which the servo motor is connected
int barrierStatus = 0;//Define the variable to store the barrier state  
int servoStep = 90;   //Define servo motor step count variable
int angleValue = 90;  //Define the variable to store the current angle
int triggerStatus = 0;//Define the variable that will store whether the button is pressed or not during motion
Servo servo;          //Define servo motor

void setup() {
    pinMode(LDRPin, INPUT);    //Set the pin to which the LDR is connected as input
    servo.attach(servoPin);    //Define the pin to which the servo motor is connected
    servo.write(90);           //Move servo motor to 90-degree position
}

void loop() {
    if(analogRead(LDRPin) > 900) {  //If the value read from the LDR is above the limit value
        barrierStatus = 1;           //Store the barrier state as open 
    }
    
    if(barrierStatus == 1) {        //If barrier status is open
        //Raise the barrier by rotating the servo motor 90 degrees
        for(int i=0; i<angleValue; i++) {
            servoStep += 1;          //Rotate the servo motor in one degree steps
            servo.write(servoStep);   //Adjust the angle of the servo motor according to the servoStep variable
            delay(25);               //Wait for 25ms
        }
        
        for(int j=0; j<100; j++) {   //5-second wait cycle
            delay(50);               //Wait for 50ms
            //Check if a new car has arrived during the waiting time
            if(analogRead(LDRPin) > 900) {  //if the value read from ADC is greater than 900, a new car has arrived
                triggerStatus = 1;    //Save that it is closed
                j = 100;              //Set j to 100 to exit the loop
                delay(200);           //Wait for 200ms
                break;                //Exit for loop
            }
        }
        
        //Lower the barrier by rotating the servo motor 90 degrees in reverse
        for(int i=0; i<90; i++) {
            servoStep -= 1;          //Rotate the servo motor in one degree steps
            servo.write(servoStep);   //Adjust the angle of the servo motor according to the servoStep variable
            delay(25);               //Wait for 25ms
            
            if(analogRead(LDRPin) > 900) {
                angleValue = 180 - servoStep;  //Continue the angle value from where it left off
                i = 90;                        //Set i to 90 to exit the loop
                delay(200);                    //Wait for 200ms
                break;
            } else {
                triggerStatus = 0;    //Reset the variable controlled by the button
                angleValue = 90;      //Store angle value as 90
            }
            
            if(servoStep == 90) {
                barrierStatus = 0;    //Store the barrier status as closed
            }
        }
    }
}
