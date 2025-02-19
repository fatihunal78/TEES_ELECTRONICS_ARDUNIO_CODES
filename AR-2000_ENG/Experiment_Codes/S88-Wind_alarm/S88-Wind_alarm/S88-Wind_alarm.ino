//S88 - Wind alarm

int windSensor = 2;     //Define the pin number to which the wind sensor is connected
int speakerPin = 4;     //Define the pin number to which the Speaker is connected
int LEDPin = 7;         //Define the pin number to which the LED is connected

void setup()
{
    pinMode(windSensor, INPUT);     //Set the pin to which the wind sensor is connected as input
    pinMode(speakerPin, OUTPUT);    //Set the pin to which the Speaker is connected as output
    pinMode(LEDPin, OUTPUT);        //Set the pin to which the LED is connected as output
}

void loop()
{
    if(digitalRead(windSensor) == HIGH)    //If there is wind
    {
        digitalWrite(LEDPin, HIGH);     //Turn ON the LED
        tone(speakerPin, 700);         //Play audio from the Speaker
        delay(100);                    //Wait for 100ms
        noTone(speakerPin);           //Mute the Speaker
        digitalWrite(LEDPin, LOW);     //Turn OFF the LED
        delay(100);                    //Wait for 100ms
    }
    else    //If there is no wind
    {
        noTone(speakerPin);           //Mute the Speaker
        digitalWrite(LEDPin, LOW);     //Turn OFF the LED
    }
}
