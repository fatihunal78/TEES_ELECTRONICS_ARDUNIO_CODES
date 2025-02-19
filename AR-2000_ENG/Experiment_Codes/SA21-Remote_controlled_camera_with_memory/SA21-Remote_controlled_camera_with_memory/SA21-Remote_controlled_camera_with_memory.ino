//SA21 - Remote controlled camera with memory

#include <IRremote.h> //Add IR receiver library
#include <Servo.h> //Add servo motor library

//Define IR control codes
#define oneKey 0xFFA25D    //IR Control key 1
#define twoKey 0xFF629D    //IR Control key 2
#define threeKey 0xFFE21D  //IR Control key 3
#define fourKey 0xFF22DD   //IR Control key 4
#define okKey 0xFF38C7     //Command OK Key

//Define the pin number to which the joystick X axis is connected
int xPin = A0;

int xPosition = 0;         //Define the variable that will store the position of the Joystick X axis

int IRPin = 2;            //Define the pin to which the IR receiver signal leg is connected

int buzzerPin = 8;        //Define the pin to which the Buzzer is connected

int servoPin = 5;         //Define the pin number to which the servo motor is connected
int servoStep = 0;        //Define the variable to store servo steps
int cameraPosition = 0;    //Define the variable to store the camera position angle

int oneKeyRecord = 0;
int twoKeyRecord = 0;
int threeKeyRecord = 0;
int fourKeyRecord = 0;

IRrecv IRReceive(IRPin);   //Define an IR Receiver named IRReceive
decode_results result;     //Define variable to store values from IR receiver
Servo servo;              //Define servo motor

void setup() {
    IRReceive.enableIRIn();           //Start IR receiver
    pinMode(buzzerPin, OUTPUT);       //Set the pin to which the Buzzer is connected as output
    servo.attach(servoPin);           //Set the pin to which the servo motor is connected
    servo.write(90);                  //Move servo motor to 90-degree position
}

void loop() {
    //Read the position of the Joystick X axis and save it to the xPosition variable
    xPosition = analogRead(xPin);
    //Proportion the xPosition value relative to the servo angle
    cameraPosition = map(xPosition, 0, 1023, 180, 0);
    //Adjust the angle of the servo motor according to the cameraPosition variable
    servo.write(cameraPosition);
    //Check if there is any information coming from IR receiver
    if(IRReceive.decode(&result)) {
        if(result.value == oneKey) {  //If key 1 is pressed
            oneKeyRecord = cameraPosition;     //Save the camera position to the oneKeyRecord variable
            digitalWrite(buzzerPin, HIGH);     //Make a sound from the buzzer
            delay(100);                        //Wait for 100ms
            digitalWrite(buzzerPin, LOW);      //Mute the Buzzer
        }
        else if(result.value == twoKey) {     //If key 2 is pressed
            twoKeyRecord = cameraPosition;     //Save the camera position to the oneKeyRecord variable
            digitalWrite(buzzerPin, HIGH);     //Make a sound from the buzzer
            delay(100);                        //Wait for 100ms
            digitalWrite(buzzerPin, LOW);      //Mute the Buzzer
        }
        else if(result.value == threeKey) {   //If key 3 is pressed
            threeKeyRecord = cameraPosition;   //Save the camera position to the threeKeyRecord variable
            digitalWrite(buzzerPin, HIGH);     //Make a sound from the buzzer
            delay(100);                        //Wait for 100ms
            digitalWrite(buzzerPin, LOW);      //Mute the Buzzer
        }
        else if(result.value == fourKey) {    //If key 4 is pressed
            fourKeyRecord = cameraPosition;    //Save the camera position to the fourKeyRecord variable
            digitalWrite(buzzerPin, HIGH);     //Make a sound from the buzzer
            delay(100);                        //Wait for 100ms
            digitalWrite(buzzerPin, LOW);      //Mute the Buzzer
        }
        else if(result.value == okKey) {      //if OK key is pressed
            digitalWrite(buzzerPin, HIGH);     //Make a sound from the buzzer
            delay(100);                        //Wait for 100ms
            digitalWrite(buzzerPin, LOW);      //Mute the Buzzer
            delay(100);                        //Wait for 100ms
            digitalWrite(buzzerPin, HIGH);     //Make a sound from the buzzer
            delay(100);                        //Wait for 100ms
            digitalWrite(buzzerPin, LOW);      //Mute the Buzzer
            IRReceive.resume();
            while(1) {
                if(IRReceive.decode(&result)) {
                    if(result.value == oneKey) {       //If key 1 is pressed
                        digitalWrite(buzzerPin, HIGH);  //Make a sound from the Buzzer
                        delay(50);                     //Wait for 50ms
                        digitalWrite(buzzerPin, LOW);   //Mute the Buzzer
                        servo.write(oneKeyRecord);      //Rotate the motor until the oneKeyRecord variable
                    }
                    else if(result.value == twoKey) {  //If key 2 is pressed
                        digitalWrite(buzzerPin, HIGH);  //Make a sound from the Buzzer
                        delay(50);                     //Wait for 50ms
                        digitalWrite(buzzerPin, LOW);   //Mute the Buzzer
                        servo.write(twoKeyRecord);      //Rotate the motor until the twoKeyRecord variable
                    }
                    else if(result.value == threeKey) { //If key 3 is pressed
                        digitalWrite(buzzerPin, HIGH);   //Make a sound from the Buzzer
                        delay(50);                      //Wait for 50ms
                        digitalWrite(buzzerPin, LOW);    //Mute the Buzzer
                        servo.write(threeKeyRecord);     //Rotate the motor until the threeKeyRecord variable
                    }
                    else if(result.value == fourKey) {  //If key 4 is pressed
                        digitalWrite(buzzerPin, HIGH);   //Make a sound from the Buzzer
                        delay(50);                      //Wait for 50ms
                        digitalWrite(buzzerPin, LOW);    //Mute the Buzzer
                        servo.write(fourKeyRecord);      //Rotate the motor until the fourKeyRecord variable
                    }
                    else if(result.value == okKey) {    //if OK key is pressed
                        digitalWrite(buzzerPin, HIGH);   //Make a sound from the Buzzer
                        delay(50);                      //Wait for 50ms
                        digitalWrite(buzzerPin, LOW);    //Mute the Buzzer
                        delay(50);                      //Wait for 50ms
                        digitalWrite(buzzerPin, HIGH);   //Make a sound from the Buzzer
                        delay(50);                      //Wait for 50ms
                        digitalWrite(buzzerPin, LOW);    //Mute the Buzzer
                        break;
                    }
                    IRReceive.resume();                 //Reset IR receiver to get other values
                }
            }
        }
        IRReceive.resume();                            //Reset IR receiver to get other values
    }
    delay(100);                                        //Wait for 100ms
}
