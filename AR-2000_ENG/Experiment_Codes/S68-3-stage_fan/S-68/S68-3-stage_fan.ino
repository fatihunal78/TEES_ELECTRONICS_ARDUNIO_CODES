//S68 - 3-stage fan

//Define the pin number to which the transistor driving the Motor is connected
int motorPin = 6;
//Define the pin number to which the step button is connected
int stepButtonPin = 2;
//Define the variable to store the step status
int stepStatus = 0;

void setup() {
    //Set the pin to which the transistor driving the Motor is connected as output
    pinMode(motorPin, OUTPUT);
    //Set the pin to which the step button is connected as input
    pinMode(stepButtonPin, INPUT);

    //Set the pin to which the button is connected as Interrupt
    //When the button is pressed, perform the operation in the buttonControl function
    //Trigger at RISING (Rising Edge)
    attachInterrupt(digitalPinToInterrupt(stepButtonPin), buttonControl, RISING);
}

void loop() {
    if(stepStatus == 0) {    //If stepStatus variable is 0
        analogWrite(motorPin, 0);    //Stop the motor
    }
    else if(stepStatus == 1) {    //If the stepStatus variable is 1
        analogWrite(motorPin, 255);    //Rotate motor full speed (1st step)
    }
    else if(stepStatus == 2) {    //If stepStatus variable is 2
        analogWrite(motorPin, 155);    //Decrease motor speed (2nd step)
    }
    else if(stepStatus == 3) {    //If stepStatus variable is 3
        analogWrite(motorPin, 75);    //Decrease motor speed a little more (3rd step)
    }
}

//Create a buttonControl function to check if the button is pressed
//This function will check whether the button is pressed or not inside the for loops
void buttonControl() {
    //Create variable last_interrupt_time and set its initial value to 0
    static unsigned long last_interrupt_time = 0;
    //Create a variable named interrupt_time and assign the system start time to it with the millis() command
    unsigned long interrupt_time = millis();
    
    //If the time difference between interrupt_time and last_interrupt_time is greater than 500ms
    //This process is used to prevent detection of multiple button presses.
    if(interrupt_time - last_interrupt_time > 500) {
        stepStatus++;    //Increment stepStatus variable by one
        if(stepStatus > 3) {    //If stepStatus variable is greater than 3
            stepStatus = 0;    //Set stepStatus variable value to 0
        }
    }
    last_interrupt_time = interrupt_time;    //Assign the value in the interrupt_time variable to the last_interrupt_time variable
}
