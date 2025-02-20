//S101 - Processing_Plane

//Define relevant variables
int i, j;
float height;
float angle;
int distance1;
int distance2;
float birdX;

float birdY;
float seaX;
String dataIn;

float[] cloudX = new float[6];
float[] cloudY = new float[6];

PImage cloud;
PImage bird;
PImage plane;
PImage sea;

import processing.serial.*;                //Initialize serial communication
Serial myPort;                            //Establish serial communication through port

void setup() {
    myPort = new Serial(this, "COM3", 9600);  //Use COM3 port for Arduino connection in serial port screen,
                                              //change according to your port number
    myPort.bufferUntil(10);
    frameRate(30);
    size(800, 600);
    rectMode(CORNERS);
    noCursor();
    textSize(16);
    height = 300;
    //Load relevant images
    cloud = loadImage("cloud.png");
    bird = loadImage("bird.png");
    plane = loadImage("plane.png");
    sea = loadImage("sea.png");
    for (int i = 1; i <= 5; i = i+1) {
        cloudX[i] = random(1000);
        cloudY[i] = random(400);
    }
}

void serialEvent(Serial p) {
    dataIn = p.readString();
    distance2 = parseInt(trim(dataIn));
    println(distance2);
    if (distance2 > 1 && distance2 < 100) {
        distance1 = distance2;
    }
}

void draw() {
    background(0, 0, 0);
    drawSky();
    fill(5, 72, 0);
    for (int i = -2; i <= 4; i = i+1) {
        image(sea, 224*i + seaX, 550, 224, 58);
    }
    seaX = seaX - cos(radians(angle)) * 10;
    if (seaX < -224) {
        seaX = 224;
    }
    text(angle, 10, 30);
    text(height, 10, 60);
    angle = (18 - distance1) * 4;
    height = height + sin(radians(angle)) * 10;
    if (height < 0) {
        height = 0;
    }
    if (height > 600) {
        height = 600;
    }
    drawPlane(height, angle);
    birdX = birdX - cos(radians(angle)) * 10;
    if (birdX < -30) {
        birdX = 900;
        birdY = random(600);
    }
    for (int i = 1; i <= 5; i = i+1) {
        cloudX[i] = cloudX[i] - cos(radians(angle)) * (10 + 2*i);
        image(cloud, cloudX[i], cloudY[i], 300, 200);
        if (cloudX[i] < -300) {
            cloudX[i] = 1000;
            cloudY[i] = random(400);
        }
    }
    image(bird, birdX, birdY, 72, 46);
}

void drawSky() {
    noStroke();
    rectMode(CORNERS);
    for (int i = 1; i < 600; i = i+10) {
        fill(49 + i*0.165, 118 + i*0.118, 181 + i*0.075);
        rect(0, i, 800, i+10);
    }
}

void drawPlane(float Y, float inclinationAngle) {
    noStroke();
    pushMatrix();
    translate(400, Y);
    rotate(radians(inclinationAngle));
    scale(0.5);
    image(plane, -111, -55, 400, 196);
    popMatrix();
}
