//SA85 - Level crossing application

#include <Servo.h>                                    //Add the servo motor library

int servoPin = 2;                                    //Define the pin number to which the servo motor is connected
int buzzerPin = 11;                                  //Define the pin to which the Buzzer is connected
#define triggerPin 4                                 //Define the pin to which the HC-SR04 Trigger leg is connected
#define echoPin 5                                    //Define the pin to which the HC-SR04 Echo pin is connected

int red_LED = 12;                                    //Define the pin to which the red LED on the Traffic Module is connected
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
    measure_distance();                             //Call the measure_distance() function to measure the distance
    digitalWrite(buzzerPin, LOW);
    
    if(distance <= 5) {                            //If the distance is less than or equal to 5cm, that is, train is coming 
        for(int i=90; i>=0; i--) {                 //Close the barrier to vehicles
            servo.write(i);
            digitalWrite(green_LED, LOW);           //Turn OFF the Green LED 
            delay(30);
            newTime = millis();
            
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
        
        if(distance > 5) {                         //If the distance is greater than 5cm, that is, there is no train 
            digitalWrite(buzzerPin, LOW);
            digitalWrite(red_LED, HIGH); 
            delay(5000);
            
            if(distance > 5) {                     //If the distance is greater than 5cm, that is, there is no train 
                for(int i=0; i<=90; i++) {         //Open the barrier, allow the vehicles to pass 
                    servo.write(i);
                    delay(30);
                    
                    newTime = millis();
                    if(newTime - oldTime > 500) {
                        if(buzzerStatus == 0) {
                            digitalWrite(yellow_LED, HIGH); 
                            digitalWrite(red_LED, LOW);    //When the barrier is opened, turn OFF the Red LED
                            buzzerStatus = 1;
                        } else {
                            digitalWrite(buzzerPin, LOW);
                            digitalWrite(yellow_LED, LOW); 
                            buzzerStatus = 0;
                        }
                        oldTime = newTime;
                    }
                }
            }
            digitalWrite(green_LED, HIGH);         //Turn ON the Green LED when the barrier is opened
            digitalWrite(yellow_LED, LOW);         //Turn OFF the Yellow LED when the barrier is opened
            digitalWrite(red_LED, HIGH);           //Turn OFF the Red LED when the barrier is opened
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
