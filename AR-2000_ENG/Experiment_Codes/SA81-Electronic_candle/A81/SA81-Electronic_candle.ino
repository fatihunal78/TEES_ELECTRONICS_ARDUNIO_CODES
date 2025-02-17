//SA81 - Electronic candle

#include <FreqCount.h>                    //Add library required to measure frequency

float frequency;                          //Define the variable to store the frequency value
int LEDStatus = 0;                        //Define variable to store the LED status  
int LEDPin = 7;                          //Define the pin to which the LED is connected

void setup() {                
    FreqCount.begin(100);                //Start frequency measurement and take 100 sample values 
    pinMode(LEDPin, OUTPUT);             //Set the pin to which the LED is connected as output 
}
 
void loop() {
    if(FreqCount.available()) {          //If the system is working and the values are coming in the frequency measurement
        frequency = FreqCount.read() * 10; //Assign the measured value to the frequency variable
    }

    if(frequency > 500) {                //If frequency value is greater than 500 
        LEDStatus++;                     //Increment the LEDStatus variable by one 
        delay(200); 
        if(LEDStatus > 1)               //If the LEDStatus variable is greater than one 
            LEDStatus = 0;              //Set the LEDStatus variable value to 0 
    }

    if(LEDStatus == 1) {                //If the LEDStatus variable is 1 
        digitalWrite(LEDPin, HIGH);      //Turn ON the LED 
    }
    else {                              //If the LEDStatus variable is 0 
        digitalWrite(LEDPin, LOW);       //Turn OFF the LED
    }
    delay(200);                         //Delay for 200ms
}
