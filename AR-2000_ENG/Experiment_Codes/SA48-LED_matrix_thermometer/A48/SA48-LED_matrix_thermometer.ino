// SA48 - LED matrix thermometer

// Add math.h library
#include <math.h>
#include <MaxMatrix.h> // Add library
#include <avr/pgmspace.h>
#include <stdlib.h>    // Library to use the itoa function required for the integer-to-character transformation

// Define the analog pin number to which the NTC is connected
int NTCPin = A5;

// Define the variable to store the NTC value
int analogValue;

// Define the variable to store the temperature value
double temperature;

// Binary format of letters, numbers and symbols
PROGMEM const unsigned char CH[] = {
    3, 8, B00000000, B00000000, B00000000, B00000000, B00000000, // space
    1, 8, B01011111, B00000000, B00000000, B00000000, B00000000, // !
    3, 8, B00000011, B00000000, B00000011, B00000000, B00000000, // "
    5, 8, B00010100, B00111110, B00010100, B00111110, B00010100, // #
    4, 8, B00100100, B01101010, B00101011, B00010010, B00000000, // $
    5, 8, B01100011, B00010011, B00001000, B01100100, B01100011, // %
    5, 8, B00110110, B01001001, B01010110, B00100000, B01010000, // &
    1, 8, B00000011, B00000000, B00000000, B00000000, B00000000, // '
    3, 8, B00011100, B00100010, B01000001, B00000000, B00000000, // (
    3, 8, B01000001, B00100010, B00011100, B00000000, B00000000, // )
    5, 8, B00101000, B00011000, B00001110, B00011000, B00101000, // *
    5, 8, B00001000, B00001000, B00111110, B00001000, B00001000, // +
    2, 8, B10110000, B01110000, B00000000, B00000000, B00000000, // ,
    4, 8, B00001000, B00001000, B00001000, B00001000, B00000000, // -
    2, 8, B01100000, B01100000, B00000000, B00000000, B00000000, // .
    4, 8, B01100000, B00011000, B00000110, B00000001, B00000000, // /
    4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // 0
    3, 8, B01000010, B01111111, B01000000, B00000000, B00000000, // 1
    4, 8, B01100010, B01010001, B01001001, B01000110, B00000000, // 2
    4, 8, B00100010, B01000001, B01001001, B00110110, B00000000, // 3
    4, 8, B00011000, B00010100, B00010010, B01111111, B00000000, // 4
    4, 8, B00100111, B01000101, B01000101, B00111001, B00000000, // 5
    4, 8, B00111110, B01001001, B01001001, B00110000, B00000000, // 6
    4, 8, B01100001, B00010001, B00001001, B00000111, B00000000, // 7
    4, 8, B00110110, B01001001, B01001001, B00110110, B00000000, // 8
    4, 8, B00000110, B01001001, B01001001, B00111110, B00000000, // 9
    2, 8, B01010000, B00000000, B00000000, B00000000, B00000000, // :
    2, 8, B10000000, B01010000, B00000000, B00000000, B00000000, // ;
    3, 8, B00010000, B00101000, B01000100, B00000000, B00000000, // <
    3, 8, B00010100, B00010100, B00010100, B00000000, B00000000, // =
    3, 8, B01000100, B00101000, B00010000, B00000000, B00000000, // >
    4, 8, B00000010, B01011001, B00001001, B00000110, B00000000, // ?
    5, 8, B00111110, B01001001, B01010101, B01011101, B00001110, // @
    4, 8, B01111110, B00010001, B00010001, B01111110, B00000000, // A
    4, 8, B01111111, B01001001, B01001001, B00110110, B00000000, // B
    4, 8, B00111110, B01000001, B01000001, B00100010, B00000000, // C
    4, 8, B01111111, B01000001, B01000001, B00111110, B00000000, // D
    4, 8, B01111111, B01001001, B01001001, B01000001, B00000000, // E
    4, 8, B01111111, B00001001, B00001001, B00000001, B00000000, // F
    4, 8, B00111110, B01000001, B01001001, B01111010, B00000000, // G
    4, 8, B01111111, B00001000, B00001000, B01111111, B00000000, // H
    3, 8, B01000001, B01111111, B01000001, B00000000, B00000000, // I
    4, 8, B00110000, B01000000, B01000001, B00111111, B00000000, // J
    4, 8, B01111111, B00001000, B00010100, B01100011, B00000000, // K
    4, 8, B01111111, B01000000, B01000000, B01000000, B00000000, // L
    5, 8, B01111111, B00000010, B00001100, B00000010, B01111111, // M
    5, 8, B01111111, B00000100, B00001000, B00010000, B01111111, // N
    4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // O
    4, 8, B01111111, B00001001, B00001001, B00000110, B00000000, // P
    4, 8, B00111110, B01000001, B01000001, B10111110, B00000000, // Q
    4, 8, B01111111, B00001001, B00001001, B01110110, B00000000, // R
    4, 8, B01000110, B01001001, B01001001, B00110010, B00000000, // S
    5, 8, B00000001, B00000001, B01111111, B00000001, B00000001, // T
    4, 8, B00111111, B01000000, B01000000, B00111111, B00000000, // U
    5, 8, B00001111, B00110000, B01000000, B00110000, B00001111, // V
    5, 8, B00111111, B01000000, B00111000, B01000000, B00111111, // W
    5, 8, B01100011, B00010100, B00001000, B00010100, B01100011, // X
    5, 8, B00000111, B00001000, B01110000, B00001000, B00000111, // Y
    4, 8, B01110001, B01001001, B01001001, B01000111, B00000000, // Z
    2, 8, B01111111, B01000001, B00000000, B00000000, B00000000, // [
    4, 8, B00000001, B00000110, B00011000, B01100000, B00000000, // \ backslash
    2, 8, B01000001, B01111111, B00000000, B00000000, B00000000, // ]
    3, 8, B00000010, B00000001, B00000010, B00000000, B00000000, // hat
    4, 8, B01000000, B01000000, B01000000, B01000000, B00000000, // _
    2, 8, B00000001, B00000010, B00000000, B00000000, B00000000, // `
    4, 8, B00100000, B01010100, B01010100, B01111000, B00000000, // a
    4, 8, B01111111, B01000100, B01000100, B00111000, B00000000, // b
    4, 8, B00111000, B01000100, B01000100, B00101000, B00000000, // c
    4, 8, B00111000, B01000100, B01000100, B01111111, B00000000, // d
    4, 8, B00111000, B01010100, B01010100, B00011000, B00000000, // e
    3, 8, B00000100, B01111110, B00000101, B00000000, B00000000, // f
    4, 8, B10011000, B10100100, B10100100, B01111000, B00000000, // g
    4, 8, B01111111, B00000100, B00000100, B01111000, B00000000, // h
    3, 8, B01000100, B01111101, B01000000, B00000000, B00000000, // i
    4, 8, B01000000, B10000000, B10000100, B01111101, B00000000, // j
    4, 8, B01111111, B00010000, B00101000, B01000100, B00000000, // k
    3, 8, B01000001, B01111111, B01000000, B00000000, B00000000, // l
    5, 8, B01111100, B00000100, B01111100, B00000100, B01111000, // m
    4, 8, B01111100, B00000100, B00000100, B01111000, B00000000, // n
    4, 8, B00111000, B01000100, B01000100, B00111000, B00000000, // o
    4, 8, B11111100, B00100100, B00100100, B00011000, B00000000, // p
    4, 8, B00011000, B00100100, B00100100, B11111100, B00000000, // q
    4, 8, B01111100, B00001000, B00000100, B00000100, B00000000, // r
    4, 8, B01001000, B01010100, B01010100, B00100100, B00000000, // s
    3, 8, B00000100, B00111111, B01000100, B00000000, B00000000, // t
    4, 8, B00111100, B01000000, B01000000, B01111100, B00000000, // u
    5, 8, B00011100, B00100000, B01000000, B00100000, B00011100, // v
    5, 8, B00111100, B01000000, B00111100, B01000000, B00111100, // w
    5, 8, B01000100, B00101000, B00010000, B00101000, B01000100, // x
    4, 8, B10011100, B10100000, B10100000, B01111100, B00000000, // y
    3, 8, B01100100, B01010100, B01001100, B00000000, B00000000, // z
    3, 8, B00001000, B00110110, B01000001, B00000000, B00000000, // {
    1, 8, B01111111, B00000000, B00000000, B00000000, B00000000, // |
    3, 8, B01000001, B00110110, B00001000, B00000000, B00000000, // }
    5, 8, 0x00, 0x06, 0x09, 0x09, 0x06, 0x00 // ° degree symbol
};

int DIN = 4; // Define DIN pin
int CS = 3;  // Define CS pin
int CLK = 2; // Define CLK pin

int LED_Matrix_Count = 1; // LED matrices can be connected in series
                          // If more than one matrix is to be connected, you can change the number here

MaxMatrix m(DIN, CS, CLK, LED_Matrix_Count); // Define matrix m with matrix pin connections

byte buffer[10];

void setup() {
    m.init();           // Start the LED matrix
    m.setIntensity(8);  // Brightness is adjustable from 0 to 15
}

// Define NTCCalculate function
double NTCCalculate(int analogRead) {
    // Calculate temperature value according to NTC specifications
    temperature = log(((10240000 / analogRead) - 10000));
    temperature = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temperature * temperature)) * temperature);
    temperature = temperature - 273.15;
    // Return the calculated temperature value
    return temperature;
}

void loop() {
    // Read NTC value and save it to analogValue variable
    analogValue = analogRead(NTCPin);
    // Calculate the temperature value with the NTCCalculate function and save the value to the temperature variable
    temperature = NTCCalculate(analogValue);
    char temperature2[4];
    itoa(temperature, temperature2, 10); // Convert integer to character, convert temperature which is integer number to temperature2 character.
    m.clear();                          // Clear LED Matrix
    printStringWithShift("TEMPERATURE ", 160); // Write "TEMPERATURE" text
    printStringWithShift(temperature2, 160);   // Write the actual temperature
    printStringWithShift("°C", 160);           // Write centigrade symbol (°C).
    m.shiftLeft(false, true);                  // Slide left
    delay(200);                                // Wait for 200ms seconds
}

// Function required to print characters
void printCharWithShift(char c, int shift_speed) {
    if (c < 32) return;
    c -= 32;
    memcpy_P(buffer, CH + 7 * c, 7);
    m.writeSprite(1 * 8, 0, buffer);
    m.setColumn(1 * 8 + buffer[0], 0);

    for (int i = 0; i < buffer[0] + 1; i++) {
        delay(shift_speed);
        m.shiftLeft(false, false);
    }
}

// Function required to print string
void printStringWithShift(char* s, int shift_speed) {
    while (*s != 0) {
        printCharWithShift(*s, shift_speed);
        s++;
    }
}