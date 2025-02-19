//S25 - Customer alert for shops

int doorPin = 2;    //Define the pin number to which the door contact is connected
int buzzerPin = 4;  //Define the pin number to which the Buzzer is connected

void setup() {
    pinMode(doorPin, INPUT);     //Set the pin to which the door contact is connected as input
    pinMode(buzzerPin, OUTPUT);  //Set the pin to which the buzzer is connected as the output pin
}

void loop() {
    if(digitalRead(doorPin) == LOW) {  //If the door is opened
        for(int i=0; i<3; i++) {       //To make the Buzzer beep beep beep sound 3 times
            digitalWrite(buzzerPin, HIGH);  //Make a sound from the Buzzer
            delay(100);                    //Wait for 100ms
            digitalWrite(buzzerPin, LOW);   //Mute the Buzzer
            delay(100);                    //Wait for 100ms
        }
    }
    else {                           //If the door is closed
        digitalWrite(buzzerPin, LOW);  //Mute the Buzzer
    }
    delay(3000);  //Wait for 3 seconds
}
