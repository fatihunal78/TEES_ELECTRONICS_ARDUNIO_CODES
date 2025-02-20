//SA47 - LED matrix dimmer

#include <MaxMatrix.h> // Add library

int DIN = 4; // Define DIN pin
int CS = 3; // Define CS pin
int CLK = 2; // Define CLK pin

int LED_Matrix_Count = 1; // LED matrices can be connected in series
                    // If more than one matrix is to be connected, you can change the number here
int potPin = A0; // Define the pin to which the potentiometer is connected
int potStatus = 0; // Define the variable to store the value of the potentiometer
int brightness = 0; // Define the variable on which the brightness variable will ignite

MaxMatrix m(DIN, CS, CLK, LED_Matrix_Count); // Define matrix m with matrix pin connections

char HEART[] = {
    8, 8, // Code line to show heart
    0x0C, 0x1E, 0x3E, 0x7C, 0x7C, 0x3E, 0x1E, 0x0C
};

void setup() {
    m.init(); // Start the LED matrix
    m.setIntensity(8); // Brightness is adjustable from 0 to 15
}

void loop() {
    potStatus = analogRead(potPin); // Read values from Potentiometer
    brightness = map(potStatus, 0, 1023, 0, 15); // Proportion the value read from the potentiometer between 0 and 15 and save it to the brightness variable.
    m.writeSprite(0, 0, HEART); // Export smiling face to LED Matrix
    m.setIntensity(brightness); // Set the brightness of the LED Matrix with the setIntensity command
}
