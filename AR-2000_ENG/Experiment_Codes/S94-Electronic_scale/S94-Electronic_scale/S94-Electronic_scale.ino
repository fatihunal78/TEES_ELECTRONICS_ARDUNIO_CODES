//S94 - Electronic scale

int sensorPin = A5;    //Define the pin number to which the Sensor is connected

double readValue;      //Define the variable that will store the value read from the Sensor
double voltage;        //Define the variable that will store the voltage conversion of the value read from the sensor
double initialValue;   //Define the variable to store the first value read from the Sensor when the system starts
double value;         //Define the variable to store the difference between the voltage variable and the initialValue variable
double proportion;    //Define the variable to store the proportional version of the value variable

//Define the pin numbers to which the LEDs on the LEDBAR module are connected
int greenLED1 = 3;
int greenLED2 = 4;
int yellowLED = 5; 
int redLED1 = 6;
int redLED2 = 7;

void setup() 
{
    //Set the pin to which the sensor is connected as input
    pinMode(sensorPin, INPUT);
    //Set the pins to which LEDs on LEDBAR are connected as output
    pinMode(greenLED1, OUTPUT);
    pinMode(greenLED2, OUTPUT);
    pinMode(yellowLED, OUTPUT); 
    pinMode(redLED1, OUTPUT);
    pinMode(redLED2, OUTPUT);
    
    //When the system is running, read the value for calibration and save this value to the initialValue variable
    initialValue = analogRead(A5);
    //Convert the initialValue variable to the voltage value
    initialValue = (initialValue * 5) / 1023;
}
 
void loop() 
{
    readValue = analogRead(A5) + 10;    //Read value from the sensor and save 10 more of this value in readValue variable
    voltage = (readValue * 5) / 1023;   //Save the voltage equivalent of the readValue in the voltage variable 
  
    value = voltage - initialValue;      //Save the difference between voltage variable and initialValue variable to value variable
    proportion = value * 5;              //Save the value variable multiplied by 5 to the proportion variable 

    //Turn ON the LEDs on the LEDBAR according to the value in the proportion variable 
    if(proportion >= 0 && proportion < 1)    //If proportion variable is between 0 and 1, Turn ON 1st Green LED on LEDBAR
    {
        digitalWrite(greenLED1, HIGH);
        digitalWrite(greenLED2, LOW);
        digitalWrite(yellowLED, LOW);
        digitalWrite(redLED1, LOW);
        digitalWrite(redLED2, LOW); 
    }
    else if(proportion >= 1 && proportion < 2)    //If proportion variable is between 1 and 2, Turn ON 1st and 2nd Green LEDs
    {
        digitalWrite(greenLED1, HIGH);
        digitalWrite(greenLED2, HIGH);
        digitalWrite(yellowLED, LOW);
        digitalWrite(redLED1, LOW);
        digitalWrite(redLED2, LOW); 
    }
    else if(proportion >= 2 && proportion < 3)    //If proportion variable is between 2 and 3, Turn ON Green LEDs and Yellow LED
    {
        digitalWrite(greenLED1, HIGH);
        digitalWrite(greenLED2, HIGH);
        digitalWrite(yellowLED, HIGH);
        digitalWrite(redLED1, LOW);
        digitalWrite(redLED2, LOW); 
    }
    else if(proportion >= 3 && proportion < 4)    //If proportion variable is between 3 and 4, Turn ON Green LEDs, Yellow and 1st Red
    {
        digitalWrite(greenLED1, HIGH);
        digitalWrite(greenLED2, HIGH);
        digitalWrite(yellowLED, HIGH);
        digitalWrite(redLED1, HIGH);
        digitalWrite(redLED2, LOW); 
    }
    else if(proportion >= 4)    //If proportion variable is between 4 and 5, Turn ON all LEDs
    {
        digitalWrite(greenLED1, HIGH);
        digitalWrite(greenLED2, HIGH);
        digitalWrite(yellowLED, HIGH);
        digitalWrite(redLED1, HIGH);
        digitalWrite(redLED2, HIGH); 
    }
    delay(200);
}
