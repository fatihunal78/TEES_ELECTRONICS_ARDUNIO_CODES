//SA62 - Motor direction control

int MotorPwm2 = 10;    //Define the pin number to which INPUT4 leg of LM293 is connected
                       //The motor will rotate counterclockwise with the help of the pin connected from Arduino 
                       //pin 10 to the LM293D integrated circuit's 15th leg 
int MotorPwm1 = 9;     //Define the pin number to which INPUT1 leg of LM293 is connected
                       //The motor will rotate clockwise with the help of the pin connected from Arduino 
                       //pin 9 to the LM293D integrated circuit's 2nd leg 

int rightButton = 2;    //Define the pin number to which the PB1 button on the right hand side is connected 
int leftButton = 3;     //Define the pin number to which the PB2 button on the left hand side is connected

void setup() {
    pinMode(rightButton, INPUT_PULLUP);    //Set the pin to which the right Button is connected as input
    pinMode(leftButton, INPUT_PULLUP);     //Set the pin to which the left Button is connected as input 
    
    pinMode(MotorPwm1, OUTPUT);           //Set the pin to which the INPUT4 leg of the LM293 is connected as output 
    pinMode(MotorPwm2, OUTPUT);           //Set the pin to which the INPUT1 leg of the LM293 is connected as output 
}

void loop() {
    if(digitalRead(rightButton) == LOW) {  //If the PB1 button on the right hand side is pressed 
                                          //Perform the following operations to rotate the motor clockwise 
        digitalWrite(MotorPwm1, HIGH);     //Energize pin 9 for clockwise rotation of the motor 
        digitalWrite(MotorPwm2, LOW);      //Pull pin 10 to ground
    }
    else if(digitalRead(leftButton) == LOW) {  //If the PB2 button on the left hand side is pressed 
                                              //Perform the following operations to rotate the motor counterclockwise
        digitalWrite(MotorPwm1, LOW);          //Pull pin 9 to ground for counterclockwise rotation of the motor 
        digitalWrite(MotorPwm2, HIGH);         //Energize pin 10 
    }
    else {                                     //If no button is pressed 
                                              //Stop the Motor 
        digitalWrite(MotorPwm1, LOW); 
        digitalWrite(MotorPwm2, LOW); 
    }
    delay(200);                               //Wait for 200ms 
}
