//S43 - Fan
int motorPin = 3;    //Define the pin to which the Motor is connected
int buttonPin = 2;    //Define the pin to which the Button is connected
boolean motorStatus = 0;    //Define the variable that will store the value of whether the motor is ON or OFF
                          //0--> motor OFF (not rotating), 1--> motor ON (rotating)
boolean buttonStatus = LOW;    //Define the variable that will store whether the button is pressed or not

void setup() {
    pinMode(motorPin, OUTPUT);    //Set the Motor pin as output
    pinMode(buttonPin, INPUT);    //Set the pin to which the Button is connected as input
    //Set the pin to which the button is connected as Interrupt. When the button is pressed, perform the 
    //operation in the buttonQuery function. Trigger at RISING (Rising Edge)
    attachInterrupt(digitalPinToInterrupt(buttonPin), buttonQuery, RISING);
}

void loop() {
    if(motorStatus == 1) {    //If the motorStatus variable is 1
        digitalWrite(motorPin, HIGH);    //rotate the Motor
    }
    else {    //If the motorStatus variable is 0
        digitalWrite(motorPin, LOW);    //stop the Motor
    }
}

void buttonQuery() {    //Define the Interrupt function. Perform the operation in the function when the Button 
                       //is pressed
    //If the motorStatus variable is 0, set it to 1, if it is 1, set it to 0. If the Motor is rotating, that
    //is, if the motorStatus variable is 1, set it to 0. If the motor is not rotating, that is, if the 
    //motorStatus variable is 0, set it to 1.
    motorStatus = !motorStatus;
}
