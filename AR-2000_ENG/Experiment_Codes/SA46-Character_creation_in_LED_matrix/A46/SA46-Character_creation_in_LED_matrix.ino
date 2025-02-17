//SA46 - Character creation in LED matrix

#include <MaxMatrix.h> //Add library

int DIN = 4; //Define DIN pin
int CS = 3;  //Define CS pin
int CLK = 2; //Define CLK pin

int LED_Matrix_Count = 1; //LED matrices can be connected in series
                         //If more than one matrix is to be connected, you can change the number here
MaxMatrix m(DIN, CS, CLK, LED_Matrix_Count); //Define matrix m with matrix pin connections

char HEART[] = {8, 8,  //Codes to show heart
                      //You can paste your own code instead of the code line here.
         0x0C, 0x1E, 0x3E, 0x7C, 0x7C, 0x3E, 0x1E, 0x0C
};

void setup() {
  m.init();           //Start the LED matrix
  m.setIntensity(8);  //Brightness is adjustable from 0 to 15
}

void loop() { 
  m.writeSprite(0, 0, HEART);  //Export Heart icon to LED Matrix 
  delay(1000);                 //Wait for 1 second
  m.clear();                   //Turn OFF LEDs 
  delay(1000);                 //Wait for 1 second
}
