//S42 - RGB LED control with potentiometer

//Since RGB LED is common anode (CA), its common part (CA) is connected to +5V supply.
//The red, green and blue LED pins are connected to PWM output numbers 6, 5 and 3
//Define the digital pin numbers to which the LEDs are connected
int redLEDPin = 6;
int greenLEDPin = 5;
int blueLEDPin = 3;

//Define the analog pin number to which the Potentiometer is connected
int potPin = A0;

//Define the variable to store the Potentiometer value
int potValue = 0;

void setup() {
    //Set the pins to which the LEDs are connected as output
    pinMode(redLEDPin, OUTPUT);
    pinMode(greenLEDPin, OUTPUT);
    pinMode(blueLEDPin, OUTPUT);
    
    //Initially turn OFF all LEDs.
    analogWrite(redLEDPin, 255);
    analogWrite(greenLEDPin, 255);
    analogWrite(blueLEDPin, 255);
}

void loop() {
    //Read the value of the Potentiometer and assign it to the potValue variable
    potValue = analogRead(potPin);
    
    //Change the colour of the LEDs according to the potValue
    if(potValue > 850) {
        analogWrite(redLEDPin, 255 - potValue + 850);
        analogWrite(greenLEDPin, 255 - potValue + 850);
        analogWrite(blueLEDPin, 255 - potValue + 850);
    }
    else if(potValue > 680) {
        analogWrite(redLEDPin, 0);
        analogWrite(greenLEDPin, 255);
        analogWrite(blueLEDPin, 255);
    }
    else if(potValue > 510) {
        analogWrite(redLEDPin, 255 - 143);
        analogWrite(greenLEDPin, 255);
        analogWrite(blueLEDPin, 0);
    }
    else if(potValue > 340) {
        analogWrite(redLEDPin, 255);
        analogWrite(greenLEDPin, 255);
        analogWrite(blueLEDPin, 255 - potValue + 340);
    }
    else if(potValue > 170) {
        analogWrite(redLEDPin, 255);
        analogWrite(greenLEDPin, 255 - potValue - 170);
        analogWrite(blueLEDPin, 255);
    }
    else if(potValue >= 0) {
        analogWrite(redLEDPin, 255 - potValue);
        analogWrite(greenLEDPin, 255);
        analogWrite(blueLEDPin, 255);
    }
}
