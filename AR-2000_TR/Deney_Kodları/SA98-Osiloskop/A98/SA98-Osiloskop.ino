// SA98 - Osiloskop

unsigned adc_hizi = 3;
unsigned tetik_modu = 0;    //Tetik yok = 0; Yükselen Kenar = 1; Negatif Kenar = 2;
unsigned single_tetik = 0;
int trigVal = 200;
unsigned char cmd;
unsigned int dim = 256;
unsigned long vect[256];

unsigned k = 0;
boolean stringComplete = false;
int ledPin = 13;

void setup() {
    Serial.begin(115200);
    pinMode(10, OUTPUT);
    tone(10, 800);
    analogRead(A0);
    ADCSRA = B11011100;    //ADC Ayarları
    pinMode(ledPin, OUTPUT);
}

void loop() {
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    delay(50);
}

ISR(ADC_vect) {
    vect[k] = ADC;
    k++;

    //Trigger (tetikleme) durumunu kontrol et Normal Mode = 1
    if (k == 2 && tetik_modu >= 1) {
        trigger();
    }

    if (single_tetik == 1) {
        if (k == dim) {
            afisare();
            return;
        }
    } else {
        if (k == dim) {
            afisare();
            k = 0;
        }
    }
    check_speed();
}

void serialEvent() {        //Seri haberleşmeyi etkinleştir
    while (Serial.available()) {
        cmd = (char)Serial.read();    //Yeni data al
        comand();
        if (cmd == '\n') {
            stringComplete = true;
        }
    }
}

void afisare() {           //Bilgisayara data göndermek için gerekli fonksiyonu tanımla
    if (single_tetik == 1) {
        Serial.print("&");
    }
    Serial.print("*:");
    for (k = 0; k < dim; k++) {
        Serial.print(vect[k]);
        Serial.print(",");
    }
    Serial.println();
}

void comand() {            //Bilgisayardan data okumak için gerekli olan fonksiyonu tanımla
    if (cmd == 'R') {
        single_tetik = 0;
        tetik_modu = 0;
        ADCSRA = B11011100;
    }
    if (cmd == 'S') {
        single_tetik = 1;
    }

    //Çevirme hızı ayarları
    if (!single_tetik) {
        if (cmd == 'T') {
            tetik_modu = 1;
        }
        if (cmd == 't') {
            tetik_modu = 2;
        }
        if (cmd == 'Z') {
            adc_hizi = 6;
        }
        if (cmd == 'X') {
            adc_hizi = 5;
        }
        if (cmd == 'C') {
            adc_hizi = 4;
        }
        if (cmd == 'V') {
            adc_hizi = 3;
        }
        if (cmd == 'B') {
            adc_hizi = 2;
        }
    }
}

void trigger() {
    //Positif kenarda tetikleme
    if (tetik_modu == 1) {
        if ((vect[0] >= trigVal) && (vect[1] >= vect[0])) {
            ADCSRA = B11011100;
        } else {
            vect[0] = vect[1];
            k = 1;
            ADCSRA = B11011100;
        }
    }

    //Negatif Kenarda Tetikleme
    if (tetik_modu == 2) {
        if ((vect[0] <= trigVal) && (vect[1] <= vect[0])) {
            ADCSRA = B11011100;
        } else {
            vect[0] = vect[1];
            k = 1;
            ADCSRA = B11011100;
        }
    }
}

void check_speed() {
    if (adc_hizi == 0) {
        ADCSRA = B11011001;    //PRESCALER 2 ~615Khz
    }
    if (adc_hizi == 1) {
        ADCSRA = B11011010;    //PRESCALER 4 ~307Khz
    }
    if (adc_hizi == 2) {
        ADCSRA = B11111011;    //PRESCALER 8 ~153Khz
    }
    if (adc_hizi == 3) {
        ADCSRA = B11011100;    //PRESCALER 16 ~76Khz
    }
    if (adc_hizi == 4) {
        ADCSRA = B11011101;    //PRESCALER 32 ~38Khz
    }
    if (adc_hizi == 5) {
        ADCSRA = B11011110;    //PRESCALER 64 ~19Khz
    }
    if (adc_hizi == 6) {
        ADCSRA = B11011111;    //PRESCALER 128 ~9.6Khz
    }
    if (adc_hizi == 7) {
        delay(1000);
        ADCSRA = B11011111;    //PRESCALER 128 >>9.6Khz
    }
}
