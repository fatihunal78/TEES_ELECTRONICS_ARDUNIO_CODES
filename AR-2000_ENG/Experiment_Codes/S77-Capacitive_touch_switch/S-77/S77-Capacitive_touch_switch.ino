//S77 - Capacitive touch switch

//Add capacitive touch library
#include <CapacitiveSensor.h>

int LEDPin = 2;    //Define the pin number to which the LED is connected
int LEDStatus = 0; //Define the variable to store the LED status
long measureValue; //Define the measureValue variable where the value in the touch sensor will be stored

//Define capacitive touch receiver and transmitter pins
CapacitiveSensor touch = CapacitiveSensor(3, 4);

void setup()
{
    touch.set_CS_AutocaL_Millis(0xF); //Turn OFF automatic calibration
    pinMode(LEDPin, OUTPUT);           //Set the pin to which the LED is connected as output
}

void loop()
{
    //Set sensor sensitivity and save the measurement to measureValue variable
    measureValue = touch.capacitiveSensor(3000);
    
    if(measureValue > 2000) //If the measurement value is greater than 2000
    {
        LEDStatus++; //Increment the LEDStatus variable by one
        
        if(LEDStatus > 1)
            LEDStatus = 0; //If the LEDStatus variable is greater than 1, set the LEDStatus variable to zero
        
        if(LEDStatus == 0) //If LEDStatus variable is zero
            digitalWrite(LEDPin, HIGH); //Turn ON the LED
        if(LEDStatus == 1) //If the LEDStatus variable is one
            digitalWrite(LEDPin, LOW);  //Turn OFF the LED
    }
    
    if(measureValue <= 2000) //If the measurement value is less than or equal to 2000
    {
        if(LEDStatus == 0) //If LEDStatus variable is zero
            digitalWrite(LEDPin, LOW);  //Turn OFF the LED
        if(LEDStatus == 1) //If the LEDStatus variable is one
            digitalWrite(LEDPin, HIGH); //Turn ON the LED
    }
    
    delay(100); //Wait for 100ms
}
