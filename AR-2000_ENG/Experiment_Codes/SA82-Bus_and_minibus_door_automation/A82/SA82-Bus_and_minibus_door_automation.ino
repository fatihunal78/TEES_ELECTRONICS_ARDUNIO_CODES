//SA82 - Bus and minibus door automation

#include <MaxMatrix.h>    //Add LED matrix library
#include <Servo.h>        //Include servo motor library

int DIN = 7;             //DIN pin is connected to pin 7
int CS = 6;              //CS pin is connected to pin 6  
int CLK = 5;             //CLK pin is connected to pin 5

int LED_Matrix_Count = 1; //LED matrices can be connected in series. If more than one matrix is to be connected, 
                         //you can change the number here
                            
MaxMatrix m(DIN, CS, CLK, LED_Matrix_Count);  //Define matrix m with matrix pin connections
Servo servo;                                   //Create a Servo object named servo
byte buffer[10];

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

int passengerButton = 3;      //Define the pin number to which the PB1 button on the panel is connected, 
                             //the button that the passenger will press
int doorButton = 2;          //Define the pin number to which the PB2 button on the panel is connected, 
                            //the button that the driver will press

int doorStatus = 0;          //Define the variable to store the state of the door 0 --> Closed, 1--> Open
int passenger_buttonStatus = 0; //Define the variable to store the status of the passenger button  
                              //0--> Button pressed, 1--> Button not pressed

int buzzerPin = 8;           //Define the pin number to which the Buzzer is connected
int buzzerStatus = 0;        //Define the variable to store the status of the buzzer, whether it makes a sound or not
unsigned long newTime = 0;
unsigned long oldTime = 0;

void setup() {
    m.init();                              //Start the LED matrix
    m.setIntensity(5);                     //Adjust the brightness level
    servo.attach(4);                       //Set the pin to which the servo motor is connected
    pinMode(passengerButton, INPUT_PULLUP); //Set the pin to which the PB1 Button is connected as input
    pinMode(doorButton, INPUT_PULLUP);      //Set the pin to which the PB2 Button is connected as input
    pinMode(buzzerPin, OUTPUT);             //Set the pin to which the Buzzer is connected as output
    servo.write(90);                        //Initially set servo motor to 90-degree position
}

void loop() {
    digitalWrite(buzzerPin, LOW);          //Mute the Buzzer 
    
    if(doorStatus == 0 && digitalRead(doorButton) == LOW) { //If the door is closed and driver pressed button to open door
        doorStatus = 1;                    //Save doorStatus as open
        passenger_buttonStatus = 0;        //Set passenger_buttonStatus variable to 0
        m.clear();                        //Clear the LED Matrix

        for(int i=90; i<=180; i++) {      //To open the door, increment i from 90 to 180 degrees
            servo.write(i);               //Write the value to servo motor
            delay(30);
            newTime = millis(); 
            
            if(newTime - oldTime > 500) { //To sound the buzzer at half-second intervals 
                if(buzzerStatus == 0) {   //If the Buzzer does not sound 
                    digitalWrite(buzzerPin, HIGH); //Make a sound from the Buzzer
                    buzzerStatus = 1;     //Save the buzzer status as making sound 
                }  
                else {                    //If the Buzzer is not making sound 
                    digitalWrite(buzzerPin, LOW); //Mute the Buzzer
                    buzzerStatus = 0;     //Save the Buzzer status as not making sound
                }
                oldTime = newTime;        //Save the newTime in oldTime variable 
            }       
        }
    }
    
    if(doorStatus == 1 && digitalRead(doorButton) == LOW) { //If door is opened and driver pressed button to close door
        doorStatus = 0;                   //Save doorStatus as closed

        for(int i=180; i>=90; i--) {     //To close the door, decrement i from 180 to 90 degrees
            servo.write(i);              //Write the value to servo motor
            delay(30);                   //Delay for 30ms
            newTime = millis(); 
            
            if(newTime - oldTime > 500) { //To sound the buzzer at half-second intervals 
                if(buzzerStatus == 0) {   //If the Buzzer does not sound 
                    digitalWrite(buzzerPin, HIGH); //Make a sound from the Buzzer 
                    buzzerStatus = 1;     //Save the buzzer status as making sound 
                }  
                else {                    //If the Buzzer is not making sound
                    digitalWrite(buzzerPin, LOW); //Mute the Buzzer
                    buzzerStatus = 0;     //Save the Buzzer status as not making sound
                }
                oldTime = newTime;        //Save the newTime in oldTime variable 
            } 
        }
    }

    if(digitalRead(passengerButton) == LOW && doorStatus == 0) { //If passenger pressed button and door is closed
        passenger_buttonStatus = 1;       //Save passenger_buttonStatus as pressed
        
        //Buzzer makes a beep sound
        digitalWrite(buzzerPin, HIGH); 
        delay(100);
        digitalWrite(buzzerPin, LOW);
        delay(50);
        digitalWrite(buzzerPin, HIGH); 
        delay(300);
        digitalWrite(buzzerPin, LOW);
        delay(50);
    }

    while(passenger_buttonStatus == 1) {  //As long as passenger_buttonStatus is 1
        printStringWithShift("STOP  ", 80); //Write "STOP" on the LED matrix
    }
}

//Define the function required to print characters
void printCharWithShift(char c, int shift_speed) {
    if(c < 32) return;
    c -= 32;
    memcpy_P(buffer, CH + 7*c, 7);
    m.writeSprite(LED_Matrix_Count * 8, 0, buffer);
    m.setColumn(LED_Matrix_Count * 8 + buffer[0], 0);

    for(int i=0; i<buffer[0]+1; i++) {
        delay(shift_speed);
        m.shiftLeft(false, false);
    }
}

//Define the function required to print the string
void printStringWithShift(char* s, int shift_speed) {
    while (*s != 0) {
        if(digitalRead(doorButton) == LOW) { //If the driver pressed the button to open the door
            passenger_buttonStatus = 0;      //Set the value of the passenger_buttonStatus variable to 0
            break;
        }
        printCharWithShift(*s, shift_speed);
        s++;
    }
}
