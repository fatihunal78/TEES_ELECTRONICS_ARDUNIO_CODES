//SA79 - Backgammon dice

//Define the digital pin numbers to which the LEDs are connected
int LEDs[] = {3, 4, 5, 6, 7, 8, 9};
//Define the pin number to which the Button is connected
int buttonPin = 2;
//Define the pin number to which the Speaker is connected  
int speakerPin = 12;
//Define the variable to store the number
int number = 0;

void setup() {
    //Set the pins to which the LEDs are connected as output
    //With for loop, set the pin to which the LEDs are connected as output
    for(int i=0; i<7; i++) {
        pinMode(LEDs[i], OUTPUT);
    }
    //Set the pin to which the button is connected as input
    pinMode(buttonPin, INPUT_PULLUP);
    //Set the pin to which the Speaker is connected as output
    pinMode(speakerPin, OUTPUT);
}

void loop() {
    //Check whether the Button is pressed or not
    if(digitalRead(buttonPin) == LOW) {    //If the button is pressed
        for(int i=0; i<7; i++) {          //Repeat 7 times
            randomSeed(analogRead(A0));    //Reference Analog 0 pin to generate random number
            //Set a random number between 1 and 6 and save it to the number variable
            number = random(1, 7);
            tone(speakerPin, number*220);
            showDice(number);              //Send number variable to showDice() function
            delay(300);                    //Wait for 300ms
            noTone(speakerPin);
        }
    }
}

//Define the showDice function
void showDice(int dice) {
    switch(dice) {                        //Perform switch case operation according to the dice value
        case 1:
            //Turn OFF all LEDs
            for(int i=0; i<7; i++)
                digitalWrite(LEDs[i], LOW);
            //Show 1 on the dice
            digitalWrite(LEDs[4], HIGH);
            break;

        case 2:
            //Turn OFF all LEDs
            for(int i=0; i<7; i++)
                digitalWrite(LEDs[i], LOW);
            //Show 2 on dice
            digitalWrite(LEDs[1], HIGH);
            digitalWrite(LEDs[6], HIGH);
            break;

        case 3:
            //Turn OFF all LEDs
            for(int i=0; i<7; i++)
                digitalWrite(LEDs[i], LOW);
            //Show 3 on the dice
            digitalWrite(LEDs[1], HIGH);
            digitalWrite(LEDs[4], HIGH);
            digitalWrite(LEDs[6], HIGH);
            break;

        case 4:
            //Turn OFF all LEDs
            for(int i=0; i<7; i++)
                digitalWrite(LEDs[i], LOW);
            //Show 4 on the dice
            digitalWrite(LEDs[0], HIGH);
            digitalWrite(LEDs[1], HIGH);
            digitalWrite(LEDs[3], HIGH);
            digitalWrite(LEDs[6], HIGH);
            break;

        case 5:
            //Turn OFF all LEDs
            for(int i=0; i<7; i++)
                digitalWrite(LEDs[i], LOW);
            //Show 5 on the dice
            digitalWrite(LEDs[0], HIGH);
            digitalWrite(LEDs[1], HIGH);
            digitalWrite(LEDs[3], HIGH);
            digitalWrite(LEDs[4], HIGH);
            digitalWrite(LEDs[6], HIGH);
            break;

        case 6:
            //Turn OFF all LEDs
            for(int i=0; i<7; i++)
                digitalWrite(LEDs[i], LOW);
            //Show 6 on the dice
            digitalWrite(LEDs[0], HIGH);
            digitalWrite(LEDs[1], HIGH);
            digitalWrite(LEDs[2], HIGH);
            digitalWrite(LEDs[3], HIGH);
            digitalWrite(LEDs[5], HIGH);
            digitalWrite(LEDs[6], HIGH);
            break;
    }
}
