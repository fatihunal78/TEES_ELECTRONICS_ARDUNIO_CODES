// SA38 - Tuş Takımı ile Piano

#include <Keypad.h>                                    // Keypad kütüphanesi eklendi
int hoparlorPin = 3;                                  // Hoparlörün bağlandığı pin numarasını tanımla

const byte SATIR = 4;                                 // Tuş takımının kaç satırdan oluştuğunu belirt 
const byte SUTUN = 4;                                 // Tuş takımının kaç sütundan oluştuğunu belirt

// Satır ve sütundaki tuşların yerini ve sırasını tanımla
char tuslar[SATIR][SUTUN] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

byte satirPinleri[SATIR] = {13, 12, 11, 10};         // Satır bağlantılarının Arduino'da bağlandığı pinleri tanımla
byte sutunPinleri[SUTUN] = {9, 8, 7, 6};            // Sütun bağlantılarının Arduino'da bağlandığı pinleri tanımla

// Tuş takımı için yukarıda tanımladıklarımız yardımı ile Keypad'i oluştur
Keypad Tus_takimi = Keypad(makeKeymap(tuslar), satirPinleri, sutunPinleri, SATIR, SUTUN);

char tus;                                            // Keypad'den basılan tuşların tutulacağı değişken tanımlandı 

// Notaları tanımla
#define do     262                                   // do
#define re     294                                   // re
#define mi     330                                   // mi
#define fa     349                                   // fa
#define sol    392                                   // sol
#define la     440                                   // la
#define si     494                                   // si
#define incedo 512                                   // incedo

void setup() {
    pinMode(hoparlorPin, OUTPUT);                    // Hoparlörün bağlandığı pini çıkış olarak ayarla
}

void loop() {
    tus = Tus_takimi.getKey();                      // tus değişkenine tuş takımından basılan tuşları kayıt et
    
    if (tus != NO_KEY) {                            // Eğer bir tuşa basıldı ise 
        switch(tus) {                               // switch case yapısında hangi tuşa basıldıysa o case'e git
            case '1':                               // Eğer 1'e basıldı ise 
                tone(hoparlorPin, do);              // Hoparlörden do notasını çal
                delay(200);                         // 200 ms bekle
                noTone(hoparlorPin);               // Hoparlörü sustur 
                break;
                
            case '2': 
                tone(hoparlorPin, re);             // Hoparlörden re notasını çal
                delay(200);                        // 200 ms bekle
                noTone(hoparlorPin);
                break;
                
            case '3': 
                tone(hoparlorPin, mi);             // Hoparlörden mi notasını çal
                delay(200);                        // 200 ms bekle
                noTone(hoparlorPin);               // Hoparlörü sustur 
                break;
                
            case 'A': 
                tone(hoparlorPin, fa);             // Hoparlörden fa notasını çal
                delay(200);                        // 200 ms bekle
                noTone(hoparlorPin);               // Hoparlörü sustur 
                break;
                
            case '4': 
                tone(hoparlorPin, sol);            // Hoparlörden sol notasını çal
                delay(200);                        // 200 ms bekle
                noTone(hoparlorPin);               // Hoparlörü sustur 
                break;
                
            case '5': 
                tone(hoparlorPin, la);             // Hoparlörden la notasını çal
                delay(200);                        // 200 ms bekle
                noTone(hoparlorPin);               // Hoparlörü sustur 
                break;
                
            case '6': 
                tone(hoparlorPin, si);             // Hoparlörden si notasını çal
                delay(200);                        // 200 ms bekle
                noTone(hoparlorPin);               // Hoparlörü sustur 
                break;
                
            case 'B': 
                tone(hoparlorPin, incedo);         // Hoparlörden incedo notasını çal
                delay(200);                        // 200 ms bekle
                noTone(hoparlorPin);               // Hoparlörü sustur 
                break;
                
            default:                               // Üstteki case'ler harici başka bir komut gelirse
                noTone(hoparlorPin);               // Hoparlörü sustur
        }
    }
    delay(10);
} 
