// SA2 - Joystick ile Kamera Yön Kontrolü

#include <Servo.h>                                    // Servo motor kütüphanesini ekle

int xPin = A0;                                       // Joystick X ekseninin bağlandığı pin numarasını tanımla
int xPozisyonu = 0;                                  // Joystick X ekseninin pozisyonunun tutulacağı değişkeni tanımla

int servoPin = 3;                                    // Servo motorun bağlandığı dijital pin numarasını tanımla

int kameraPosizyon = 0;                              // Kamera pozisyon açısının tutulacağı değişkeni tanımla
 
Servo servo;                                         // servo adı ile kontrol edilecek servo motoru tanımla 

void setup() {
    pinMode(xPin, INPUT);                            // Joystick X ekseninin bağlandığı pini giriş olarak ayarla
    
    servo.attach(servoPin);                          // Servo motorun bağlandığı pini ayarla  
    servo.write(90);                                 // Servo motoru 90 derece konumuna götür
}
 
void loop() {
    xPozisyonu = analogRead(xPin);                   // Joystick X ekseninin pozisyonunun oku ve xPozisyonu değişkenine kaydet
  
    kameraPosizyon = map(xPozisyonu, 0, 1023, 180, 0);
    servo.write(kameraPosizyon);                     // Servo motorun açısını kameraPosizyon değişkenine göre ayarla
    delay(100);                                      // 100ms bekle
}
