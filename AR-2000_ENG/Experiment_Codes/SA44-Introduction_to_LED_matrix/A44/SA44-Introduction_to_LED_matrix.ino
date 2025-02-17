//SA44 - Introduction to LED matrix

#include <MaxMatrix.h>              //Add library

int DIN = 4;                        //Define DIN pin
int CS = 3;                         //Define CS pin
int CLK = 2;                        //Define CLK pin

int LED_Matrix_Count = 1;           //LED matrices can be connected in series
                                   //If more than one matrix is to be connected, you can change the number here

MaxMatrix m(DIN, CS, CLK, LED_Matrix_Count);  //Define matrix m with matrix pin connections 

char smiling_face[] = {8, 8,       //Codes to show smiling face
  0x3C, 0x42, 0x95, 0xA1, 
  0xA1, 0x95, 0x42, 0x3C
};

char grumpy_face[] = {8, 8,        //Codes to show grumpy face
  0x3C, 0x42, 0xA5, 0xA1, 
  0xA1, 0xA5, 0x42, 0x3C
};

char sad_face[] = {8, 8,           //Codes to show sad face
  0x3C, 0x42, 0xA5, 0x91, 
  0x91, 0xA5, 0x42, 0x3C
};

void setup() {
  m.init();                        //Start the LED matrix
  m.setIntensity(8);              //Brightness is adjustable from 0 to 15
}

void loop() {
  //This function can be used to light a single LED
  //m.setDot(6, 2, true); 
  //m.clear();                     //Function required to clean the screen, turn OFF all LEDs

  m.writeSprite(0, 0, smiling_face);  //Export smiling face to LED matrix 
  delay(1000);
  
  m.writeSprite(0, 0, grumpy_face);   //Export grumpy face to LED matrix 
  delay(1000);
  
  m.writeSprite(0, 0, sad_face);      //Export sad face to LED matrix
  delay(1000); 
  
  for(int i = 0; i < 8; i++) {        //Slide sad face to the left
    m.shiftLeft(false, false);
    delay(300);
  }
  m.clear();                          //Turn OFF LEDs
}
