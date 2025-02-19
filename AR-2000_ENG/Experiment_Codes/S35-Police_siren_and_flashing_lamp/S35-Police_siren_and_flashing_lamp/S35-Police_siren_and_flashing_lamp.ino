//S35 - Police siren and flashing lamp

//Define the digital pin numbers to which the LEDs are connected
int LED1Pin = 3;
int LED2Pin = 4;
//Define the digital pin number to which the Button is connected
int buttonPin = 2;
//Define the pin number to which the Speaker is connected
int speakerPin = 5;
//Define the variable to store the siren tone variable
int f;
//Define the variable to store the duration of siren
int d = 10;
//Define the variables to be used for LED animation
int signalStatus = 0;
int repeatCount = 0;
int LEDStatus = 0;

void setup() {
    //Set the pins to which the LEDs are connected as output
    pinMode(LED1Pin, OUTPUT);
    pinMode(LED2Pin, OUTPUT);
    //Set the pin to which the Button is connected as input
    pinMode(buttonPin, INPUT);
    //Set the pin to which the Speaker is connected as output
    pinMode(speakerPin, OUTPUT);
}

void loop() {
    LEDStatus = 0;
    repeatCount = 0;
    signalStatus = 0;
    for(f = 635; f <= 909; f++) {
        //Check whether the Button is pressed or not
        if(digitalRead(buttonPin) == LOW) { //If the Button is not pressed
            //Sound the siren
            tone(speakerPin, f);
            delay(d);
        }
        else { //If the Button is pressed
            //Play the sound beep beep beep
            noTone(speakerPin);
            tone(speakerPin, 250);
            delay(5);
            noTone(speakerPin);
            delay(5);
        }
        d = 10;
        signalStatus++;
        //Light up the LEDs with animation
        if(signalStatus == 5) {
            switch(LEDStatus) {
                case 0:
                    digitalWrite(LED1Pin, HIGH);
                    LEDStatus++;
                    break;
                case 1:
                    digitalWrite(LED1Pin, LOW);
                    if(repeatCount < 2) {
                        repeatCount++;
                        LEDStatus = 0;
                    }
                    else {
                        LEDStatus++;
                        repeatCount = 0;
                    }
                    break;
                case 2:
                    repeatCount++;
                    if(repeatCount == 5) {
                        LEDStatus++;
                        repeatCount = 0;
                    }
                    break;
                case 3:
                    digitalWrite(LED2Pin, HIGH);
                    LEDStatus++;
                    break;
                case 4:
                    digitalWrite(LED2Pin, LOW);
                    if(repeatCount < 2) {
                        repeatCount++;
                        LEDStatus = 3;
                    }
                    else {
                        LEDStatus++;
                        repeatCount = 0;
                    }
                    break;
                case 5:
                    repeatCount++;
                    if(repeatCount == 5) {
                        LEDStatus = 0;
                        repeatCount = 0;
                    }
                    break;
            }
            signalStatus = 0;
        }
    }

    LEDStatus = 0;
    repeatCount = 0;
    signalStatus = 0;
    for(f = 909; f >= 634; f--) {
        //Check whether the Button is pressed or not
        if(digitalRead(buttonPin) == LOW) { //If the Button is not pressed
            //Sound the siren
            tone(speakerPin, f);
            delay(d);
        }
        else { //If the Button is pressed
            //Play the sound beep beep beep
            noTone(speakerPin);
            tone(speakerPin, 250);
            delay(5);
            noTone(speakerPin);
            delay(5);
        }
        d = 10;
        signalStatus++;
        //Light up the LEDs with animation
        if(signalStatus == 5) {
            switch(LEDStatus) {
                case 0:
                    digitalWrite(LED2Pin, HIGH);
                    LEDStatus++;
                    break;
                case 1:
                    digitalWrite(LED2Pin, LOW);
                    if(repeatCount < 2) {
                        repeatCount++;
                        LEDStatus = 0;
                    }
                    else {
                        LEDStatus++;
                        repeatCount = 0;
                    }
                    break;
                case 2:
                    repeatCount++;
                    if(repeatCount == 5) {
                        LEDStatus++;
                        repeatCount = 0;
                    }
                    break;
                case 3:
                    digitalWrite(LED1Pin, HIGH);
                    LEDStatus++;
                    break;
                case 4:
                    digitalWrite(LED1Pin, LOW);
                    if(repeatCount < 2) {
                        repeatCount++;
                        LEDStatus = 3;
                    }
                    else {
                        LEDStatus++;
                        repeatCount = 0;
                    }
                    break;
                case 5:
                    repeatCount++;
                    if(repeatCount == 5) {
                        LEDStatus = 0;
                        repeatCount = 0;
                    }
                    break;
            }
            signalStatus = 0;
        }
    }
}
