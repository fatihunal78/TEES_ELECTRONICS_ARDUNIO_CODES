//S100 - Processing_code

import processing.serial.*;                    // Start serial communication

// Define relevant variables
int segs = 12;
int steps = 6;
float rotAdjust = TWO_PI / segs / 2;
float radius;

float segWidth;
float interval = TWO_PI / segs;

color bc = color(0, 0, 0);

byte[] rgbdata = new byte[64];

int data;
int data1;
int data2;

Serial ardPort;                               // Perform serial communication through port

void setup() {
    size(600, 600);                          // Create a 600x600 square
    background(0);                           // Make the background of our square black
    smooth();
    ellipseMode(RADIUS);
    noStroke();

    // Draw a circle that is 90% of the drawing area
    radius = min(width, height) * 0.45;
    segWidth = radius / steps;
    println(Serial.list());
    ardPort = new Serial(this, "COM3", 9600); // Use COM3 port for Arduino connection in serial port screen,
                                             // change according to your port number
    drawTintWheel();
}

void draw() {
    if (mousePressed && (mouseButton == LEFT)) { // If left mouse button is pressed
        bc = get(mouseX, mouseY);
        
        println("R G B = " + int(red(bc)) + " " + int(green(bc)) + " " + int(blue(bc)));
        
        rgbdata[0] = (byte(int(red(bc))));
        rgbdata[1] = (byte(int(green(bc))));
        rgbdata[2] = (byte(int(blue(bc))));
        
        data = int(red(bc));
        data1 = int(green(bc));
        data2 = int(blue(bc));
        
        println("R G B  data= " + data + " " + data1 + " " + data2);

        ardPort.write('R');
        ardPort.write(data);
        ardPort.write(data1);
        ardPort.write(data2);
    }
}

void drawTintWheel() {
    for (int j = 0; j < steps; j++) {
        color[] cols = {
            color(255, 255, ((255/(steps-1))*j)),
            color(255, ((170)+(170/steps)*j), 255/steps*j),
            color(255, ((127)+(127/steps)*j), (255/steps)*j),
            color(255, ((102)+(102/(steps-2))*j), (255/steps)*j),
            
            color(255, (255/steps)*j, ((255)/steps)*j),
            color(255, (255/steps)*j, ((127)+(127/steps)*j)),
            color(255, (255/steps)*j, 255),
            color(((127)+(127/steps)*j), (255/steps)*j, 255),
            
            color(((255)/steps)*j, (255/steps)*j, 255),
            color((255/steps)*j, 255, ((102)+(102/steps)*j)),
            color((255/(steps))*j, 255, (255/(steps))*j),
            color(((127)+(127/steps)*j), 255, (255/steps)*j)
        };

        for (int i = 0; i < segs; i++) {
            fill(cols[i]);
            arc(width/2, height/2, radius, radius,
                interval*i+rotAdjust, interval*(i+1)+rotAdjust);
        }
        radius -= segWidth;
    }
}
