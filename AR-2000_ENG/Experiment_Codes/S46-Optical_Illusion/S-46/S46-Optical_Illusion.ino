//S46 - Optical Illusion
int PotPin = A0;    //Define the pin to which the Potentiometer is connected
int motorPin = 5;    //Define the pin to which the Motor is connected

int potValue;    //Define the variable to store the value read from the Potentiometer

void setup() {
    pinMode(PotPin, INPUT);    //Set the pin to which the Potentiometer is connected as input
    pinMode(motorPin, OUTPUT);    //Set the pin to which the motor is connected as output
}

void loop() {
    potValue = analogRead(PotPin);    //Save value read from analog A0 pin to potValue variable 
    int proportion = map(potValue, 0, 1023, 0, 255);    //Proportion the value between 0 and 1023 read from 
                                                        //the analog pin to between 0 and 255.
    analogWrite(motorPin, proportion);    //Adjust motor rotation speed by proportion variable
}
