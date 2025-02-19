//S32 - Doorbell with melody

int speakerPin = 3;  //Define the pin number to which the Speaker is connected
int buttonPin = 2;   //Define the pin number to which the Button is connected

//FREQUENCY VALUES CORRESPONDING TO THE MUSICAL NOTES
#define NOTE_C4  262
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247
#define NOTE_C4  262

//We write the musical notes to be played in order in a series
int melody_notes[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

//We define the waiting time between musical notes as follows.
//Such as 4 = quarter stroke (note), 8 = eighth note
int note_strokes[] = {
    4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
    pinMode(speakerPin, OUTPUT);  //Set the pin to which speaker is connected as output
    pinMode(buttonPin, INPUT);    //Set the pin to which the Button is connected as input
}

void loop() {
    if(digitalRead(buttonPin) == HIGH) {  //If the Button is pressed, perform the following actions to ring the bell
        for(int note = 0; note < 8; note++) {  //We created a for loop from 0 to 7 because there are 7 notes
                                              //With this loop, we will play the music notes one by one
            //To calculate the duration of the note, take one second (1000ms) as a reference
            //Divide this duration by the amount of strokes corresponding to that note
            //For example, NOTE_C4 will play at first and the stroke amount will be 4
            //The playing time of this note will be 1000/4 = 250ms
            //Or it will be 1000/8 = 125ms for another note
            
            int noteTime = 1000 / note_strokes[note];
            
            tone(speakerPin, melody_notes[note], noteTime);
            
            //The pause time between notes is 30% longer than the note duration.
            //This time may vary depending on each music sample.
            //It should be set to whatever value sounds good to you.
            
            int note_waiting_time = noteTime * 1.30;
            delay(note_waiting_time);
            
            noTone(speakerPin);  //Mute the music
        }
    }
}
