//SA96 - Processing LED matrix

#include <LedControl.h>

//Define LED Matrix connections
int DIN = 4;                    //Define DIN pin
int CS = 3;                     //Define CS pin
int CLK = 2;                    //Define CLK pin

int LED_Matrix_Count = 1;       //LED matrices can be connected in series
                               //If more than one matrix is to be connected, you can change the number here

LedControl lc = LedControl(DIN, CLK, CS, LED_Matrix_Count);    //Define the matrix lc with matrix pin connections

int incoming_data[8] = {};      //Define the variable to store the data coming from Processing

void setup() {
    lc.shutdown(0, false);      //Turn OFF LED matrix sleep mode
    lc.setIntensity(0, 8);      //Set brightness to 8
    lc.clearDisplay(0);         //Clear the LCD screen
    Serial.begin(9600);
}

void loop() {
    if(Serial.available() > 0) {    //If processing is started 
        for(int i=0; i<8; i++) {    //For loop from 0 to 8
            while(Serial.available() == 0) {}    //As long as serial communication is open
            incoming_data[i] = Serial.read();    //Save data read from serial communication to incoming_data variable
        }
        
        for(int i=0; i<8; i++) {    //For loop from 0 to 8
            lc.setColumn(0, i%8, incoming_data[i]);    //Transfer the data from incoming_data to the LED matrix
        }
        delay(100);
    }
}
