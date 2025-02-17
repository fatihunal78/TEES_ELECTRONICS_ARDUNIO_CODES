//S53 - Colour changing lamp depending on light level

//Define the digital pin numbers to which the LEDs are connected
int redLEDPin = 6;
int greenLEDPin = 5;
int blueLEDPin = 3;
//Define the pin number to which the Speaker is connected
int speakerPin = 8;
//Define the analog pin number to which the LDR is connected
int LDRPin = A0;
//Define the variable in which the light value will be stored
int light_value = 0;

void setup() {
    //Set the pins to which the LEDs are connected as output
    pinMode(redLEDPin, OUTPUT);
    pinMode(greenLEDPin, OUTPUT);
    pinMode(blueLEDPin, OUTPUT);
    //Set the pin to which the Speaker is connected as output
    pinMode(speakerPin, OUTPUT);
    //Initially turn OFF all LEDs.
    digitalWrite(redLEDPin, HIGH);
    digitalWrite(greenLEDPin, HIGH);
    digitalWrite(blueLEDPin, HIGH);
}

void loop() {
    //Read the measured light value from the analog pin and assign the value to light_value variable
    light_value = analogRead(LDRPin);
    delay(100);    //Wait for 100ms

    //Light value is read between 0-1023
    //The value is low in darkness and high in light. You can change the light levels as you wish.
    if(light_value < 300) {    //If the value is less than 300
        //Turn ON all LEDs
        digitalWrite(redLEDPin, LOW);
        digitalWrite(greenLEDPin, LOW);
        digitalWrite(blueLEDPin, LOW);
        //Generate the tone from the Speaker based on light value
        tone(speakerPin, light_value);
        delay(100);    //Wait for 100ms
    }
    else if(light_value < 400) {    //If the value is less than 400
        //Turn ON the Red LED, turn OFF the others.
        digitalWrite(redLEDPin, LOW);
        digitalWrite(greenLEDPin, HIGH);
        digitalWrite(blueLEDPin, HIGH);
        //Generate the tone from the Speaker based on light value
        tone(speakerPin, light_value);
        delay(100);    //Wait for 100ms
    }
    else if(light_value < 600) {    //If the value is lower than 600
        //Turn ON the Blue LED, turn OFF the others.
        digitalWrite(redLEDPin, HIGH);
        digitalWrite(greenLEDPin, HIGH);
        digitalWrite(blueLEDPin, LOW);
        //Generate the tone from the Speaker based on light value
        tone(speakerPin, light_value);
        delay(100);    //Wait for 100ms
    }
    else if(light_value < 1024) {    //If the value is lower than 1024
        //Turn ON the Green LED, turn OFF the others.
        digitalWrite(redLEDPin, HIGH);
        digitalWrite(greenLEDPin, LOW);
        digitalWrite(blueLEDPin, HIGH);
        //Generate the tone from the Speaker based on light value
        tone(speakerPin, light_value);
        delay(100);    //Wait for 100ms
    }
    noTone(speakerPin);    //Restore the Speaker pin
}
