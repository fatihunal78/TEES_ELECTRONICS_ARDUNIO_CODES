//S55 - Direction recording and playback

#include <Servo.h>
#include <EEPROM.h>    //EEPROM library to save directions
Servo myServo;
float eeprom_register = 1000;    //EEPROM length must be less than 1024
int buttonPin = 3;              //Define the pin to which the Button is connected
//Define the pin numbers to which the LEDs are connected
int yellowLED = 5;
int greenLED = 6;
int record_duration;            //Define the variable that will keep track of how long the recording process has been in progress
int buttonStatus = 0;          //Define the variable to store the button pressed state

void setup() {
    pinMode(yellowLED, OUTPUT);    //Set the pin to which the Yellow LED is connected as output
    pinMode(greenLED, OUTPUT);     //Set the pin to which the Green LED is connected as output
    pinMode(buttonPin, INPUT);     //Set the pin to which the Button is connected as input
    myServo.attach(2);            //Set the pin to which the servo motor is connected
}

void loop() {
    if (digitalRead(buttonPin) == HIGH) {    //If the Button is pressed
        delay(200);                          //Wait for 200ms
        buttonStatus++;                      //Increment the buttonStatus variable by one
    }
    if (buttonStatus > 2) {                  //if buttonStatus variable is greater than 2
        buttonStatus = 0;                    //Set he buttonStatus variable to 0
    }

    if (buttonStatus == 0) {    //If the value of the button variable is 0
        for (int i = 0; i <= eeprom_register; i++) {    //Use a for loop to perform the save operation and increment the 
                                                        //variable i from zero to 1000 (eeprom_register value).
            digitalWrite(yellowLED, HIGH);    //Turn ON the yellow LED to indicate that recording has started
            digitalWrite(greenLED, LOW);      //Turn OFF the Green LED

            if (digitalRead(buttonPin) == HIGH) {    //If the Button is pressed during the recording process
                buttonStatus = 1;                    //make the buttonStatus variable 1, end recording and proceed to repeat
                                                    //the play (playback)
                record_duration = i;                 //When the button is pressed, transfer the value of the variable i to
                                                    //the record_duration variable
                delay(200);
                break;                              //End for loop, end recording
            }

            //Proportion the value read from the Potentiometer to the servo motor angle values. If the value 1023 received 
            //from the Potentiometer, this value will be 0 after proportion. If the value read from the Potentiometer is 
            //512, this value will be 90 after proportion
            int val = map(analogRead(A0), 0, 1023, 180, 0);

            EEPROM.write(i, val);    //Save the read values to eeprom in order (according to the increase in the i variable)
            myServo.write(val);      //Move the servo motor
            record_duration = i;      //Transfer the value of the variable i to the variable record_duration
            delay(10);               //Wait for 10ms
        }
        buttonStatus = 1;    //Set the buttonStatus variable to 1 and go into repeat (playback) mode.
    }
    else {    //If the value of the buttonStatus is other than 0
        digitalWrite(yellowLED, LOW);     //Turn OFF the Yellow LED
        digitalWrite(greenLED, HIGH);     //Turn ON the Green LED to indicate that it is in repeat (playback) mode.

        for (int i = 0; i <= record_duration; i++) {    //Use a for loop to repeat the process and increment the variable i
                                                        //by one from zero to the record duration (record_duration).
            if (digitalRead(buttonPin) == HIGH) {    //If the Button is pressed again
                buttonStatus = 0;                    //Set the buttonStatus variable to 0 to switch to recording mode
                delay(200);
                break;                              //End the for loop and stop the playback
            }
            int readValue = EEPROM.read(i);    //Save the stored value in Eeprom to the "readValue" variable
            myServo.write(readValue);          //write the value saved in readValue variable to the servo
            delay(10);                         //Wait for 10ms
        }

        //Flash the LED to show the playback
        digitalWrite(greenLED, HIGH);    //Turn ON the Green LED
        delay(100);                      //Wait for 100ms
        digitalWrite(greenLED, LOW);     //Turn OFF the Green LED
        delay(100);                      //Wait for 100ms
    }
}
