//S31 - RGB LED control

//Define the digital pin numbers to which the LEDs are connected
int redLEDPin = 5;
int greenLEDPin = 4;
int blueLEDPin = 3;

//Define the digital pin number to which the Button is connected
int buttonPin = 2;

//Define the variable to store the Button status
int buttonStatus = 0;

//Define the variable to store the status of the LEDs
int LEDStatus = 0;

void setup() {
    //Set the pins to which the LEDs are connected as output
    pinMode(redLEDPin, OUTPUT);
    pinMode(greenLEDPin, OUTPUT);
    pinMode(blueLEDPin, OUTPUT);
    
    //Set the pin to which the Button is connected as input
    pinMode(buttonPin, INPUT);
    
    //Initially turn OFF all LEDs.
    digitalWrite(redLEDPin, HIGH);
    digitalWrite(greenLEDPin, HIGH);
    digitalWrite(blueLEDPin, HIGH);
}

void loop() {
    /*
     * NOTE: The RGB LED used in our set is common anode, meaning the power supply end is common.
     * In this case, in order to light the LEDs in the RGB LED module, it is necessary to make
     * the pin connected to that LED LOW. That is, when +5v supply is given to the place written
     * CA on the module and we make the pin connected to the LED digitalWrite(redLEDPin, LOW)
     * Red LED will turn ON
     */
    
    //Query button status and assign the value to buttonStatus variable
    buttonStatus = digitalRead(buttonPin);
    
    //Set the status of the LED according to the status of the Button
    if(buttonStatus == HIGH) { //If the Button is pressed
        //Move to the next LED state by incrementing the LEDStatus variable by one
        LEDStatus++;
        
        while(buttonStatus == HIGH) { //Wait as long as the Button is pressed
            buttonStatus = digitalRead(buttonPin); //Check if the Button is pressed
        }
    }
    
    //Select the LED colors to turn ON based on the LEDStatus variable
    if(LEDStatus == 1) {
        //Turn ON the Red LED, turn OFF the others.
        digitalWrite(redLEDPin, LOW);
        digitalWrite(greenLEDPin, HIGH);
        digitalWrite(blueLEDPin, HIGH);
    }
    else if(LEDStatus == 2) {
        //Turn ON the Green LED, turn OFF the others.
        digitalWrite(redLEDPin, HIGH);
        digitalWrite(greenLEDPin, LOW);
        digitalWrite(blueLEDPin, HIGH);
    }
    else if(LEDStatus == 3) {
        //Turn ON the Blue LED, turn OFF the others.
        digitalWrite(redLEDPin, HIGH);
        digitalWrite(greenLEDPin, HIGH);
        digitalWrite(blueLEDPin, LOW);
    }
    else if(LEDStatus == 4) {
        //Turn ON the Red and Green LED, turn OFF the other one.
        digitalWrite(redLEDPin, LOW);
        digitalWrite(greenLEDPin, LOW);
        digitalWrite(blueLEDPin, HIGH);
    }
    else if(LEDStatus == 5) {
        //Turn ON the Green and Blue LED, turn OFF the other one.
        digitalWrite(redLEDPin, HIGH);
        digitalWrite(greenLEDPin, LOW);
        digitalWrite(blueLEDPin, LOW);
    }
    else if(LEDStatus == 6) {
        //Turn ON all LEDs
        digitalWrite(redLEDPin, LOW);
        digitalWrite(greenLEDPin, LOW);
        digitalWrite(blueLEDPin, LOW);
        //Set the variable LEDStatus to its initial state
        LEDStatus = 0;
    }
}
