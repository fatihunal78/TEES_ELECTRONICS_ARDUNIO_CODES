//S67 - Fire alarm

//Add math.h library
#include <math.h>    //We added the math library to calculate the data received from NTC.

//Define the digital pin number to which the Button is connected
int buttonPin = 2;
//Define the pin numbers to which the LEDs are connected
int redLED = 8;
int greenLED = 9;
//Define the pin number to which the Speaker is connected
int speakerPin = 3;
//Define the pin number to which the NTC is connected
int NTCPin = A5;
//Define the variable to store the fire state
int fireStatus = 0;
//Define the variable to store the alarm state
int alarmStatus = 0;
//Define the variable to store the temperature value
double temperature;

void setup() {
    //Set the pin to which the LEDs are connected as output
    pinMode(redLED, OUTPUT);
    pinMode(greenLED, OUTPUT);
    //Set the pin to which the Speaker is connected as output
    pinMode(speakerPin, OUTPUT);
    //Set the pin to which the Button is connected as input
    pinMode(buttonPin, INPUT);
}

void loop() {
    //To convert the temperature value read from NTC to centigrade
    //Perform the necessary mathematical calculations and save the resulting value in the temperature variable
    temperature = log(((10240000 / analogRead(NTCPin)) - 10000));
    temperature = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temperature * temperature)) * temperature);
    temperature = temperature - 273.15;

    //Check whether the Button is pressed or not
    if(digitalRead(buttonPin) == HIGH) {    //If the Button is pressed
        if(alarmStatus == 0) {    //If the alarm is OFF
            alarmStatus = 1;    //Save the alarm status as ON
            digitalWrite(greenLED, HIGH);    //Turn ON the Green LED
        }
        else {
            alarmStatus = 0;    //Save the alarm status as OFF
            digitalWrite(greenLED, LOW);    //Turn OFF the Green LED
            digitalWrite(redLED, LOW);    //Turn OFF the Red LED
        }
        delay(500);    //Wait for 500ms
    }

    if(alarmStatus == 1) {    //If the alarm status is ON
        if(temperature > 45) {    //If the NTC value is higher than 45 Celsius degree
            tone(speakerPin, 250);    //Play alarm sound from speaker
            digitalWrite(redLED, HIGH);    //Turn ON the Red LED
            delay(250);    //Wait for 250ms
            noTone(speakerPin);    //Mute the Speaker
            digitalWrite(redLED, LOW);    //Turn OFF the Red LED
            delay(250);    //Wait for 250ms
        }
    }
    delay(50);    //Wait for 50ms
}
