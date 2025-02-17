//S56 - Alarm clock

//Define the necessary variables
int queryStatus = 0;    //Define query status variable and set initial state to 0
int hour;
int minute;
int second;
int dummy = 0;
int Alarm_hour;
int Alarm_minute;
int buttonStatus = 0;
int buttonPin = 2;    //Define the pin number to which the Button is connected
int greenLED = 3;    //Define the digital pin number to which the Green LED is connected 
int redLED = 4;    //Define the pin number to which the Red LED is connected 
int speakerPin = 5;    //Define the pin number to which the Speaker is connected

void setup() {
    Serial.begin(9600);    //Start serial communication
    pinMode(buttonPin, INPUT);    //Set the pin to which the Button is connected as input
    pinMode(greenLED, OUTPUT);    //Set the pin to which the Green LED is connected as output
    pinMode(redLED, OUTPUT);    //Set the pin to which the Red LED is connected as output
    pinMode(speakerPin, OUTPUT);    //Set the pin to which the Speaker is connected as output 
}

void loop() {
    switch(queryStatus) {    //As the initial state of the queryStatus variable is 0
        case 0:    //It will enter the first case
        { 
            Serial.println("Enter hour");    //Print "Enter hour" to serial port screen.
            queryStatus = 1;    //Set the queryStatus to 1 
            break;    //Exit case 0
        }
        case 1:    //queryStatus variable had become 1 (on the line above)
        {
            if(Serial.available() > 0) {    //If there is data coming from the serial port
                hour = Serial.parseInt();    //Store the entered value in the hour variable
                Serial.print("Hour : "); Serial.println(hour);    //Print hour on the screen
                Serial.println("Enter minute");    //Print "Enter minute" to serial port screen.
                dummy = Serial.parseInt();    //If it detects any command even though we haven't pressed it, save it to the dummy variable.
                queryStatus = 2;    //Set the queryStatus variable to 2 
            }    
            break;    //Exit case 1
        }
        case 2:    //Define case 2
        {
            if(Serial.available() > 0) {    //If there is data coming from the serial port
                minute = Serial.parseInt();    //Store the entered value in the minute variable
                Serial.print("Minute:"); Serial.println(minute);    //Print minute on the screen
                queryStatus = 3;    //Set the queryStatus variable to 3
                //We exited the switch loop because there is no case 3 
            }
            break;    //Exit case 2
        }
    }

    if(digitalRead(buttonPin) == HIGH) {    //If the button is pressed 
        queryStatus = 4;    //Let's set the queryStatus variable to 4, which we set 3 above and put it into the switch loop below
        digitalWrite(redLED, LOW);    //Turn OFF the Red LED
        while(1) {    //Enter infinite loop 
            switch(queryStatus) {    //As the initial state of the queryStatus variable is 4
                case 4: {    //enter the first case as we set the queryStatus variable to 4
                    Serial.println("Enter Alarm Hour");    //Print "Enter Alarm Hour"
                    if(Serial.available() > 0) {
                        queryStatus = 5;    //Set the queryStatus to 5 
                        dummy = Serial.parseInt();    //If it detects any command even though no value os entered, save it to the dummy variable.
                    }
                    break;    //Exit case 4
                }
                case 5:    //queryStatus variable had become 5 (on the line above)
                {
                    if(Serial.available() > 0) {    //If serial communication is available 
                        Alarm_hour = Serial.parseInt();    //Store the entered value in the Alarm_hour variable
                        Serial.print("Alarm Hour :"); Serial.println(Alarm_hour);    //print "Alarm Hour" on screen
                        Serial.println("Enter Alarm Minute");    //Print "Enter Alarm Minute"
                        dummy = Serial.parseInt();    //If it detects any command even though we haven't pressed it, save it to the dummy variable.
                        queryStatus = 6;    //Set the queryStatus variable to 6 
                    }    
                    break;    //Exit case 5 
                }
                case 6:    //Switch to case 6
                {
                    if(Serial.available() > 0) {    //If there is data coming from the serial port
                        Alarm_minute = Serial.parseInt();    //Store the entered value in the Alarm_minute variable
                        Serial.print("Alarm Minute:"); Serial.println(Alarm_minute);    //Print "Alarm Minute" on the screen
                        digitalWrite(greenLED, HIGH);    //Turn ON the Green LED indicating that the Alarm has been set
                        queryStatus = 7;    //Set the queryStatus variable to 7
                        //Exit switch loop because there is no case 7 
                    }
                    break;    //Exit case 6 
                }
            } 
            if(digitalRead(buttonPin) == HIGH) {    //If the Button is pressed 
                break;    //exit while loop 
            }
        }
    }

    if(Serial.available()) {
        if(Alarm_hour == hour && Alarm_minute == minute) {    //If hour equals alarm hour and minute equals alarm minute 
            digitalWrite(redLED, HIGH);    //Turn ON the Red LED 
            digitalWrite(greenLED, LOW);    //Turn OFF the Green LED 
            tone(speakerPin, 300);    //Make sound from the Speaker
            delay(100);    //Wait for 100ms 
            noTone(speakerPin);    //Mute the Speaker
            digitalWrite(redLED, LOW);    //Turn OFF the Red LED
            delay(100);    //Wait for 100ms 
      
            //Print "Time :" to the serial port screen
            //Print hour.minute.second respectively.
            Serial.println("---------------------------------------------");
            Serial.print("Hour :"); Serial.print(hour); Serial.print("."); Serial.print(minute); Serial.print("."); 
            Serial.print(second);
            Serial.print("       "); Serial.print("Alarm :"); Serial.print(Alarm_hour); Serial.print("."); 
            Serial.println(Alarm_minute); 
            //After 1 second, the second variable will be incremented by one
            //When this operation continues 60 times, it will be 1 minute 
            delay(800);
            second++;
            if(second >= 60) {    //If the minute variable is greater than or equal to 60, it has been one minute 
                second = 0;    //Reset the second variable
                minute = minute + 1;    //Increment the minute variable by one.
            }
            if(minute >= 60) {    //If the minute variable is greater than or equal to 60, it has been 1 hour
                minute = 0;    //Reset the minute variable 
                hour = hour + 1;    //Increment the hour variable by 1 
            }
            if(hour >= 24) {    //If the hour is greater than or equal to 24 
                hour = 0;    //Set the hour variable to 0 
            }
        }
        else {    //If hour and minute are not equal to alarm hour and alarm minute 
            digitalWrite(redLED, LOW);    //Turn OFF the Red LED 
    
            //Print "Time :" to the serial port screen
            //Print hour.minute.second respectively.
            Serial.println("---------------------------------------------");
            Serial.print("Hour :"); Serial.print(hour); Serial.print("."); Serial.print(minute); Serial.print("."); 
            Serial.print(second);
            Serial.print("       "); Serial.print("Alarm :"); Serial.print(Alarm_hour); Serial.print("."); 
            Serial.println(Alarm_minute); 
            //After 1 second, the second variable will be incremented by one
            //When this operation continues 60 times, it will be 1 minute 
            delay(1000);
            second++;
            if(second >= 60) {    //If the minute variable is greater than or equal to 60, it has been one minute
                second = 0;    //Reset the second variable
                minute = minute + 1;    //Increment the minute variable by one.
            }
            if(minute >= 60) {    //If the minute variable is greater than or equal to 60, it has been 1 hour
                minute = 0;    //Reset the minute variable 
                hour = hour + 1;    //Increment the hour variable by 1 
            }
            if(hour >= 24) {    //If the hour is greater than or equal to 24 
                hour = 0;    //Set the hour variable to 0 
            }
        }
    }
}