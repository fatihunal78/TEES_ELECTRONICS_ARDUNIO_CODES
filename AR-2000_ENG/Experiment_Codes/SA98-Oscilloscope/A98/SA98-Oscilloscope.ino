//SA98 - Oscilloscope

unsigned adc_speed = 3;
unsigned trigger_mode = 0;                          //No trigger = 0; Rising Edge = 1; Negative Edge = 2;
unsigned single_trigger = 0;
int triggerValue = 200;
unsigned char cmd;
unsigned int dim = 256;
unsigned long vect[256];
unsigned k = 0;
boolean stringComplete = false;
int LEDPin = 13;

void setup() {
    Serial.begin(115200);
    pinMode(10, OUTPUT);
    tone(10, 800);
    analogRead(A0);
    ADCSRA = B11011100;                            //ADC Settings
    pinMode(LEDPin, OUTPUT);
}

void loop() {
    digitalWrite(LEDPin, HIGH);
    delay(50);
    digitalWrite(LEDPin, LOW);
    delay(50);
}

ISR(ADC_vect) {
    vect[k] = ADC;
    k++;

    //Check trigger status, Normal Mode = 1
    if(k == 2 && trigger_mode >= 1) {
        trigger();
    }

    if(single_trigger == 1) {
        if(k == dim) {
            afisare();
            return;
        }
    }
    else {
        if(k == dim) {
            afisare();
            k = 0;
        }
    }
    check_speed();
}

//Enable serial communication
void serialEvent() {
    while(Serial.available()) {
        //Receive new data
        cmd = (char) Serial.read();
        comand();
        if(cmd == '\n') {
            stringComplete = true;
        }
    }
}

//Define the function required to send data to the computer
void afisare() {
    if(single_trigger == 1) {
        Serial.print("&");
    }
    Serial.print("*:");
    for(k=0; k<dim; k++) {
        Serial.print(vect[k]); 
        Serial.print(",");
    }
    Serial.println();
}

//Define the function required to read data from the computer
void comand() {
    if(cmd == 'R') {
        single_trigger = 0;
        trigger_mode = 0;
        ADCSRA = B11011100;
    }
    if(cmd == 'S') {
        single_trigger = 1;
    }

    //Dial speed settings
    if(!single_trigger) {
        if(cmd == 'T') {
            trigger_mode = 1;
        }
        if(cmd == 't') {
            trigger_mode = 2;
        }
        if(cmd == 'Z') {
            adc_speed = 6;
        }
        if(cmd == 'X') {
            adc_speed = 5;
        }
        if(cmd == 'C') {
            adc_speed = 4;
        }
        if(cmd == 'V') {
            adc_speed = 3;
        }
        if(cmd == 'B') {
            adc_speed = 2;
        }
    }
}

void trigger() {
    //Triggering on the positive edge
    if(trigger_mode == 1) {
        if((vect[0] >= triggerValue) && (vect[1] >= vect[0])) {
            ADCSRA = B11011100;
        }
        else {
            vect[0] = vect[1];
            k = 1;
            ADCSRA = B11011100;
        }
    }

    //Triggering on the negative edge
    if(trigger_mode == 2) {
        if((vect[0] <= triggerValue) && (vect[1] <= vect[0])) {
            ADCSRA = B11011100;
        }
        else {
            vect[0] = vect[1];
            k = 1;
            ADCSRA = B11011100;
        }
    }
}

void check_speed() {
    if(adc_speed == 0) {
        ADCSRA = B11011001;                        //PRESCALER 2 ~615Khz
    }
    if(adc_speed == 1) {
        ADCSRA = B11011010;                        //PRESCALER 4 ~307Khz
    }
    if(adc_speed == 2) {
        ADCSRA = B11111011;                        //PRESCALER 8 ~153Khz
    }
    if(adc_speed == 3) {
        ADCSRA = B11011100;                        //PRESCALER 16 ~76Khz
    }
    if(adc_speed == 4) {
        ADCSRA = B11011101;                        //PRESCALER 32 ~38Khz
    }
    if(adc_speed == 5) {
        ADCSRA = B11011110;                        //PRESCALER 64 ~19Khz
    }
    if(adc_speed == 6) {
        ADCSRA = B11011111;                        //PRESCALER 128 ~9.6Khz
    }
    if(adc_speed == 7) {
        delay(1000);
        ADCSRA = B11011111;                        //PRESCALER 128  >>9.6Khz
    }
}
