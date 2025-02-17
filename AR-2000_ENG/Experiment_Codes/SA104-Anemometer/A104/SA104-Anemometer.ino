//SA104 - Anemometer

#include <LiquidCrystal_I2C.h>                    //Add I2C LCD library 

LiquidCrystal_I2C lcd(0x27, 16, 2);              //Define 1602 LCD display

const byte Propeller_Blades = 3;                  //Value indicating how many blades there are on the propeller on the panel
                                                 //Since our propeller has 3 blades, it reads 3 pulses per turn.
const unsigned long ZeroDebouncing = 100000;      //Define ZeroDebouncing variable for sensitivity and make the initial value 100000

const byte read_count = 2; 

volatile unsigned long Last_Time;                 //Define the variable to keep the last time the pulse was read for calculations
volatile unsigned long Period_Between_Pulse = ZeroDebouncing + 1000;  //Define the variable for the period between each read pulse
volatile unsigned long Average_Period = ZeroDebouncing + 1000;        //Define variable to store average period between pulses in microseconds

unsigned long Frequency_Decimal;                  //Define the variable to store the frequency as a decimal number
unsigned long Frequency_Integer;                  //Define the variable to store the frequency as an integer
unsigned long RPM;                               //Define the variable to store the calculated PRM
unsigned int PulseCounter = 1;                   //Define the variable to keep the read pulses, equalize the first value to 1

unsigned long Total_Period;                      //Define the variable to store the sum of the average periods 

unsigned long Last_Time_Measure = Last_Time;     //Define the variable to store the measured last time 
unsigned long Current_Time = micros();           //Define the variable to store the current time

unsigned int Read_Quantity = 1;
unsigned int ZeroDebouncingExtra; 

unsigned long Reading[read_count];               //Define the variable to store the read values as an array
unsigned long Read_Index;                        //Define variable to understand how many readings are done
unsigned long total;                            //Define the variable to store the total of readings 
unsigned long average;                          //Define the variable to store the average of total readings (RPM average)
unsigned long kmh;                              //Define variable to convert read rpm to kmh (kilometers/h)
unsigned long ms;                               //Define the variable to convert from kilometers/hour to meters/second

int motorPin = 6;                               //Define the pin number to which the motor is connected
int potPin = A0;                                //Define the pin to which the Potentiometer that will control the motor is connected
int potValue = 0;                               //Define the variable to store the values to be read from the Potentiometer

void setup() {
    lcd.begin();                                //Start the LCD display
    lcd.backlight();                            //Turn ON the LCD backlights
    lcd.clear();                                //Clear the LCD display

    pinMode(motorPin, OUTPUT);                  //Set the pin to which the motor is connected as output
    Serial.begin(9600);                         //Start serial communication
    attachInterrupt(digitalPinToInterrupt(2), Interrupt_Function, RISING);  //To read interrupt from digital pin 2
                                                                           //Events inside Interrupt_Function occur on RISING edge
    lcd.setCursor(0, 0);                        //Move the cursor to the first row 
    lcd.print("TEES ELECTRONICS");              //Write "TEES ELECTRONICS" on the first row
    lcd.setCursor(0, 1);                        //Switch to the second row
    lcd.print("ANEMOMETER");                    //Write "ANEMOMETER" on the LCD display
    delay(2000);                                //Wait for 2 seconds
    lcd.clear();                                //Clear the LCD display 
}

void loop() {
    potValue = map(analogRead(potPin), 0, 1023, 0, 180);  //Proportion the values read from analog pin between 0 and 255 
    analogWrite(motorPin, potValue);                       //Send proportion value between 0 and 255 to the motor 

    Last_Time_Measure = Last_Time;                         //Save value in Last_Time variable to Last_Time_Measure variable 
    Current_Time = micros();                              //Read current time in microseconds and save to Current_Time variable

    if(Current_Time < Last_Time_Measure) {                //If the Current_Time read is less than the Last_Time_Measure variable
        Last_Time_Measure = Current_Time;                 //Save the current time to Last_Time_Measure variable 
    }
    
    Frequency_Decimal = 10000000000 / Average_Period;     //Save the time between pulses in decimal to Frequency_Decimal 

    //If the motor stops rotating or rotates too slowly, save the frequency reading as 0
    if(Period_Between_Pulse > ZeroDebouncing - ZeroDebouncingExtra || 
       Current_Time - Last_Time_Measure > ZeroDebouncing - ZeroDebouncingExtra) {  
        Frequency_Decimal = 0;                            //Set Frequency_Decimal variable to 0
        ZeroDebouncingExtra = 2000;
    } else {
        ZeroDebouncingExtra = 0; 
    }
    
    Frequency_Integer = Frequency_Decimal / 10000;        //Convert the calculated Frequency_Decimal to integer

    //Calculate RPM (Rotation per Minute)
    //To calculate the RPM, divide Frequency_Decimal by Propeller_Blades because we don't want to read 3 pulses.
    //If we don't divide by Propeller_Blades, the RPM value will be 3 times more
    //Multiply by 60 to get the value in 1 minute (1 minute = 60 seconds)
    RPM = Frequency_Decimal / Propeller_Blades * 60;      
    RPM = RPM / 10000;                                   //Divide by 10000 to convert to integer and convert RPM from microseconds to seconds 
    
    total = total - Reading[Read_Index]; 
    Reading[Read_Index] = RPM; 
    total = total + Reading[Read_Index]; 
    Read_Index = Read_Index + 1; 

    if(Read_Index >= read_count) {                       //If the end of the array is reached 
        Read_Index = 0;                                  //Reset Read_Index variable 
    }
    
    average = total / read_count;                        //Calculate the average value
    kmh = average * 0.001885 * 9;                       //Convert the average RPM value to KM
    ms = kmh / 0.278;                                   //Convert km/h (kilometers/hour) to m/s (meters/second)

    lcd.clear();                                        //Clear the LCD display 
    lcd.setCursor(0, 0);                                //Move to the first row on the LCD display 
    lcd.print("AIR FLOW RATE");                         //Write "AIR FLOW RATE" ON THE LCD display 
    lcd.setCursor(0, 1);                                //Switch to the lower row 
    lcd.print(float(ms));                               //Print the calculated wind speed in float (fractional) in ms
    lcd.print("m/s");                                   //Write m/s on the LCD screen
    delay(200);
}  

void Interrupt_Function() {                             //Define the interrupt function to be able to read pulses
    Period_Between_Pulse = micros() - Last_Time; 
    Last_Time = micros();                              //Save the time to Last_Time variable in microseconds 

    if(PulseCounter >= Read_Quantity) {                //If PulseCounter variable is greater than Read_Quantity variable 
        Average_Period = Total_Period / Read_Quantity; //Divide Total_Period by Read_Quantity to find average period
        
        PulseCounter = 1;                             //Reset PulseCounter variable to 1
        Total_Period = Period_Between_Pulse;          //Set Total_Period to Period_Between_Pulse for new average

        //Proportion value read between 40000 and 5000 from Period_Between_Pulse to value between 1 and 10
        int proportion = map(Period_Between_Pulse, 40000, 5000, 1, 10);
        
        proportion = constrain(proportion, 1, 10);    //Limit proportion variable between 1 and 10
        Read_Quantity = proportion;                   //Save proportion value to Read_Quantity variable
    } else {
        PulseCounter++;                              //Increment pulse counter by one 
        Total_Period = Total_Period + Period_Between_Pulse;  //Add Period_Between_Pulse to Total_Period
    }
}
