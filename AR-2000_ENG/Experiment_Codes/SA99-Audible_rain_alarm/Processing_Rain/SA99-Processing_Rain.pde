//S99 - Processing_Rain

import processing.serial.*;    // Add serial communication library to communicate with Arduino
import ddf.minim.*;          // Add minim library for playing sounds
Serial serialPort;           // Create an object named serialPort to read values from Serial port
Minim minim;                // Create a minim object
AudioPlayer rainPlayer;      // Create an object to store rain sound
AudioPlayer thunderPlayer;   // Create an object to store thunder sound
float incomingData;         // Variable defined to hold values read from Serial port


void setup() {
    minim = new Minim(this);                                    // Setup minim
    rainPlayer = minim.loadFile("rain.mp3");                 // Load rain sound effect from data folder
    thunderPlayer = minim.loadFile("thunder.mp3");       // Load thunder sound effect from data folder
    serialPort = new Serial(this, "COM4", 9600);              // Enter required Port and BaudRate for Arduino communication
                                                              // You can change COM value according to your Arduino
    serialPort.bufferUntil('\n');                            // Get data from Arduino until end of line
}

void serialEvent(Serial serialPort) {
    incomingData = float(serialPort.readStringUntil('\n'));   // Save incoming Arduino data to incomingData variable
    println(incomingData);                                    // Show incomingData on serial monitor
}

void draw() {
    println(incomingData);                                    // Show incomingData on serial monitor
    
    if (incomingData == 0) {                                 // If incoming data is 0
        rainPlayer.pause();                                   // Stop playing sound
        thunderPlayer.pause();                                // Stop playing sound
    }

    if (incomingData == 1) {                                 // If incoming data is 1
        rainPlayer.rewind();                                  // To repeat when sound ends
        thunderPlayer.rewind();                               // To repeat when sound ends
        rainPlayer.play();                                    // Play rain sound
        thunderPlayer.play();                                 // Play thunder sound
        
        for (int i = 0; i < 100; i++) {
            delay(50);
            if (incomingData == 0) {                         // If incoming data is 0
                rainPlayer.pause();                           // Stop playing sound
                thunderPlayer.pause();                        // Stop playing sound
            }
        }
    }
}
