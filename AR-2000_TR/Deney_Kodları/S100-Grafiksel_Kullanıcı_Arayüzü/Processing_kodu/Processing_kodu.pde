//S100 - Processing_kodu

import processing.serial.*;                    // Seri haberleşmeyi başlat

// İlgili değişkenleri tanımla
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

Serial ardPort;                               // Seri haberleşmeyi port üzerinden yap 

void setup() {
    size(600, 600);                          // 600'a 600 bir kare oluştur 
    background(0);                           // Oluşturduğumuz karenin arka planını siyah yap 
    smooth();
    ellipseMode(RADIUS);
    noStroke();

    // Çizim alanının %90'ı büyüklüğünde bir çember çiz
    radius = min(width, height) * 0.45;
    segWidth = radius / steps;
    println(Serial.list());
    
    // Seri port ekranında Arduino bağlantısı için COM6 portundan faydalan, kendi port numaranıza göre 
    // değiştirin
    ardPort = new Serial(this, "COM3", 9600);
    
    drawTintWheel();
}

void draw() {
    if (mousePressed && (mouseButton == LEFT)) {    // Eğer farenin sol tuşuna basılmış ise 
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
