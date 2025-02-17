//SA14 - LED control with remote control

#include <IRremote.h>          //Add IR receiver library

//Define IR control codes
#define LEDOpenClose  0xFF38C7 //IR Control OK Key
#define LEDDecrease  0xFF4AB5  //IR Control Down key
#define LEDIncrease  0xFF18E7  //IR Control Up key
#define repeat  0xFFFFFFFF     //If the pressed key is pressed continuously

int LEDPin = 5;               //Define the digital pin number to which the LED is connected
int IRPin = 2;                //Define the pin to which the IR receiver signal leg is connected

IRrecv IRReceive(IRPin);      //Define an IR Receiver named IRReceive
decode_results result;        //Define variable to store values received from IR receiver

int brightness = 0;           //Define the variable where we will store the brightness value of the LED.
int LEDStatus = 0;           //Define variable to store the LED status
int lastKey = 0;             //Define the variable to store the last key pressed

void setup() {
    IRReceive.enableIRIn();   //Start IR receiver
    pinMode(LEDPin, OUTPUT);  //Set the pin to which the LED is connected as output
}

void loop() {
    //Check if there is any information coming from IR receiver
    if(IRReceive.decode(&result)) {
        if(result.value == repeat) {  //If the same key is pressed again
            if(lastKey == 2) {        //If the last key pressed is LEDIncrease
                result.value = LEDIncrease;
            }
            else if(lastKey == 3) {   //If the last key pressed is LEDDecrease
                result.value = LEDDecrease;
            }
        }
        
        if(result.value == LEDOpenClose) {  //If the key pressed is LEDOpenClose
            lastKey = 1;                    //Set lastKey variable to 1
            if(LEDStatus == 0) {            //If the LED is OFF 
                analogWrite(LEDPin, 255);    //Turn ON the LED as maximum
                brightness = 255;            //Set its brightness value to 255
                LEDStatus = 1;               //Save the LED status as ON
            }
            else {
                analogWrite(LEDPin, 0);      //Turn OFF the LED
                brightness = 0;              //Set brightness value to 0
                LEDStatus = 0;               //Save the LED status as OFF
            }
        }
        else if(result.value == LEDIncrease) {  //If the key pressed is LEDIncrease
            lastKey = 2;                        //Set lastKey variable to 2
            LEDStatus = 1;                      //Save the LED status as ON
            brightness += 50;                    //Increase brightness value by 50
            if(brightness > 255) {              //If the brightness value is greater than 255
                brightness = 255;                //Set its brightness value to 255
            }
            analogWrite(LEDPin, brightness);     //Turn ON the LED according to the brightness value
        }
        else if(result.value == LEDDecrease) {  //If the key pressed is LEDDecrease
            lastKey = 3;                        //Set lastKey variable to 3
            brightness -= 50;                    //Decrease brightness value by 50
            if(brightness < 0) {                //If the brightness value is less than 0
                brightness = 0;                  //Set brightness value to 0
                LEDStatus = 0;                  //Save the LED status as OFF
            }
            analogWrite(LEDPin, brightness);     //Turn ON the LED according to the brightness value
        }
        else {                                  //If an undefined key is pressed
            lastKey = 0;                        //Set lastKey variable to 0
        }
        
        delay(200);                            //Wait for 200ms
        IRReceive.resume();                    //Reset IR receiver to get other values 
    }
}
