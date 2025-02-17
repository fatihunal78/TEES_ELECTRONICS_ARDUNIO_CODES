//S36 - Automatic room lighting system

int doorPin = 3;     //Define the pin number to which the door contact is connected
int LEDPin = 7;      //Define the digital pin number to which the LED is connected
int LDRPin = A5;     //Define the analog pin number to which the LDR is connected
int buttonPin = 2;   //Define the pin number to which the Button is connected
int LEDStatus = 0;   //Define the variable that will store the LED state on or off

void setup() {
    pinMode(LEDPin, OUTPUT);         //Set the pin to which the LED is connected as output
    pinMode(doorPin, INPUT);         //Set the pin to which the door contact is connected as input
    pinMode(LDRPin, INPUT);          //Set LDR pin as input
    pinMode(buttonPin, INPUT_PULLUP); //Set the pin to which the Button is connected as input, activate the pull up resistor
}

void loop() {
    if(analogRead(LDRPin) <= 300) {  //If the value read from LDR is less than 300, that is, if the weather is dark
        if(digitalRead(doorPin) == LOW) {  //If the door is opened
            digitalWrite(LEDPin, HIGH);     //Turn ON the LED
            LEDStatus = 1;                  //Save the variable LEDStatus as the door opened
            while(1) {                      //Enter infinite loop
                buttonControl();            //Call the buttonControl() function to turn the LED ON and OFF with the Button whenever desired
                if(digitalRead(doorPin) == HIGH || analogRead(LDRPin) > 300) {  //If the door is closed or the weather is bright
                    break;                  //End infinite loop
                }
            }
        }
        else if(digitalRead(doorPin) == HIGH) {  //If the door is closed
            digitalWrite(LEDPin, LOW);           //Turn OFF the LED
            LEDStatus = 0;                       //Save the variable LEDStatus as the door closed
            while(1) {                           //Enter infinite loop
                buttonControl();                 //Call the buttonControl() function to turn the LED ON and OFF with the Button whenever desired
                if(digitalRead(doorPin) == LOW || analogRead(LDRPin) > 300) {  //If the door is open or the weather is bright
                    break;                       //Exit infinite loop
                }
            }
        }
    }
    else {  //if the weather is bright
        buttonControl();  //Call the buttonControl() function to turn the LED ON and OFF with the Button whenever desired
    }
}

void buttonControl() {  //Create the buttonControl() function to turn the LED ON and OFF when desired
    if(digitalRead(buttonPin) == LOW && LEDStatus == 0) {  //if the Button is pressed and the LED is OFF
        digitalWrite(LEDPin, HIGH);                         //Turn ON the LED
        LEDStatus = 1;                                     //Save the variable LEDStatus as the door opened
        while(digitalRead(buttonPin) == LOW);              //Wait as long as the Button is pressed
    }
    if(digitalRead(buttonPin) == LOW && LEDStatus == 1) {  //if the Button is pressed and the LED is ON
        digitalWrite(LEDPin, LOW);                          //Turn OFF the LED
        LEDStatus = 0;                                      //Save the variable LEDStatus as the door closed
        while(digitalRead(buttonPin) == LOW);               //Wait as long as the Button is pressed
    }
}
