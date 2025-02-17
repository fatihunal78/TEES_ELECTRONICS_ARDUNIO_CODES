//SA59 - Illuminated warning sign with LED matrix

#include <MaxMatrix.h>                                    //Add library

int DIN = 4;                                             //Define DIN pin
int CS = 3;                                              //Define CS pin 
int CLK = 2;                                             //Define CLK pin

int LED_Matrix_Count = 1;                                //LED matrices can be connected in series
                                                        //If more than one matrix is to be connected, 
                                                        //you can change the number here
MaxMatrix m(DIN, CS, CLK, LED_Matrix_Count);            //Define matrix m with matrix pin connections 

char warning_sign[] = {8, 8,                            //Arrow codes for warning sign
    0x3C, 0x42, 0x95, 0xA1, 0xA1, 0x95, 0x42, 0x3C
};

int wait_time = 200;                                    //Define the variable that will hold the duration for which the LEDs will light up
int ADCPin = A5;                                        //Define the pin number to which the ADC is connected
int readValue;                                          //define the variable to keep the value read from ADC

void setup() {
    m.init();                                          //Start the LED matrix
    m.setIntensity(8);                                 //Brightness is adjustable from 0 to 15
}

void loop() {
    readValue = analogRead(ADCPin);                    //Read signal in ADC connected to analog pin and save it to readValue variable
    if(readValue <= 350) {                            //if readValue is less than or equal to 350 
                                                      //If the light falling on it has decreased (if it is night), do the following:
        for(int i=0; i<3; i++) {                     //Loop to repeat 3 times 
                                                     //For the Arrow shape to light up slowly from the beginning to the end 
                                                     //Turn ON the LEDs one by one and put a delay between them and repeat 3 times
            m.setDot(0, 3, true);                    //This function can be used to turn ON a single LED
            m.setDot(0, 4, true); 
            delay(wait_time);
            m.setDot(1, 3, true); 
            m.setDot(1, 4, true); 
            delay(wait_time);
            m.setDot(2, 3, true); 
            m.setDot(2, 4, true); 
            delay(wait_time);
            m.setDot(3, 0, true); 
            m.setDot(3, 1, true); 
            m.setDot(3, 2, true); 
            m.setDot(3, 3, true); 
            m.setDot(3, 4, true); 
            m.setDot(3, 5, true); 
            m.setDot(3, 6, true); 
            m.setDot(3, 7, true); 
            delay(wait_time);
            m.setDot(4, 1, true); 
            m.setDot(4, 2, true); 
            m.setDot(4, 3, true); 
            m.setDot(4, 4, true); 
            m.setDot(4, 5, true); 
            m.setDot(4, 6, true); 
            delay(wait_time);
            m.setDot(5, 2, true); 
            m.setDot(5, 3, true); 
            m.setDot(5, 4, true); 
            m.setDot(5, 5, true); 
            delay(wait_time);
            m.setDot(6, 3, true); 
            m.setDot(6, 4, true); 
            m.setDot(6, 5, true); 
            delay(wait_time); 
            m.setDot(7, 4, true); 
            delay(wait_time);
            m.clear();                               //Function required to clean the screen, turn OFF all LEDs
        }
    
        for(int j=0; j<3; j++) {                    //Loop to repeat 3 times 
                                                    //Turn ON the necessary LEDs to create the Arrow shape
                                                    //Flash them with half a second delay and repeat it 3 times
            m.setDot(0, 3, true);                   //This function can be used to turn ON a single LED
            m.setDot(0, 4, true); 
            m.setDot(1, 3, true); 
            m.setDot(1, 4, true); 
            m.setDot(2, 3, true); 
            m.setDot(2, 4, true); 
            m.setDot(3, 0, true); 
            m.setDot(3, 1, true); 
            m.setDot(3, 2, true); 
            m.setDot(3, 3, true); 
            m.setDot(3, 4, true); 
            m.setDot(3, 5, true); 
            m.setDot(3, 6, true); 
            m.setDot(3, 7, true); 
            m.setDot(4, 1, true); 
            m.setDot(4, 2, true); 
            m.setDot(4, 3, true); 
            m.setDot(4, 4, true); 
            m.setDot(4, 5, true); 
            m.setDot(4, 6, true); 
            m.setDot(5, 2, true); 
            m.setDot(5, 3, true); 
            m.setDot(5, 4, true); 
            m.setDot(5, 5, true); 
            m.setDot(6, 3, true); 
            m.setDot(6, 4, true); 
            m.setDot(6, 5, true); 
            m.setDot(7, 4, true); 
            delay(500);
            m.clear();                              //Function required to clean the screen, turn OFF all LEDs
            delay(500);
        }
    }
}
