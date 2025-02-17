// SA22 - Engelden Kaçma Oyunu

//I2C LCD kütüphanesini ekle
#include <LiquidCrystal_I2C.h>

volatile int zorlukSeviyesi;
volatile int zorlukSeviyesiSayac;

int PIN_SECME_BUTTON = 2;
int PIN_BUTTON = 3;
#define HOPARLOR_PIN      4
#define PIN_AUTOPLAY      1
#define PIN_READWRITE     10
#define PIN_CONTRAST      12
#define HIZLI_KOSMA1      1
#define HIZLI_KOSMA2      2
#define HIZLI_ZIPLAMA     3
#define HIZLI_ZIPLAMA_UST '.'         
#define HIZLI_ZIPLAMA_ALT 4
#define SPRITE_TERRAIN_EMPTY       ' '      
#define SPRITE_TERRAIN_SOLID       5
#define SPRITE_TERRAIN_SOLID_RIGHT 6
#define SPRITE_TERRAIN_SOLID_LEFT  7
#define HERO_YATAY_POZISYON       1    
#define TERRAIN_WIDTH             16
#define TERRAIN_EMPTY             0
#define TERRAIN_LOWER_BLOCK       1
#define TERRAIN_UPPER_BLOCK       2
#define HERO_POSITION_OFF         0          
#define HERO_ALT_KOSMA_POSIZYONU_1  1  
#define HERO_ALT_KOSMA_POSIZYONU_2  2  
#define HERO_ZIPLAMA_POZISYON_1     3       
#define HERO_ZIPLAMA_POZISYON_2     4       
#define HERO_ZIPLAMA_POZISYON_3     5       
#define HERO_ZIPLAMA_POZISYON_4     6     
#define HERO_ZIPLAMA_POZISYON_5     7    
#define HERO_ZIPLAMA_POZISYON_6     8       
#define HERO_ZIPLAMA_POZISYON_7     9       
#define HERO_ZIPLAMA_POZISYON_8    10      
#define HERO_UST_KOSMA_POSIZYONU_1 11 
#define HERO_UST_KOSMA_POSIZYONU_2 12

unsigned int skor;

//LCD için Türkçe karakteri tanımla
byte karakteri[8] = {0x0, 0x0, 0x4, 0x4, 0x4, 0x4, 0x4, 0x0};     //ı karakterini oluştur
byte karakterc[8] = {0x0, 0xE, 0x11, 0x10, 0x11, 0xE, 0x4, 0x0};  //ç karakterini oluştur



//1602 LCD ekranı tanımla
LiquidCrystal_I2C lcd(0x27, 16, 2);
static char terrainUpper[TERRAIN_WIDTH + 1];
static char terrainLower[TERRAIN_WIDTH + 1];
static bool buttonPushed = false;

//Grafikleri tanımla
void grafikleriTanimla() {
    static byte grafikler[] = {
        // Koşma pozisyonu 1
        0x0C, 0x0C, 0x00, 0x0E, 0x1C, 0x0C, 0x1A, 0x13,
        // Koşma pozisyonu 2
        0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x0C, 0x0C, 0x0E,
        // Zıpla
        0x0C, 0x0C, 0x00, 0x1E, 0x0D, 0x1F, 0x10, 0x00,
        // Aşağıdan Zıpla
        0x1E, 0x0D, 0x1F, 0x10, 0x00, 0x00, 0x00, 0x00,
        // Taban
        0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
        // Taban sağ
        0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
        // Taban sol
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    };
  
    for (int i = 0; i < 7; ++i) {
        lcd.createChar(i + 1, &grafikler[i * 8]);
    }
    for (int i = 0; i < TERRAIN_WIDTH; ++i) {
        terrainUpper[i] = SPRITE_TERRAIN_EMPTY;
        terrainLower[i] = SPRITE_TERRAIN_EMPTY;
    }
}

void advanceTerrain(char* terrain, byte newTerrain) {
    for (int i = 0; i < TERRAIN_WIDTH; ++i) {
        char current = terrain[i];
        char next = (i == TERRAIN_WIDTH-1) ? newTerrain : terrain[i+1];
        switch (current) {
            case SPRITE_TERRAIN_EMPTY:
                terrain[i] = (next == SPRITE_TERRAIN_SOLID) ? SPRITE_TERRAIN_SOLID_RIGHT : SPRITE_TERRAIN_EMPTY;
                break;
            case SPRITE_TERRAIN_SOLID:
                terrain[i] = (next == SPRITE_TERRAIN_EMPTY) ? SPRITE_TERRAIN_SOLID_LEFT : SPRITE_TERRAIN_SOLID;
                break;
            case SPRITE_TERRAIN_SOLID_RIGHT:
                terrain[i] = SPRITE_TERRAIN_SOLID;
                break;
            case SPRITE_TERRAIN_SOLID_LEFT:
                terrain[i] = SPRITE_TERRAIN_EMPTY;
                break;
        }
    }
}

//notaCal fonksiyonunu tanımla
void notaCal(int bekleme, int ton) {
    tone(HOPARLOR_PIN, ton);
    delay(bekleme);
    noTone(HOPARLOR_PIN);
}

//heroCiz fonksiyonunu tanımla
bool heroCiz(byte position, char* terrainUpper, char* terrainLower, unsigned int score) {
    bool collide = false;
    char upperSave = terrainUpper[HERO_YATAY_POZISYON];
    char lowerSave = terrainLower[HERO_YATAY_POZISYON];
    byte upper, lower;
    
    switch (position) {
        case HERO_POSITION_OFF:
            upper = lower = SPRITE_TERRAIN_EMPTY;
            break;
        case HERO_ALT_KOSMA_POSIZYONU_1:
            upper = SPRITE_TERRAIN_EMPTY;
            lower = HIZLI_KOSMA1;
            break;
        case HERO_ALT_KOSMA_POSIZYONU_2:
            upper = SPRITE_TERRAIN_EMPTY;
            lower = HIZLI_KOSMA2;
            break;
        case HERO_ZIPLAMA_POZISYON_1:
        case HERO_ZIPLAMA_POZISYON_8:
            upper = SPRITE_TERRAIN_EMPTY;
            lower = HIZLI_ZIPLAMA;
            break;
        case HERO_ZIPLAMA_POZISYON_2:
        case HERO_ZIPLAMA_POZISYON_7:
            upper = HIZLI_ZIPLAMA_UST;
            lower = HIZLI_ZIPLAMA_ALT;
            break;
        case HERO_ZIPLAMA_POZISYON_3:
        case HERO_ZIPLAMA_POZISYON_4:
        case HERO_ZIPLAMA_POZISYON_5:
        case HERO_ZIPLAMA_POZISYON_6:
            upper = HIZLI_ZIPLAMA;
            lower = SPRITE_TERRAIN_EMPTY;
            break;
        case HERO_UST_KOSMA_POSIZYONU_1:
            upper = HIZLI_KOSMA1;
            lower = SPRITE_TERRAIN_EMPTY;
            break;
        case HERO_UST_KOSMA_POSIZYONU_2:
            upper = HIZLI_KOSMA2;
            lower = SPRITE_TERRAIN_EMPTY;
            break;
    }
    
    if (upper != ' ') {
        terrainUpper[HERO_YATAY_POZISYON] = upper;
        collide = (upperSave == SPRITE_TERRAIN_EMPTY) ? false : true;
    }
    
    if (lower != ' ') {
        terrainLower[HERO_YATAY_POZISYON] = lower;
        collide |= (lowerSave == SPRITE_TERRAIN_EMPTY) ? false : true;
    }
  
    byte digits = (score > 9999) ? 5 : (score > 999) ? 4 : (score > 99) ? 3 : (score > 9) ? 2 : 1;
  
    terrainUpper[TERRAIN_WIDTH] = '\0';
    terrainLower[TERRAIN_WIDTH] = '\0';
    char temp = terrainUpper[16-digits];
    terrainUpper[16-digits] = '\0';
    lcd.setCursor(0, 0);
    lcd.print(terrainUpper);
    terrainUpper[16-digits] = temp;  
    lcd.setCursor(0, 1);
    lcd.print(terrainLower);
  
    lcd.setCursor(16 - digits, 0);
    lcd.print(score);
    skor = score;
    terrainUpper[HERO_YATAY_POZISYON] = upperSave;
    terrainLower[HERO_YATAY_POZISYON] = lowerSave;
    return collide;
}

//Butona basılma kesmesinde çağırılacak fonksiyon
void butonaBasildi() {
    buttonPushed = true;
}

void engelOlustur(int beklemeZamani) {
    static byte heroPos = HERO_ALT_KOSMA_POSIZYONU_1;
    static byte newTerrainType = TERRAIN_EMPTY;
    static byte newTerrainDuration = 1;
    static bool playing = false;
    static bool blink = false;
    static unsigned int distance = 0;
    
    if (!playing) {
        heroCiz((blink) ? HERO_POSITION_OFF : heroPos, terrainUpper, terrainLower, distance >> 3);
        if (blink) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Kaybettiniz!");
            lcd.setCursor(0, 1);
            lcd.print("Skor: ");
            lcd.print(skor);
            delay(2000);
            
            while(digitalRead(2)) {      
                lcd.setCursor(0, 0);
                lcd.print("Yeniden Baslamak");
                lcd.setCursor(0, 1);
                lcd.print("icin PB1'e Bas");
            }
        }
        delay(250);
        blink = !blink;
        if (buttonPushed) {
            notaCal(100, 400);
            notaCal(100, 600);
            notaCal(100, 400);
            grafikleriTanimla();
            heroPos = HERO_ALT_KOSMA_POSIZYONU_1;
            playing = true;
            buttonPushed = false;
            distance = 0;
        }
        return;
    }

    //Engelleri sola doğru kaydır
    advanceTerrain(terrainLower, newTerrainType == TERRAIN_LOWER_BLOCK ? SPRITE_TERRAIN_SOLID : SPRITE_TERRAIN_EMPTY);
    advanceTerrain(terrainUpper, newTerrainType == TERRAIN_UPPER_BLOCK ? SPRITE_TERRAIN_SOLID : SPRITE_TERRAIN_EMPTY);
  
    //Yeni engel tanımla ve sağdan ekrana sok
    if (--newTerrainDuration == 0) {
        if (newTerrainType == TERRAIN_EMPTY) {
            newTerrainType = (random(3) == 0) ? TERRAIN_UPPER_BLOCK : TERRAIN_LOWER_BLOCK;
            newTerrainDuration = 2 + random(10);
        } else {
            newTerrainType = TERRAIN_EMPTY;
            newTerrainDuration = 10 + random(10);
        }
    }
    
    if (buttonPushed) {
        if (heroPos <= HERO_ALT_KOSMA_POSIZYONU_2) {
            notaCal(100, 300);
        }
        heroPos = HERO_ZIPLAMA_POZISYON_1;
        buttonPushed = false;
    }  

    if (heroCiz(heroPos, terrainUpper, terrainLower, distance >> 3)) {
        playing = false;  // The hero collided with something. Too bad.
        notaCal(100, 500);
        notaCal(100, 400);
        notaCal(120, 300);
        notaCal(160, 400);
        lcd.clear();
    } else {
        if (heroPos == HERO_ALT_KOSMA_POSIZYONU_2 || heroPos == HERO_ZIPLAMA_POZISYON_8) {
            heroPos = HERO_ALT_KOSMA_POSIZYONU_1;
        } else if ((heroPos >= HERO_ZIPLAMA_POZISYON_3 && heroPos <= HERO_ZIPLAMA_POZISYON_5) && 
                   terrainLower[HERO_YATAY_POZISYON] != SPRITE_TERRAIN_EMPTY) {
            heroPos = HERO_UST_KOSMA_POSIZYONU_1;
        } else if (heroPos >= HERO_UST_KOSMA_POSIZYONU_1 && 
                  terrainLower[HERO_YATAY_POZISYON] == SPRITE_TERRAIN_EMPTY) {
            heroPos = HERO_ZIPLAMA_POZISYON_5;
        } else if (heroPos == HERO_UST_KOSMA_POSIZYONU_2) {
            heroPos = HERO_UST_KOSMA_POSIZYONU_1;
        } else {
            ++heroPos;
        }
        ++distance;
        
        digitalWrite(PIN_AUTOPLAY, 
                    terrainLower[HERO_YATAY_POZISYON + 2] == SPRITE_TERRAIN_EMPTY ? HIGH : LOW);
    }
    delay(beklemeZamani);
}
  
void setup() {
    //Zorluk seçme butonunu giriş olarak ayarla
    pinMode(PIN_SECME_BUTTON, INPUT_PULLUP);
    //Zıplama butonunu giriş olarak ayarla
    pinMode(PIN_BUTTON, INPUT_PULLUP);
    //Hoparlörün bağlandığı pini çıkış olarak ayarla
    pinMode(HOPARLOR_PIN, OUTPUT);
    zorlukSeviyesiSayac = 1;

    //PIN_BUTTON bacağı için kesme tanımla
    //2 numaralı bacak için kesme için 0 yazılır, 3 numaralı bacak kullanılsaydı 1 yazılır
    attachInterrupt(0/*PIN_BUTTON*/, butonaBasildi, FALLING);
  
    grafikleriTanimla();
  
    lcd.begin();
    //Eklenen Türkçe karakterleri tanımla
    lcd.createChar(1, karakteri);  //ı karakterini oluştur
    lcd.createChar(2, karakterc);  //ç karakterini oluştur
    lcd.setCursor(6, 0);
    lcd.print("Ka");
    lcd.write(byte(2));
    lcd.setCursor(3, 3);
    lcd.print("Ve Z");
    lcd.write(byte(1));
    lcd.print("pla!");
    //Oyun başlangıç notalarını çal
    notaCal(100, 400);
    notaCal(100, 300);
    notaCal(100, 200);
    notaCal(100, 300);
    notaCal(100, 400);
    notaCal(100, 600);
    delay(1000);  //1sn bekle
    lcd.clear();  //LCD'yi sil
    //Zıplama tuşuna basılıncaya kadar menu() fonksiyonunu çağır
    do {
        menu();
    } while(digitalRead(PIN_BUTTON) == HIGH);
}

void loop() { 
    switch (zorlukSeviyesi) {
        case 1:
            engelOlustur(70);
            break;
        case 2:
            engelOlustur(50);
            break;
        case 3:
            engelOlustur(15);
            break;
    }
}

void menu() {
    if (zorlukSeviyesiSayac > 3 || zorlukSeviyesiSayac < 0) {
        zorlukSeviyesiSayac = 0;  // Fixed assignment operator
    }

    if (digitalRead(PIN_SECME_BUTTON) == LOW) {
        zorlukSeviyesiSayac++;
    }
    
    switch (zorlukSeviyesiSayac) {
        case 1:
            lcd.setCursor(0, 0);
            lcd.print("Zorluk Se");
            lcd.write(byte(2));
            lcd.print(" :");
            lcd.setCursor(0, 1);
            lcd.print("<    Kolay     >");
            delay(250);
            
            if(digitalRead(PIN_BUTTON) == LOW) {
                zorlukSeviyesi = 1;
            }
            break;
            
        case 2:
            lcd.setCursor(0, 0);
            lcd.print("Zorluk Se");
            lcd.write(byte(2));
            lcd.print(" :");
            lcd.setCursor(0, 1);
            lcd.print("<    Orta      >");
            delay(250);
            if(digitalRead(PIN_BUTTON) == LOW) {
                zorlukSeviyesi = 2;
            }
            break;
            
        case 3:
            lcd.setCursor(0, 0);
            lcd.print("Zorluk Se");
            lcd.write(byte(2));
            lcd.print(" :");
            lcd.setCursor(0, 1);
            lcd.print("<     Zor      >");
            delay(250);
            if(digitalRead(PIN_BUTTON) == LOW) {
                zorlukSeviyesi = 3;
            }
            break;
            
        default:
            zorlukSeviyesiSayac = 0;
            break;
    }
}
