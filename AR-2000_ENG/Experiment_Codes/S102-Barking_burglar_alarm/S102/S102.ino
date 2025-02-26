//S102 - Barking burglar alarm

//Define the digital pin number to which the LEDs are connected
int redLEDPin = 6;
int greenLEDPin = 7;

int doorPin = 3;      //Define the pin number to which the door contact is connected
int buttonPin = 2;    //Define the pin number to which the alarm reset button is connected
int doorStatus = 0;   //Define the variable to store the status of the door contact
int alarmStatus = 0;  //Define the variable to store the status of the alarm

void setup() {
    //Set the pins to which the LEDs are connected as output
    pinMode(redLEDPin, OUTPUT);
    pinMode(greenLEDPin, OUTPUT);
    pinMode(buttonPin, INPUT_PULLUP);  //Set the pin to which the resetting button is connected as input, activate the pull up resistor
    pinMode(doorPin, INPUT);           //Set the pin to which the door contact is connected as input
    Serial.begin(9600);
}

void loop() {
    //Query door contact status and assign its value to the variable
    doorStatus = digitalRead(doorPin);

    //Check the status of the door contact
    if(doorStatus == LOW && alarmStatus == 1) {  //If the door contact is open
        //The alarm does not stop even if the door contact is closed.
        //The alarm is silenced when the door contact is closed and the alarm silence button is pressed.
        //It stays within the while loop until the alarm is silenced.
        while(1) {
            Serial.println(1);                //Send value 1 to the serial screen to play Alarm music
            digitalWrite(greenLEDPin, LOW);   //Turn OFF the Green LED
            digitalWrite(redLEDPin, HIGH);    //Turn ON the Red LED
            delay(100);                       //Reduced delay to make barking more responsive
            digitalWrite(redLEDPin, LOW);     //Turn OFF the Red LED
            delay(100);                       //Reduced delay to make barking more responsive
            Serial.println(1);                //Send another trigger for continuous barking
            
            if(digitalRead(buttonPin) == LOW) {  //If the Alarm Reset Button is pressed
                delay(500);                        //Wait for 500ms
                Serial.println(0);                 //Send 0 to the serial screen to silence the Alarm music
                digitalWrite(greenLEDPin, LOW);    //Turn OFF the Green LED
                break;                            //Exit infinite loop, disable the Alarm
            }
        }
        while(1) {  //Waiting in the loop while the Alarm is OFF
            //If the Button is pressed
            if(digitalRead(buttonPin) == LOW) {
                delay(500);                       //Wait for 500ms
                digitalWrite(greenLEDPin, HIGH);  //Turn ON the Green LED
                Serial.println(0);                //Send 0 to the serial screen to silence the Alarm music.
                break;                           //Exit the infinite loop and set the Alarm
            }
        }
    }
    else {
        //If the Button is pressed
        if(digitalRead(buttonPin) == LOW) {
            if(alarmStatus == 0) {
                digitalWrite(greenLEDPin, HIGH);  //Turn ON the Green LED
                alarmStatus = 1;                  //Save the alarm status as ON
            }
            else {
                digitalWrite(greenLEDPin, LOW);   //Turn OFF the Green LED
                alarmStatus = 0;                  //Save the alarm status as OFF
            }
            delay(500);                          //Wait for 500ms
        }
    }
}
