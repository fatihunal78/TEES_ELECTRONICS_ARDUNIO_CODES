//S62 - Jukebox

//FREQUENCY VALUES CORRESPONDING TO THE MUSICAL NOTES
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

//Define the pin number to which the Speaker is connected
int speakerPin = 6;
//Define the pin number to which the Red LED is connected
int RedLED = 10;
//Define the digital pin number to which the Green LED is connected
int GreenLED = 8;
//Define the pin number to which the Yellow LED is connected
int YellowLED = 9;
//Define the pin number to which the Button is connected
int buttonPin = 2;
//Define the variable to store the button state
int buttonStatus;
int counter = 0;

//Length of notes of the happy birthday song
int birthdaySongLength = 28;
//Length of notes of the jingle bells song
int jingleBellsLength = 26;

char jingleBellsNotes[] = "eeeeeeegcde fffffeeeeddedg";
char birthdaySongNotes[] = "GGAGcB GGAGdc GGxecBA yyecdc";

int birthdaySongStrokes[] = {2, 2, 8, 8, 8, 8, 16, 1, 2, 2, 8, 8, 8, 16, 1, 2, 2, 8, 8, 8, 16, 1, 2, 2, 8, 8, 16};
int jingleBellsStrokes[] = {1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};

//Playing speed of Jingle Bells song
int jingleBellsTempo = 200;
//Playing speed of birthday song
int birthdaySongTempo = 185;

//MUSICAL NOTES REQUIRED FOR THE TURKISH ANTHEM (MOZART - RONDO ALLA TURCA)
int melodies[] = {
    NOTE_B4, NOTE_A4, NOTE_GS4, NOTE_A4, NOTE_C5,
    NOTE_D5, NOTE_C5, NOTE_B4, NOTE_C5, NOTE_E5,
    NOTE_F5, NOTE_E5, NOTE_DS5, NOTE_E5,
    NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_A5, NOTE_C6,
    NOTE_A5, NOTE_C6, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_A5,
    NOTE_G5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_E5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_G5, NOTE_FS5, NOTE_E5,
    NOTE_E5, NOTE_F5, NOTE_G5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5,
    NOTE_E5, NOTE_F5, NOTE_G5, NOTE_G5, NOTE_A5, NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5,
    NOTE_C5, NOTE_D5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4,
    NOTE_C5, NOTE_D5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_E5, NOTE_D5, NOTE_C5, NOTE_B4,
    NOTE_B4, NOTE_A4, NOTE_GS4, NOTE_A4, NOTE_C5,
    NOTE_D5, NOTE_C5, NOTE_B4, NOTE_C5, NOTE_E5,
    NOTE_F5, NOTE_E5, NOTE_DS5, NOTE_E5,
    NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_A5, NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_A5, NOTE_C6,
    NOTE_A5, NOTE_B5, NOTE_C6, NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_A5, NOTE_E5, NOTE_F5, NOTE_D5, NOTE_C5, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_A4,
    NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_FS5, NOTE_GS5, NOTE_A5, NOTE_B5, NOTE_GS5, NOTE_E5,
    NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_FS5, NOTE_B5, NOTE_GS5, NOTE_E5, NOTE_A5,
    NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_FS5, NOTE_GS5, NOTE_A5, NOTE_B5, NOTE_GS5, NOTE_E5,
    NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_A5, NOTE_B5, NOTE_CS6, NOTE_B5, NOTE_A5, NOTE_GS5, NOTE_FS5, NOTE_B5, NOTE_GS5, NOTE_E5, NOTE_A5
};

//PAUSES CORRESPONDING TO MOZART - RONDO ALLA TURCA
int TurkishMarchNoteTimes[] = {
    8, 8, 8, 8, 2,
    8, 8, 8, 8, 2,
    8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 2,
    4, 4, 16, 16, 16, 4,
    4, 4, 16, 16, 16, 4, 4, 4, 16, 16, 16, 4, 4, 4, 2,
    4, 4, 4, 4, 8, 8, 8, 8, 2,
    4, 4, 4, 4, 8, 8, 8, 8, 2,
    4, 4, 4, 4, 8, 8, 8, 8, 2,
    4, 4, 4, 4, 8, 8, 8, 8, 2,
    8, 8, 8, 8, 2,
    8, 8, 8, 8, 2,
    8, 8, 8, 8,
    8, 8, 8, 8, 8, 8, 8, 8, 2,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2, 4, 8, 8, 2,
    4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2,
    4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 2, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 2
};

void jingleBellsPlayNotes(char note, int jingleBellsNoteTime) {
    char noteName[] = {'c', 'd', 'e', 'f', 'g', 'a', 'b', 'C'};
    // Here the jingleBellsPlayNotes function is required to play the Jingle Bells song. Frequency values 
    // corresponding to the notes (tones) are played in order.
    int tones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014, 956};
    
    for (int i = 0; i < 8; i++) {
        if (noteName[i] == note) {
            for (long j = 0; j < jingleBellsNoteTime * 1300L; j += tones[i] * 2) {
                digitalWrite(speakerPin, HIGH);
                delayMicroseconds(tones[i]);
                digitalWrite(speakerPin, LOW);
                delayMicroseconds(tones[i]);
            }
        }
    }
}

//The function here is to play happy birthday song
void birthdayPlayTones(int tone, int birthdayNoteTime) {
    for(long i = 0; i < birthdayNoteTime * 1000L; i += tone * 2) {
        digitalWrite(speakerPin, HIGH);
        delayMicroseconds(tone);
        digitalWrite(speakerPin, LOW);
        delayMicroseconds(tone);
    }
}

void birthdayPlayNotes(char note, int birthdayNoteTime) {
    char birthdayNotes[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B',
                           'c', 'd', 'e', 'f', 'g', 'a', 'b',
                           'x', 'y'};

    int birthdayTones[] = {1915, 1700, 1519, 1432, 1275, 1136, 1014,
                          956, 834, 765, 593, 468, 346, 224,
                          655, 715};

    for(int i = 0; i < 17; i++) {
        if(birthdayNotes[i] == note) {
            int newBirthdayNoteTime = birthdayNoteTime / 5;
            birthdayPlayTones(birthdayTones[i], newBirthdayNoteTime);
        }
    }
}

void setup() {
    //Set LEDs and speaker as output, button as input
    pinMode(RedLED, OUTPUT);
    pinMode(GreenLED, OUTPUT);
    pinMode(YellowLED, OUTPUT);
    pinMode(buttonPin, INPUT);
    pinMode(speakerPin, OUTPUT);
}

void loop() {
    //Write the value of the Button to the buttonStatus variable
    buttonStatus = digitalRead(buttonPin);
    //If buttonStatus = 1, that is, if the Button is pressed
    if(buttonStatus == HIGH) {
        //Increase counter variable by 1
        counter++;
        delay(500);
        if(counter > 3)
            //If the counter variable is greater than 3, set the counter value to zero
            counter = 0;
    }

    //Go to 'cases' based on the value of the counter variable
    switch(counter) {
        //If the counter variable is zero (0)
        case 0:
            //Turn OFF all LEDs and mute the Speaker
            digitalWrite(RedLED, LOW);
            digitalWrite(YellowLED, LOW);
            digitalWrite(GreenLED, LOW);
            digitalWrite(speakerPin, LOW);
            break;

        //If the counter variable is 1
        case 1:
            //Turn ON the Red LED and play birthday song
            digitalWrite(RedLED, HIGH);
            digitalWrite(YellowLED, LOW);
            digitalWrite(GreenLED, LOW);
            for(int i = 0; i < birthdaySongLength; i++) {
                //Read the Button value
                buttonStatus = digitalRead(buttonPin);
                //Check whether the Button is pressed or not. If the Button is pressed, switch to the other case
                if(buttonStatus == HIGH) {
                    //Make the counter 2
                    counter = 2;
                    delay(500);
                    break;
                }
                if(birthdaySongNotes[i] == ' ') {
                    delay(birthdaySongStrokes[i] * birthdaySongTempo);
                } else {
                    birthdayPlayNotes(birthdaySongNotes[i], birthdaySongStrokes[i] * birthdaySongTempo);
                }
                //Waiting time between notes
                delay(birthdaySongTempo);
            }
            break;

        //If the counter variable is 2
        case 2:
            //Turn ON the Yellow LED and play Jingle Bells Song
            digitalWrite(RedLED, LOW);
            digitalWrite(YellowLED, HIGH);
            digitalWrite(GreenLED, LOW);
            for(int i = 0; i < jingleBellsLength; i++) {
                //Read the buttonPin value and write it to the buttonStatus variable
                buttonStatus = digitalRead(buttonPin);
                //Check whether the Button is pressed or not. If the Button is pressed, switch to the other case
                if(buttonStatus == HIGH) {
                    //Set the counter to 3
                    counter = 3;
                    delay(500);
                    break;
                }
                if(jingleBellsNotes[i] == ' ') {
                    delay(jingleBellsStrokes[i] * jingleBellsTempo / 4);
                } else {
                    jingleBellsPlayNotes(jingleBellsNotes[i], jingleBellsStrokes[i] * jingleBellsTempo);
                }
            }
            break;

        //If the counter value is 3
        case 3:
            //Turn ON the Green LED and play the Mozart Turkish March
            digitalWrite(RedLED, LOW);
            digitalWrite(YellowLED, LOW);
            digitalWrite(GreenLED, HIGH);

            for(int thisNote = 0; thisNote < 178; thisNote++) {
                //Read the Button value
                buttonStatus = digitalRead(buttonPin);
                //Check whether the Button is pressed or not. If the Button is pressed, switch to the other case
                if(buttonStatus == HIGH) {
                    //Set the counter to 0
                    counter = 0;
                    delay(500);
                    break;
                }
                int noteDuration = 1000 / TurkishMarchNoteTimes[thisNote];
                tone(speakerPin, melodies[thisNote], noteDuration);
                int pauseBetweenNotes = noteDuration * 1.30;
                delay(pauseBetweenNotes);
            }
            break;
    }
}
