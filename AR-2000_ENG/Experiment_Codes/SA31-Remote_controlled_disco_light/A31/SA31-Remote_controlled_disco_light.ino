//S31 - Remote controlled disco light

//Add IR receiver library
#include <IRremote.h>

//Define IR control codes
#define oneKey   0xFFA25D // IR Control key 1
#define twoKey   0xFF629D // IR Control key 2
#define threeKey 0xFFE21D // IR Control key 3
#define fourKey  0xFF22DD // IR Control key 4
#define fiveKey  0xFF02FD // IR Control key 5
#define sixKey   0xFFC23D // IR Control key 6
#define sevenKey 0xFFE01F // IR Control key 7
#define eightKey 0xFFA857 // IR Control key 8
#define nineKey  0xFF906F // IR Control key 9
#define starKey  0xFF6897 // IR Control Star Key
#define zeroKey  0xFF9867 // IR Control key 0
#define hashKey  0xFFB04F // IR Control key #
#define upKey    0xFF18E7 // IR Control up arrow key
#define downKey  0xFF4AB5 // IR Control down arrow key
#define rightKey 0xFF5AA5 // IR Control right arrow key
#define leftKey  0xFF10EF // IR Control left arrow key
#define okKey    0xFF38C7 // IR Control OK key
#define repeat   0xFFFFFFFF // If the pressed key is pressed continuously

int blue_LED = 3;   // Define the pin to which the blue LED is connected
int green_LED = 4;  // Define the pin to which the green LED is connected
int yellow_LED = 5; // Define the pin to which the yellow LED is connected
int red_LED = 6;    // Define the pin to which the red LED is connected

int IRPin = 2;      // Define the pin to which the IR receiver signal leg is connected

IRrecv IRReceive(IRPin); // Define an IR Receiver named IRReceive
decode_results result;   // Define variable to store values received from IR receiver

void setup() {
  IRReceive.enableIRIn(); // Start IR receiver
  // Set the pins to which the LEDs are connected as output
  pinMode(blue_LED, OUTPUT);
  pinMode(green_LED, OUTPUT);
  pinMode(yellow_LED, OUTPUT);
  pinMode(red_LED, OUTPUT);
}

void loop() {
  if (IRReceive.decode(&result)) { // Check if there is any data coming from the IR receiver
    IRReceive.resume();            // Reset IR receiver to get other values 
  }
  
  if (result.value == oneKey) { // If key 1 is pressed on the remote controller
    digitalWrite(blue_LED, HIGH); // Turn ON the Blue LED
    // Turn OFF other LEDs
    digitalWrite(green_LED, LOW);
    digitalWrite(yellow_LED, LOW);
    digitalWrite(red_LED, LOW);
  }
  else if (result.value == twoKey) { // If key 2 is pressed on the remote controller
    digitalWrite(green_LED, HIGH); // Turn ON the Green LED
    // Turn OFF other LEDs
    digitalWrite(blue_LED, LOW);
    digitalWrite(yellow_LED, LOW);
    digitalWrite(red_LED, LOW);
  }
  else if (result.value == threeKey) { // If key 3 is pressed on the remote controller
    digitalWrite(yellow_LED, HIGH); // Turn ON the Yellow LED
    // Turn OFF other LEDs
    digitalWrite(blue_LED, LOW);
    digitalWrite(green_LED, LOW);
    digitalWrite(red_LED, LOW);
  }
  else if (result.value == fourKey) { // If key 4 is pressed on the remote controller
    digitalWrite(red_LED, HIGH); // Turn ON the Red LED
    // Turn OFF other LEDs
    digitalWrite(blue_LED, LOW);
    digitalWrite(green_LED, LOW);
    digitalWrite(yellow_LED, LOW);
  }
  else if (result.value == fiveKey) { // If key 5 is pressed on the remote controller
    // Turn ON all LEDs
    digitalWrite(red_LED, HIGH);
    digitalWrite(blue_LED, HIGH);
    digitalWrite(green_LED, HIGH);
    digitalWrite(yellow_LED, HIGH);
  }
  else if (result.value == zeroKey) { // If key 0 is pressed on the remote controller
    // Turn OFF all LEDs
    digitalWrite(blue_LED, LOW);
    digitalWrite(green_LED, LOW);
    digitalWrite(yellow_LED, LOW);
    digitalWrite(red_LED, LOW);
  }
  
  delay(200); // Wait for 200ms
}