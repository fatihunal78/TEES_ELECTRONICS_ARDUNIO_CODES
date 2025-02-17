//S85 - Ultrasonic vault safety alarm

//Define the pin to which the HC-SR04 Trigger leg is connected
#define triggerPin 6
//Define the pin to which the HC-SR04 Echo pin is connected  
#define echoPin 7
//Define time and distance variables
long time, distance;
int speakerPin = 3;    //Define the pin number to which the Speaker is connected
int LEDPin = 2;        //Define the digital pin number to which the LED is connected

void setup()
{
    //Set the pin to which the trigger leg is connected as output
    pinMode(triggerPin, OUTPUT);
    //Set the pin to which the echo leg is connected as input
    pinMode(echoPin, INPUT);
    
    pinMode(speakerPin, OUTPUT);    //Set the pin to which the Speaker is connected as output
    pinMode(LEDPin, OUTPUT);        //Set the pin to which the LED is connected as output
}

void loop()
{
    //Pull the trigger leg to zero
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);           //Wait for 2 microseconds
    //Pull the trigger leg to 5V
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);          //Wait for 10 microseconds
    //Pull the trigger leg to zero
    digitalWrite(triggerPin, LOW);
    //Measure the return time of the audio signal from the echo pin
    time = pulseIn(echoPin, HIGH);
    //Calculate the distance in cm by multiplying the measured time by the speed of sound
    distance = (time/2) * 0.034;

    if(distance >= 5)    //If the distance is greater than 5cm 
                        //That is, if the lid is open 
    {
        digitalWrite(LEDPin, HIGH);    //Turn ON the LED
        tone(speakerPin, 200);        //Play audio from the Speaker
        delay(200);                    //Wait for 200ms
        tone(speakerPin, 400);        //Play a different sound from the Speaker
        digitalWrite(LEDPin, LOW);     //Turn OFF the LED
    }
    else                //If the distance is less than 5cm
                       //That is, if the lid is closed
    {
        noTone(speakerPin);           //Mute the Speaker
        digitalWrite(LEDPin, LOW);     //Turn OFF the LED
    }
    delay(200);                        //Wait for 200ms
}
