//S54 - Servo motor control with potentiometer
#include <Servo.h> //Add servo library

Servo myservo; //Add servo object to control servo

int potPin = A0; //Define the pin to which the Potentiometer is connected
int val; //Define the variable to store the value to be measured from the analog pin

void setup() {
    myservo.attach(5); //Set the pin to which the servo motor is connected
}

void loop() {
    val = analogRead(potPin); //Save the value between 0 and 1023 that we read from the Potentiometer to the val variable
    //Proportion the value between 0 and 1023 kept in the val variable to the value between 0 and 180, which is 
    //the angle that the servo will make. The value of 1023 will be 0 degrees. If the val variable is 0, that is, 
    //if the Potentiometer is at step 1, the servo will make a 180-degree angle, if the val variable is 512, 
    //the servo will make a 90-degree angle.
    val = map(val, 0, 1023, 180, 0);
    myservo.write(val); //Rotate the servo motor according to the degree in the val variable
    delay(15); //Wait for 15ms
}
