//S80 - Infrared vault alarm

int SensorPin = 4;    //Define the pin number to which the Sensor is connected
int buzzerPin = 11;   //Define the pin number to which the buzzer is connected
int RedLED = 5;       //Define the pin number to which the Red LED is connected

void setup()
{
    pinMode(SensorPin, INPUT);    //Set the pin to which the Sensor is connected as input
    pinMode(buzzerPin, OUTPUT);   //Set the pin to which the Buzzer is connected as output
    pinMode(RedLED, OUTPUT);      //Set the pin to which the Red LED is connected as output
}

void loop()
{
    bool val = digitalRead(SensorPin);    //Read value on sensor pin
    
    if(val == HIGH)    //If the reading is 1, if the lid is open
    {
        digitalWrite(RedLED, HIGH);      //Turn ON the Red LED
        digitalWrite(buzzerPin, HIGH);   //Make a sound from the Buzzer
        delay(200);                      //Wait for 200ms
        digitalWrite(RedLED, LOW);       //Turn OFF the Red LED
        digitalWrite(buzzerPin, LOW);    //Mute the Buzzer
        delay(200);                      //Wait for 200ms
    }
    else    //If the reading is 0, if the lid is closed
    {
        digitalWrite(RedLED, LOW);       //Turn OFF the Red LED
        digitalWrite(buzzerPin, LOW);    //Mute the Buzzer
    }
}
