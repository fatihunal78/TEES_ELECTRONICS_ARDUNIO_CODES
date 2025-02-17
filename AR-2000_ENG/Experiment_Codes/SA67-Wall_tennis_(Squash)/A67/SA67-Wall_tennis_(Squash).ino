//SA67 - Wall tennis (Squash)

//Add libraries
#include "LedControl.h" 
#include <MaxMatrix.h>
#include <avr/pgmspace.h>
#include <stdlib.h>

//Binary format of letters, numbers and symbols
PROGMEM const unsigned char CH[] = {
    3, 8, B00000000, B00000000, B00000000, B00000000, B00000000,    // space
    1, 8, B01011111, B00000000, B00000000, B00000000, B00000000,    // !
    3, 8, B00000011, B00000000, B00000011, B00000000, B00000000,    // "
    5, 8, B00010100, B00111110, B00010100, B00111110, B00010100,    // #
    4, 8, B00100100, B01101010, B00101011, B00010010, B00000000,    // $
    5, 8, B01100011, B00010011, B00001000, B01100100, B01100011,    // %
    5, 8, B00110110, B01001001, B01010110, B00100000, B01010000,    // &
    1, 8, B00000011, B00000000, B00000000, B00000000, B00000000,    // '
    3, 8, B00011100, B00100010, B01000001, B00000000, B00000000,    // (
    3, 8, B01000001, B00100010, B00011100, B00000000, B00000000,    // )
    5, 8, B00101000, B00011000, B00001110, B00011000, B00101000,    // *
    5, 8, B00001000, B00001000, B00111110, B00001000, B00001000,    // +
    2, 8, B10110000, B01110000, B00000000, B00000000, B00000000,    // ,
    4, 8, B00001000, B00001000, B00001000, B00001000, B00000000,    // -
    2, 8, B01100000, B01100000, B00000000, B00000000, B00000000,    // .
    4, 8, B01100000, B00011000, B00000110, B00000001, B00000000,    // /
    4, 8, B00111110, B01000001, B01000001, B00111110, B00000000,    // 0
    3, 8, B01000010, B01111111, B01000000, B00000000, B00000000,    // 1
    4, 8, B01100010, B01010001, B01001001, B01000110, B00000000,    // 2
    4, 8, B00100010, B01000001, B01001001, B00110110, B00000000,    // 3
    4, 8, B00011000, B00010100, B00010010, B01111111, B00000000,    // 4
    4, 8, B00100111, B01000101, B01000101, B00111001, B00000000,    // 5
    4, 8, B00111110, B01001001, B01001001, B00110000, B00000000,    // 6
    4, 8, B01100001, B00010001, B00001001, B00000111, B00000000,    // 7
    4, 8, B00110110, B01001001, B01001001, B00110110, B00000000,    // 8
    4, 8, B00000110, B01001001, B01001001, B00111110, B00000000,    // 9
    2, 8, B01010000, B00000000, B00000000, B00000000, B00000000,    // :
    2, 8, B10000000, B01010000, B00000000, B00000000, B00000000,    // ;
    3, 8, B00010000, B00101000, B01000100, B00000000, B00000000,    // <
    3, 8, B00010100, B00010100, B00010100, B00000000, B00000000,    // =
    3, 8, B01000100, B00101000, B00010000, B00000000, B00000000,    // >
    4, 8, B00000010, B01011001, B00001001, B00000110, B00000000,    // ?
    5, 8, B00111110, B01001001, B01010101, B01011101, B00001110,    // @
    4, 8, B01111110, B00010001, B00010001, B01111110, B00000000,    // A
    4, 8, B01111111, B01001001, B01001001, B00110110, B00000000,    // B
    4, 8, B00111110, B01000001, B01000001, B00100010, B00000000,    // C
    4, 8, B01111111, B01000001, B01000001, B00111110, B00000000,    // D
    4, 8, B01111111, B01001001, B01001001, B01000001, B00000000,    // E
    4, 8, B01111111, B00001001, B00001001, B00000001, B00000000,    // F
    4, 8, B00111110, B01000001, B01001001, B01111010, B00000000,    // G
    4, 8, B01111111, B00001000, B00001000, B01111111, B00000000,    // H
    3, 8, B01000001, B01111111, B01000001, B00000000, B00000000,    // I
    4, 8, B00110000, B01000000, B01000001, B00111111, B00000000,    // J
    4, 8, B01111111, B00001000, B00010100, B01100011, B00000000,    // K
    4, 8, B01111111, B01000000, B01000000, B01000000, B00000000,    // L
    5, 8, B01111111, B00000010, B00001100, B00000010, B01111111,    // M
    5, 8, B01111111, B00000100, B00001000, B00010000, B01111111,    // N
    4, 8, B00111110, B01000001, B01000001, B00111110, B00000000,    // O
    4, 8, B01111111, B00001001, B00001001, B00000110, B00000000,    // P
    4, 8, B00111110, B01000001, B01000001, B10111110, B00000000,    // Q
    4, 8, B01111111, B00001001, B00001001, B01110110, B00000000,    // R
    4, 8, B01000110, B01001001, B01001001, B00110010, B00000000,    // S
    5, 8, B00000001, B00000001, B01111111, B00000001, B00000001,    // T
    4, 8, B00111111, B01000000, B01000000, B00111111, B00000000,    // U
    5, 8, B00001111, B00110000, B01000000, B00110000, B00001111,    // V
    5, 8, B00111111, B01000000, B00111000, B01000000, B00111111,    // W
    5, 8, B01100011, B00010100, B00001000, B00010100, B01100011,    // X
    5, 8, B00000111, B00001000, B01110000, B00001000, B00000111,    // Y
    4, 8, B01110001, B01001001, B01001001, B01000111, B00000000,    // Z
    2, 8, B01111111, B01000001, B00000000, B00000000, B00000000,    // [
    4, 8, B00000001, B00000110, B00011000, B01100000, B00000000,    // \ backslash
    2, 8, B01000001, B01111111, B00000000, B00000000, B00000000,    // ]
    3, 8, B00000010, B00000001, B00000010, B00000000, B00000000,    // hat
    4, 8, B01000000, B01000000, B01000000, B01000000, B00000000,    // _
    2, 8, B00000001, B00000010, B00000000, B00000000, B00000000,    // `
    4, 8, B00100000, B01010100, B01010100, B01111000, B00000000,    // a
    4, 8, B01111111, B01000100, B01000100, B00111000, B00000000,    // b
    4, 8, B00111000, B01000100, B01000100, B00101000, B00000000,    // c
    4, 8, B00111000, B01000100, B01000100, B01111111, B00000000,    // d
    4, 8, B00111000, B01010100, B01010100, B00011000, B00000000,    // e
    3, 8, B00000100, B01111110, B00000101, B00000000, B00000000,    // f
    4, 8, B10011000, B10100100, B10100100, B01111000, B00000000,    // g
    4, 8, B01111111, B00000100, B00000100, B01111000, B00000000,    // h
    3, 8, B01000100, B01111101, B01000000, B00000000, B00000000,    // i
    4, 8, B01000000, B10000000, B10000100, B01111101, B00000000,    // j
    4, 8, B01111111, B00010000, B00101000, B01000100, B00000000,    // k
    3, 8, B01000001, B01111111, B01000000, B00000000, B00000000,    // l
    5, 8, B01111100, B00000100, B01111100, B00000100, B01111000,    // m
    4, 8, B01111100, B00000100, B00000100, B01111000, B00000000,    // n
    4, 8, B00111000, B01000100, B01000100, B00111000, B00000000,    // o
    4, 8, B11111100, B00100100, B00100100, B00011000, B00000000,    // p
    4, 8, B00011000, B00100100, B00100100, B11111100, B00000000,    // q
    4, 8, B01111100, B00001000, B00000100, B00000100, B00000000,    // r
    4, 8, B01001000, B01010100, B01010100, B00100100, B00000000,    // s
    3, 8, B00000100, B00111111, B01000100, B00000000, B00000000,    // t
    4, 8, B00111100, B01000000, B01000000, B01111100, B00000000,    // u
    5, 8, B00011100, B00100000, B01000000, B00100000, B00011100,    // v
    5, 8, B00111100, B01000000, B00111100, B01000000, B00111100,    // w
    5, 8, B01000100, B00101000, B00010000, B00101000, B01000100,    // x
    4, 8, B10011100, B10100000, B10100000, B01111100, B00000000,    // y
    3, 8, B01100100, B01010100, B01001100, B00000000, B00000000,    // z
    3, 8, B00001000, B00110110, B01000001, B00000000, B00000000,    // {
    1, 8, B01111111, B00000000, B00000000, B00000000, B00000000,    // |
    3, 8, B01000001, B00110110, B00001000, B00000000, B00000000,    // }
    4, 8, B00001000, B00000100, B00001000, B00000100, B00000000,    // ~
};

int DIN = 4;                                    //Define DIN pin
int CS = 3;                                     //Define CS pin  
int CLK = 2;                                    //Define CLK pin

int LED_Matrix_Count = 1;                       //LED matrices can be connected in series
                                               //If more than one matrix is to be connected, you can change the number here
MaxMatrix m(DIN, CS, CLK, LED_Matrix_Count);   //Define matrix m with matrix pin connections 

//DATAIN pin(4), CLK pin(2), CS pin(3), define how many matrices are connected(1)
LedControl myMatrix = LedControl(4, 2, 3, 1);   

int column = 0, row = random(8);                //Set column value to 0, assign a random number to row value
int Xdirection = 1, Ydirection = 1;             //Define directions for the LED movements
int potPin = 0, potPinValue;                    //Define that the POT is connected to Analog Pin 0 and define the variable to hold its value
int Action_speed = 300;                         //Define the action_speed variable so that the game gets faster and faster
int counter = 0;
int speakerPin = 7;                            //Define the pin number to which the Speaker is connected

unsigned long StartTime = 0;
unsigned long elapsedTime = 0;
byte buffer[10];
char result[2];

void setup() { 
    pinMode(speakerPin, OUTPUT);               //Set the pin to which the Speaker is connected as output
    m.init();                                  //Start the 8x8 LED matrix
    m.setIntensity(8);                        //Set brightness value to 8
  
    myMatrix.shutdown(0, false);               //For the brightness settings of the LED 
    myMatrix.setIntensity(0, 8);              //8 value can be changed to change the brightness value
    randomSeed(analogRead(0));                //Get random reference value from analog 0
    lost();
}
 
void loop() { 
    StartTime = millis();                     //Save the time elapsed since the Arduino started to the StartTime variable
    potPinValue = analogRead(potPin);         //Read the Potentiometer value
    potPinValue = map(potPinValue, 0, 1024, 0, 6);  //Proportion the read value between 0 and 1024 to between 0 and 6 
    
    //If the LED movement has reached the end and the lower moving panel has reached the end, the panel should not move any further
    if(row == 1 && (potPinValue == column || potPinValue+1 == column || potPinValue+2 == column)) {
        Ydirection = 1;
        tone(speakerPin, 600);
        delay(50);
        noTone(speakerPin);
    }                                         //LED movement is upwards
    
    if(row == 7) {
        Ydirection = -1;                      //If the ball hits the top, change direction downwards
    }
    if(column == 7) {
        Xdirection = -1;                      //If the ball hits the right side, change direction to the left
    }
    if(column == 0) {
        Xdirection = 1;                       //If the ball hits the upper left side, change direction to the right
    }

    if(row == 0) {                           //If the LED is on row 0, that is, you lost
        unsigned long score = 0;              //Create a score variable and set its initial value to zero
        elapsedTime = StartTime - elapsedTime; //Take the difference between the last lost and the start time
        score = elapsedTime/200;              //To earn 5 points per second 
        
        for(int i=0; i<3; i++) {
            tone(speakerPin, 100);
            delay(150);
            tone(speakerPin, 400);
            delay(150);
            noTone(speakerPin);
        }
        
        char score2[4]; 
        itoa(score, score2, 10);             //Convert integer number to char, convert score integer number to score2 char
        myMatrix.clearDisplay(0);             //Clear the LED Matrix
        m.shiftLeft(false, true);             //Slide left
        printStringWithShift("SCORE ", 80);   //Print the text "SCORE"
        printStringWithShift(score2, 80);     //Print the score
        printStringWithShift("  ", 80);       //Print whitespace
        delay(1000);                          //Wait for 1 second
        elapsedTime = millis();               //Save the time before switching to the new game
        lost();                               //Go to the game lost function 
    }  
  
    column += Xdirection; 
    row += Ydirection;
    Action();
    counter++; 
}

void lost() {                                 //Define lost() function
    for(int x=0; x<3; x++) {                 //By means of for loop 
        myMatrix.clearDisplay(0);             //Clear LED Matrix screen 
        delay(250);
        for(int y=0; y<8; y++) { 
            myMatrix.setRow(0, y, 255); 
        }
        delay(150); 
    } 
    
    //Initialize variables 
    counter = 0;
    Action_speed = 300;
    column = random(2, 8);
    row = random(2, 8);
    Action(); 
}
 
void Action() { 
    myMatrix.clearDisplay(0);                 //Clear the screen 
    myMatrix.setLed(0, column, row, HIGH);    //Define directions of the ball movement, 0, Column, Row, HIGH
    myMatrix.setLed(0, potPinValue, 0, HIGH); //Define the directions of the lower pedal movement (The pedal consisted of 3 points)
    myMatrix.setLed(0, potPinValue+1, 0, HIGH); //Define the movement directions of the lower pedal 
    myMatrix.setLed(0, potPinValue+2, 0, HIGH); //Define the movement directions of the lower pedal 
    
    if(!(counter % 10)) {                     //To make the game progressively faster 
        Action_speed -= 5;
    }
    delay(Action_speed); 
}

//Function required to print characters
void printCharWithShift(char c, int shift_speed) {
    if(c < 32) return;
    c -= 32;
    memcpy_P(buffer, CH + 7*c, 7);
    m.writeSprite(1*8, 0, buffer);
    m.setColumn(1*8 + buffer[0], 0);
   
    for(int i=0; i<buffer[0]+1; i++) {
        delay(shift_speed);
        m.shiftLeft(false, false);
    }
}
  
//Function required to print string
void printStringWithShift(char* s, int shift_speed) {
    while (*s != 0) {
        printCharWithShift(*s, shift_speed);
        s++;
    }
}
