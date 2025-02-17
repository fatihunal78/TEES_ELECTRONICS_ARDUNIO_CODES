//SA66 - Motor control with remote control

//Add IR receiver library
#include <IRremote.h>

//Define IR control codes
#define oneKey     0xFFA25D    //IR Control key 1 
#define twoKey     0xFF629D    //IR Control key 2 
#define threeKey   0xFFE21D    //IR Control key 3 
#define fourKey    0x9FF22DD   //IR Control key 4 
#define fiveKey    0x9FF02FD   //IR Control key 5 
#define sixKey     0xFFC23D    //IR Control key 6 
#define sevenKey   0xFFE01F    //IR Control key 7 
#define eightKey   0xFFA857    //IR Control key 8 
#define nineKey    0xFF906F    //IR Control key 9 
#define starKey    0xFF6897    //IR Control Star Key 
#define zeroKey    0xFF9867    //IR Control key 0 
#define hashKey    0xFFB04F    //IR Control key # 
#define upKey      0xFF18E7    //IR Control up arrow key 
#define downKey    0xFF4AB5    //IR Control down arrow key 
#define rightKey   0xFF5AA5    //IR Control right arrow key
#define leftKey    0xFF10EF    //IR Control left arrow key
#define okKey      0xFF38C7    //IR Control OK key
#define repeat     0xFFFFFFFF  //If the pressed key is pressed continuously

//Define the pin number to which INPUT2 (7th leg) of LM293 is connected to Arduino
//The motor will rotate counterclockwise with the help of the pin connected from Arduino pin 10 to the LM293D 
//integrated circuit's 7th leg 
int MotorPwm1 = 10;    

//Define the pin number to which INPUT1 (2nd leg) of LM293 is connected to Arduino
//The motor will rotate clockwise with the help of the pin connected from Arduino pin 9 to the LM293D 
//integrated circuit's 2nd leg 
int MotorPwm2 = 9;     

int motorDirection = 0; //Define the variable that will store the information of which direction the motor is rotating
                       //It is counterclockwise if value is 0
                       //It is clockwise if value is 1
int IRPin = 2;         //Define the pin to which the IR receiver signal leg is connected
int motor_speed = 0;   //Define the variable to store the speed of the motor

IRrecv IRReceive(IRPin);      //Define an IR Receiver named IRReceive
decode_results result;        //Define variable to store values received from IR receiver

void setup() {
    IRReceive.enableIRIn();      //Start IR receiver
    pinMode(MotorPwm1, OUTPUT);  //Set the pin to which the INPUT2 (7th leg) of the LM293 is connected as output 
    pinMode(MotorPwm2, OUTPUT);  //Set the pin to which the INPUT1 (2nd leg) of the LM293 is connected as output 
}

void loop() {
    if(IRReceive.decode(&result)) {    //Check if there is any data coming from the IR receiver      
        IRReceive.resume();            //Reset IR receiver to get other values 
    }   

    if(result.value == rightKey) {     //If the right key is pressed from the IR remote controller 
        analogWrite(MotorPwm1, 255);   //Rotate the motor clockwise at maximum speed 
        analogWrite(MotorPwm2, 0);     //Pull the other PWM output to low to which the LM293D integrated circuit is connected
        motorDirection = 1;            //Set motorDirection variable to 1, which indicates clockwise rotation
        motor_speed = 255;             //Set motor_speed variable value to 255, maximum speed
    }    
    else if(result.value == leftKey) { //If left key is pressed from remote controller 
        analogWrite(MotorPwm2, 255);   //Turn the motor counterclockwise at maximum speed
        analogWrite(MotorPwm1, 0);     //Pull the other PWM output to low to which the LM293D integrated circuit is connected
        motorDirection = 0;            //Set motorDirection variable to 0, which indicates counterclockwise rotation
        motor_speed = 255;             //Set motor_speed variable value to 255, maximum speed
    }
    else if(result.value == okKey) {   //If OK key is pressed from remote controller 
        analogWrite(MotorPwm1, 0);     //Set PWM output to LOW 
        analogWrite(MotorPwm2, 0);     //Set PWM output to LOW 
        motor_speed = 0;               //Set motor_speed variable value to 0
        motorDirection = 0;            //Set motorDirection variable to 0
    }
    //If the down key is pressed on the remote control and the motorDirection value is 1, that is, the motor is 
    //rotating clockwise. Under these conditions, the motor speed is at maximum(255)
    else if(result.value == downKey && motorDirection == 1) {
        motor_speed = motor_speed - 50;     //Reduce the motor speed by 50 starting from 255.
        if(motor_speed <= 0) motor_speed = 0; //If motor_speed is less than or equal to 0, keep the value at zero
        analogWrite(MotorPwm1, motor_speed); //Rotate the MotorPwm1 output connected to the integrated circuit by motor_speed.
        analogWrite(MotorPwm2, 0);          //Set the other PWM output to 0
        //Set the variable result.value, which is the variable that stores the value read from the remote control, 
        //to NULL. Setting it to NULL means emptying the content of the variable as if it had no value.
        result.value = NULL;  
    } 
    //If the down key is pressed on the remote control and the motorDirection value is 0, that is, the motor is 
    //rotating counterclockwise. Under these conditions, the motor speed is at maximum(255)
    else if(result.value == downKey && motorDirection == 0) {
        motor_speed = motor_speed - 50;     //Reduce the motor speed by 50 starting from 255
        if(motor_speed <= 0) motor_speed = 0; //If motor_speed is less than or equal to 0, keep the value at zero
        analogWrite(MotorPwm2, motor_speed); //Rotate the MotorPwm2 output connected to the integrated circuit by motor_speed.
        analogWrite(MotorPwm1, 0);          //Set the other PWM output to 0
        //Set the variable result.value, which is the variable that stores the value read from the remote control, 
        //to NULL. Setting it to NULL means emptying the content of the variable as if it had no value.
        result.value = NULL;  
    }
    //If the up key is pressed on the remote control and the motorDirection value is 1, that is, the motor is 
    //rotating clockwise. Under these conditions, the speed of the motor is at zero
    else if(result.value == upKey && motorDirection == 1) {
        motor_speed = motor_speed + 50;     //Increase the motor speed by 50
        if(motor_speed >= 255) motor_speed = 255; //If motor_speed is greater than 255, keep motor_speed constant at 255
        analogWrite(MotorPwm1, motor_speed); //Rotate the MotorPwm1 output connected to the integrated circuit by motor_speed.
        analogWrite(MotorPwm2, 0);          //Set the other PWM output to 0
        result.value = NULL; 
    }
    //If the up key is pressed on the remote control and the motorDirection value is 0, that is, the motor is 
    //rotating counterclockwise. Under these conditions, the speed of the motor is at zero
    else if(result.value == upKey && motorDirection == 0) {
        motor_speed = motor_speed + 50;     //Increase the motor speed by 50
        if(motor_speed >= 255) motor_speed = 255; //If motor_speed is greater than 255, keep motor_speed constant at 255
        analogWrite(MotorPwm2, motor_speed); //Rotate the MotorPwm2 output connected to the integrated circuit by motor_speed.
        analogWrite(MotorPwm1, 0);          //Set the other PWM output to 0
        result.value = NULL; 
    }
    delay(200);                             //Wait for 200ms
}
