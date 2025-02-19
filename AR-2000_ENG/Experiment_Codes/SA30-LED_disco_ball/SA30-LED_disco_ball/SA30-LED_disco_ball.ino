//SA30 - LED disco ball

/*
 * AlaLed library was used to make the Disco Light Module in various colors and animations.
 */

#include <AlaLed.h> // Add library

AlaLed Animation; // Create an object named Animation
byte pins[] = {5, 6, 9, 10}; // Define the pins to which the LEDs are connected

// Pull the following commands from the library for animation loops
AlaSeq seq[] = {
  { ALA_FADEIN, 1000, 1000 },
  { ALA_ON, 1000, 1000 },
  { ALA_FADEOUT, 1000, 1000 },
  { ALA_BARSHIFTRIGHT, 1000, 1000 },
  { ALA_BARSHIFTLEFT, 1000, 1000 },
  { ALA_OFF, 1000, 1000 },
  { ALA_PIXELSHIFTRIGHT, 700, 1400 },
  { ALA_PIXELSHIFTLEFT, 700, 1400 },
  { ALA_BLINKALT, 500, 3000 },
  { ALA_PIXELSMOOTHSHIFTRIGHT, 1000, 4000 },
  { ALA_PIXELSMOOTHSHIFTLEFT, 1000, 4000 },
  { ALA_FADEINOUT, 1000, 4000 },
  { ALA_COMET, 1000, 4000 },
  { ALA_GLOW, 1000, 4000 },
  { ALA_STROBO, 200, 4000 },
  { ALA_ENDSEQ, 0, 0 }
};

void setup() {
  Animation.initPWM(4, pins); // Set the pin numbers and number of them to which the LEDs are connected
  Animation.setAnimation(seq); // Set which animation will be played
}

void loop() {
  Animation.runAnimation(); // Run the animation
}