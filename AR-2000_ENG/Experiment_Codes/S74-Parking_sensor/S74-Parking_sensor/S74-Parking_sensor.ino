//S74 - Parking sensor

//Define the pin numbers to which the LEDs are connected
int GreenLED1 = 4;
int GreenLED2 = 5;
int YellowLED = 6;
int RedLED1 = 7;
int RedLed2 = 8;

//Define the pin number to which the Speaker is attached
int speakerPin = 9;

//Define the pin to which the HC-SR04 Trigger leg is connected
#define triggerPin 2

//Define the pin to which the HC-SR04 Echo pin is connected
#define echoPin 3

//Define the variable to store the warning tone duration
int beepTime = 300;

//Define time and distance variables
long time, distance;

void setup() {
    //Set LEDs as output
    pinMode(GreenLED1, OUTPUT);
    pinMode(GreenLED2, OUTPUT);
    pinMode(YellowLED, OUTPUT); 
    pinMode(RedLED1, OUTPUT);
    pinMode(RedLED2, OUTPUT);
    
    //Set the pin to which the trigger leg is connected as output
    pinMode(triggerPin, OUTPUT);
    
    //Set the pin to which the echo leg is connected as input
    pinMode(echoPin, INPUT);
}

void loop() {
    //Pull the trigger leg to zero
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2); //Wait for 2 microseconds
    
    //Pull the trigger leg to 5V
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10); //Wait for 10 microseconds
    
    //Pull the trigger leg to zero
    digitalWrite(triggerPin, LOW);
    
    //Measure the return time of the audio signal from the echo pin
    time = pulseIn(echoPin, HIGH);
    
    //Calculate the distance in cm by multiplying the measured time by the speed of sound
    distance = (time/2) * 0.034;

    //Turn on the LEDs according to the result of the distance calculation process 
    if(distance > 50) { //If distance is greater than 50cm
        //Initially turn OFF all LEDs.
        digitalWrite(GreenLED1, LOW);
        digitalWrite(GreenLED2, LOW);
        digitalWrite(YellowLED, LOW);
        digitalWrite(RedLED1, LOW);
        digitalWrite(RedLED2, LOW);
    }
    else if(distance > 40) { //If distance is less than 50cm and greater than 40cm
        //Turn ON the first warning LED
        digitalWrite(GreenLED1, HIGH);
        
        //Turn OFF all other LEDs. 
        digitalWrite(GreenLED2, LOW);
        digitalWrite(YellowLED, LOW);
        digitalWrite(RedLED1, LOW);
        digitalWrite(RedLED2, LOW);
    }
    else if(distance > 30) { //If the distance is less than 40cm and greater than 30cm
        //Turn ON the first two LEDs
        digitalWrite(GreenLED1, HIGH);
        digitalWrite(GreenLED2, HIGH);
        
        //Turn OFF other LEDs
        digitalWrite(YellowLED, LOW);
        digitalWrite(RedLED1, LOW);
        digitalWrite(RedLED2, LOW);
        
        tone(speakerPin, 440); //Make a beep sound from the Speaker
        delay(beepTime/3); //Wait for one third of the beep time value
        noTone(speakerPin); //Mute the Speaker
        delay(beepTime/3); //Wait for one third of the beep time value
    }
    else if(distance > 20) { //If the distance is less than 30cm and greater than 20cm
        //Turn ON the first three LEDs
        digitalWrite(GreenLED1, HIGH);
        digitalWrite(GreenLED2, HIGH);
        digitalWrite(YellowLED, HIGH);
        
        //Turn OFF other LEDs 
        digitalWrite(RedLED1, LOW);
        digitalWrite(RedLED2, LOW);
        
        tone(speakerPin, 440); //Make a beep sound from the Speaker
        delay(beepTime/4); //Wait for one fourth of the beep time value
        noTone(speakerPin); //Mute the Speaker
        delay(beepTime/4); //Wait for one fourth of the beep time value
    }
    else if(distance > 10) { //If the distance is less than 20cm and greater than 10cm
        //Turn ON the first three LEDs
        digitalWrite(GreenLED1, HIGH);
        digitalWrite(GreenLED2, HIGH);
        digitalWrite(YellowLED, HIGH);
        digitalWrite(RedLED1, HIGH);
        
        //Turn OFF other LEDs 
        digitalWrite(RedLED2, LOW);
        
        tone(speakerPin, 440); //Make a beep sound from the Speaker
        delay(beepTime/5); //Wait for one fifth of the beep time value
        noTone(speakerPin); //Mute the Speaker
        delay(beepTime/5); //Wait for one fifth of the beep time value
    }
    else if(distance > 0) { //If the distance is less than 10cm and greater than 0cm
        //Turn ON all LEDs
        digitalWrite(GreenLED1, HIGH);
        digitalWrite(GreenLED2, HIGH);
        digitalWrite(YellowLED, HIGH);
        digitalWrite(RedLED1, HIGH);
        digitalWrite(RedLED2, HIGH);
        
        tone(speakerPin, 440); //Make a beep sound from the Speaker
    }
}
