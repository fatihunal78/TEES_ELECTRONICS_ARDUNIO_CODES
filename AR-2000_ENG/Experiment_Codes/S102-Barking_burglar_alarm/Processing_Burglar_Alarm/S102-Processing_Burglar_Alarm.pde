//S102 - Processing

import processing.serial.*;    // Add serial communication library to communicate with Arduino
import ddf.minim.*;          // Add minim library for playing sounds
Serial myPort;               // Create an object named myPort for reading values from Serial port
Minim minim;                // Create a minim object
AudioPlayer player;          // Create an object to store sounds
float incoming_data;         // Define variable to hold values read from Serial port


void setup() {
    minim = new Minim(this);                          // Setup minim
    player = minim.loadFile("nightdog.mp3");          // Load dog sound effect 'nightdog.mp3' from Data folder into player
    
    myPort = new Serial(this, "COM4", 9600);          // Enter required Port and BoundRate values for Arduino communication
                                                      // You can change COM value according to your Arduino
    myPort.bufferUntil('\n');                         // Get data from Arduino until end of line
}

void serialEvent(Serial myPort) {
    incoming_data = float(myPort.readStringUntil('\n'));  // Save incoming Arduino data to incoming_data variable
    println(incoming_data);                               // Show incoming_data on serial monitor
}

void draw() {
    println(incoming_data);                    // Show incoming_data on serial monitor

    if (incoming_data == 0) {                 // If incoming data is 0
        player.pause();                       // Stop playing sound
    }

    if (incoming_data == 1) {                // If incoming data is 1
        player.rewind();                     // To repeat when sound ends
        player.play();                       // Play dog sound
        
        for (int i = 0; i < 100; i++) {
            delay(50);
            if (incoming_data == 0) {        // If incoming data is 0
                player.pause();              // Stop playing sound
            }
        }
    }
}
