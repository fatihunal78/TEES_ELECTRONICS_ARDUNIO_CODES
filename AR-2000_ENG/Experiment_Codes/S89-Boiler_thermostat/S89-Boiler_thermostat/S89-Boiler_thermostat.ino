//S89 - Boiler thermostat

//Add the math.h library to perform the logarithmic calculations
#include <math.h>

int NTCPin = A0;        //Define the analog pin number to which the NTC is connected
int analogValue;        //Define variable to store the NTC value
double temperature;     //Define the variable to store the temperature value

int Yellow_LEDPin = 2;  //Define the pin number to which the Yellow LED is connected 
int Red_LEDPin = 7;     //Define the pin number to which the Red LED is connected 
int buzzerPin = 5;      //Define the pin number to which the Buzzer is connected 

void setup()
{
    pinMode(Yellow_LEDPin, OUTPUT);    //Set the pin to which the Yellow LED is connected as output
    pinMode(Red_LEDPin, OUTPUT);       //Set the pin to which the Red LED is connected as output 
    pinMode(buzzerPin, OUTPUT);        //Set the pin to which the Buzzer is connected as output 
}

void loop()
{
    //Read NTC value and save it to analogValue variable
    analogValue = analogRead(NTCPin);

    //Calculate temperature value according to NTC specifications
    temperature = log(((10240000 / analogValue) - 10000));
    temperature = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temperature * temperature )) * temperature);
    temperature = temperature - 273.15;

    if(temperature >= 45)    //If the temperature value is greater than or equal to 45 
    {
        digitalWrite(Yellow_LEDPin, LOW);     //Turn OFF the Yellow LED 
        digitalWrite(Red_LEDPin, HIGH);       //Turn ON the Red LED 
        digitalWrite(buzzerPin, HIGH);        //Make a sound from the Buzzer 
        delay(100);                          //Wait for 100ms 
        digitalWrite(Red_LEDPin, LOW);        //Turn OFF the Red LED 
        digitalWrite(buzzerPin, LOW);         //Mute the Buzzer 
        delay(100);                          //Wait for 100ms 
    }
    else    //If the temperature is below 45 degrees 
    {
        digitalWrite(Yellow_LEDPin, HIGH);    //Turn ON the Yellow LED 
        digitalWrite(Red_LEDPin, LOW);        //Turn OFF the Red LED 
        digitalWrite(buzzerPin, LOW);         //Mute the Buzzer 
    }
}
