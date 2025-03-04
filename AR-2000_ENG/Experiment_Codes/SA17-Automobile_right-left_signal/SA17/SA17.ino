//SA17 - Automobile right-left signal

//Define the pin number to which the left signal LED is connected
int leftSignalPin = 7;
//Define the pin number to which the right signal LED is connected
int rightSignalPin = 6;
//Define the pin number to which the joystick X axis is connected
int xPin = A5;
//Define the pin number to which the Speaker is connected
int speakerPin = 4;

int xPosition = 0; //Define the variable that will store the position of the Joystick X axis

void setup() {
    //Set the pin to which the left signal LED is connected as output
    pinMode(leftSignalPin, OUTPUT);
    //Set the pin to which the right signal LED is connected as output
    pinMode(rightSignalPin, OUTPUT);
    //Set the pin to which the headset is connected as output
    pinMode(speakerPin, OUTPUT);
    //Set the pin to which the Joystick X axis is connected as input
    pinMode(xPin, INPUT);
}

void loop() {
    //Read the position of the Joystick Y axis and save it to the yPosition variable
    xPosition = analogRead(xPin);

    if(xPosition > 900) { //If the Joystick is pulled to the right
        for(int i=0; i<3; i++) {
            //Turn ON the right signal LED
            digitalWrite(rightSignalPin, HIGH);
            tone(speakerPin, 1000, 5); //Play tictac sound
            delay(400); //Wait for 400ms
            //Turn OFF right signal LED
            digitalWrite(rightSignalPin, LOW);
            noTone(speakerPin); //Mute the note
            delay(400); //Wait for 400ms
        }
    }

    if(xPosition < 120) { //If the Joystick is pulled to the left
        for(int i=0; i<3; i++) {
            //Turn ON the left signal LED
            digitalWrite(leftSignalPin, HIGH);
            tone(speakerPin, 1000, 5); //Play tictac sound
            delay(400); //Wait for 400ms
            //Turn OFF left signal LED
            digitalWrite(leftSignalPin, LOW);
            noTone(speakerPin); //Mute the note
            delay(400); //Wait for 400ms
        }
    }
}
