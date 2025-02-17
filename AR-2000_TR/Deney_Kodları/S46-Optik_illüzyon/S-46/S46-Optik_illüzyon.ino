// S46 - Optik illüzyon

int PotPin = A0;      // Potansiyometrenin bağlandığı pini tanımla
int motorPin = 5;     // Motorun bağlandığı pini tanımla

int analogokuma;      // Potansiyometreden okunan değerin tutulacağı değişkeni tanımla

void setup() {  
    pinMode(PotPin, INPUT);      // Potansiyometrenin bağlandığı pini giriş olarak ayarla
    pinMode(motorPin, OUTPUT);    // Motorun bağlandığı pini çıkış olarak ayarla
}

void loop() {
    analogokuma = analogRead(PotPin);                    // analogokuma değişkenine analog A0 pininden okunan değeri kaydet 
    int oranla = map(analogokuma, 0, 1023, 0, 255);     // analog pinden okunan 0 ile 1023 arasındaki değeri 0 ile 255 
                                                        // arasında oranla
    analogWrite(motorPin, oranla);                      // Motor dönüş hızını oranla değişkenine göre ayarla
}
