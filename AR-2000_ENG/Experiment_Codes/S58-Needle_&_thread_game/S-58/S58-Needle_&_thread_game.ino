//S58 - Needle & thread game

int LEDPin = 2;      //Define the pin number to which the LED on the panel is connected
int speakerPin = 7;  //Define the pin number to which the Speaker is connected 
int sensorPin = 4;   //Define the connection coming from the 10K resistor as sensor pin

void setup() {
    pinMode(LEDPin, OUTPUT);      //Set the pin to which the LED is connected as output
    pinMode(speakerPin, OUTPUT);  //Set the pin to which the Speaker is connected as output 
    pinMode(sensorPin, INPUT);    //Set the pin to which the Sensor is connected as input 
}

void loop() {
    //Free mode settings 
    if(digitalRead(sensorPin) == HIGH) {  //If the value read from the sensor is 1, that is, if the needle and thread 
                                         //touch each other
        digitalWrite(LEDPin, HIGH);       //Turn ON the Red LED on the panel 
        tone(speakerPin, 700);           //Play audio from the Speaker 
    }
    else {  //If the value read from the sensor is 0, that is, the needle and thread does not touch each other 
        digitalWrite(LEDPin, LOW);        //Turn OFF the LED 
        noTone(speakerPin);              //Mute the Speaker 
    }
    delay(100);
}
