//SA85 - Level crossing application

#include <Servo.h>                                    //Add the servo motor library

int servoPin = 2;                                    //Define the pin number to which the servo motor is connected
int buzzerPin = 11;                                  //Define the pin to which the Buzzer is connected
#define triggerPin 4                                 //Define the pin to which the HC-SR04 Trigger leg is connected
#define echoPin 5                                    //Define the pin to which the HC-SR04 Echo pin is connected

int red_LED = 8;                                    //Define the pin to which the red LED on the Traffic Module is connected
int yellow_LED = 9;                                  //Define the pin to which the yellow LED on the Traffic Module is connected
int green_LED = 10;                                  //Define the pin to which the green LED on the Traffic Module is connected

long time, distance;                                 //Define time and distance variables
unsigned long newTime;
unsigned long oldTime;
int buzzerStatus = 0;                               //Define the variable to store the status of the Buzzer
Servo servo;                                        //Define the servo motor variable

void setup() {
    pinMode(red_LED, OUTPUT);                       //Set the pin to which the Red LED is connected as output
    pinMode(yellow_LED, OUTPUT);                    //Set the pin to which the Yellow LED is connected as output
    pinMode(green_LED, OUTPUT);                     //Set the pin to which the Green LED is connected as output
    pinMode(triggerPin, OUTPUT);                    //Set the pin to which the Trigger leg is connected as output 
    pinMode(echoPin, INPUT);                        //Set the pin to which the Echo leg is connected as input
    pinMode(buzzerPin, OUTPUT);                     //Set the pin to which the Buzzer is connected as output
    servo.attach(servoPin);                         //Set the pin to which the servo motor is connected 
    servo.write(90);                                //Move servo motor to 90-degree position
    digitalWrite(green_LED, HIGH);                   //Initially turn ON the Green LED 
}

void loop() {
    measure_distance();                             
    digitalWrite(buzzerPin, LOW);
    
    if(distance <= 5) {                            //If train is detected
        digitalWrite(green_LED, LOW);               // Turn off green LED immediately when train is detected
        for(int i=90; i>=0; i--) {                 //Move servo motor from 90 to 0 degrees
            servo.write(i);
            delay(30);
            newTime = millis();
            
            if(newTime - oldTime > 500) {
                if(buzzerStatus == 0) {
                    digitalWrite(buzzerPin, HIGH);
                    digitalWrite(red_LED, HIGH);     // Red LED control
                    buzzerStatus = 1;
                } else {
                    digitalWrite(buzzerPin, LOW);
                    digitalWrite(red_LED, LOW);      // Red LED control
                    buzzerStatus = 0;
                }
                oldTime = newTime;
            }
        }
        
        while(distance <= 5) {                     //If train is still passing 
            measure_distance();                     //Call the measure_distance() function to measure the distance
            newTime = millis();                    //Flash the Red LED at intervals
            
            if(newTime - oldTime > 500) {
                if(buzzerStatus == 0) {
                    digitalWrite(buzzerPin, HIGH);
                    digitalWrite(red_LED, HIGH); 
                    buzzerStatus = 1;
                } else {
                    digitalWrite(buzzerPin, LOW);
                    digitalWrite(red_LED, LOW); 
                    buzzerStatus = 0;
                }
                oldTime = newTime;
            }
            delay(100);
        }
        
        if(distance > 5) {                         //If train has passed
            digitalWrite(buzzerPin, LOW);
            digitalWrite(red_LED, LOW);             // Turn off red LED when train has passed
            delay(5000);
            
            if(distance > 5) {                     //Check again if train has passed
                for(int i=0; i<=90; i++) {         //Move servo motor from 0 to 90 degrees
                    servo.write(i);
                    delay(30);
                    
                    newTime = millis();
                    if(newTime - oldTime > 500) {
                        if(buzzerStatus == 0) {
                            digitalWrite(yellow_LED, HIGH); 
                            buzzerStatus = 1;
                        } else {
                            digitalWrite(yellow_LED, LOW); 
                            buzzerStatus = 0;
                        }
                        oldTime = newTime;
                    }
                }
            }
            digitalWrite(green_LED, HIGH);          //Turn ON Green LED
            digitalWrite(yellow_LED, LOW);          //Turn OFF Yellow LED
            digitalWrite(red_LED, LOW);             // Ensure red LED is off when back to normal operation
        }
    }
}

int measure_distance() {
    digitalWrite(triggerPin, LOW);                //Pull the Trigger leg to zero
    delayMicroseconds(2);                        //Wait for 2 microseconds 
    digitalWrite(triggerPin, HIGH);               //Pull the Trigger leg to 5V
    delayMicroseconds(10);                       //Wait for 10 microseconds 
    digitalWrite(triggerPin, LOW);                //Pull the Trigger leg to zero

    time = pulseIn(echoPin, HIGH);               //Measure the return time of the sound waves from the Echo pin 
    distance = (time/2) * 0.034;                 //Calculate distance in cm by multiplying the measured time by the speed of sound
    return distance;
}
