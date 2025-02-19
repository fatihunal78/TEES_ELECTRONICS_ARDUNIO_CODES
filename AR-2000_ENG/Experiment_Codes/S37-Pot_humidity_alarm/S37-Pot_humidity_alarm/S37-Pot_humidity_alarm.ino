//S37 - Pot humidity alarm

int GreenLED = 8;      //Define the digital pin number to which the Green LED is connected
int sensorPin = 2;     //Define the pin number to which the humidity sensor is connected
int speakerPin = 4;    //Define the pin number to which the Speaker is connected
int podHumidityStatus = 0;  //Define the variable to store the humidity sensor state

//When the humidity level is low, the music will play. Musical notes to use in this music
int la, ti, re, reDiez, mi, fa, so;  //Do-Re-Mi-Fa-So-La-Ti-Do

int noteTime;  //Variable to store the musical note playing time is defined

void setup() {
    pinMode(GreenLED, OUTPUT);    //Set the pin to which the LED is connected as output
    pinMode(speakerPin, OUTPUT);  //Set the pin to which the Speaker is connected as output
    pinMode(sensorPin, INPUT);    //Set the pin to which the humidity sensor is connected as input

    //Frequency values corresponding to the musical notes
    la = 440;
    ti = 494;
    re = 587;
    reDiez = 622;
    mi = 659;
    fa = 698;
    so = 784;
    noteTime = 110;  //Set note playing time
}

void loop() {
    //Query the humidity sensor status and assign it to the variable
    potHumidityStatus = digitalRead(sensorPin);
    //Check the humidity status of the pot
    if(potHumidityStatus == LOW) {  //If the pot humidity is low
        digitalWrite(GreenLED, LOW);  //Turn OFF the Green LED
        //Play the music
        tone(speakerPin, re);
        delay(2*noteTime);
        tone(speakerPin, mi);
        delay(2*noteTime);
        tone(speakerPin, mi);
        delay(4*noteTime);
        tone(speakerPin, reDiez);
        delay(2*noteTime);
        tone(speakerPin, so);
        delay(2*noteTime);
        tone(speakerPin, fa);
        delay(2*noteTime);
        tone(speakerPin, mi);
        delay(4*noteTime);
        noTone(speakerPin);
        delay(2*noteTime);
        tone(speakerPin, so);
        delay(2*noteTime);
        tone(speakerPin, la);
        delay(2*noteTime);
        tone(speakerPin, ti);
        delay(4*noteTime);
        tone(speakerPin, ti);
        delay(2*noteTime);
        tone(speakerPin, ti);
        delay(2*noteTime);
        tone(speakerPin, la);
        delay(2*noteTime);
        tone(speakerPin, ti);
        delay(4*noteTime);
    }
    else {  //If the pot humidity is sufficient
        noTone(speakerPin);           //Mute the Speaker
        digitalWrite(GreenLED, HIGH);  //Turn ON the Green LED
    }
}
