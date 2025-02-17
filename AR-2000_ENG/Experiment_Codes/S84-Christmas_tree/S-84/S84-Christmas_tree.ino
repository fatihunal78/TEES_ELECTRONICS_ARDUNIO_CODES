//S84 - Christmas tree

//Define the digital pin numbers to which the LEDs are connected
int LEDs[] = {2,3,4,5,6,7,8,9,10,11};

//Define the variable in which the randomly generated number will be stored
int randomNumber = 0;

int speakerPin = 12;
int length = 26;
char notes[] = "eeeeeeegcde fffffeeeeddedg";
int strokes[] = {1,1,2,1,1,2,1,1,1,1,4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2};

//Playing tempo
int tempo = 200;

//Define the playNote function
void playNote(char note, int time) {
    char noteName[] = {'c','d','e','f','g','a','b','C'};
    int tones[] = {1915,1700,1519,1432,1275,1136,1014,956};
    
    for(int i=0; i<8; i++) {
        if(noteName[i] == note) {
            for(long j=0; j<time*1000L; j+=tones[i]*2) {
                digitalWrite(speakerPin, HIGH);
                delayMicroseconds(tones[i]);
                digitalWrite(speakerPin, LOW);
                delayMicroseconds(tones[i]);
            }
        }
    }
}

void setup() {
    //Set the pins to which the LEDs are connected as output
    //With for loop, set the pin to which the LEDs are connected as output
    for(int i=0; i<10; i++) {
        pinMode(LEDs[i], OUTPUT);
    }
    
    //Set the pin to which the Speaker is connected as output
    pinMode(speakerPin, OUTPUT);
}

void loop() {
    for(int i=0; i<length; i++) {
        if(notes[i] == ' ') {
            for(int i=0; i<10; i++) {
                digitalWrite(LEDs[i], HIGH);
            }
            delay(strokes[i] * tempo/4);
            
            for(int i=0; i<10; i++) {
                digitalWrite(LEDs[i], LOW);
            }
            delay(strokes[i] * tempo/4);
        }
        else {
            playNote(notes[i], strokes[i] * tempo);
        }
        
        for(int j=0; j<5; j++) {
            randomNumber = random(0,10);    //Define a random number between 0-9
            
            //Turn the LEDs ON and OFF randomly
            digitalWrite(LEDs[randomNumber], HIGH);
            digitalWrite(LEDs[(randomNumber * 2) % 5], HIGH);
            digitalWrite(LEDs[(randomNumber * 5) % 6], HIGH);
            digitalWrite(LEDs[(randomNumber * 8) % 7], HIGH);
            delay(tempo/20);    //Wait until tempo/20
            
            digitalWrite(LEDs[randomNumber], HIGH);
            digitalWrite(LEDs[(randomNumber * 2) % 5], HIGH);
            digitalWrite(LEDs[(randomNumber * 5) % 6], HIGH);
            digitalWrite(LEDs[(randomNumber * 8) % 7], HIGH);
            delay(tempo/20);    //Wait until tempo/20
        }
    }
}
