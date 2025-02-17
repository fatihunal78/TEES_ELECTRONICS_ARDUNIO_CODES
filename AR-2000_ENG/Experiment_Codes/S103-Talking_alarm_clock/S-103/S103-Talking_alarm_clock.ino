//S103 - Talking alarm clock

int alarm_hour_button = 2;    //Define the pin to which the button to set the alarm hour is connected
int alarm_minute_button = 3;  //Define the pin to which the button to set the alarm minute is connected

void setup() {
    Serial.begin(9600);                         //Serial communication is started
    pinMode(alarm_hour_button, INPUT);          //Define the pin to which the button to set the alarm hour is connected as input
    pinMode(alarm_minute_button, INPUT);        //Define the pin to which the button to set the alarm minute is connected as input
}

void loop() {
    if(digitalRead(alarm_hour_button) == HIGH) {  //If the button to set the alarm hour is pressed
        Serial.println(1);                        //Send value 1 to the serial screen
        delay(100);                              //Wait for 100ms
    }
    else {                                       //If the button is not pressed
        Serial.println(0);                       //Send value 0 to the serial screen
        delay(100);                             //Wait for 100ms
    }

    if(digitalRead(alarm_minute_button) == HIGH) {  //If the button to set the alarm minute is pressed
        Serial.println(2);                          //Send value 2 to the serial screen
        delay(100);                                //Wait for 100ms
    }
    else {                                         //If the button is not pressed
        Serial.println(0);                         //Send value 0 to the serial screen
        delay(100);                               //Wait for 100ms
    }
}
