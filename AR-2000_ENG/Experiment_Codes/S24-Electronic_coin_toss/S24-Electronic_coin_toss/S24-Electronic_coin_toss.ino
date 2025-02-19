//S24 - Electronic coin toss

//Define the digital pin number to which the LEDs are connected
int greenPin = 3;
int redPin = 4;

//Define the digital pin number to which the Button is connected
int buttonPin = 2;

//Define the variable to store the Button status
int buttonStatus = 0;

//Define the variable to store the random number
int randomNumber = 0;

void setup() {
    //Set the pin to which the LED is connected as output
    pinMode(greenPin, OUTPUT);
    pinMode(redPin, OUTPUT);
    
    //Set the pin to which the Button is connected as input
    pinMode(buttonPin, INPUT);
}

void loop() {
    //Query button status and assign the value to buttonStatus variable
    buttonStatus = digitalRead(buttonPin);

    //Set the status of the LED according to the status of the Button
    if(buttonStatus == HIGH) { //If the Button is pressed
        //Animate for 3 second wait.
        for(int i=0; i < 15; i++) { //Repeat 15 times
            digitalWrite(greenPin, HIGH); //Turn ON the Green LED
            delay(100); //Wait for 100ms
            digitalWrite(greenPin, LOW); //Turn OFF the Green LED
            digitalWrite(redPin, HIGH); //Turn ON the Red LED
            delay(100); //Wait for 100ms
            digitalWrite(redPin, LOW); //Turn OFF the Red LED
        }
        
        randomSeed(analogRead(A0)); //Assign the timer variable to a random value for the Random function
        //set random number between 0-1
        randomNumber = random(0,2);
        
        if(randomNumber == 1) { //If the random number is 1, then it is Tails
            digitalWrite(redPin, LOW); //Turn OFF the Red LED
            digitalWrite(greenPin, HIGH); //Turn ON the Green LED
        }
        else { //If the random number is 0, it is Heads
            digitalWrite(greenPin, LOW); //Turn OFF the Green LED
            digitalWrite(redPin, HIGH); //Turn ON the Red LED
        }    
    }
}
