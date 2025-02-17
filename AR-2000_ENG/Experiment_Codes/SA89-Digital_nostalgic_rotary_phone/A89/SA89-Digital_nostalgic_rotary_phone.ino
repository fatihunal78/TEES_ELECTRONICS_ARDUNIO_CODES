//SA89 - Digital nostalgic rotary phone

#include <Servo.h>                                    //Add servo motor library
#include <Keypad.h>                                  //Add Keypad library

const byte ROW = 4;                                  //Specify how many rows the keypad consists of 
const byte COLUMN = 4;                               //Specify how many columns the keypad consists of 

//Define the keys on the keypad 
char keys[ROW][COLUMN] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

//Define the pins to which the row and column pins of the keypad are connected
byte rowPins[ROW] = {7, 6, 5, 4}; 
byte columnPins[COLUMN] = {3, 2, 1, 0}; 

//Start the keypad
Keypad keyPad = Keypad(makeKeymap(keys), rowPins, columnPins, ROW, COLUMN); 

Servo servo;                                         //Create a Servo object named servo

int servoPin = 8;                                    //Define the pin number to which the servo motor is connected
int speakerPin = 10;                                //Define the pin number to which the Speaker is connected

void setup() {
    pinMode(speakerPin, OUTPUT);                     //Set the pin to which the Speaker is connected as output
    servo.attach(servoPin);                         //Set the pin to which the servo motor is connected
    servo.write(0);                                 //Set the starting position of the servo motor to 0-degree
}

void loop() {
    char key = keyPad.getKey();                     //Save the key pressed from the keypad
    if(key != NO_KEY) {                             //If any key is pressed
        switch(key) {                               //With switch case structure, perform the action on the key that is pressed
            case '0':                               //In case 0 perform the following actions
                tone(speakerPin, 600);
                delay(50);
                noTone(speakerPin); 
                servo.write(180);                   //If the value entered is zero, move the servo to 180-degree position 
                for (int i=180; i>=0; i--) {        //With for loop from 180 degrees to zero-degree
                    servo.write(i);                 //Move the servo motor
                    delay(10);                      //Perform the movement operation at 10ms intervals
                }  
                break;                              //End case 0

            case '1':                               //In case 1 perform the following actions
                tone(speakerPin, 650);
                delay(50);
                noTone(speakerPin);
                servo.write(18);                    //Move servo to 18 degrees 
                for (int i=18; i>=0; i--) {         //With for loop from 18 degrees to zero-degree
                    servo.write(i);                 //Move the servo motor
                    delay(10);                      //Perform the movement operation at 10ms intervals
                }
                break;                              //End case 1

            case '2':                               //In case 2 perform the following actions
                tone(speakerPin, 700);
                delay(50);
                noTone(speakerPin);
                servo.write(36);                    //Move servo to 36 degrees 
                for (int i=36; i>=0; i--) {         //With for loop from 36 degrees to zero-degree
                    servo.write(i);                 //Move the servo motor
                    delay(10);                      //Perform the movement operation at 10ms intervals
                }
                break;                              //End case 2

            case '3':                               //In case 3 perform the following actions
                tone(speakerPin, 750);
                delay(50);
                noTone(speakerPin);
                servo.write(54);                    //Move servo to 54 degrees 
                for (int i=54; i>=0; i--) {         //With for loop from 54 degrees to zero-degree
                    servo.write(i);                 //Move the servo motor
                    delay(10);                      //Perform the movement operation at 10ms intervals
                }
                break;                              //End case 3 

            case '4':                               //In case 4 perform the following actions
                tone(speakerPin, 800);
                delay(50);
                noTone(speakerPin);
                servo.write(72);                    //Move servo to 72 degrees 
                for (int i=72; i>=0; i--) {         //With for loop from 72 degrees to zero-degree
                    servo.write(i);                 //Move the servo motor
                    delay(10);                      //Perform the movement operation at 10ms intervals
                }
                break;                              //End case 4

            case '5':                               //In case 5 perform the following actions
                tone(speakerPin, 850);
                delay(50);
                noTone(speakerPin);
                servo.write(90);                    //Move servo motor to 90-degree position 
                for (int i=90; i>=0; i--) {         //With for loop from 90 degrees to zero-degree
                    servo.write(i);                 //Move the servo motor
                    delay(10);                      //Perform the movement operation at 10ms intervals
                }
                break;                              //End case 5 

            case '6':                               //In case 6 perform the following actions
                tone(speakerPin, 900);
                delay(50);
                noTone(speakerPin);
                servo.write(108);                   //Move servo motor to 108-degree position 
                for (int i=108; i>=0; i--) {        //With for loop from 108 degrees to zero-degree
                    servo.write(i);                 //Move the servo motor
                    delay(10);                      //Perform the movement operation at 10ms intervals
                }
                break;                              //End case 6

            case '7':                               //In case 7 perform the following actions
                tone(speakerPin, 950);
                delay(50);
                noTone(speakerPin);
                servo.write(126);                   //Move servo motor to 126-degree position 
                for (int i=126; i>=0; i--) {        //With for loop from 126 degrees to zero degree
                    servo.write(i);                 //Move the servo motor
                    delay(10);                      //Perform the movement operation at 10ms intervals
                }
                break;                              //End case 7

            case '8':                               //In case 8 perform the following actions
                tone(speakerPin, 1000);
                delay(50);
                noTone(speakerPin); 
                servo.write(144);                   //Move servo motor to 144-degree position 
                for (int i=144; i>=0; i--) {        //With for loop from 144 degrees to zero degree
                    servo.write(i);                 //Move the servo motor
                    delay(10);                      //Perform the movement operation at 10ms intervals
                }
                break;                              //End case 8

            case '9':                               //In case 9 perform the following actions
                tone(speakerPin, 1050);
                delay(50);
                noTone(speakerPin);
                servo.write(162);                   //Move servo motor to 162-degree position 
                for (int i=162; i>=0; i--) {        //With for loop from 162 degrees to zero degree
                    servo.write(i);                 //Move the servo motor
                    delay(10);                      //Perform the movement operation at 10ms intervals
                }
                break;                              //End case 9
        }
    }
}
