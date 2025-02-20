//SA72 - Automatic opening and closing door (with motion sensor)

#include <Servo.h>                            //Add servo motor library
int buttonPin = 2;                            //Define the pin number to which the Button is connected
int sensorPin = 3;                            //Define the pin number to which the PIR Sensor is connected
int greenLED = 11;                            //Define the digital pin number to which the Green LED is connected
Servo servo;                                  //Create a Servo object named servo

void setup() {
    servo.attach(4);                          //Set the pin to which the servo motor is connected
    pinMode(buttonPin, INPUT_PULLUP);         //Set the pin to which the Button is connected as input
    pinMode(greenLED, OUTPUT);                //Set the pin to which the Green LED is connected as output
    servo.write(0);                           //Set the start position of the servo motor to zero-degree
    pinMode(sensorPin, INPUT);                //Set the pin to which the infrared sensor is connected as input
}

void loop() {
    if(digitalRead(buttonPin) == LOW) {       //If the button is pressed
        digitalWrite(greenLED, HIGH);          //Turn ON the Green LED indicating that the circuit is active
        
        while(1) {                            //Go to infinite loop to start the system
            if(digitalRead(sensorPin) == HIGH) {  //If the sensor value is HIGH (if the PIR sensor detects movement)
                for(int i=0; i <= 90; i++) {      //Increment i by one from 0 to 90 to open the door
                    servo.write(i);               //Write the i value as servo's rotation angle and rotate servo by i angle
                    delay(30);                    //Delay for 30ms
                }
                delay(5000);                      //Wait 5 seconds when the door is opened

                for(int z=90; z>0; z--) {        //Decrease the z value by one from 90 degrees to 0 for closing the door
                    if(digitalRead(sensorPin) == HIGH) {  //If movement is detected again while the door is closing
                        //To reopen the door without closing it
                        for (int i=z; i<=90; i++) {      //Increment i by one from position when door was closing to 90
                            servo.write(i);              //Save as servo angle and return servo motor
                            z = i;                       //Save angle value in variable i to variable z
                            delay(30);                   //Delay for 30ms
                        }
                        delay(5000);                     //Wait for 5 seconds to keep the door open
                    }
                    else {                              //If no movement was detected while the door was closing
                        servo.write(z);                 //Rotate servo by decreasing it by z value (Close the door)
                    }
                    delay(30);                          //Delay for 30ms
                }
            }
        }
    }
}
