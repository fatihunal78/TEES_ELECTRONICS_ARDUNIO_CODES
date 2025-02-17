//S86 - Room thermometer with LED

//Add math.h library
#include <math.h>

int NTCPin = A5;        //Define the analog pin number to which the NTC is connected
int analogValue;        //Define variable to store the NTC value
double temperature;     //Define the variable to store the temperature value

int GreenLED1 = 2;     //Define the pin number to which the 1st Green LED on LEDBAR is connected
int GreenLED2 = 3;     //Define the pin number to which the 2nd Green LED on LEDBAR is connected
int YellowLED = 4;     //Define the pin number to which the Yellow LED on LEDBAR is connected
int RedLED1 = 5;       //Define the pin number to which the 1st Red LED on LEDBAR is connected
int RedLED2 = 6;       //Define the pin number to which the 2nd Red LED on LEDBAR is connected

void setup()
{
    pinMode(GreenLED1, OUTPUT);    //Set the pin to which the 1st Green LED on LEDBAR is connected as output
    pinMode(GreenLED2, OUTPUT);    //Set the pin to which the 2nd Green LED on LEDBAR is connected as output
    pinMode(YellowLED, OUTPUT);    //Set the pin to which the Yellow LED on LEDBAR is connected as output
    pinMode(RedLED1, OUTPUT);      //Set the pin to which the 1st Red LED on LEDBAR is connected as output
    pinMode(RedLED2, OUTPUT);      //Set the pin to which the 2nd Red LED on LEDBAR is connected as output
}

//Define NTCCalculate function
double NTCCalculate(int analogRead)
{
    //Calculate temperature value according to NTC specifications
    temperature = log(((10240000 / analogRead) - 10000));
    temperature = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temperature * temperature )) * temperature);
    temperature = temperature - 273.15;
    //Return the calculated temperature value
    return temperature;
}

void loop()
{
    //Read NTC value and save it to analogValue variable
    analogValue = analogRead(NTCPin);
    //Calculate the temperature value with the NTCCalculate function and save the value to the temperature variable
    temperature = NTCCalculate(analogValue);

    if(temperature >= 16 && temperature <= 18)    //If the temperature value is between 16 degrees and 18 degrees
    {
        digitalWrite(GreenLED1, HIGH);    //Turn ON the 1st Green LED
        digitalWrite(GreenLED2, LOW);     //Turn OFF the 2nd Green LED
        digitalWrite(YellowLED, LOW);     //Turn OFF the Yellow LED
        digitalWrite(RedLED1, LOW);       //Turn OFF the 1st Red LED
        digitalWrite(RedLED2, LOW);       //Turn OFF the 2nd Red LED
    }
    else if(temperature > 18 && temperature <= 20)    //If the temperature value is greater than 18 degrees and less than or equal to 20 degrees
    {
        digitalWrite(GreenLED1, LOW);     //Turn OFF the 1st Green LED
        digitalWrite(GreenLED2, HIGH);    //Turn ON the 2nd Green LED
        digitalWrite(YellowLED, LOW);     //Turn OFF the Yellow LED
        digitalWrite(RedLED1, LOW);       //Turn OFF the 1st Red LED
        digitalWrite(RedLED2, LOW);       //Turn OFF the 2nd Red LED
    }
    else if(temperature > 20 && temperature <= 22)    //If the temperature value is greater than 20 degrees and less than or equal to 22 degrees
    {
        digitalWrite(GreenLED1, LOW);     //Turn OFF the 1st Green LED
        digitalWrite(GreenLED2, LOW);     //Turn OFF the 2nd Green LED
        digitalWrite(YellowLED, HIGH);    //Turn ON the Yellow LED
        digitalWrite(RedLED1, LOW);       //Turn OFF the 1st Red LED
        digitalWrite(RedLED2, LOW);       //Turn OFF the 2nd Red LED
    }
    else if(temperature > 22 && temperature < 24)    //If the temperature value is greater than 22 degrees and less than 24 degrees
    {
        digitalWrite(GreenLED1, LOW);     //Turn OFF the 1st Green LED
        digitalWrite(GreenLED2, LOW);     //Turn OFF the 2nd Green LED
        digitalWrite(YellowLED, LOW);     //Turn OFF the Yellow LED
        digitalWrite(RedLED1, HIGH);      //Turn ON the 1st Red LED
        digitalWrite(RedLED2, LOW);       //Turn OFF the 2nd Red LED
    }
    else if(temperature >= 24)    //If the temperature value is greater than or equal to 24
    {
        digitalWrite(GreenLED1, LOW);     //Turn OFF the 1st Green LED
        digitalWrite(GreenLED2, LOW);     //Turn OFF the 2nd Green LED
        digitalWrite(YellowLED, LOW);     //Turn OFF the Yellow LED
        digitalWrite(RedLED1, LOW);       //Turn OFF the 1st Red LED
        digitalWrite(RedLED2, HIGH);      //Turn ON the 2nd Red LED
    }
    delay(500);    //Wait for 500ms
}
