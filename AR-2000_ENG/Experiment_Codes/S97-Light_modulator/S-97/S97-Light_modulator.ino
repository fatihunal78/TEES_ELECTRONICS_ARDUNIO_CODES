//S97 - Light modulator

#include <FreqCount.h> //Add library required to measure frequency 

float frequency; //Define the variable to store the frequency value
//Define the pin numbers to which the LEDs are connected
int RGB_red = 8;
int RGB_green = 9;
int RGB_blue = 10;

void setup() {
    FreqCount.begin(100); //Start frequency measurement and take 100 sample values 
    //Set the pin to which the LEDs are connected as output
    pinMode(RGB_red, OUTPUT);
    pinMode(RGB_green, OUTPUT);
    pinMode(RGB_blue, OUTPUT);
}

void loop() {
    if(FreqCount.available()) { //If the system is working and the values are coming in the frequency measurement
        frequency = FreqCount.read()*10; //Multiply the measured value by 10 and save it in the frequency variable
    }
    if(frequency >= 16 && frequency < 60) { //If the frequency value is between 16 and 60 Hertz
                                           //Turn ON the Red LED
        digitalWrite(RGB_red, LOW);
        digitalWrite(RGB_green, HIGH);
        digitalWrite(RGB_blue, HIGH);
    }
    else if(frequency >= 60 && frequency < 150) { //If frequency value is between 60 and 150 Hertz
                                                 //Turn ON the Green LED
        digitalWrite(RGB_red, HIGH);
        digitalWrite(RGB_green, LOW);
        digitalWrite(RGB_blue, HIGH);
    }
    else if(frequency >= 150 && frequency < 350) { //If the frequency value is between 150 and 350 Hertz
                                                  //Turn ON the Blue LED
        digitalWrite(RGB_red, HIGH);
        digitalWrite(RGB_green, HIGH);
        digitalWrite(RGB_blue, LOW);
    }
    else if(frequency >= 350 && frequency < 500) { //If the frequency value is between 350 and 500 Hertz
                                                  //Turn ON the Red and Green LED
        digitalWrite(RGB_red, LOW);
        digitalWrite(RGB_green, LOW);
        digitalWrite(RGB_blue, HIGH);
    }
    else if(frequency >= 500 && frequency < 750) { //If the frequency value is between 500 and 750 Hertz
                                                  //Turn ON the Red and Blue LED
        digitalWrite(RGB_red, LOW);
        digitalWrite(RGB_green, HIGH);
        digitalWrite(RGB_blue, LOW);
    }
    else if(frequency >= 750 && frequency < 1000) { //If the frequency value is between 750 and 1000 Hertz
                                                   //Turn ON the Green and Blue LED
        digitalWrite(RGB_red, HIGH);
        digitalWrite(RGB_green, LOW);
        digitalWrite(RGB_blue, LOW);
    }
    else if(frequency >= 1000) { //If the frequency value is greater than 1000
        //Turn ON all LEDs
        digitalWrite(RGB_red, LOW);
        digitalWrite(RGB_green, LOW);
        digitalWrite(RGB_blue, LOW);
    }
    else { //If none of the above conditions meet, turn OFF the LEDs
        digitalWrite(RGB_red, HIGH);
        digitalWrite(RGB_green, HIGH);
        digitalWrite(RGB_blue, HIGH);
    }
}
