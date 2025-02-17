//S51 - Space wars
//Define the pin numbers to which the LEDs are connected
int LEDPin1 = 6;
int LEDPin2 = 7;
//Define the pin number to which the Speaker is connected 
int speakerPin = 3;
//Define the pin number to which the Button is connected
int buttonPin = 2;
//Define the counter variable
int counter = 0;

void setup() {
    //Set the pin to which the LEDs are connected as output
    pinMode(LEDPin1, OUTPUT);
    pinMode(LEDPin2, OUTPUT);
    //Set the pin to which the Speaker is connected as output
    pinMode(speakerPin, OUTPUT);
    //Set the pin to which the Button is connected as input
    pinMode(buttonPin, INPUT);
}

void loop() {
    //Query the Button status
    if(digitalRead(buttonPin) == HIGH) //If the Button is pressed
    {
        playSound(random(0, 200), random(100, 200));  //Play sound from the Speaker with playSound function
        playSound(random(0, 200), random(100, 200));
        playSound(random(0, 200), random(100, 200));
        playSound(random(0, 200), random(100, 200));
        playSound(1200, 150);
        playSound(2000, 150);                         //Fixed typo in function name from sesCaldir to playSound
        playSound(2800, 150);
        playSound(3600, 150);
        playSound(random(0, 200), random(100, 200));
        playSound(random(0, 200), random(100, 200));
        playSound(random(0, 200), random(100, 200));
        playSound(random(0, 200), random(100, 200));
        playSound(600, 200);
        playSound(800, 200);
        playSound(1000, 200);
        playSound(1800, 200);
        playSound(1200, 200);
    }
}

void playSound(int note, int time) //Define playSound function, take musical note and time as input parameters
{
    for(int i = 0; i < 3; i++)
    {
        note = note + 100;
        tone(speakerPin, note, time/3);  //Play the note
        delay(time/3);                   //wait for time/3
        noTone(speakerPin);             //Mute the note
    }
    
    if(counter%2 == 0)                  //Turn ON and OFF the LEDs in order
    {
        digitalWrite(LEDPin1, HIGH);     //Turn ON the first LED
        delay(time);                     //Wait as long as desired  
        digitalWrite(LEDPin1, LOW);      //Turn OFF the first LED
    }
    else
    {
        digitalWrite(LEDPin2, HIGH);     //Turn ON the second LED
        delay(time);                     //Wait as long as desired
        digitalWrite(LEDPin2, LOW);      //Turn OFF the second LED
    }
    
    delay(50);                          //Wait for 50ms
    counter++;                          //Increment counter variable by one
}