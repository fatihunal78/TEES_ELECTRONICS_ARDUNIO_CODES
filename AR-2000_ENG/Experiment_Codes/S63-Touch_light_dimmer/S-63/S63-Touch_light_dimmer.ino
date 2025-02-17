//S63 - Touch light dimmer

int LEDPin = 5;              //Define the digital pin number to which the LED is connected
int touchPin = 2;            //Define the digital pin number to which the touch button is connected
int buttonStatus = 0;        //Define the variable to store the touch button state
int LEDStatus = 0;          //Define variable to store the LED status
int LEDBrightness = 0;      //Define the variable to store the LED brightness
int LEDControlStatus = 0;    //Define the variable to store the LED dimming status

void setup() {
    //Set the pin to which the LED is connected as output
    pinMode(LEDPin, OUTPUT);
    //Set the pin to which the touch button is connected as input 
    pinMode(touchPin, INPUT);
}

void loop() {
    //Query the touch button status and assign the value to buttonStatus variable
    buttonStatus = digitalRead(touchPin);

    //Set the status of the LED according to the status of the touch button
    if(buttonStatus == LOW) {    //If the touch button is pressed
        if(LEDStatus == 0) {     //If the LED is OFF
            delay(500);          //Wait for 500ms
            if(digitalRead(touchPin) == HIGH) {    //If the touch button is released
                LEDBrightness = 255;               //Turn ON the LED at maximum brightness
                analogWrite(LEDPin, LEDBrightness); //Turn ON the LED according to the brightness value
                delay(500);                        //Wait for 500ms
            }
            else {    //If the touch button is not released
                while(digitalRead(touchPin) == LOW) {    //If the touch button is still pressed
                    LEDBrightness += 25;                //Increase LEDBrightness value by 25
                    if(LEDBrightness > 255) {          //If LEDBrightness value is greater than 255
                        LEDBrightness = 255;           //Set LEDBrightness value to 255
                    }
                    analogWrite(LEDPin, LEDBrightness); //Turn ON the LED according to the LEDBrightness value
                    delay(250);                        //Wait for 250ms
                }
            }
            LEDControlStatus = 1;    //Save the LED setting status as increase
            LEDStatus = 1;           //Save the LED status as ON
        }
        else {    //If the LED is ON
            delay(500);    //Wait for 500ms
            if(digitalRead(touchPin) == HIGH) {    //If the touch button is released
                LEDBrightness = 0;                 //Set LEDBrightness value to minimum
                analogWrite(LEDPin, LEDBrightness); //Turn ON the LED according to the brightness value
                LEDStatus = 0;                     //Save the LED status as OFF 
                delay(500);                        //Wait for 500ms
            }
            else {    //If the touch button is not released
                while(digitalRead(touchPin) == LOW) {    //If the touch button is still pressed
                    if(LEDControlStatus == 0) {         //If there is an increase from dim to high light
                        LEDBrightness += 25;           //Increase LEDBrightness value by 25
                        if(LEDBrightness > 255) {      //If LEDBrightness value is greater than 255
                            LEDBrightness = 255;       //Set LEDBrightness value to 255
                        }
                    }
                    else {
                        LEDBrightness -= 25;           //Decrease LEDBrightness value by 25
                        if(LEDBrightness < 0) {        //If LEDBrightness value is less than 0
                            LEDBrightness = 0;         //Set LEDBrightness value to 0
                            LEDStatus = 0;             //Save the LED status as OFF 
                        }
                    }
                    analogWrite(LEDPin, LEDBrightness);
                    delay(250);                        //Wait for 250ms
                }
                if(LEDControlStatus == 0) {           //If LED setting is set to decrease
                    LEDControlStatus = 1;             //Save the LED setting status as increase
                }
                else {
                    LEDControlStatus = 0;             //Save the LED setting status as decrease
                }
            }
        }
    }
}
