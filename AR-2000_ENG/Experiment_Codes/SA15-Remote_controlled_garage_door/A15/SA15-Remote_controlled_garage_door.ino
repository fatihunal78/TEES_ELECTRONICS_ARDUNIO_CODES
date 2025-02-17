//SA15 - Remote controlled garage door

#include <IRremote.h>    //Add IR receiver library
#include <Servo.h>       //Add servo motor library

#define doorOpenClose 0xFF38C7    //IR Control Key OK

int IRPin = 2;          //Define the pin to which the IR receiver signal leg is connected
int buzzerPin = 7;      //Define the pin to which the Buzzer is connected 
int servoPin = 5;       //Define the pin number to which the servo motor is connected

IRrecv IRReceive(IRPin);    //Define an IR Receiver named IRReceive
decode_results result;      //Define variable to store values received from IR receiver
Servo servo;               //Define servo motor

int doorStatus = 0;        //Define the variable to store the status of the door contact

void setup() {
    IRReceive.enableIRIn();      //Start IR receiver 
    pinMode(buzzerPin, OUTPUT);   //Set the pin to which the Buzzer is connected as output 
    servo.attach(servoPin);       //Set the pin to which the servo motor is connected 
    servo.write(90);              //Rotate servo motor to 90 degrees 
}

void loop() {
    //Check if there is any information coming from IR receiver
    if(IRReceive.decode(&result)) {
        if(result.value == doorOpenClose && doorStatus == 0) {    //If the OK key of the remote controller is pressed and the door is closed 
            digitalWrite(buzzerPin, HIGH);    //Make a sound from the Buzzer 
            delay(50);                        //Wait for 50ms 
            digitalWrite(buzzerPin, LOW);     //Mute the Buzzer 
            doorStatus = 1;                   //Set the doorStatus variable as door open 
       
            for(int i = 90; i <= 180; i++) {  //To open the door, increment the variable i one by one from 90 degrees to 180 degrees
                servo.write(i);               //Write the value to servo motor 
                delay(30);                    //Delay for 30ms
            }
        }
        
        if(result.value == doorOpenClose && doorStatus == 1) {    //If the OK key of the remote controller is pressed and the door is open 
            digitalWrite(buzzerPin, HIGH);    //Make a sound from the Buzzer 
            delay(50);                        //Wait for 50ms 
            digitalWrite(buzzerPin, LOW);     //Mute the Buzzer 
            doorStatus = 0;                   //Set doorStatus variable as door closed 
      
            for(int i = 180; i >= 90; i--) {  //To close the door, decrement the variable i one by one from 180 degrees to 90 degrees
                servo.write(i);               //Write the value to servo motor 
                delay(30);                    //Delay for 30ms
            }
        }
        
        IRReceive.resume();    //Reset IR receiver to get other values 
    }
}
