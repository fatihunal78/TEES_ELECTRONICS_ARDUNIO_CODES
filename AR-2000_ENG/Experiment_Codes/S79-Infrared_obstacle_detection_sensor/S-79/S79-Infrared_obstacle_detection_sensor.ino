//S79 - Infrared obstacle detection sensor

int SensorPin = 4;  //Define the pin number to which the Sensor is connected
int LEDPin = 8;     //Define the pin number to which the LED is connected

void setup()
{
    pinMode(SensorPin, INPUT);  //Set the pin to which the sensor is connected as input 
    pinMode(LEDPin, OUTPUT);    //Set the pin to which the LED is connected as output 
}
   
void loop()
{
    //Read the value in the pin to which the sensor is connected. If the reading is 0, that is, if there is an 
    //obstacle in front of the sensor
    if(digitalRead(SensorPin) == LOW)
    {
        digitalWrite(LEDPin, HIGH);  //Turn ON the LED 
    }
    else  //If the reading is 1, there is no obstacle in front of the sensor 
    {
        digitalWrite(LEDPin, LOW);   //Turn OFF the LED
    }
    delay(300);  //Wait for 300ms 
}
