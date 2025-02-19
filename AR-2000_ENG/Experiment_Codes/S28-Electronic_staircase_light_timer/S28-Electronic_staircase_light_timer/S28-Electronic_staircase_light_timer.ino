//S28 - Electronic staircase light timer

//Define the digital pin number to which the LEDs are connected
int whitePin = 7;
int yellowPin = 6;
int redPin = 5;
int greenPin = 4;

//Define the digital pin number to which the Button is connected
int buttonPin = 2;

//Define the variable to store the Button status
int buttonStatus = 0;

void setup() {
    //Set the pin to which the LED is connected as output
    pinMode(whitePin, OUTPUT);
    pinMode(yellowPin, OUTPUT);
    pinMode(redPin, OUTPUT);
    pinMode(greenPin, OUTPUT);
    
    //Set the pin to which the Button is connected as input
    pinMode(buttonPin, INPUT);
}

void loop() {
    //Query button status and assign the value to buttonStatus variable
    buttonStatus = digitalRead(buttonPin);
    
    //Set the status of the LED according to the status of the Button
    if(buttonStatus == HIGH) { //If the Button is pressed
        //Turn ON the LEDs
        digitalWrite(whitePin, HIGH);
        digitalWrite(yellowPin, HIGH);
        digitalWrite(redPin, HIGH);
        digitalWrite(greenPin, HIGH);
        
        //Turn OFF the LEDs sequentially
        delay(5000);                      //Wait for 5 seconds
        digitalWrite(greenPin, LOW);      //Turn OFF the Green LED
        delay(5000);                      //Wait for 5 seconds
        digitalWrite(redPin, LOW);        //Turn OFF the Red LED
        delay(5000);                      //Wait for 5 seconds
        digitalWrite(yellowPin, LOW);     //Turn OFF the yellow LED
        delay(5000);                      //Wait for 5 seconds
        digitalWrite(whitePin, LOW);      //Turn OFF the White LED
    }
}
