//S23 - Night light

//Define the digital pin number to which the LED is connected
int LEDPin = 3;
//Define the pin number to which the Button is connected 
int buttonPin = 2;
//Define the analog pin number to which the LDR is connected
int LDRPin = A5;
//Define the variable in which the light value will be stored
int light_value = 0;
//Define the variable that will hold the information about whether the LED is ON or OFF.
int LEDStatus = 0;

void setup() {
    //Set the pin to which the LED is connected as output
    pinMode(LEDPin, OUTPUT);
    //Set the buttonPin as input pin
    pinMode(buttonPin, INPUT_PULLUP); //We set it as input and activated the Pull Up resistor
}

void loop() {
    //Read the measured light value from the analog pin
    //and assign to light_value variable
    //Light value is read between 0-1023
    //The value is low in the dark,
    //High in light. You may change the value 300 
    //according to the brightness level you want.
    light_value = analogRead(LDRPin);
  
    if(digitalRead(buttonPin) == LOW) { //If the Button is pressed 
        if(LEDStatus == 0) { //If LEDStatus variable is 0 (if light is OFF)
            LEDStatus = 1; //Make the LEDStatus variable 1 (store the light status as ON)
        }
        else { //If the LEDStatus variable is 1 (if the light is ON)
            LEDStatus = 0; //Make the LEDStatus variable 0 (store the light status as OFF)
        }
    }
  
    if(LEDStatus == 1 || light_value <= 300) { //If LEDStatus variable is 1 or the value read from the LDR is less than or equal to 300 
                                               //Namely, if the Button is pressed or it is dark 
        digitalWrite(LEDPin, HIGH); //Turn ON the LED 
    }
    else if(LEDStatus == 0 || light_value > 300) { //If LEDStatus variable is 0 or the value read from the LDR is greater than 300 
                                                   //Namely, if the Button is pressed or the weather become bright 
        digitalWrite(LEDPin, LOW); //Turn OFF the LED 
    }
    delay(250); //Wait for 250ms
}
