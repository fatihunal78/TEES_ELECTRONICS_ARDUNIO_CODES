//S97 - Processing_Radar

import processing.serial.*;      //Start serial communication
import processing.serial.*;      //Add serial communication library
import java.awt.event.KeyEvent;  //Add required library to read data from serial port
import java.io.IOException;


Serial myPort;                   //Create myPort object to control Serial port

// Define necessary variables
String angle = "";              //Define angle variable to control servo
String distance = "";           //Define distance variable to store distance measurement
String data = "";              //Define variable to store data
String object_detection;        //Define variable for object absence state
float pixel_distance;          //Define pixel_distance variable for visual distance transfer
int iangle, idistance;
int input1 = 0;                //Define input1 and input2 variables
int input2 = 0;
PFont orcFont;

void setup() {
    size(1280, 750);           //Visual screen size
    smooth();
    myPort = new Serial(this, "COM3", 9600);  //Serial communication port and COM address defined
    myPort.bufferUntil('.');   //Read data from serial port until '.' character
    orcFont = loadFont("OCRAExtended-30.vlw");
}

void draw() {
    fill(98, 245, 31);
    textFont(orcFont);
    noStroke();
    fill(0, 4);
    rect(0, 0, width, height - height * 0.065);
    
    fill(98, 245, 31);
    drawRadar();
    drawLine();
    drawObject();
    drawText();
}

void serialEvent(Serial myPort) {
    data = myPort.readStringUntil('.');
    data = data.substring(0, data.length() - 1);
    
    input1 = data.indexOf(",");
    angle = data.substring(0, input1);
    distance = data.substring(input1 + 1, data.length());
    
    iangle = int(angle);
    idistance = int(distance);
}

void drawRadar() {
    pushMatrix();
    translate(width/2, height - height * 0.074);
    noFill();
    strokeWeight(2);
    stroke(98, 245, 31);
    // draws the arc lines
    arc(0, 0, (width - width * 0.0625), (width - width * 0.0625), PI, TWO_PI);
    arc(0, 0, (width - width * 0.27), (width - width * 0.27), PI, TWO_PI);
    arc(0, 0, (width - width * 0.479), (width - width * 0.479), PI, TWO_PI);
    arc(0, 0, (width - width * 0.687), (width - width * 0.687), PI, TWO_PI);
    // draws the angle lines
    line(-width/2, 0, width/2, 0);
    line(0, 0, (-width/2) * cos(radians(30)), (-width/2) * sin(radians(30)));
    line(0, 0, (-width/2) * cos(radians(60)), (-width/2) * sin(radians(60)));
    line(0, 0, (-width/2) * cos(radians(90)), (-width/2) * sin(radians(90)));
    line(0, 0, (-width/2) * cos(radians(120)), (-width/2) * sin(radians(120)));
    line(0, 0, (-width/2) * cos(radians(150)), (-width/2) * sin(radians(150)));
    line((-width/2) * cos(radians(30)), 0, width/2, 0);
    popMatrix();
}

void drawObject() {
    pushMatrix();
    translate(width/2, height - height * 0.074);
    strokeWeight(9);
    stroke(255, 10, 10);       //red color
    pixel_distance = idistance * ((height - height * 0.1666) * 0.025);
    if (idistance < 40) {
        line(pixel_distance * cos(radians(iangle)), 
             -pixel_distance * sin(radians(iangle)),
             (width - width * 0.505) * cos(radians(iangle)),
             -(width - width * 0.505) * sin(radians(iangle)));
    }
    popMatrix();
}

void drawLine() {
    pushMatrix();
    strokeWeight(9);
    stroke(30, 250, 60);
    translate(width/2, height - height * 0.074);  //moves the starting coordinates to new location
    //draws the line according to the angle
    line(0, 0, (height - height * 0.12) * cos(radians(iangle)), 
         -(height - height * 0.12) * sin(radians(iangle)));
    popMatrix();
}

void drawText() {
    pushMatrix();
    if (idistance > 40) {
        object_detection = "Out of Range";
    } else {
        object_detection = "In Range";
    }
    fill(0, 0, 0);
    noStroke();
    rect(0, height - height * 0.0648, width, height);
    fill(98, 245, 31);
    textSize(25);
    
    text("10cm", width - width * 0.3854, height - height * 0.0833);
    text("20cm", width - width * 0.281, height - height * 0.0833);
    text("30cm", width - width * 0.177, height - height * 0.0833);
    text("40cm", width - width * 0.0729, height - height * 0.0833);
    textSize(40);
    text("Object: " + object_detection, width - width * 0.875, height - height * 0.0277);
    text("angle: " + iangle + " °", width - width * 0.48, height - height * 0.0277);
    text("distance: ", width - width * 0.26, height - height * 0.0277);
    if (idistance < 40) {
        text("        " + idistance + " cm", width - width * 0.225, height - height * 0.0277);
    }
    textSize(25);
    fill(98, 245, 60);
    translate((width - width * 0.4994) + width/2 * cos(radians(30)),
             (height - height * 0.0907) - width/2 * sin(radians(30)));
    rotate(-radians(-60));
    text("30°", 0, 0);
    resetMatrix();
    translate((width - width * 0.503) + width/2 * cos(radians(60)),
             (height - height * 0.0888) - width/2 * sin(radians(60)));
    rotate(-radians(-30));
    text("60°", 0, 0);
    resetMatrix();
    translate((width - width * 0.507) + width/2 * cos(radians(90)),
             (height - height * 0.0833) - width/2 * sin(radians(90)));
    rotate(radians(0));
    text("90°", 0, 0);
    resetMatrix();
    translate(width - width * 0.513 + width/2 * cos(radians(120)),
             (height - height * 0.07129) - width/2 * sin(radians(120)));
    rotate(radians(-30));
    text("120°", 0, 0);
    resetMatrix();
    translate((width - width * 0.5104) + width/2 * cos(radians(150)),
             (height - height * 0.0574) - width/2 * sin(radians(150)));
    rotate(radians(-60));
    text("150°", 0, 0);
    popMatrix();
}
