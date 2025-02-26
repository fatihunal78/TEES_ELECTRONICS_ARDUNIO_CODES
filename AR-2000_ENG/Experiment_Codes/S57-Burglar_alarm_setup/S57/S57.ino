//S57 - Burglar alarm setup

//Define the digital pin number to which the LEDs are connected
int redLEDPin = 8;      //Define the pin number to which the Red LED is connected
int greenLEDPin = 9;    //Define the pin number to which the Green LED is connected

int doorPin = 3;        //Define the pin number to which the door contact is connected
int buttonPin = 2;      //Define the pin number to which the alarm reset button is connected
int speakerPin = 4;     //Define the pin number to which the Speaker is connected
int doorStatus = 0;     //Define the variable to store the status of the door contact
int alarmStatus = 0;    //Define the variable to store the status of the alarm

void setup() {
    //Set the pin to which the LED is connected as output
    pinMode(redLEDPin, OUTPUT);
    pinMode(greenLEDPin, OUTPUT);
    pinMode(speakerPin, OUTPUT);    //Set the pin to which the Speaker is connected as output
    pinMode(buttonPin, INPUT);      //Set the pin to which the reset button is connected as input
    pinMode(doorPin, INPUT);        //Set the pin to which the door contact is connected as input
}

void loop() {
    //Query door contact status and assign its value to the variable
    doorStatus = digitalRead(doorPin);

    //Check the status of the door contact
    if(doorStatus == LOW && alarmStatus == 1) {    //If the door contact is open
        //The alarm does not stop even if the door contact is closed.
        //The alarm is silenced when the door contact is closed and the alarm silence button is pressed.
        //It stays within the while loop until the alarm is silenced.
        while(1) {
            digitalWrite(redLEDPin, HIGH);     //Turn ON the Red LED
            
            tone(speakerPin, 380);            //Activate the Speaker
            delay(250);                        //Wait for 250ms
            
            digitalWrite(redLEDPin, LOW);      //Turn OFF the red LED
            
            noTone(speakerPin);               //Mute the Speaker
            delay(250);                        //Wait for 250ms
            
            if(digitalRead(buttonPin) == HIGH) {    //If the Alarm Reset Button is pressed
                digitalWrite(greenLEDPin, LOW);     //Turn OFF the Green LED
                while(digitalRead(buttonPin) == HIGH);    //Wait as long as the Button is pressed
                break;                              //Exit infinite loop, disable the Alarm
            }
        }
        while(1) {    //Waiting in the loop while the Alarm is OFF
            //If the Button is pressed
            if(digitalRead(buttonPin) == HIGH) {
                digitalWrite(greenLEDPin, HIGH);    //Turn ON the Green LED
                while(digitalRead(buttonPin) == HIGH);    //Wait as long as the Button is pressed
                break;    //Exit the infinite loop and set the Alarm
            }
        }
    }
    else {
        //If the Button is pressed
        if(digitalRead(buttonPin) == HIGH) {
            if(alarmStatus == 0) {
                digitalWrite(greenLEDPin, HIGH);    //Turn ON the Green LED
                alarmStatus = 1;                    //Set AlarmStatus variable to 1, indicate that the Alarm is active
                while(digitalRead(buttonPin) == HIGH);    //Wait as long as the Button is pressed
            }
            else {
                digitalWrite(greenLEDPin, LOW);     //Turn OFF the Green LED
                alarmStatus = 0;                    //Set AlarmStatus variable to 0, indicate that the Alarm is passive
                while(digitalRead(buttonPin) == HIGH);    //Wait as long as the Button is pressed
            }
        }
    }
}
