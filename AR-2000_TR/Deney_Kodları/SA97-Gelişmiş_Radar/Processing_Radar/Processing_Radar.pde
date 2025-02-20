//SA97 - Processing_Radar


import processing.serial.*;      //Seri haberleşmeyi başlat
import java.awt.event.KeyEvent;  //Serial porttan verileri okumak için gerekli kütüphaneyi ekle
import java.io.IOException;


Serial myPort;                   //Serial portu kontrol etmek için myPort isimli obje oluştur

//Gerekli değişkenleri tanımla
String aci = "";                //Servo açısını kontrol etmek için aci değişkeni tanımla
String mesafe = "";             //Mesafe ölçümünün kayıt edileceği mesafe değişkeni tanımla
String veri = "";               //Verilerin kaydedileceği değişken tanımla
String nesne_algilama;          //Nesnenin olmama durumu için değişkeni tanımla
float piksel_mesafe;            //Mesafenin görsel olarak aktarılması için piksel_mesafe değişkeni tanımla
int iaci, imesafe;
int girdi1 = 0;                 //Girdi1 ve girdi2 değişkenleri tanımla
int girdi2 = 0;
PFont orcFont;

void setup() {
    size(1280, 750);            //Görsel ekran boyutu
    smooth();
    myPort = new Serial(this, "COM3", 9600);  //Seri haberleşme portu ve COM adresi tanımlandı
    myPort.bufferUntil('.');    //Seri porttan '.' işareti gelene kadar verileri oku
    orcFont = loadFont("OCRAExtended-30.vlw");
}

void draw() {
    fill(98, 245, 31);
    textFont(orcFont);
    noStroke();
    fill(0, 4);
    rect(0, 0, width, height-height*0.065);
    
    fill(98, 245, 31);
    drawRadar();
    drawLine();
    drawObject();
    drawText();
}

void serialEvent(Serial myPort) {
    veri = myPort.readStringUntil('.');
    veri = veri.substring(0, veri.length()-1);
    
    girdi1 = veri.indexOf(",");
    aci = veri.substring(0, girdi1);
    mesafe = veri.substring(girdi1+1, veri.length());
    
    iaci = parseInt(aci);
    imesafe = parseInt(mesafe);
}

void drawRadar() {
    pushMatrix();
    translate(width/2, height-height*0.074);
    noFill();
    strokeWeight(2);
    stroke(98, 245, 31);
    
    // Draws the arc lines
    arc(0, 0, (width-width*0.0625), (width-width*0.0625), PI, TWO_PI);
    arc(0, 0, (width-width*0.27), (width-width*0.27), PI, TWO_PI);
    arc(0, 0, (width-width*0.479), (width-width*0.479), PI, TWO_PI);
    arc(0, 0, (width-width*0.687), (width-width*0.687), PI, TWO_PI);
    
    // Draws the angle lines
    line(-width/2, 0, width/2, 0);
    line(0, 0, (-width/2)*cos(radians(30)), (-width/2)*sin(radians(30)));
    line(0, 0, (-width/2)*cos(radians(60)), (-width/2)*sin(radians(60)));
    line(0, 0, (-width/2)*cos(radians(90)), (-width/2)*sin(radians(90)));
    line(0, 0, (-width/2)*cos(radians(120)), (-width/2)*sin(radians(120)));
    line(0, 0, (-width/2)*cos(radians(150)), (-width/2)*sin(radians(150)));
    line((-width/2)*cos(radians(30)), 0, width/2, 0);
    popMatrix();
}

void drawObject() {
    pushMatrix();
    translate(width/2, height-height*0.074);
    strokeWeight(9);
    stroke(255, 10, 10);        //Red color
    piksel_mesafe = imesafe*((height-height*0.1666)*0.025);
    
    if (imesafe < 40) {
        line(piksel_mesafe*cos(radians(iaci)), -piksel_mesafe*sin(radians(iaci)),
             (width-width*0.505)*cos(radians(iaci)), -(width-width*0.505)*sin(radians(iaci)));
    }
    popMatrix();
}

void drawLine() {
    pushMatrix();
    strokeWeight(9);
    stroke(30, 250, 60);
    translate(width/2, height-height*0.074);  //Moves the starting coordinates to new location
    //Draws the line according to the angle
    line(0, 0, (height-height*0.12)*cos(radians(iaci)), -(height-height*0.12)*sin(radians(iaci)));
    popMatrix();
}

void drawText() {
    pushMatrix();
    
    if (imesafe > 40) {
        nesne_algilama = "Menzil Disi";
    } else {
        nesne_algilama = "Menzilde";
    }
    
    fill(0, 0, 0);
    noStroke();
    rect(0, height-height*0.0648, width, height);
    fill(98, 245, 31);
    textSize(25);
    
    text("10cm", width-width*0.3854, height-height*0.0833);
    text("20cm", width-width*0.281, height-height*0.0833);
    text("30cm", width-width*0.177, height-height*0.0833);
    text("40cm", width-width*0.0729, height-height*0.0833);
    
    textSize(40);
    text("Nesne: " + nesne_algilama, width-width*0.875, height-height*0.0277);
    text("aci: " + iaci + " °", width-width*0.48, height-height*0.0277);
    text("mesafe: ", width-width*0.26, height-height*0.0277);
    
    if (imesafe < 40) {
        text("        " + imesafe + " cm", width-width*0.225, height-height*0.0277);
    }
    
    textSize(25);
    fill(98, 245, 60);
    
    translate((width-width*0.4994)+width/2*cos(radians(30)), (height-height*0.0907)-width/2*sin(radians(30)));
    rotate(-radians(-60));
    text("30°", 0, 0);
    resetMatrix();
    
    translate((width-width*0.503)+width/2*cos(radians(60)), (height-height*0.0888)-width/2*sin(radians(60)));
    rotate(-radians(-30));
    text("60°", 0, 0);
    resetMatrix();
    
    translate((width-width*0.507)+width/2*cos(radians(90)), (height-height*0.0833)-width/2*sin(radians(90)));
    rotate(radians(0));
    text("90°", 0, 0);
    resetMatrix();
    
    translate(width-width*0.513+width/2*cos(radians(120)), (height-height*0.07129)-width/2*sin(radians(120)));
    rotate(radians(-30));
    text("120°", 0, 0);
    resetMatrix();
    
    translate((width-width*0.5104)+width/2*cos(radians(150)), (height-height*0.0574)-width/2*sin(radians(150)));
    rotate(radians(-60));
    text("150°", 0, 0);
    popMatrix();
}
