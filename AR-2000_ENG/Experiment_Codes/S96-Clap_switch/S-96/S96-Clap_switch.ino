//S96 - Clap switch

#include <FreqCount.h> //Add library required to measure frequency 

float frequency; //Define the variable to store the frequency value
int LEDPin = 8; //Define the pin number to which the LED is connected
int LEDStatus = 0; //Define the variable to store the LED status

void setup() {
    FreqCount.begin(100); //Start frequency measurement and take 100 sample values
    pinMode(LEDPin, OUTPUT); //Set the pin to which the LED is connected as output
}

void loop() {
    if(FreqCount.available()) { //If the system is working and the values are coming in the frequency measurement
        frequency = FreqCount.read()*10; //Multiply the measured value by 10 and save it in the frequency variable
    }

    if(frequency > 100 && LEDStatus == 0) { //If the frequency value is greater than 100 and LED is OFF
        digitalWrite(LEDPin, HIGH); //Turn ON the LED
        delay(300); //Wait for 300ms
        LEDStatus = 1; //Make the LEDStatus variable 1 (store the LED as ON)
    }
    else if(frequency > 100 && LEDStatus == 1) { //If the frequency value is greater than 100 and LED is ON
        digitalWrite(LEDPin, LOW); //Turn OFF the LED
        delay(300); //Wait for 300ms
        LEDStatus = 0; //Make the LEDStatus variable 0 (store the LED as OFF)
    }
}
