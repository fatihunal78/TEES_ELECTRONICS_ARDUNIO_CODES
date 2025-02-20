//S78 - Singing flower

//Add capacitive touch library
#include <CapacitiveSensor.h>

//Define the pin number to which the Speaker is connected
int speakerPin = 4;
//Define capacitive touch receiver and transmitter pins
CapacitiveSensor cs_2_3 = CapacitiveSensor(2, 3);

void setup()
{
    cs_2_3.set_CS_AutocaL_Millis(0xF); //Turn OFF automatic calibration
}

void loop()
{
    //Save timer start time
    long start = millis();
    //Set sensor sensitivity and save measurement
    long measureValue = cs_2_3.capacitiveSensor(3000);
    int randomNumber = random(50, 500); //Generate a random between 50 and 500
    
    if(measureValue > 500) //If the measurement value is greater than 500
    {
        tone(speakerPin, randomNumber); //Play randomNumber tone sound from the Speaker
        delay(100); //Wait for 100ms
    }
    
    if(measureValue <= 2000) //If the measurement value is less than or equal to 2000
        noTone(speakerPin); //Mute the Speaker
        
    delay(10); //Wait for 10ms
}
