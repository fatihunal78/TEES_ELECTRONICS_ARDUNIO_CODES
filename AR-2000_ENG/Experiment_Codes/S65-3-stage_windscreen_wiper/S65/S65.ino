//S65 - 3-stage windscreen wiper

#include <Servo.h>    //Add servo motor library

Servo servomotor;    //Create an object named servomotor to control the servo motor

int buttonPin = 2;    //Define the pin number to which the Button is connected
int buttonStatus = 0;    //Define a variable to hold the number of times the button is pressed and set the initial value to zero
int i = 0;    //Define the initial value used in the for loops
int wiper_speed = 65;    //Define the variable that will adjust the movement speed of the wiper and set its initial value to 65
  
void setup() {
    servomotor.attach(5);    //Set the pin to which the servo motor is connected
    pinMode(buttonPin, INPUT);    //Set the pin to which the Button is connected as input

    //Set the pin to which the button is connected as Interrupt
    //When the button is pressed, perform the operation in the buttonControl function
    //Trigger at RISING (Rising Edge)
    attachInterrupt(digitalPinToInterrupt(buttonPin), buttonControl, RISING);
}

void loop() {
    while(1) {    //Enter infinite loop 
        if(buttonStatus == 0) {    //If buttonStatus is equal to zero 
            servomotor.write(0);    //Set servomotor to zero-degree position 
            break;    //End infinite loop 
        }
        else {    //If buttonStatus is other than zero 
            for(i = 0; i < 180; i++) {    //Use for loop for 180 degree movement of servo motor
                                         //Move from 0-degree to 180-degree position
                servomotor.write(i);    //Move servo motor according to the variable i
                delay(wiper_speed);    //Move the servo with the delay in the wiper_speed variable
            }
            for(i = 180; i > 0; i--) {    //Use for loop for 180 degree movement of servo motor
                                         //Move from 180-degree to 0-degree position
                servomotor.write(i);    //Move servo motor according to the variable i
                delay(wiper_speed);    //Move the servo with the delay in the wiper_speed variable
            }  
        }    
    }     
    wiper_speed = 65;    //Set wiper_speed variable to 65 
}

//Create a buttonControl function to check if the button is pressed
//This function will check whether the button is pressed or not inside the for loops
void buttonControl() {
    static unsigned long last_interrupt_time = 0;    //Create variable last_interrupt_time and set its initial value to 0
    unsigned long interrupt_time = millis();    //Create a variable named interrupt_time and assign the system start time to it
                                               //with the millis() command
    
    //If the time difference between interrupt_time and last_interrupt_time is greater than 500ms
    //This process is used to prevent detection of multiple button presses.
    if(interrupt_time - last_interrupt_time > 500) {
        buttonStatus++;    //Increment the buttonStatus variable by one
        //Change the value of the wiper_speed variable according to the number of times the button is pressed
        if(buttonStatus == 1) wiper_speed = 35;
        if(buttonStatus == 2) wiper_speed = 13;
        if(buttonStatus == 3) wiper_speed = 6;
    
        if(wiper_speed < 0) {    //If the wiper_speed variable is less than 0
            wiper_speed = 0;    //Reset wiper_speed variable to zero
        }
  
        if(buttonStatus > 3) {    //If the buttonStatus variable is greater than 3 
            buttonStatus = 0;    //Reset buttonStatus variable to zero
            wiper_speed = 6;    //Set wiper_speed variable to 6
        }   
    }
    last_interrupt_time = interrupt_time;    //Assign the value in the interrupt_time variable to the last_interrupt_time variable
}
