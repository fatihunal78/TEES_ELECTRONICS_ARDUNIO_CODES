//SA75 - Automated transit system

#include <Servo.h>                    //Add servo library

Servo servo;                          //Create a Servo object named servo

#define triggerPin 2                  //Define the pin to which the HC-SR04 Trigger leg is connected
#define echoPin 3                     //Define the pin to which the HC-SR04 Echo pin is connected
long time, distance;                  //Define time and distance variables

void setup() {
    servo.attach(4);                  //Set the pin to which the servo motor is connected
    servo.write(0);                   //Set the starting position of the servo motor to 0-degree
    
    pinMode(triggerPin, OUTPUT);      //Set the pin to which the Trigger leg is connected as output 
    pinMode(echoPin, INPUT);          //Set the pin to which the Echo leg is connected as input
}

void loop() {
    measure_distance();
    
    if(distance <= 5) {              //If the distance value is less than 5 cm (If a car is passing by) 
        for(int i=0; i<=90; i++) {   //Increment i by one from 0 to 90 to open the door 
            servo.write(i);           //Write the i value as the servo's rotation angle and rotate the servo by the i angle 
            delay(15);               //15 ms delay
        }
        delay(5000);                 //Wait 5 seconds when the door is opened 
        
        for(int z=90; z>0; z--) {   //Decrease the z value by one from 90 degrees to 0 for closing the door 
            measure_distance();
            if(distance <= 5) {      //If another car comes again while the door is closing 
                                    //To reopen the door without closing it 
                for (int i=z; i<=90; i++) {  //Increment the i variable by one from the position when the door was closing 
                                            //(the last z value) to 90 
                    servo.write(i);          //Save as the angle of servo motor and rotate servo motor 
                    z = i;                   //Save angle value in variable i to variable z 
                    delay(15);               //Delay for 15ms
                }
                delay(5000);                 //Wait for 5 seconds to keep the door open
            }
            else {                          //If another car does not arrive while the door is closing
                servo.write(z);             //Rotate the servo by decreasing the servo by the value of the z variable 
                                           //(Close the door) 
            }
            delay(15);                      //Delay for 15ms 
        } 
    }
}

void measure_distance() {                   //Create the measure_distance function to measure distance
    digitalWrite(triggerPin, LOW);          //Pull the Trigger leg to zero
    delayMicroseconds(2);                   //Wait for 2 microseconds 
    digitalWrite(triggerPin, HIGH);         //Pull the Trigger leg to 5V
    delayMicroseconds(10);                  //Wait for 10 microseconds 
    digitalWrite(triggerPin, LOW);          //Pull the Trigger leg to zero
    time = pulseIn(echoPin, HIGH);         //Measure the return time of the sound waves from the Echo pin 
    distance = (time/2) * 0.034;           //Calculate distance in cm by multiplying the measured time by the speed of sound. 
                                           //The speed of sound is approximately 343m/s or 0.034cm/μs
}
