//S90 - Ultrasonic theremin

//Define the pin to which the HC-SR04 Trigger leg is connected
#define triggerPin 4
//Define the pin to which the HC-SR04 Echo pin is connected
#define echoPin 5
//Define the pin number to which the Speaker is connected
int speakerPin = 2;
//Define time and distance variables
long time, distance;
int proportion;

void setup()
{
    //Set the pin to which the trigger leg is connected as output
    pinMode(triggerPin, OUTPUT);
    //Set the pin to which the echo leg is connected as input
    pinMode(echoPin, INPUT);
}

void loop()
{
    //Pull the trigger leg to zero
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);    //Wait for 2 microseconds
    //Pull the trigger leg to 5V
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);    //Wait for 10 microseconds
    //Pull the trigger leg to zero
    digitalWrite(triggerPin, LOW);
    //Measure the return time of the audio signal from the echo pin
    time = pulseIn(echoPin, HIGH);
    //Calculate the distance in cm by multiplying the measured time by the speed of sound
    distance = (time/2) * 0.034;
    //Multiply the distance by 10
    distance = distance * 10;
    proportion = map(distance, 0, 250, 0, 1000);
    if(distance > 250)    //Mute the Speaker if the measured distance is greater than 25cm
    {
        noTone(speakerPin);    //Mute the Speaker
    }
    else    //If the measured distance is less than 25cm
    {
        tone(speakerPin, proportion);    //Play sound from speaker as per distance value
    }
    delay(250);    //Wait for 250ms
}
