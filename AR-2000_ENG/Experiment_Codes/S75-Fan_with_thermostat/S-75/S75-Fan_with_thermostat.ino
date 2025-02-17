//S75 - Fan with thermostat

//Add math.h library
#include <math.h>

//Define the pin number to which the LED is connected
int LEDPin = 7;
//Define the pin number to which the transistor is connected 
int transistorPin = 2;
//Define the analog pin number to which the NTC is connected
int NTCPin = A5;
//Define the analog pin number to which the Potentiometer is connected
int potPin = A1;
//Define the variable to store the Potentiometer value
int potValue = 0;
//Define the variable to store the set temperature value
double setTemperature = 0;
//Define the variable to store the NTC value
int analogValue;
//Define the variable to store the temperature value
double temperature;

void setup() {
    //Connect serial port with 9600 baud rate
    Serial.begin(9600);
    //Set the pin to which the transistor is connected as output
    pinMode(transistorPin, OUTPUT);
    //Set the pin to which the LED is connected as output
    pinMode(LEDPin, OUTPUT);
}

//Define NTCCalculate function
double NTCCalculate(int analogRead) {
    double temperature;
    temperature = log(((10240000 / analogRead) - 10000));
    temperature = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temperature * temperature)) * temperature);
    temperature = temperature - 273.15;
    return temperature;
}

void loop() {
    //Read NTC value and save it to analogValue variable
    analogValue = analogRead(NTCPin);
    //Calculate the temperature value with the NTCCalculate function and save the value to the temperature variable
    temperature = NTCCalculate(analogValue);
    
    potValue = analogRead(potPin);
    setTemperature = (float)(map(potValue, 0, 1023, 500, 150)) / 10;
    //Send the read and calculated values to the serial port screen
    Serial.print("Set Temperature:");
    Serial.print(setTemperature);
    Serial.print(" - ");
    Serial.print("Measured Temperature:");
    Serial.println(temperature);
    
    if(temperature > setTemperature) {
        digitalWrite(transistorPin, HIGH); //Switch the transistor to conduction state
        digitalWrite(LEDPin, HIGH); //Turn ON the LED
    }
    else {
        digitalWrite(transistorPin, LOW); //Switch the transistor to cut-off state
        digitalWrite(LEDPin, LOW); //Turn OFF the LED
    }
    delay(500); //Wait for 500ms
}
