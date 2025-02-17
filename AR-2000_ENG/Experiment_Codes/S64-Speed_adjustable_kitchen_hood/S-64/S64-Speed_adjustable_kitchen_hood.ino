//S64 - Speed adjustable kitchen hood

//Define the pin number to which the transistor driving the Motor is connected
int motorPin = 3;
//Define the pin number to which the Potentiometer is connected
int potentiometerPin = A0;
//Define the variable to store the speed state
int speedStatus = 0;
//Define the variable to store the hood status
int hoodStatus = 0;

void setup() {
    //Set the pin to which the transistor is connected as output
    pinMode(motorPin, OUTPUT);
    //Set the pin to which the Potentiometer is connected as input
    pinMode(potentiometerPin, INPUT);
}

void loop() {
    //Check the Potentiometer status
    speedStatus = analogRead(potentiometerPin);
    //Proportion the value read from the Potentiometer to the speed of the motor
    speedStatus = map(speedStatus, 0, 1023, 100, 255);

    if(hoodStatus == 0) {    //If the hood is not working
        if(speedStatus > 104) {
            //Set the motor speed to maximum power so that the motor can accelerate
            analogWrite(motorPin, 255);
            delay(50);    //Wait for 50ms
            //Adjust the motor speed according to the set speed value.
            analogWrite(motorPin, speedStatus);
            hoodStatus = 1;    //Save the hood status as ON
        }
    }
    else {    //If the hood is running
        if(speedStatus < 105) {    //If the speedStatus is less than 105
            //Turn OFF the Motor
            analogWrite(motorPin, 0);
            hoodStatus = 0;    //Save the hood as OFF
        }
        else {
            //Adjust the motor speed according to the set speed value.
            analogWrite(motorPin, speedStatus);
        }
        delay(50);    //Wait for 50ms
    }
}
