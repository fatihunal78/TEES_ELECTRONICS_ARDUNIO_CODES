//S93 - Proximity sensor

int sensorPin = A5;      //Define the pin number to which the Sensor is connected
float sensorValue = 0;   //Define the variable to store the sensor value 
int speakerPin = 5;      //Define the pin number to which the Speaker is connected
int beepTime = 300;      //Define the warning time variable and set its initial value to 300

void setup() 
{
    pinMode(sensorPin, INPUT);     //Set the pin to which the Sensor is connected as input
    pinMode(speakerPin, OUTPUT);   //Set the pin to which the Speaker is connected as output
}

void loop() 
{
    sensorValue = analogRead(sensorPin);           //Read the data from the sensor on the analog 0 pin and save it to the sensorValue variable
    sensorValue = sensorValue * 5.0/1023.0;       //Convert the value between 0 and 1024 read from the analog pin to voltage by multiplying it by 5 and dividing by 1023.
    delay(100);                                    //Wait for 100ms

    if(sensorValue <= 1.3) {                      //If sensorValue is less than 1.3
        noTone(speakerPin);
    }

    if(sensorValue >= 1.3 && sensorValue < 1.9) { //If sensorValue is greater than or equal to 1.3 and less than or equal to 1.9
        tone(speakerPin, 440);                    //Play audio on the Speaker
        delay(beepTime/4);
        noTone(speakerPin);
        delay(beepTime/4);
    }

    if(sensorValue >= 1.9 && sensorValue < 2.5) { //If sensorValue is greater than or equal to 1.9 and less than 2.5
        tone(speakerPin, 440);                    //Play audio on the Speaker
        delay(beepTime/5);
        noTone(speakerPin);
        delay(beepTime/5);
    }

    if(sensorValue >= 2.5 && sensorValue < 3.1) { //If sensorValue is greater than or equal to 2.5 and less than 3.1
        tone(speakerPin, 440);                    //Play audio on the Speaker
        delay(beepTime/6);
        noTone(speakerPin);
        delay(beepTime/6);
    }

    if(sensorValue >= 3.1 && sensorValue < 3.7) { //If sensorValue is greater than or equal to 3.1 and less than 3.7
        tone(speakerPin, 440);                    //Play audio on the Speaker
        delay(beepTime/7);
        noTone(speakerPin);
        delay(beepTime/7);
    }

    if(sensorValue >= 3.7 && sensorValue < 4.3) { //If sensorValue is greater than or equal to 3.7 and less than 4.3
        tone(speakerPin, 440);                    //Play audio on the Speaker
        delay(beepTime/8);
        noTone(speakerPin);
        delay(beepTime/8);
    }

    if(sensorValue >= 4.3) {                      //If sensorValue is greater than 4.3
        tone(speakerPin, 440);                    //Play audio on the Speaker
    }
}
