//SA100 - Audible fire alarm

#include <math.h>              //Add the math library to calculate the data received from NTC

int buttonPin = 2;            //Define the digital pin number to which the Button is connected
int redLED = 3;               //Define the pin numbers to which the LEDs are connected
int greenLED = 4;
int NTCPin = A5;              //Define the pin number to which the NTC is connected
int fireStatus = 0;           //Define the variable to store the fire state
int alarmStatus = 0;          //Define the variable to store the alarm state
double temperature;           //Define the variable to store the temperature value

void setup() {
    pinMode(redLED, OUTPUT);      //Set the pin to which the LEDs are connected as output
    pinMode(greenLED, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);  //Set the pin to which the Button is connected as input
    Serial.begin(9600);
}

void loop() {
    //To convert the temperature value read from NTC to centigrade
    //Necessary mathematical operations are performed and this value is recorded in the temperature variable.
    temperature = log(((10240000 / analogRead(NTCPin)) - 10000));
    temperature = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temperature * temperature)) * temperature);
    temperature = temperature - 273.15;

    //Check whether the Button is pressed or not
    if(digitalRead(buttonPin) == LOW) {    //If the button is pressed
        if(alarmStatus == 0) {             //If the alarm is OFF
            alarmStatus = 1;               //Save the alarm status as ON
            digitalWrite(greenLED, HIGH);   //Turn ON the Green LED
        }
        else {
            alarmStatus = 0;               //Save the alarm status as OFF
            digitalWrite(greenLED, LOW);    //Turn OFF the Green LED
            digitalWrite(redLED, LOW);      //Turn OFF the Red LED
        }
        delay(500);                        //Wait for 500ms
    }

    if(alarmStatus == 1) {                 //If the alarm status is ON
        if(temperature > 45) {             //If the NTC value is higher than 45 Celsius degree
            Serial.println(1);
            digitalWrite(greenLED, LOW);    //Turn OFF the Green LED
            digitalWrite(redLED, HIGH);     //Turn ON the Red LED
            delay(250);                     //Wait for 250ms
            digitalWrite(redLED, LOW);      //Turn OFF the Red LED
            delay(250);                     //Wait for 250ms
        }
        else {
            Serial.println(0);
            digitalWrite(greenLED, HIGH);   //Turn ON the Green LED
            digitalWrite(redLED, LOW);      //Turn OFF the Red LED
        }
    }
    delay(50);                             //Wait for 50ms
}
