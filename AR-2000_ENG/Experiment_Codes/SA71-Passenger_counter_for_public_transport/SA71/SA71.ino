//SA71 - Passenger counter for public transport

#include <MaxMatrix.h>                    //We have added the LED Matrix library 

int SensorPin = 3;                       //Define the pin to which the first sensor (Input sensor) is connected
int Sensor2Pin = 4;                      //Define the pin to which the second sensor (Output sensor) is connected
int buzzerPin = 2;                       //Define the pin number to which the Speaker is connected
int counter = 0;                         //Define the variable to store the number of inputs and outputs and set its initial value to zero
char CharCounter[4];                     //Convert an interger number to the character (char) variable to transfer it to the LED Matrix
                                        //Create CharCounter character (char) variable to convert the counter variable where the input 
                                        //output count will be stored into char
                   
byte buffer[10]; 

int DIN = 7;                            //Define that the LED Matrix is connected to pin 7 of the DIN pin
int CS = 6;                             //Define that the LED Matrix is connected to pin 6 of the CS pin
int CLK = 5;                            //Define that the LED Matrix is connected to pin 5 of the CLK pin

int Led_Matrix_Count = 1;               //Define LED Matrix count

MaxMatrix m(DIN, CS, CLK, Led_Matrix_Count); //Define matrix m with matrix pin connections

//Binary format of letters, numbers and symbols
PROGMEM const unsigned char CH[] = {
    3, 8, B00000000, B00000000, B00000000, B00000000, B00000000,  // space
    1, 8, B01011111, B00000000, B00000000, B00000000, B00000000,  // !
    3, 8, B00000011, B00000000, B00000011, B00000000, B00000000,  // "
    5, 8, B00010100, B00111110, B00010100, B00111110, B00010100,  // #
    4, 8, B00100100, B01101010, B00101011, B00010010, B00000000,  // $
    5, 8, B01100011, B00010011, B00001000, B01100100, B01100011,  // %
    5, 8, B00110110, B01001001, B01010110, B00100000, B01010000,  // &
    1, 8, B00000011, B00000000, B00000000, B00000000, B00000000,  // '
    3, 8, B00011100, B00100010, B01000001, B00000000, B00000000,  // (
    3, 8, B01000001, B00100010, B00011100, B00000000, B00000000,  // )
    5, 8, B00101000, B00011000, B00001110, B00011000, B00101000,  // *
    5, 8, B00001000, B00001000, B00111110, B00001000, B00001000,  // +
    2, 8, B10110000, B01110000, B00000000, B00000000, B00000000,  // ,
    4, 8, B00001000, B00001000, B00001000, B00001000, B00000000,  // -
    2, 8, B01100000, B01100000, B00000000, B00000000, B00000000,  // .
    4, 8, B01100000, B00011000, B00000110, B00000001, B00000000,  // /
    4, 8, B00111110, B01000001, B01000001, B00111110, B00000000,  // 0
    3, 8, B01000010, B01111111, B01000000, B00000000, B00000000,  // 1
    4, 8, B01100010, B01010001, B01001001, B01000110, B00000000,  // 2
    4, 8, B00100010, B01000001, B01001001, B00110110, B00000000,  // 3
    4, 8, B00011000, B00010100, B00010010, B01111111, B00000000,  // 4
    4, 8, B00100111, B01000101, B01000101, B00111001, B00000000,  // 5
    4, 8, B00111110, B01001001, B01001001, B00110000, B00000000,  // 6
    4, 8, B01100001, B00010001, B00001001, B00000111, B00000000,  // 7
    4, 8, B00110110, B01001001, B01001001, B00110110, B00000000,  // 8
    4, 8, B00000110, B01001001, B01001001, B00111110, B00000000,  // 9
    2, 8, B01010000, B00000000, B00000000, B00000000, B00000000,  // :
    2, 8, B10000000, B01010000, B00000000, B00000000, B00000000,  // ;
    3, 8, B00010000, B00101000, B01000100, B00000000, B00000000,  // <
    3, 8, B00010100, B00010100, B00010100, B00000000, B00000000,  // =
    3, 8, B01000100, B00101000, B00010000, B00000000, B00000000,  // >
    4, 8, B00000010, B01011001, B00001001, B00000110, B00000000,  // ?
    5, 8, B00111110, B01001001, B01010101, B01011101, B00001110,  // @
    4, 8, B01111110, B00010001, B00010001, B01111110, B00000000,  // A
    4, 8, B01111111, B01001001, B01001001, B00110110, B00000000,  // B
    4, 8, B00111110, B01000001, B01000001, B00100010, B00000000,  // C
    4, 8, B01111111, B01000001, B01000001, B00111110, B00000000,  // D
    4, 8, B01111111, B01001001, B01001001, B01000001, B00000000,  // E
    4, 8, B01111111, B00001001, B00001001, B00000001, B00000000,  // F
    4, 8, B00111110, B01000001, B01001001, B01111010, B00000000,  // G
    4, 8, B01111111, B00001000, B00001000, B01111111, B00000000,  // H
    3, 8, B01000001, B01111111, B01000001, B00000000, B00000000,  // I
    4, 8, B00110000, B01000000, B01000001, B00111111, B00000000,  // J
    4, 8, B01111111, B00001000, B00010100, B01100011, B00000000,  // K
    4, 8, B01111111, B01000000, B01000000, B01000000, B00000000,  // L
    5, 8, B01111111, B00000010, B00001100, B00000010, B01111111,  // M
    5, 8, B01111111, B00000100, B00001000, B00010000, B01111111,  // N
    4, 8, B00111110, B01000001, B01000001, B00111110, B00000000,  // O
    4, 8, B01111111, B00001001, B00001001, B00000110, B00000000,  // P
    4, 8, B00111110, B01000001, B01000001, B10111110, B00000000,  // Q
    4, 8, B01111111, B00001001, B00001001, B01110110, B00000000,  // R
    4, 8, B01000110, B01001001, B01001001, B00110010, B00000000,  // S
    5, 8, B00000001, B00000001, B01111111, B00000001, B00000001,  // T
    4, 8, B00111111, B01000000, B01000000, B00111111, B00000000,  // U
    5, 8, B00001111, B00110000, B01000000, B00110000, B00001111,  // V
    5, 8, B00111111, B01000000, B00111000, B01000000, B00111111,  // W
    5, 8, B01100011, B00010100, B00001000, B00010100, B01100011,  // X
    5, 8, B00000111, B00001000, B01110000, B00001000, B00000111,  // Y
    4, 8, B01110001, B01001001, B01001001, B01000111, B00000000,  // Z
    2, 8, B01111111, B01000001, B00000000, B00000000, B00000000,  // [
    4, 8, B00000001, B00000110, B00011000, B01100000, B00000000,  // \ backslash
    2, 8, B01000001, B01111111, B00000000, B00000000, B00000000,  // ]
    3, 8, B00000010, B00000001, B00000010, B00000000, B00000000,  // hat
    4, 8, B01000000, B01000000, B01000000, B01000000, B00000000,  // _
    2, 8, B00000001, B00000010, B00000000, B00000000, B00000000,  // `
    4, 8, B00100000, B01010100, B01010100, B01111000, B00000000,  // a
    4, 8, B01111111, B01000100, B01000100, B00111000, B00000000,  // b
    4, 8, B00111000, B01000100, B01000100, B00101000, B00000000,  // c
    4, 8, B00111000, B01000100, B01000100, B01111111, B00000000,  // d
    4, 8, B00111000, B01010100, B01010100, B00011000, B00000000,  // e
    3, 8, B00000100, B01111110, B00000101, B00000000, B00000000,  // f
    4, 8, B10011000, B10100100, B10100100, B01111000, B00000000,  // g
    4, 8, B01111111, B00000100, B00000100, B01111000, B00000000,  // h
    3, 8, B01000100, B01111101, B01000000, B00000000, B00000000,  // i
    4, 8, B01000000, B10000000, B10000100, B01111101, B00000000,  // j
    4, 8, B01111111, B00010000, B00101000, B01000100, B00000000,  // k
    3, 8, B01000001, B01111111, B01000000, B00000000, B00000000,  // l
    5, 8, B01111100, B00000100, B01111100, B00000100, B01111000,  // m
    4, 8, B01111100, B00000100, B00000100, B01111000, B00000000,  // n
    4, 8, B00111000, B01000100, B01000100, B00111000, B00000000,  // o
    4, 8, B11111100, B00100100, B00100100, B00011000, B00000000,  // p
    4, 8, B00011000, B00100100, B00100100, B11111100, B00000000,  // q
    4, 8, B01111100, B00001000, B00000100, B00000100, B00000000,  // r
    4, 8, B01001000, B01010100, B01010100, B00100100, B00000000,  // s
    3, 8, B00000100, B00111111, B01000100, B00000000, B00000000,  // t
    4, 8, B00111100, B01000000, B01000000, B01111100, B00000000,  // u
    5, 8, B00011100, B00100000, B01000000, B00100000, B00011100,  // v
    5, 8, B00111100, B01000000, B00111100, B01000000, B00111100,  // w
    5, 8, B01000100, B00101000, B00010000, B00101000, B01000100,  // x
    4, 8, B10011100, B10100000, B10100000, B01111100, B00000000,  // y
    3, 8, B01100100, B01010100, B01001100, B00000000, B00000000,  // z
    3, 8, B00001000, B00110110, B01000001, B00000000, B00000000,  // {
    1, 8, B01111111, B00000000, B00000000, B00000000, B00000000,  // |
    3, 8, B01000001, B00110110, B00001000, B00000000, B00000000,  // }
    4, 8, B00001000, B00000100, B00001000, B00000100, B00000000,  // ~
};

void setup() 
{
    pinMode(SensorPin, INPUT);           //Set sensor pin (Passenger Entry sensor) as input 
    pinMode(Sensor2Pin, INPUT);          //Set sensor pin (Passenger Exit sensor) as input 
    pinMode(buzzerPin, OUTPUT);          //Set the pin to which the Buzzer is connected as output
    m.init();                           //Start LED matrix
    m.setIntensity(8);                  //Adjust brightness
}
   
void loop() 
{ 
    bool val = digitalRead(SensorPin);   //Read value in sensor pin
    bool val2 = digitalRead(Sensor2Pin); //Read the value in sensor 2 pin
  
    if(val == HIGH) {                    //If sensor1, that is, the value in the passenger entry sensor, is HIGH, that is, a passenger 
                                        //has entered. When a passenger gets on, a beep will sound from the speaker for an audible warning
        for(int i=0; i<2; i++) {
            digitalWrite(buzzerPin, HIGH);
            delay(50);
            digitalWrite(buzzerPin, LOW);
            delay(50);
        }
        counter = counter + 1;           //Increment counter value by 1 
        itoa(counter, CharCounter, 10);  //Convert integer number to character(char) (convert counter integer number to CharCounter 
                                        //character(char)) 
        printStringWithShift(CharCounter, 70); //Export the value in the CharCounter variable converted to characters to the LED Matrix
                                             //70 indicates the sliding speed
                                         
        printStringWithShift("  ", 70);  //Put a space between them to avoid confusion with the next number in the LED Matrix
    
        m.shiftLeft(false, true);        //Slide left 

        while(1) {                       //When there is a continuous obstacle in front of the sensor, enter an infinite loop so that it 
                                        //does not count 
            if(digitalRead(SensorPin) == LOW) break; //If the obstacle is removed, exit the loop 
        }
    }
    else if(val2 == HIGH) {             //If the value in sensor2, that is, the passenger exit sensor, is HIGH, that is, if the passenger 
                                        //got off. When the passenger gets off, a beep will be heard from the speaker for an audible warning
        digitalWrite(buzzerPin, HIGH);
        delay(50);
        digitalWrite(buzzerPin, LOW);
        delay(50);
        counter = counter - 1;           //Decrement counter value by 1
        itoa(counter, CharCounter, 10);  //Convert integer number to character(char) (convert counter integer number to CharCounter 
                                        //character(char))
        printStringWithShift(CharCounter, 70); //Export the value in the CharCounter variable converted to characters to the LED Matrix
                                             //70 indicates the sliding speed
                                         
        printStringWithShift("  ", 70);  //Put a space between them to avoid confusion with the next number in the LED Matrix
        m.shiftLeft(false, true);        //Slide left 
    
        while(1) {                       //When there is a continuous obstacle in front of the sensor, enter an infinite loop so that it 
                                        //does not count 
            if(digitalRead(Sensor2Pin) == LOW) break; //If the obstacle is removed, exit the loop 
        }
    }
}

//Define the function required to print characters
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
