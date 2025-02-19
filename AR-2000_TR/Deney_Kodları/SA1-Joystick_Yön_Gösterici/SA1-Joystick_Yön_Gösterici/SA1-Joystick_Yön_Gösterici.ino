// SA1 - Joystick Yön Gösterici

// LED'lerin bağlandığı pinleri tanımla
int sol = 4;
int sag = 3; 
int yukari = 5; 
int asagi = 2; 

int Joystick_VRX = A4;    // Joystick'in x ekseninin bağlandığı pini tanımla
int Joystick_VRY = A5;    // Joystick'in y ekseninin bağlandığı pini tanımla

int xPozisyonu = 0;       // Joystick X ekseninin pozisyonunun tutulacağı değişkeni tanımla
int yPozisyonu = 0;       // Joystick Y ekseninin pozisyonunun tutulacağı değişkeni tanımla

void setup() {
    // LED'lerin bağlandığı pinleri çıkış olarak ayarla
    pinMode(sol, OUTPUT); 
    pinMode(sag, OUTPUT); 
    pinMode(yukari, OUTPUT); 
    pinMode(asagi, OUTPUT); 
  
    pinMode(Joystick_VRX, INPUT);    // Joystick VRX ekseninin bağlandığı pini giriş olarak ayarla
    pinMode(Joystick_VRY, INPUT);    // Joystick VRY ekseninin bağlandığı pini giriş olarak ayarla
}

void loop() {
    // Joystick X ekseninin pozisyonunun oku ve xPozisyonu değişkenine kaydet
    xPozisyonu = analogRead(Joystick_VRX);
    // Joystick Y ekseninin pozisyonunun oku ve yPozisyonu değişkenine kaydet
    yPozisyonu = analogRead(Joystick_VRY);

    if (xPozisyonu > 900 && yPozisyonu > 120) {    // Yön sağ ise
        // Sağı temsil eden LED'i yak, diğerlerini söndür
        digitalWrite(sag, HIGH);
        digitalWrite(sol, LOW);
        digitalWrite(yukari, LOW);
        digitalWrite(asagi, LOW);
    }
    else if (xPozisyonu < 120 && yPozisyonu > 120) {    // Yön sol ise
        // Solu temsil eden LED'i yak, diğerlerini söndür
        digitalWrite(sag, LOW);
        digitalWrite(sol, HIGH);
        digitalWrite(yukari, LOW);
        digitalWrite(asagi, LOW);
    }
    else if (xPozisyonu > 120 && yPozisyonu < 120) {    // Yön yukarı ise
        // Yukarı temsil eden LED'i yak, diğerlerini söndür
        digitalWrite(sag, LOW);
        digitalWrite(sol, LOW);
        digitalWrite(yukari, HIGH);
        digitalWrite(asagi, LOW);
    }
    else if (xPozisyonu > 120 && yPozisyonu > 900) {    // Yön aşağı ise
        // Aşağı temsil eden LED'i yak, diğerlerini söndür
        digitalWrite(sag, LOW);
        digitalWrite(sol, LOW);
        digitalWrite(yukari, LOW);
        digitalWrite(asagi, HIGH);
    }
    else {    // Joystick ortada ise
        // Bütün LED'leri söndür
        digitalWrite(sag, LOW);
        digitalWrite(sol, LOW);
        digitalWrite(yukari, LOW);
        digitalWrite(asagi, LOW);
    }
}
