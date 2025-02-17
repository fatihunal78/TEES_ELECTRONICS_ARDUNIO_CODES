// SA60 - Yılan Oyunu

//Kütüphaneleri ekle
#include <LedControl.h> 
#include <MaxMatrix.h>

//LED Matriks bağlantılarını tanımla
#define CLK     8   //CLK pinini tanımla
#define CS      9   //CS pinini tanımla
#define DIN     10  //DIN pinini tanımla

int Led_Matrix_Sayisi = 1;  //LED matriksler arka arkaya bağlanabilir
                           //Birden fazla matriks bağlanacak ise buradaki sayıyı değiştirebilirsiniz

MaxMatrix m(DIN, CS, CLK, Led_Matrix_Sayisi);  //Matriks pinlerinin bağlantıları ile m matriksini tanımla 
LedControl lc = LedControl(DIN, CLK, CS, 1);   //lc adında LedControl objesini oluştur

//Joystick bağlantırlarını tanımla
#define VRX          A4  //Joystickin VRX bacağının bağlandığı pini tanımla
#define VRY          A5  //Joystickin VRX bacağının bağlandığı pini tanımla
#define SW           2   //Joystickin SW bacağının bağlandığı pini tanımla
#define hoparlorPin  4   //Hoparlorün bağlandığı pin numarasını tanımla

char string1[] = "   OYUN BITTI   ";  //Ekranda kaydırılmasını istediğiniz yazıyı çift tırnakların içine yazın

#define Boyut           8
#define Gecikme_Suresi  20

byte buffer[10];
int yilan[Boyut*Boyut][2];  
int length;
int food[2], v[2];
bool oyun_bitti = false;
long simdiki_zaman;
long onceki_zaman;
int blink_count;
const short mesaj_hizi = 5;
int skor = 0;

void oyunu_baslat() {
    onceki_zaman = simdiki_zaman = 0;  //onceki_zaman ve simdiki_zaman değişkenlerini sıfırla
    blink_count = 3;
    int half = Boyut / 2;
    length = Boyut / 3;

    for (int i = 0; i < length; i++) {
        yilan[i][0] = half - 1;
        yilan[i][1] = half + i;
    }

    food[0] = half + 1;
    food[1] = half - 1;

    v[0] = 0;
    v[1] = -1;
}

void render() {
    for (int i = 0; i < length; i++) {
        lc.setLed(0, yilan[i][0], yilan[i][1], 1);
    }
    lc.setLed(0, food[0], food[1], 1);
}

void ekrani_Temizle() { 
    for (int x = 0; x < Boyut; x++) {
        for (int y = 0; y < Boyut; y++) {
            lc.setLed(0, x, y, 0);
        }
    }
}

bool advance() {
    int head[2] = {yilan[0][0] + v[0], yilan[0][1] + v[1]};

    if (head[0] < 0 || head[0] >= Boyut) {
        delay(1000);
        oyun_bitti_mesaji();
        return true;
    }

    if (head[1] < 0 || head[1] >= Boyut) {
        delay(1000);
        oyun_bitti_mesaji();
        return true;
    }

    for (int i = 0; i < length; i++) {
        if (yilan[i][0] == head[0] && yilan[i][1] == head[1]) {
            delay(1000);
            oyun_bitti_mesaji();
            return true;
        }
    }

    bool grow = (head[0] == food[0] && head[1] == food[1]);
    if (grow) {
        tone(hoparlorPin, 500);
        length++;
        skor = skor + 5;    
        randomSeed(simdiki_zaman);    
        food[0] = random(Boyut);
        food[1] = random(Boyut);
        delay(50);
        noTone(hoparlorPin);
    }

    for (int i = length - 1; i >= 0; i--) {
        yilan[i + 1][0] = yilan[i][0];
        yilan[i + 1][1] = yilan[i][1];
    }
    yilan[0][0] += v[0];
    yilan[0][1] += v[1];
    return false;
}

void setup() {
    pinMode(SW, INPUT_PULLUP);         //Joystick SW pinini giriş olarak ayarla 
    pinMode(VRX, INPUT);               //Joystick VRX pinini giriş olarak Ayarla 
    pinMode(VRY, INPUT);               //Joystick VRY pinini giriş olarak Ayarla 
    pinMode(hoparlorPin, OUTPUT);      //Hoparlör pinini çıkış olarak ayarla
  
    attachInterrupt(digitalPinToInterrupt(SW), yeniden_baslat, RISING);  //Kesmeyi aktif et 
                                                                         //Kesme Joystickin butonuna bağlı pinde ve 
                                                                         //yeniden_baslat fonksiyonuna tanımlı
    lc.shutdown(0, false); 
    lc.setIntensity(0, 8);            //Parlaklık ayarı 0 ila 15 arasında ayarlanabilir
    m.init();                         //LED matriksi başlat
    m.setIntensity(8);               //Parlaklık ayarı 0 ila 15 arasında ayarlanabilir
    oyunu_baslat();                  //oyunu_baslat fonksiyonunu çağır
    render();                        //render fonksiyonunu çağır 
}

void loop() {
  if (!oyun_bitti) 
  {
    ekrani_Temizle();
    render();

    if (simdiki_zaman - onceki_zaman > Gecikme_Suresi) {
      oyun_bitti = advance();
      onceki_zaman = simdiki_zaman;    
    }
  } 
  else {
    while (blink_count > 0) {
      ekrani_Temizle();
      delay(300);
      render();
      delay(300);
      blink_count--;     
    }
  }
  Yilan_Kontrolu();
  simdiki_zaman++;
}

void yeniden_baslat() {  
  oyunu_baslat();
  oyun_bitti = false;
}

void Yilan_Kontrolu() {
  int VRX_Okunan = map(analogRead(VRX), 0, 906, -2, 2); //Joystickin X eksenine bağlı Analog 1 deki pindeki değeri oku ve 0 ile 906 arasındaki değeri 2 ile -2 arasında oranla 
  int VRY_Okunan = map(analogRead(VRY), 0, 906, 2, -2); //Joystickin Y eksenine bağlı Analog 2 deki pindeki değeri oku ve 0 ile 906 arasındaki değeri 2 ile -2 arasında oranla 
  
  if (VRX_Okunan != 0) //Eğer okunan değer sıfırdan farklı ise 
  {
    VRX_Okunan = VRX_Okunan / abs(VRX_Okunan); //VRX_Okunan değişkeninin aldığı veriler kendi mutlağı ile böl
                                               //ve çıkan sonucu VRX_Okunan değişkenine kaydet
  }  
  
  if (VRY_Okunan != 0)  // Eğer okunan değer sıfırdan farklı ise 
  {VRY_Okunan = VRY_Okunan / abs(VRY_Okunan);}  //VRX_Okunan değişkeninin aldığı veriler kendi mutlağı ile böl
                                                //ve çıkan sonucu VRX_Okunan değişkenine kaydet

  if (VRY_Okunan != 0 && v[0] != 0) {
    v[0] = 0;
    v[1] = VRY_Okunan;    
  }

  if (VRX_Okunan != 0 && v[1] != 0) {
    v[0] = VRX_Okunan;
    v[1] = 0;
  }

}

void oyun_bitti_mesaji() {

  for(int i=0;i<3; i++) {
    tone(hoparlorPin,500);
    delay(50);
    noTone(hoparlorPin);
    delay(50);
    
  }
  m.shiftLeft(false, true);
  printStringWithShift("Skor :",80);
  char skor2[4];
  itoa(skor,skor2,10); //integer sayıyı karaktere(char) dönüştür, skor integer sayısını skor2 karakter(char)'a dönüştür
  printStringWithShift(skor2,80);
  printStringWithShift("   ",80);
  skor=0;
}

//Harfler sayılar ve sembollerin binary (ikili) formatı
PROGMEM const unsigned char CH[] = {
3, 8, B00000000, B00000000, B00000000, B00000000, B00000000, // space
1, 8, B01011111, B00000000, B00000000, B00000000, B00000000, // !
3, 8, B00000011, B00000000, B00000011, B00000000, B00000000, // "
5, 8, B00010100, B00111110, B00010100, B00111110, B00010100, // #
4, 8, B00100100, B01101010, B00101011, B00010010, B00000000, // $
5, 8, B01100011, B00010011, B00001000, B01100100, B01100011, // %
5, 8, B00110110, B01001001, B01010110, B00100000, B01010000, // &
1, 8, B00000011, B00000000, B00000000, B00000000, B00000000, // '
3, 8, B00011100, B00100010, B01000001, B00000000, B00000000, // (
3, 8, B01000001, B00100010, B00011100, B00000000, B00000000, // )
5, 8, B00101000, B00011000, B00001110, B00011000, B00101000, // *
5, 8, B00001000, B00001000, B00111110, B00001000, B00001000, // +
2, 8, B10110000, B01110000, B00000000, B00000000, B00000000, // ,
4, 8, B00001000, B00001000, B00001000, B00001000, B00000000, // -
2, 8, B01100000, B01100000, B00000000, B00000000, B00000000, // .
4, 8, B01100000, B00011000, B00000110, B00000001, B00000000, // /
4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // 0
3, 8, B01000010, B01111111, B01000000, B00000000, B00000000, // 1
4, 8, B01100010, B01010001, B01001001, B01000110, B00000000, // 2
4, 8, B00100010, B01000001, B01001001, B00110110, B00000000, // 3
4, 8, B00011000, B00010100, B00010010, B01111111, B00000000, // 4
4, 8, B00100111, B01000101, B01000101, B00111001, B00000000, // 5
4, 8, B00111110, B01001001, B01001001, B00110000, B00000000, // 6
4, 8, B01100001, B00010001, B00001001, B00000111, B00000000, // 7
4, 8, B00110110, B01001001, B01001001, B00110110, B00000000, // 8
4, 8, B00000110, B01001001, B01001001, B00111110, B00000000, // 9
2, 8, B01010000, B00000000, B00000000, B00000000, B00000000, // :
2, 8, B10000000, B01010000, B00000000, B00000000, B00000000, // ;
3, 8, B00010000, B00101000, B01000100, B00000000, B00000000, // <
3, 8, B00010100, B00010100, B00010100, B00000000, B00000000, // =
3, 8, B01000100, B00101000, B00010000, B00000000, B00000000, // >
4, 8, B00000010, B01011001, B00001001, B00000110, B00000000, // ?
5, 8, B00111110, B01001001, B01010101, B01011101, B00001110, // @
4, 8, B01111110, B00010001, B00010001, B01111110, B00000000, // A
4, 8, B01111111, B01001001, B01001001, B00110110, B00000000, // B
4, 8, B00111110, B01000001, B01000001, B00100010, B00000000, // C
4, 8, B01111111, B01000001, B01000001, B00111110, B00000000, // D
4, 8, B01111111, B01001001, B01001001, B01000001, B00000000, // E
4, 8, B01111111, B00001001, B00001001, B00000001, B00000000, // F
4, 8, B00111110, B01000001, B01001001, B01111010, B00000000, // G
4, 8, B01111111, B00001000, B00001000, B01111111, B00000000, // H
3, 8, B01000001, B01111111, B01000001, B00000000, B00000000, // I
4, 8, B00110000, B01000000, B01000001, B00111111, B00000000, // J
4, 8, B01111111, B00001000, B00010100, B01100011, B00000000, // K
4, 8, B01111111, B01000000, B01000000, B01000000, B00000000, // L
5, 8, B01111111, B00000010, B00001100, B00000010, B01111111, // M
5, 8, B01111111, B00000100, B00001000, B00010000, B01111111, // N
4, 8, B00111110, B01000001, B01000001, B00111110, B00000000, // O
4, 8, B01111111, B00001001, B00001001, B00000110, B00000000, // P
4, 8, B00111110, B01000001, B01000001, B10111110, B00000000, // Q
4, 8, B01111111, B00001001, B00001001, B01110110, B00000000, // R
4, 8, B01000110, B01001001, B01001001, B00110010, B00000000, // S
5, 8, B00000001, B00000001, B01111111, B00000001, B00000001, // T
4, 8, B00111111, B01000000, B01000000, B00111111, B00000000, // U
5, 8, B00001111, B00110000, B01000000, B00110000, B00001111, // V
5, 8, B00111111, B01000000, B00111000, B01000000, B00111111, // W
5, 8, B01100011, B00010100, B00001000, B00010100, B01100011, // X
5, 8, B00000111, B00001000, B01110000, B00001000, B00000111, // Y
4, 8, B01110001, B01001001, B01001001, B01000111, B00000000, // Z
2, 8, B01111111, B01000001, B00000000, B00000000, B00000000, // [
4, 8, B00000001, B00000110, B00011000, B01100000, B00000000, // \ ters slash
2, 8, B01000001, B01111111, B00000000, B00000000, B00000000, // ]
3, 8, B00000010, B00000001, B00000010, B00000000, B00000000, // hat
4, 8, B01000000, B01000000, B01000000, B01000000, B00000000, // _
2, 8, B00000001, B00000010, B00000000, B00000000, B00000000, // `
4, 8, B00100000, B01010100, B01010100, B01111000, B00000000, // a
4, 8, B01111111, B01000100, B01000100, B00111000, B00000000, // b
4, 8, B00111000, B01000100, B01000100, B00101000, B00000000, // c
4, 8, B00111000, B01000100, B01000100, B01111111, B00000000, // d
4, 8, B00111000, B01010100, B01010100, B00011000, B00000000, // e
3, 8, B00000100, B01111110, B00000101, B00000000, B00000000, // f
4, 8, B10011000, B10100100, B10100100, B01111000, B00000000, // g
4, 8, B01111111, B00000100, B00000100, B01111000, B00000000, // h
3, 8, B01000100, B01111101, B01000000, B00000000, B00000000, // i
4, 8, B01000000, B10000000, B10000100, B01111101, B00000000, // j
4, 8, B01111111, B00010000, B00101000, B01000100, B00000000, // k
3, 8, B01000001, B01111111, B01000000, B00000000, B00000000, // l
5, 8, B01111100, B00000100, B01111100, B00000100, B01111000, // m
4, 8, B01111100, B00000100, B00000100, B01111000, B00000000, // n
4, 8, B00111000, B01000100, B01000100, B00111000, B00000000, // o
4, 8, B11111100, B00100100, B00100100, B00011000, B00000000, // p
4, 8, B00011000, B00100100, B00100100, B11111100, B00000000, // q
4, 8, B01111100, B00001000, B00000100, B00000100, B00000000, // r
4, 8, B01001000, B01010100, B01010100, B00100100, B00000000, // s
3, 8, B00000100, B00111111, B01000100, B00000000, B00000000, // t
4, 8, B00111100, B01000000, B01000000, B01111100, B00000000, // u
5, 8, B00011100, B00100000, B01000000, B00100000, B00011100, // v
5, 8, B00111100, B01000000, B00111100, B01000000, B00111100, // w
5, 8, B01000100, B00101000, B00010000, B00101000, B01000100, // x
4, 8, B10011100, B10100000, B10100000, B01111100, B00000000, // y
3, 8, B01100100, B01010100, B01001100, B00000000, B00000000, // z
3, 8, B00001000, B00110110, B01000001, B00000000, B00000000, // {
1, 8, B01111111, B00000000, B00000000, B00000000, B00000000, // |
3, 8, B01000001, B00110110, B00001000, B00000000, B00000000, // }
4, 8, B00001000, B00000100, B00001000, B00000100, B00000000, // ~
};

 
// Karakter yazdırmak için gerekli fonksiyonu tanımla
void printCharWithShift(char c, int kaydirma_hizi){
  if (c < 32) return;
  c -= 32;
  memcpy_P(buffer, CH + 7*c, 7);
  m.writeSprite(Led_Matrix_Sayisi*8, 0, buffer);
  m.setColumn(Led_Matrix_Sayisi*8 + buffer[0], 0);
   
  for (int i=0; i<buffer[0]+1; i++) 
  {
    delay(kaydirma_hizi);
    m.shiftLeft(false, false);
  }
}
  
// String'i yazdırmak için gerekli fonksiyon
void printStringWithShift(char* s, int kaydirma_hizi){
  while (*s != 0){
    printCharWithShift(*s, kaydirma_hizi);
    s++;
  }
}
