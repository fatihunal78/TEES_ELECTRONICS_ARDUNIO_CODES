//SA88 - Disco light

#include <FreqCount.h>                                //Add library required to measure frequency 
float frequency;                                      //Define the variable to store the frequency value

int red_LED = 12;                                    //Define the pin number to which the Disco Light module Red LED is connected
int yellow_LED = 11;                                 //Define the pin number to which the Disco Light module Yellow LED is connected
int green_LED = 10;                                  //Define the pin number to which the Disco Light module Green LED is connected
int blue_LED = 9;                                    //Define the pin number to which the Disco Light module Blue LED is connected
 
void setup() { 
    FreqCount.begin(100);                            //Start frequency measurement and take 100 sample values 
  
    pinMode(red_LED, OUTPUT);                        //Set the pin to which the Red LED is connected as output 
    pinMode(yellow_LED, OUTPUT);                     //Set the pin to which the Yellow LED is connected as output
    pinMode(green_LED, OUTPUT);                      //Set the pin to which the Green LED is connected as output
    pinMode(blue_LED, OUTPUT);                       //Set the pin to which the Blue LED is connected as the output
}
 
void loop() {
    if(FreqCount.available()) {                      //If the system is working and the values are coming in the frequency measurement
        frequency = FreqCount.read() * 10;           //Assign the measured value to the frequency variable
    }

    int proportion = map(frequency, 60, 10000, 0, 16);

    switch(proportion) {
        case 0:                                      //When proportion value is 0 
            //Turn OFF all LEDs 
            digitalWrite(red_LED, LOW);
            digitalWrite(yellow_LED, LOW);
            digitalWrite(green_LED, LOW);
            digitalWrite(blue_LED, LOW);
            break;

        case 1:                                      //When proportion value is 1 
            //Turn ON the Red LED, turn OFF the others 
            digitalWrite(red_LED, HIGH);
            digitalWrite(yellow_LED, LOW);
            digitalWrite(green_LED, LOW);
            digitalWrite(blue_LED, LOW);
            break;

        case 2:                                      //When proportion value is 2 
            //Turn ON the Yellow LED, turn OFF the others. 
            digitalWrite(red_LED, LOW);
            digitalWrite(yellow_LED, HIGH);
            digitalWrite(green_LED, LOW);
            digitalWrite(blue_LED, LOW);
            break;

        case 3:                                      //When proportion value is 3 
            //Turn ON the Green LED, turn OFF the others 
            digitalWrite(red_LED, LOW);
            digitalWrite(yellow_LED, LOW);
            digitalWrite(green_LED, HIGH);
            digitalWrite(blue_LED, LOW);
            break;

        case 4:                                      //When proportion value is 4 
            //Turn ON the Blue LED, turn OFF the others 
            digitalWrite(red_LED, LOW);
            digitalWrite(yellow_LED, LOW);
            digitalWrite(green_LED, LOW);
            digitalWrite(blue_LED, HIGH);
            break;

        case 5:                                      //When proportion value is 5 
            //Turn ON the Red and Yellow LED, turn OFF the others 
            digitalWrite(red_LED, HIGH);
            digitalWrite(yellow_LED, HIGH);
            digitalWrite(green_LED, LOW);
            digitalWrite(blue_LED, LOW);
            break;

        case 6:                                      //When proportion value is 6 
            //Turn ON the Red and Green LED, turn OFF the others 
            digitalWrite(red_LED, HIGH);
            digitalWrite(yellow_LED, LOW);
            digitalWrite(green_LED, HIGH);
            digitalWrite(blue_LED, LOW);
            break;

        case 7:                                      //When proportion value is 7 
            //Turn ON the Red and Blue LED, turn OFF the others 
            digitalWrite(red_LED, HIGH);
            digitalWrite(yellow_LED, LOW);
            digitalWrite(green_LED, LOW);
            digitalWrite(blue_LED, HIGH);
            break;

        case 8:                                      //When proportion value is 8 
            //Turn ON the Yellow and Green LED, turn OFF the others 
            digitalWrite(red_LED, LOW);
            digitalWrite(yellow_LED, HIGH);
            digitalWrite(green_LED, HIGH);
            digitalWrite(blue_LED, LOW);
            break;

        case 9:                                      //When proportion value is 9 
            //Turn ON the Yellow and Blue LED, turn OFF the others 
            digitalWrite(red_LED, LOW);
            digitalWrite(yellow_LED, HIGH);
            digitalWrite(green_LED, LOW);
            digitalWrite(blue_LED, HIGH);
            break;

        case 10:                                     //When proportion value is 10 
            //Turn ON the Green and Blue LED, turn OFF the others 
            digitalWrite(red_LED, LOW);
            digitalWrite(yellow_LED, LOW);
            digitalWrite(green_LED, HIGH);
            digitalWrite(blue_LED, HIGH);
            break;

        case 11:                                     //When proportion value is 11 
            //Turn ON the Red, Yellow and Green LED and turn OFF the others 
            digitalWrite(red_LED, HIGH);
            digitalWrite(yellow_LED, HIGH);
            digitalWrite(green_LED, HIGH);
            digitalWrite(blue_LED, LOW);
            break;

        case 12:                                     //When proportion value is 12 
            //Turn ON the Red, Yellow and Blue LED, turn OFF the others 
            digitalWrite(red_LED, HIGH);
            digitalWrite(yellow_LED, HIGH);
            digitalWrite(green_LED, LOW);
            digitalWrite(blue_LED, HIGH);
            break;

        case 13:                                     //When proportion value is 13 
            //Turn ON the Red, Green and Blue LED, turn OFF the others 
            digitalWrite(red_LED, HIGH);
            digitalWrite(yellow_LED, LOW);
            digitalWrite(green_LED, HIGH);
            digitalWrite(blue_LED, HIGH);
            break;

        case 14:                                     //When proportion value is 14 
            //Turn ON the Yellow, Green and Blue LED, turn OFF the others 
            digitalWrite(red_LED, LOW);
            digitalWrite(yellow_LED, HIGH);
            digitalWrite(green_LED, HIGH);
            digitalWrite(blue_LED, HIGH);
            break;

        case 15:                                     //When proportion value is 15 
            //Turn ON all LEDs
            digitalWrite(red_LED, HIGH);
            digitalWrite(yellow_LED, HIGH);
            digitalWrite(green_LED, HIGH);
            digitalWrite(blue_LED, HIGH);
            break;
    } 
}
