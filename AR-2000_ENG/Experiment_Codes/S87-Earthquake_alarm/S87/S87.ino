//S87 - Earthquake alarm

int buttonPin = 2;     //Define the pin number to which the Button is connected
int sensorPin = 3;     //Define the pin number to which the earthquake sensor is connected
int speakerPin = 4;    //Define the pin number to which the Speaker is connected
int LEDPin = 7;        //Define the pin number to which the LED is connected
int LEDStatus = 0;     //Define the variable to store the LED status

//Define variables to store time values
unsigned long oldTime = 0;
unsigned long newTime;

void setup()
{
    pinMode(buttonPin, INPUT_PULLUP);     //Set the pin to which the Button is connected as input
    pinMode(sensorPin, INPUT_PULLUP);     //Set the pin to which the sensor is connected as input
    pinMode(speakerPin, OUTPUT);          //Set the pin to which the Speaker is connected as output
    pinMode(LEDPin, OUTPUT);              //Set the pin to which the LED is connected as output
}

void loop()
{
    if(digitalRead(sensorPin) == LOW)     //If HIGH value is detected from the sensor pin, that is, if an earthquake occurs
    {
        while(1)     //Enter infinite loop
        {
            //Save the running time of the Arduino in milliseconds
            newTime = millis();

            if(newTime - oldTime > 500)     //Flash the LED at half-second intervals
            {
                if(LEDStatus == 1)     //If the LED is ON
                {
                    digitalWrite(LEDPin, LOW);     //Turn OFF the LED
                    LEDStatus = 0;                 //Save the LED status as OFF
                }
                else     //If the LED is OFF
                {
                    digitalWrite(LEDPin, HIGH);    //Turn ON the LED
                    LEDStatus = 1;                 //Save the LED status as ON
                }
                //Update the old time value with the new time value
                oldTime = newTime;
            }

            tone(speakerPin, 350);        //Play audio from the Speaker
            delay(300);                   //Wait for 300ms
            noTone(speakerPin);          //Mute the Speaker
            delay(80);                    //Wait for 80ms

            if(digitalRead(buttonPin) == LOW)     //If the Button is pressed
            {
                noTone(speakerPin);              //Mute the Speaker
                digitalWrite(LEDPin, LOW);        //Turn OFF the LED
                break;                           //Exit infinite loop
            }
        }
    }
}
