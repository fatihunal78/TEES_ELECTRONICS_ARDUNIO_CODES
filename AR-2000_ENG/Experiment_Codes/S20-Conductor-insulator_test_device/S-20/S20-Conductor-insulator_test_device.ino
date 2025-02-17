//S20 - Conductor-insulator test device

int sensorPin = 3;  //The pin number to which the probe tip is connected is defined
                    //The name of pin 3 is set to sensorPin

int buzzerPin = 5;  //Buzzer is connected to pin 5 
                    //And the name of pin is set to buzzerPin

void setup() {
    pinMode(sensorPin, INPUT);   //Sensor pin is set as input pin
    pinMode(buzzerPin, OUTPUT);  //Buzzer pin is set as output pin 
}

void loop() {
    if(digitalRead(sensorPin) == HIGH) {  //Read the value on pin number 3 to which the probe is connected with the digitalRead(sensorPin) command
                                         //If this value is HIGH
        digitalWrite(buzzerPin, HIGH);    //Make a sound from the Buzzer
    }
    else {                               //If the pin on the sensor is LOW 
        digitalWrite(buzzerPin, LOW);     //Mute the Buzzer
    }
}
