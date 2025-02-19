//SA43 - Remote controlled fan

//Add IR receiver library
#include <IRremote.h>

//Define IR control codes
#define oneKey    0xFFA25D    //IR Control key 1 
#define twoKey    0xFF629D    //IR Control key 2 
#define threeKey  0xFFE21D    //IR Control key 3 
#define okKey     0xFF38C7    //IR Control OK key

int MotorPwm = 9;            //Define the pin number to which the motor is connected
int IRPin = 2;               //Define the pin to which the IR receiver signal leg is connected

IRrecv IRReceive(IRPin);     //Define an IR Receiver named IRReceive

decode_results result;       //Define variable to store values received from IR receiver

void setup()
{
  IRReceive.enableIRIn();    //Start IR receiver
  pinMode(MotorPwm, OUTPUT); //Set the pin to which the INPUT2 (number 7) leg of the LM293 is connected as output 
}

void loop() 
{
  if(IRReceive.decode(&result))  //Check if there is any data coming from the IR receiver
  {      
    switch(result.value) {
      case oneKey:
        analogWrite(MotorPwm, 50);   //Rotate motor at 50 PWM, lowest stage speed 
        break;
      case twoKey:
        analogWrite(MotorPwm, 100);  //Rotate motor at 100 PWM, middle step speed 
        break;
      case threeKey:
        analogWrite(MotorPwm, 255);  //Rotate motor at 255 PWM, higher stage speed 
        break;
      case okKey:
        analogWrite(MotorPwm, 0);    //Stop the motor
        break;
    }
    IRReceive.resume();             //Reset IR receiver to get other values 
  }   
  delay(200);                       //Wait for 200ms
}
