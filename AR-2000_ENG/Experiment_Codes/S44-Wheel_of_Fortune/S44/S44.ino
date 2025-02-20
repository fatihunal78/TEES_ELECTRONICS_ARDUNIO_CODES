//S44 - Wheel of Fortune

//Define the pin number to which the transistor driving the Motor is connected
int motorPin = 3;
//Define the pin number to which the rotation button is connected
int rotateButtonPin = 2;
//Define the variable to store the waiting time
int waitTime = 0;
//Define the variable to store the speed state
int speedStatus = 0;

void setup() {
    //Set the pin to which the transistor driving the Motor is connected as output
    pinMode(motorPin, OUTPUT);
    //Set the pin to which the rotation button is connected as input
    pinMode(rotateButtonPin, INPUT);
}

void loop() {
    //Check the status of the rotation button
    if(digitalRead(rotateButtonPin) == HIGH) {    //If the Button is pressed
        //Set a value between 2 seconds and 4 seconds and assign that value to the waitTime variable
        waitTime = random(2000, 4000);
        //Rotate the Motor at top speed
        analogWrite(motorPin, 255);
        delay(waitTime/3);    //Wait
        //Decrease the speed of the Motor
        analogWrite(motorPin, 180);
        delay(2 * waitTime / 3);    //Wait
        //Decrease the speed of the Motor
        analogWrite(motorPin, 75);
        delay(1000);    //Wait
        //Stop the Motor
        analogWrite(motorPin, 0);
    }
}