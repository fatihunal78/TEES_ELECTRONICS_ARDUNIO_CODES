//SA64 - Colourful optical illusion

int MotorPwm2 = 10;    //Define the pin number to which INPUT4 leg of LM293 is connected
                       //The motor will rotate counterclockwise with the help of the pin connected from Arduino 
                       //pin 10 to the LM293D integrated circuit's 15th leg 
int MotorPwm1 = 9;     //Define the pin number to which INPUT1 leg of LM293 is connected
                       //The motor will rotate clockwise with the help of the pin connected from Arduino 
                       //pin 9 to the LM293D integrated circuit's 2nd leg 

int PotPin = A0;       //Define the pin to which the Potentiometer is connected

int PB2_button = 2;    //Define the pin to which the PB2 button is connected
int PB1_button = 3;    //Define the pin to which the PB1 button is connected

int green_LED = 13;    //Define the pin to which the green LED is connected 
int red_LED = 12;      //Define the pin to which the red LED is connected

int buttonStatus = 0;  //Define the variable that will store the information of which button is pressed
int analogRead;        //Define the variable to store the value read from the Potentiometer

void setup() {
    pinMode(MotorPwm1, OUTPUT);         //Set the pin to which the INPUT4 (15th leg) of the LM293 is connected as output 
    pinMode(MotorPwm2, OUTPUT);         //Set the pin to which the INPUT1 (2nd leg) of the LM293 is connected as output 
    pinMode(PotPin, INPUT);             //Set the pin to which the Potentiometer is connected as input
    pinMode(PB2_button, INPUT_PULLUP);  //Set the pin to which the PB2 button is connected as input
    pinMode(PB1_button, INPUT_PULLUP);  //Set the pin to which the PB1 button is connected as input
    pinMode(red_LED, OUTPUT);           //Set the pin to which the Red LED is connected as output
    pinMode(green_LED, OUTPUT);         //Set the pin to which the Green LED is connected as output
}

void loop() {
    if(digitalRead(PB1_button) == LOW) {
        buttonStatus = 1;
        digitalWrite(red_LED, HIGH);     //Turn ON the Red LED
        digitalWrite(green_LED, LOW);    //Turn OFF the Green LED
    }
    
    if(digitalRead(PB2_button) == LOW) {
        buttonStatus = 2;
        digitalWrite(red_LED, LOW);      //Turn OFF the Red LED
        digitalWrite(green_LED, HIGH);   //Turn ON the Green LED
    }
    
    analogRead = analogRead(PotPin);
    int proportion = map(analogRead, 0, 1023, 0, 150);

    if(buttonStatus == 1) {
        analogWrite(MotorPwm1, proportion);  //Energize pin 9 for clockwise rotation of the motor 
        analogWrite(MotorPwm2, 0);          //Pull pin 10 to ground
    }
    else if(buttonStatus == 2) {       
        analogWrite(MotorPwm1, 0);          //Pull pin 9 to ground for counterclockwise rotation of the motor 
        analogWrite(MotorPwm2, proportion);  //Energize pin 10 
    }
    else {                                  //Stop the Motor
        analogWrite(MotorPwm1, 0); 
        analogWrite(MotorPwm2, 0); 
    }
    
    delay(200);                            //Wait for 200ms
}
