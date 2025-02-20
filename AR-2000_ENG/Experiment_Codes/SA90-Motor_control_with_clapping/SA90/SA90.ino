//SA90 - Motor control with clapping

#include <FreqCount.h>                    //Add library required to measure frequency 
float frequency;                          //Define the variable to store the frequency value
 
int motorPin = 10;                        //Define the pin number to which the motor is connected
int motorStatus = 0;                      //Define variable to store the motor status
int LEDPin = 12;                          //Define the pin to which the LED is connected
 
void setup() { 
    FreqCount.begin(100);                 //Start frequency measurement and take 100 sample values 
    pinMode(motorPin, OUTPUT);            //Set the pin to which the motor is connected as output
    pinMode(LEDPin, OUTPUT);              //Set the pin to which the LED is connected as output
}
 
void loop() {
    if(FreqCount.available()) {           //If the system is working and the values are coming in the frequency measurement
        frequency = FreqCount.read() * 10; //Assign the measured value to the frequency variable
    }

    if(frequency > 500) {                 //If frequency value is greater than 500 
        motorStatus++;                    //Increment motorStatus variable by 1 
        delay(200); 
        if(motorStatus > 1)               //If the motorStatus variable is greater than 1 
            motorStatus = 0;              //Set the value of the motorStatus variable to 0 
    }
    
    if(motorStatus == 1) {               //If the motorStatus variable is 1 
        digitalWrite(motorPin, HIGH);     //Energize the Motor 
        digitalWrite(LEDPin, HIGH);       //Turn ON the LED 
    }
    else {                               //If the motorStatus variable is 0 
        digitalWrite(motorPin, LOW);      //Stop the Motor 
        digitalWrite(LEDPin, LOW);        //Turn OFF the LED
    }
    delay(200);                          //Delay for 200ms
}
