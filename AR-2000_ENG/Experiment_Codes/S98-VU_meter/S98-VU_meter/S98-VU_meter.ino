//S98 - VU meter

#include <FreqCount.h> //Add library required to measure frequency 

float frequency; //Define the variable to store the frequency value
//Define the pin numbers to which the LEDs are connected
int LEDPin = 8;
int LEDPin2 = 9;
int LEDPin3 = 10;
int LEDPin4 = 11;
int LEDPin5 = 12;

void setup() {
    FreqCount.begin(100); //Start frequency measurement and take 100 sample values 
    //Set LEDs as output
    pinMode(LEDPin, OUTPUT);
    pinMode(LEDPin2, OUTPUT);
    pinMode(LEDPin3, OUTPUT);
    pinMode(LEDPin4, OUTPUT);
    pinMode(LEDPin5, OUTPUT);
}

void loop() {
    if(FreqCount.available()) { //If the system is working and the values are coming in the frequency measurement
        frequency = FreqCount.read()*10; //Multiply the measured value by 10 and save it in the frequency variable
    }
    if(frequency >= 16 && frequency < 60) { //If the frequency value is between 16 and 60 Hertz
        //Turn ON the Green LED
        digitalWrite(LEDPin, HIGH);
        digitalWrite(LEDPin2, LOW);
        digitalWrite(LEDPin3, LOW);
        digitalWrite(LEDPin4, LOW);
        digitalWrite(LEDPin5, LOW);
    }
    else if(frequency >= 60 && frequency < 150) { //If the frequency value is between 60 and 250 Hertz
        //Turn ON the two Green LEDs
        digitalWrite(LEDPin2, HIGH);
        digitalWrite(LEDPin, HIGH); 
        digitalWrite(LEDPin3, LOW);
        digitalWrite(LEDPin4, LOW);
        digitalWrite(LEDPin5, LOW);
    }
    else if(frequency >= 250 && frequency < 500) { //If the frequency value is between 250 and 500 Hertz
        //Turn ON the Green LEDs and Yellow LED
        digitalWrite(LEDPin3, HIGH);
        digitalWrite(LEDPin, HIGH);
        digitalWrite(LEDPin2, HIGH);
        digitalWrite(LEDPin4, LOW);
        digitalWrite(LEDPin5, LOW);
    }
    else if(frequency >= 500 && frequency < 750) { //If the frequency value is between 500 and 750 Hertz
        //Turn ON the Green LEDs, Yellow LED and Red LED
        digitalWrite(LEDPin4, HIGH);
        digitalWrite(LEDPin, HIGH);
        digitalWrite(LEDPin2, HIGH);
        digitalWrite(LEDPin3, HIGH);
        digitalWrite(LEDPin5, LOW);
    }
    else if(frequency >= 1000) { //If the frequency value is greater than 1000
        //Turn ON all LEDs 
        digitalWrite(LEDPin4, HIGH);
        digitalWrite(LEDPin, HIGH);
        digitalWrite(LEDPin2, HIGH);
        digitalWrite(LEDPin3, HIGH);
        digitalWrite(LEDPin5, HIGH);
    }
    else { //If none of the above conditions meet, turn OFF the LEDs 
        digitalWrite(LEDPin, LOW); 
        digitalWrite(LEDPin2, LOW);
        digitalWrite(LEDPin3, LOW);
        digitalWrite(LEDPin4, LOW);
        digitalWrite(LEDPin5, LOW);
    }
}
