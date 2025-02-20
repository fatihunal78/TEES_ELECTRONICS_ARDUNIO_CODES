//S69 - Reflex game

int LEDs[] = {8, 9, 10, 11, 12};    //Define the pin numbers to which the LEDs are connected
int buttonPin = 2;    //Define the pin number to which the Button is connected
int speakerPin = 3;    //Define the pin number to which the Speaker is connected

int target = 2;    //Set target number
int character = 0;    //Create the character variable and set the initial value to zero
int game_speed = 750;    //Define the variable that sets the game speed
boolean buttonStatus = 0;    //Define the variable to store the button state

int music[] = {    //Define the notes for the music effect when game is won
    262, 196, 196, 220, 196, 0, 247, 262
};

int noteTimes[] = {    //Define waiting times corresponding to notes
    4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
    for(int i = 0; i < 5; i++) {    //Set a for loop with 5 repetitions
        pinMode(LEDs[i], OUTPUT);    //Set the pins to which the LEDs are connected as the output pin
    }

    pinMode(buttonPin, INPUT_PULLUP);    //Set the pin to which the Button is connected as input pin and activate the pull up resistor
    //Set the pin to which the button is connected as Interrupt. When the button is pressed, perform the operation in 
    //the buttonControl function. Trigger at FALLING (Descending edge)
    attachInterrupt(digitalPinToInterrupt(buttonPin), buttonControl, FALLING);
}

void loop() {
    character = random(0, 6);    //Assign random numbers to the character variable to make the LEDs light up randomly
    digitalWrite(LEDs[character], HIGH);    //Turn ON the LED corresponding to this random number
    delay(game_speed);    //Wait as long as the game_speed variable
    digitalWrite(LEDs[character], LOW);    //Turn OFF the LED
    if(buttonStatus == 1) {
        if(character == target) {    //If the randomly generated value is equal to the specified target value
            won();    //Call the won() function indicating that you have won the game
        }
        else {    //If the randomly generated value is not equal to the specified target value
            lost();    //Call the lost() function indicating that you have lost the game
        }
    }
}

void won() {    //Create won function
    for(int i = 0; i < 8; i++) {    //A for loop from 0 to 8
        //Turn ON all LEDs
        digitalWrite(LEDs[0], HIGH);
        digitalWrite(LEDs[1], HIGH);
        digitalWrite(LEDs[2], HIGH);
        digitalWrite(LEDs[3], HIGH);
        digitalWrite(LEDs[4], HIGH);

        int noteTime = 1000/noteTimes[i];    //Create a variable noteTime and divide the value 1000 (1 second) by each note times
        tone(speakerPin, music[i], noteTime);    //Play the notes in sequence through the speaker

        int waitBetweenNotes = noteTime * 1.30;    //To determine the waiting times between notes. Multiply the noteTime 
                                                   //variable by 1.30
        delay(waitBetweenNotes);    //Delay as long as the calculated waitBetweenNotes duration
        noTone(speakerPin);    //Mute the Speaker
    }
    //Turn ON all LEDs
    digitalWrite(LEDs[0], HIGH);
    digitalWrite(LEDs[1], HIGH);
    digitalWrite(LEDs[2], HIGH);
    digitalWrite(LEDs[3], HIGH);
    digitalWrite(LEDs[4], HIGH);

    delay(300);    //Wait for 300 ms

    //Turn OFF all LEDs
    digitalWrite(LEDs[0], LOW);
    digitalWrite(LEDs[1], LOW);
    digitalWrite(LEDs[2], LOW);
    digitalWrite(LEDs[3], LOW);
    digitalWrite(LEDs[4], LOW);

    delay(300);    //Wait for 300 ms

    //Turn ON all LEDs
    digitalWrite(LEDs[0], HIGH);
    digitalWrite(LEDs[1], HIGH);
    digitalWrite(LEDs[2], HIGH);
    digitalWrite(LEDs[3], HIGH);
    digitalWrite(LEDs[4], HIGH);

    delay(300);    //Wait for 300 ms

    //Turn OFF all LEDs
    digitalWrite(LEDs[0], LOW);
    digitalWrite(LEDs[1], LOW);
    digitalWrite(LEDs[2], LOW);
    digitalWrite(LEDs[3], LOW);
    digitalWrite(LEDs[4], LOW);
    delay(300);
    buttonStatus = 0;    //Set buttonStatus variable to 0
    game_speed = game_speed - 75;    //Decrease the game_speed variable to increase game speed
}

void lost() {    //Define the lost function
    for(int j = 1; j < 4; j++) {    //Set 4 for loops
        tone(speakerPin, 100);    //Play audio from the Speaker
        delay(500);    //Wait for 500ms
        noTone(speakerPin);    //Mute the Speaker
    }
    buttonStatus = 0;    //Set the buttonStatus variable to 0
    game_speed = 750;
}

//Create a buttonControl function to check if the button is pressed. This function will check whether the button is 
//pressed or not inside the for loops
void buttonControl() {
    //Create variable last_interrupt_time and set its initial value to 0
    static unsigned long last_interrupt_time = 0;
    //Create a variable named interrupt_time and assign the system start time to it with the millis() command
    unsigned long interrupt_time = millis();

    //If the time difference between interrupt_time and last_interrupt_time is greater than 50ms. This process is used 
    //to prevent detection of multiple button presses.
    if(interrupt_time - last_interrupt_time > 50) {
        buttonStatus = 1;    //When the button is pressed, set the buttonStatus variable to 1
    }

    last_interrupt_time = interrupt_time;    //Assign the value in the interrupt_time variable to the last_interrupt_time variable
}
