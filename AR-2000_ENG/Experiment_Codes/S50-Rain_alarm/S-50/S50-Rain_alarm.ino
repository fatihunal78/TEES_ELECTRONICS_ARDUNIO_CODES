//S50 - Rain alarm

int LEDPin = 8;      //Define the digital pin number to which the LED is connected
int sensorPin = 2;   //Define the pin number to which the humidity sensor is connected
int speakerPin = 4;  //Define the pin number to which the Speaker is connected

int rainStatus = 0;  //Define the variable to store the status of the humidity sensor

void setup() {
    pinMode(LEDPin, OUTPUT);     //Set the pin to which the LED is connected as output
    pinMode(speakerPin, OUTPUT); //Set the pin to which the Speaker is connected as output 
    pinMode(sensorPin, INPUT);   //Set the pin to which the sensor is connected as input
}

void loop() {
    //Query rain status and assign it to the variable
    rainStatus = digitalRead(sensorPin);

    //Check the rain status
    if(rainStatus == HIGH) {     //If it is raining
        //Turn ON the LED
        digitalWrite(LEDPin, HIGH); 
        
        tone(speakerPin, 750);   //Activate the Speaker
        delay(50);               //Wait for 50ms 
        noTone(speakerPin);      //Mute the Speaker
        delay(200);              //Wait for 200ms 
        digitalWrite(LEDPin, LOW); //Turn OFF the LED
        
        tone(speakerPin, 750);   //Activate the Speaker
        delay(200);              //Wait for 200ms
        noTone(speakerPin);      //Mute the Speaker
        delay(50);               //Wait for 50ms
    }
    else {                       //If it is not raining
        //Turn OFF the LED
        digitalWrite(LEDPin, LOW); 
        noTone(speakerPin);      //Mute the Speaker
    }
}
