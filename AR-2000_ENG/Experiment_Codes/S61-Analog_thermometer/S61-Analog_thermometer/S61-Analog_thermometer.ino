//S61 - Analog thermometer

//Add math.h library
#include <math.h>
//Add servo motor library
#include <Servo.h>

//Define the analog pin number to which the NTC is connected
int NTCPin = A0;
//Define the variable to store the NTC value
int analogValue;
//Define the digital pin number to which the servo motor is connected
int servoPin = 5;
//Define the variable to store the temperature value
double temperature;
//Variable that will define the temperature value according to the angle of the servo motor
int proportion;

//We created a servo object called Servo
Servo servo;

void setup() {
    servo.attach(servoPin);    //Define that the servo is connected to pin 5
    servo.write(180);          //Initialize servo to 180 degrees position
}

void loop() {
    //Read NTC value and save it to analogValue variable
    analogValue = analogRead(NTCPin);
    //Calculate the temperature value with the NTCCalculate function and save the value to the temperature variable
    temperature = NTCCalculate(analogValue);
    proportion = map(temperature, 0, 100, 180, 0);
    servo.write(proportion);
    delay(500);               //Wait for 500ms
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
