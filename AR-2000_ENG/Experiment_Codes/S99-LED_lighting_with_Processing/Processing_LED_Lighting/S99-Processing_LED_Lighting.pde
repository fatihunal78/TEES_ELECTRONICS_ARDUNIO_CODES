//S99 - Processing_LED

import processing.serial.*;                    // Initialize serial communication
Serial myPort;                                // Create serial communication through port

void setup() {                                // Setup function
    myPort = new Serial(this, "COM3", 9600);  // Use COM3 port for Arduino connection in serial port screen
                                              // Change according to your port number
    
    size(300, 300);                           // Create a 300x300 square
    background(0, 0, 0);                      // Make the background of our square black
    
    fill(color(255, 255, 255));               // Set the initial fill color of our LED to white using RGB values
}

void draw() {                                 // Create drawing function
    ellipse(150, 150, 200, 200);             // Create a 200x200 LED centered at 150,150
    
    if (mouseX > 75 && mouseX < 225 && 
        mouseY > 75 && mouseY < 225) {        // If computer mouse is between specified values (i.e., on the circle)
        
        if (mousePressed && 
            (mouseButton == LEFT)) {          // If left mouse button is pressed
            myPort.write('1');                // Send value 1 to serial port
            fill(color(255, 255, 0));         // Make circle's fill color yellow
        }
        
        if (mousePressed && 
            (mouseButton == RIGHT)) {         // If right mouse button is pressed
            myPort.write('0');                // Send value 0 to serial port
            fill(color(255, 255, 255));       // Make circle's fill color white
        }
    }
}
