//S60 - Temperature sensor
//Add math.h library
#include <math.h>

//Define the analog pin number to which the NTC is connected
int NTCPin = A0;
//Define the variable to store the NTC value 
int analogValue;
//Define the variable to store the temperature value
double temperature;

void setup() {
    //Start serial port with 9600 baud rate
    Serial.begin(9600);
}

//Define NTCCalculate function
double NTCCalculate(int analogRead) {
    //Calculate temperature value according to NTC specifications
    temperature = log(((10240000 / analogRead) - 10000));
    temperature = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temperature * temperature)) * 
                      temperature);
    temperature = temperature - 273.15;
    //Return the calculated temperature value
    return temperature;
}

void loop() {
    //Read NTC value and save it to analogValue variable
    analogValue = analogRead(NTCPin);
    //Calculate the temperature value with the NTCCalculate function and save the value to the temperature variable
    temperature = NTCCalculate(analogValue);
    //Print temperature variable to serial port
    Serial.print("Temperature :");
    Serial.print(temperature);
    Serial.println(" C");
    delay(500);    //Wait for 500ms
}
