//SA65 - Electromagnetic braking system

int MotorPwm2 = 10;      //Define the pin number to which INPUT4 leg of LM293 is connected
                         //The motor will rotate counterclockwise with the help of the pin connected from Arduino 
                         //pin 10 to the LM293D integrated circuit's 15th leg 
int MotorPwm1 = 9;       //Define the pin number to which INPUT1 leg of LM293 is connected
                         //The motor will rotate clockwise with the help of the pin connected from Arduino 
                         //pin 9 to the LM293D integrated circuit's 2nd leg 
                   
int motorDirection = 0;   //Define the variable that will store the information of which direction the motor is rotating
                         //It is clockwise if value is 1
                         //It is counterclockwise if value is 2

int motor_speed = 0;      //Define the variable to store the speed of the motor
int PotPin = A0;         //Define the pin to which the Potentiometer is connected
int PB2_button = 2;      //Define the pin to which the PB2 button is connected
int Joystick_button = 3; //Define the pin to which the joystick button is connected
int PB1_button = 4;      //Define the pin to which the PB1 button is connected
int buttonStatus = 0;     //Define the variable that will store the information of which button is pressed
int potValue;          //Define the variable to store the value read from the Potentiometer

void setup() {
    pinMode(MotorPwm1, OUTPUT);            //Set the pin to which the INPUT4 (15th leg) of the LM293 is connected as output 
    pinMode(MotorPwm2, OUTPUT);            //Set the pin to which the INPUT1 (2nd leg) of the LM293 is connected as output 
    pinMode(PotPin, INPUT);                //Set the pin to which the Potentiometer is connected as input
    pinMode(PB2_button, INPUT_PULLUP);     //Set the pin to which the PB2 button is connected as input
    pinMode(PB1_button, INPUT_PULLUP);     //Set the pin to which the PB1 button is connected as input
    pinMode(Joystick_button, INPUT_PULLUP);//Set the pin to which the joystick button is connected as input
}

void loop() {
    if(digitalRead(PB1_button) == LOW) {   //If PB1 button is pressed 
        buttonStatus = 1;                   //Set the buttonStatus variable to 1
    }
    
    if(digitalRead(PB2_button) == LOW) {   //If PB2 button is pressed 
        buttonStatus = 2;                   //Set the buttonStatus variable to 2 
    }
    
    if(digitalRead(Joystick_button) == LOW) { //If Joystick button is pressed 
        buttonStatus = 3;                      //Set the buttonStatus variable to 3
    }
    
    potValue = analogRead(PotPin);          
    int proportion = map(potValue, 0, 1023, 0, 255); 

    if(buttonStatus == 1) {                //If PB1 is pressed - clockwise rotation
        analogWrite(MotorPwm2, 0);         //Pull pin 10 to ground
        analogWrite(MotorPwm1, proportion); //Energize pin 9 for clockwise rotation
        motorDirection = 1; 
        
        if(digitalRead(Joystick_button) == LOW) {
            buttonStatus = 3; 
        }
    }
    else if(buttonStatus == 2) {           //If PB2 is pressed - counterclockwise rotation
        analogWrite(MotorPwm2, proportion); //Energize pin 10 for counterclockwise rotation
        analogWrite(MotorPwm1, 0);         //Pull pin 9 to ground
        motorDirection = 2; 
        
        if(digitalRead(Joystick_button) == LOW) {
            buttonStatus = 3; 
        }
    }
    else if(buttonStatus == 3) {           //Stop the motor
        if(motorDirection == 1) {          //If the motor is rotating clockwise
            potValue = analogRead(PotPin);    //Save value read from analog A0 pin to potValue variable 
            int proportion = map(potValue, 0, 1023, 0, 255); //Proportion value between 0-1023 to 0-255
            
            if(proportion <= 150) {
                //To stop the motor suddenly, turn the motor counterclockwise and then turn it OFF
                analogWrite(MotorPwm1, 0);      //Pull pin 9 to ground for counterclockwise rotation of the motor
                analogWrite(MotorPwm2, 255);    //Energize pin 10 
                delay(350);                     //Wait for 350ms
                
                //Turn OFF the Motor
                analogWrite(MotorPwm1, 0);
                analogWrite(MotorPwm2, 0);
                buttonStatus = 0;
                motorDirection = 0;
            }
            else {
                //To stop the motor suddenly, turn the motor counterclockwise and then turn it OFF
                analogWrite(MotorPwm1, 0);      //Pull pin 9 to ground for counterclockwise rotation of the motor
                analogWrite(MotorPwm2, proportion); //Energize pin 10
                delay(1000);                    //Wait for 1 second
                
                //Turn OFF the Motor
                analogWrite(MotorPwm1, 0);
                analogWrite(MotorPwm2, 0);
                buttonStatus = 0;
                motorDirection = 0;
            }
        }
        else if(motorDirection == 2) {     //If the motor is rotating counterclockwise
            potValue = analogRead(PotPin);    //Save value read from analog A0 pin to potValue variable 
            int proportion = map(potValue, 0, 1023, 0, 255); //Proportion value between 0-1023 to 0-255
            
            if(proportion <= 150) {
                //To stop the motor suddenly, turn the motor counterclockwise and then turn it OFF
                analogWrite(MotorPwm1, proportion); //Energize pin 9 for clockwise rotation of the motor 
                analogWrite(MotorPwm2, 0);         //Pull pin 10 to ground
                delay(350);
                
                //Turn OFF the Motor
                analogWrite(MotorPwm1, 0);
                analogWrite(MotorPwm2, 0);
                buttonStatus = 0;
                motorDirection = 0;
            }
            else {
                //To stop the motor suddenly, turn the motor counterclockwise and then turn it OFF
                analogWrite(MotorPwm1, proportion); //Energize pin 9 for clockwise rotation of the motor 
                analogWrite(MotorPwm2, 0);         //Pull pin 10 to ground
                delay(1000);
                
                //Turn OFF the Motor
                analogWrite(MotorPwm1, 0);
                analogWrite(MotorPwm2, 0);
                buttonStatus = 0;
                motorDirection = 0;
            }  
        }
        else {
            analogWrite(MotorPwm1, 0); 
            analogWrite(MotorPwm2, 0); 
        }
    }
    else {                                 //Stop the Motor
        analogWrite(MotorPwm1, 0); 
        analogWrite(MotorPwm2, 0); 
    }
    
    delay(200);                           //Wait for 200ms
}
