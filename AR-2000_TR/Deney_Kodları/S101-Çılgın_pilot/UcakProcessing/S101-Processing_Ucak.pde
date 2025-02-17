//S101 - Processing_Ucak

//İlgili değişkenleri tanımla
int i, j;
float Tinggi;
float Sudut;
int Jarak1;
int Jarak2;
float kusX;

float kusY;
float denizX;
String DataIn;

float[] bulutX = new float[6];
float[] bulutY = new float[6];

PImage bulut;
PImage kus;
PImage ucak;
PImage deniz;

import processing.serial.*;                    //Seri haberleşmeyi başlat
Serial myPort;                                //Seri haberleşmeyi port üzerinden yap   

void setup() {
    myPort = new Serial(this, "COM3", 9600);  //Seri port ekranında Arduino bağlantısı için COM6 portundan faydalan, 
                                             //kendi port numaranıza göre değiştirin
    myPort.bufferUntil(10);
    frameRate(30);
    size(800, 600);
    rectMode(CORNERS);
    noCursor();
    textSize(16);
    Tinggi = 300;
    
    //İlgili resimleri yükle
    bulut = loadImage("bulut.png");
    kus = loadImage("kus.png");
    ucak = loadImage("ucak.png");
    deniz = loadImage("deniz.png");
    
    for (int i = 1; i <= 5; i++) {
        bulutX[i] = random(1000);
        bulutY[i] = random(400);
    }
}

void serialEvent(Serial p) {
    DataIn = p.readString();
    Jarak2 = int(trim(DataIn));
    println(Jarak2);
    
    if (Jarak2 > 1 && Jarak2 < 100) {
        Jarak1 = Jarak2;
    }
}

void draw() {
    background(0, 0, 0);
    Ciel();
    fill(5, 72, 0);
    
    for (int i = -2; i <= 4; i++) {
        image(deniz, 224*i + denizX, 550, 224, 58);
    }
    
    denizX = denizX - cos(radians(Sudut)) * 10;
    if (denizX < -224) {
        denizX = 224;
    }
    
    text(Sudut, 10, 30);
    text(Tinggi, 10, 60);
    Sudut = (18 - Jarak1) * 4;
    Tinggi = Tinggi + sin(radians(Sudut)) * 10;
    
    if (Tinggi < 0) {
        Tinggi = 0;
    }
    if (Tinggi > 600) {
        Tinggi = 600;
    }
    
    TraceAvion(Tinggi, Sudut);
    kusX = kusX - cos(radians(Sudut)) * 10;
    
    if (kusX < -30) {
        kusX = 900;
        kusY = random(600);
    }
    
    for (int i = 1; i <= 5; i++) {
        bulutX[i] = bulutX[i] - cos(radians(Sudut)) * (10 + 2*i);
        image(bulut, bulutX[i], bulutY[i], 300, 200);
        if (bulutX[i] < -300) {
            bulutX[i] = 1000;
            bulutY[i] = random(400);
        }
    }
    
    image(kus, kusX, kusY, 72, 46);
}

void Ciel() {
    noStroke();
    rectMode(CORNERS);
    for (int i = 1; i < 600; i += 10) {
        fill(49 + i*0.165, 118 + i*0.118, 181 + i*0.075);
        rect(0, i, 800, i+10);
    }
}

void TraceAvion(float Y, float SudutInklinasi) {
    noStroke();
    pushMatrix();
    translate(400, Y);
    rotate(radians(SudutInklinasi));
    scale(0.5);
    image(ucak, -111, -55, 400, 196);
    popMatrix();
}
