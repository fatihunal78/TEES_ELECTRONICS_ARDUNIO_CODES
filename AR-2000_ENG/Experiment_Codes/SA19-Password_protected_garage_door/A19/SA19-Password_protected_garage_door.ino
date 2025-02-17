//SA19 - Password protected garage door

#include <IRremote.h> //Add IR receiver library
#include <Servo.h> //Add servo motor library

//Define IR control codes
#define oneKey 0xFFA25D //IR Control key 1
#define twoKey 0XFF629D //IR Control key 2
#define threeKey 0XFFE21D //IR Control key 3
#define fourKey 0XFF22DD //IR Control key 4
#define doorOpenClose 0xFF38C7 //IR Control Key OK

int IRPin = 2; //Define the pin to which the IR receiver signal leg is connected
int buzzerPin = 7; //Define the pin to which the Buzzer is connected 
int servoPin = 5; //Define the pin number to which the servo motor is connected

IRrecv IRReceive(IRPin); //Define an IR Receiver named IRReceive
decode_results result; //Define variable to store values received from IR receiver
Servo servo; //Define servo motor

//Define the variable to store the barrier state
int barrierStatus = 0;
//Define the variable to store the angle of servo motor
int servoStep = 90;
//Define the variable to store the password counter value
int passwordCounter = 0;

void setup() {
    IRReceive.enableIRIn(); //Start IR receiver 
    pinMode(buzzerPin, OUTPUT); //Set the pin to which the Buzzer is connected as output 
    servo.attach(servoPin); //Set the pin to which the servo motor is connected 
    servo.write(90); //Move servo motor to 90-degree position
    delay(150); //Wait for 150ms 
}

void loop() {
    servo.detach();
    //Check if there is any information coming from IR receiver
    if(IRReceive.decode(&result)) { 
        switch(passwordCounter) {
            case 0:
                if(result.value == oneKey) { //If key 1 is pressed
                    passwordCounter++; //Increment passwordCounter variable by one
                    digitalWrite(buzzerPin, HIGH); //Make a sound from the buzzer
                    delay(300); //Wait for 300ms
                    digitalWrite(buzzerPin, LOW); //Mute the Buzzer 
                }
                break;
            case 1:
                if(result.value == twoKey) { //If key 2 is pressed
                    passwordCounter++; //Increment passwordCounter variable by one
                    digitalWrite(buzzerPin, HIGH); //Make a sound from the buzzer
                    delay(300); //Wait for 300ms
                    digitalWrite(buzzerPin, LOW); //Mute the Buzzer 
                }
                break;
            case 2:
                if(result.value == threeKey) { //If key 3 is pressed
                    passwordCounter++; //Increment passwordCounter variable by one
                    digitalWrite(buzzerPin, HIGH); //Make a sound from the buzzer
                    delay(300); //Wait for 300ms
                    digitalWrite(buzzerPin, LOW); //Mute the Buzzer 
                }
                break;
            case 3:
                if(result.value == fourKey) { //If key 4 is pressed
                    passwordCounter++; //Increment passwordCounter variable by one
                    digitalWrite(buzzerPin, HIGH); //Make a sound from the buzzer
                    delay(300); //Wait for 300ms
                    digitalWrite(buzzerPin, LOW); //Mute the Buzzer 
                }
                break;
            case 4:
                if(result.value == doorOpenClose) { //If key OK is pressed
                    servo.attach(servoPin); //Set the pin to which the servo motor is connected 
                    digitalWrite(buzzerPin, HIGH); //Make a sound from the buzzer
                    delay(100); //Wait for 100ms 
                    digitalWrite(buzzerPin, LOW); //Mute the Buzzer 
                    delay(100); //Wait for 100ms 
                    digitalWrite(buzzerPin, HIGH); //Make a sound from the buzzer
                    delay(100); //Wait for 100ms 
                    digitalWrite(buzzerPin, LOW); //Mute the Buzzer 
                    //Rotate the servo motor 180 degrees at 1 degree intervals
                    for(servoStep; servoStep<181; servoStep++) {
                        servo.write(servoStep); //rotate servo motor according to the servoStep variable
                        delay(25); //Wait for 25ms
                    }
                    IRReceive.resume(); //Reset IR receiver to get other values 
                    for(int j = 0; j < 100; j++) { //5 seconds wait cycle
                        delay(50); //Wait for 50ms
                        //Check if there is any information coming from IR receiver
                        if(IRReceive.decode(&result)) {
                            if(result.value == doorOpenClose) { //If the key pressed is doorOpenClose key
                                j = 100; //Set variable j to 100
                                delay(200); //Wait for 200ms
                            }
                            IRReceive.resume(); //Reset IR receiver to get other values 
                        }
                    }
                    //Rotate the servo motor 90 degrees in reverse at 1 degree intervals
                    for(servoStep; servoStep>89; servoStep--) {
                        servo.write(servoStep); //rotate servo motor according to the servoStep variable
                        delay(25); //Wait for 25ms
                    }
                    passwordCounter = 0; //Save passwordCounter variable as 0
                }
                break;
        }
        IRReceive.resume(); //Reset IR receiver to get other values
    }
}
