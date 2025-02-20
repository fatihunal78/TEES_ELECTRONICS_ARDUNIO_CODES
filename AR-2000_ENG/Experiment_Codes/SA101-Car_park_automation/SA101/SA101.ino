//SA101 - Car park automation

#include <MaxMatrix.h>                             //Add the LED Matrix library

//Define LED Matrix connections
int DIN = 4;                                       //Define DIN pin
int CS = 3;                                        //Define CS pin
int CLK = 2;                                       //Define CLK pin

int LED_Matrix_Count = 1;                          //LED matrices can be connected in series
                                                  //If more than one matrix is to be connected, you can change the number here
MaxMatrix m(DIN, CS, CLK, LED_Matrix_Count);      //Define matrix m with matrix pin connections 

char Car1[] = {8, 8, 0x04, 0x06, 0x0D, 0x05, 
               0x05, 0x0D, 0x06, 0x04};           //Graphics of the car on the top
char Car2[] = {8, 8, 0x40, 0x60, 0xE0, 0x60, 
               0xE0, 0x60, 0xE0, 0x60, 0x40};     //Graphics of the car at the below

int Sensor1Pin = 7;                               //Define the pin number to which Sensor1 is connected
int Sensor2Pin = 6;                               //Define the pin number to which Sensor2 is connected
int red_LED1 = 4;                                 //Define the pin number to which the red LED1 is connected  
int red_LED2 = 3;                                 //Define the pin number to which the red LED2 is connected
int green_LED1 = 5;                               //Define the pin number to which the green LED1 is connected
int green_LED2 = 2;                               //Define the pin number to which the Green LED2 is connected

void setup() {
    m.init();                                     //Start the LED matrix
    m.setIntensity(8);                           //Adjust brightness
    pinMode(Sensor1Pin, INPUT);                  //Set the pin to which Sensor1 is connected as input 
    pinMode(Sensor2Pin, INPUT);                  //Set the pin to which Sensor2 is connected as input 
    
    pinMode(green_LED1, OUTPUT);                 //Set the green_LED1 as output 
    pinMode(green_LED2, OUTPUT);                 //Set the green_LED2 as output 
    pinMode(red_LED1, OUTPUT);                   //Set the red_LED1 as output 
    pinMode(red_LED2, OUTPUT);                   //Set the red_LED2 as output 
}

void loop() {
    bool val1 = digitalRead(Sensor1Pin);         //Read value in Sensor1 pin 
    bool val2 = digitalRead(Sensor2Pin);         //Read value in Sensor2 pin 

    if(val1 == LOW && val2 == LOW) {            //If 2 sensors are LOW, that is, there are no cars in both of them 
        m.clear();                              //Clear the LCD screen 
        digitalWrite(green_LED1, HIGH);         //Turn ON the Green LED1 (Green LED on the top)
        digitalWrite(green_LED2, HIGH);         //Turn ON the Green LED2 (Green LED at the bottom)
        digitalWrite(red_LED1, LOW);            //Turn OFF the Red LED1 (Red LED on the top)
        digitalWrite(red_LED2, LOW);            //Turn OFF the Red LED2 (Red LED at the bottom)
    }
    else if(val1 == LOW && val2 == HIGH) {     //If there is no car at the bottom, and there is one at the top 
        m.writeSprite(0, 0, Car2);             //Bring the image that shows the car at the top on the LED matrix 
        digitalWrite(green_LED1, HIGH);         //Turn ON the Green LED1
        digitalWrite(green_LED2, LOW);          //Turn OFF the Green LED2 
        digitalWrite(red_LED1, LOW);            //Turn OFF the Red LED1 
        digitalWrite(red_LED2, HIGH);           //Turn ON the Red LED2 
    }
    else if(val1 == HIGH && val2 == LOW) {     //If there is no car at the top, there is one at the bottom 
        m.writeSprite(0, 0, Car1);             //Bring the image that shows the car at the bottom on the LED matrix 
        digitalWrite(green_LED1, LOW);          //Turn OFF the Green LED1
        digitalWrite(green_LED2, HIGH);         //Turn ON the Green LED2
        digitalWrite(red_LED1, HIGH);           //Turn on the Red LED1 
        digitalWrite(red_LED2, LOW);            //Turn OFF the Red LED2 
    }
    else if(val1 == HIGH && val2 == HIGH) {    //If there is car both at the bottom and and on the top
        m.writeSprite(0, 0, Car1);             //Display the image that shows the car at the bottom on the LED matrix
        m.writeSprite(0, 0, Car2);             //Display the image that shows the car on the top on the LED matrix 
        digitalWrite(green_LED1, LOW);          //Turn OFF the Green LED1
        digitalWrite(green_LED2, LOW);          //Turn OFF the Green LED2
        digitalWrite(red_LED1, HIGH);           //Turn on the Red LED1 
        digitalWrite(red_LED2, HIGH);           //Turn ON the Red LED2 
    }
}
