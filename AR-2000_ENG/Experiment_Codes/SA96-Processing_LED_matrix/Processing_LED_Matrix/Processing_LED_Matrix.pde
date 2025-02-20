//S96 - Processing_LED_Matrix

import processing.serial.*;                          // Start serial communication between Processing and Arduino

Serial serialPort = new Serial(this, Serial.list()[0], 9600);    // Create an object named serialPort

int LEDSize = 50;
int columns, rows;
color[][] grid;


void setup() {
    size(400, 400);                                 // Create a 400x400 LED matrix (width, height)
    columns = width/LEDSize;                        // width value 400, LEDSize value 50, 400/50 = 8 columns
    rows = height/LEDSize;                          // width value 400, LEDSize value 50, 400/50 = 8 rows
    grid = new color[columns][rows];

    // Initialize columns and rows as white at the start
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            grid[i][j] = color(255);                // Make all white
        }
    }
}

void draw() {
    background(0);                                  // Set background color to black
    
    for (int i = 0; i < columns; i++) {
        for (int j = 0; j < rows; j++) {
            int x = i * LEDSize;                    // x variable to understand where the mouse is on x plane
            int y = j * LEDSize;                    // y variable to understand where the mouse is on y plane
            
            if (mouseX > x && mouseX < (x + LEDSize) && 
                mouseY > y && mouseY < (y + LEDSize)) {    // If mouse is over the LEDs
                if (mousePressed && (mouseButton == LEFT)) {        // If left mouse button is pressed
                    grid[i][j] = color(255, 0, 0);                 // Make the pressed LED red
                } else if (mousePressed && (mouseButton == RIGHT)) {// If right mouse button is pressed
                    grid[i][j] = color(255, 255, 255);            // Make the pressed LED white
                }
            }
            
            fill(grid[i][j]);                       // Make the LED area grid-shaped (box)
            ellipse(x + 24, y + 24, LEDSize, LEDSize);    // Create ellipse-shaped LEDs
        }
    }
}

void mouseReleased() {
    // When right or left mouse button is pressed, send data to Arduino without doing any other operation
    int[] serialData = new int[8];                 // Variable to hold data to be sent

    for (int col = 0; col < 8; col++) {
        for (int row = 7; row >= 0; row--) {
            if (grid[col][row] == color(255, 0, 0)) {
                serialData[col] += pow(2, 7 - row);
            }
        }
    }

    for (int col = 0; col < 8; col++) {
        serialPort.write(serialData[col]);          // Send data to Arduino using serial monitor
    }
}
