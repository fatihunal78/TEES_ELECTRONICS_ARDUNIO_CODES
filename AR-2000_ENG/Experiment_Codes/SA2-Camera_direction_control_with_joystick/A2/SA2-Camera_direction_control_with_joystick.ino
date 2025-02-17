//SA2 - Camera direction control with joystick

#include <Servo.h>  //Add the servo motor library

int xPin = A0;          //Define the pin number to which the Joystick X axis is connected
int xPosition = 0;      //Define the variable that will store the position of the Joystick X axis

int servoPin = 3;       //Define the digital pin number to which the servo motor is connected

int cameraPosition = 0; //Define the variable to store the camera position angle

Servo servo;            //Define the servo motor to be controlled with the servo name

void setup() {
    pinMode(xPin, INPUT);     //Set the pin to which the Joystick X axis is connected as input
    
    servo.attach(servoPin);   //Set the pin to which the servo motor is connected
    servo.write(90);          //Move servo motor to 90-degree position
}

void loop() {
    //Read the position of the Joystick X axis and save it to the xPosition variable
    xPosition = analogRead(xPin);
    
    //Proportion the xPosition value relative to the servo angle
    cameraPosition = map(xPosition, 0, 1023, 180, 0);
    servo.write(cameraPosition);  //Adjust the angle of the servo motor according to the cameraPosition variable
    delay(100);                   //Wait for 100ms
}
