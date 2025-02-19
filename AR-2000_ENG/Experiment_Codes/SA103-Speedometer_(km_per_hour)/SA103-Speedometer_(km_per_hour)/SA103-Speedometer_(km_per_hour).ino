//SA103 - Speedometer (km per hour)

#include <LiquidCrystal_I2C.h>    //Add I2C LCD library 
#include <Servo.h>                 //Add the servo motor library

LiquidCrystal_I2C lcd(0x27, 16, 2);    //Define 1602 LCD display

Servo servo;                            //Add servo object to control servo motor

const byte Propeller_Blades = 3;        //Value indicating how many blades there are on the propeller on the panel
                                       //Since our propeller has 3 blades, it reads 3 pulses per turn.

const unsigned long ZeroDebouncing = 100000;    //Define ZeroDebouncing variable for sensitivity and make initial value 100000

const byte read_count = 3; 

volatile unsigned long Last_Time;               //Define variable to keep last time pulse was read for calculations
volatile unsigned long Period_Between_Pulse = ZeroDebouncing + 1000;    //Define variable for period between each read pulse
volatile unsigned long Average_Period = ZeroDebouncing + 1000;          //Define variable to store average period between pulses

unsigned long Frequency_Decimal;        //Define variable to store frequency as decimal number
unsigned long Frequency_Integer;        //Define variable to store frequency as integer  
unsigned long RPM;                      //Define variable to store calculated RPM
unsigned int PulseCounter = 1;          //Define variable to store read pulses, set initial value to 1

unsigned long Total_Period;             //Define variable to store sum of average periods
unsigned long Last_Time_Measure = Last_Time;    //Define variable to store measured last time
unsigned long Current_Time = micros();          //Define variable to store current time

unsigned int Read_Quantity = 1;
unsigned int ZeroDebouncingExtra;
unsigned long newTime;
unsigned long oldTime;

unsigned long Reading[read_count];      //Define variable to store read values as array
unsigned long Read_Index;               //Define variable to understand how many readings are done
unsigned long total;                    //Define variable to store total of readings
unsigned long average;                  //Define variable to store average of total readings (RPM average)
unsigned long kmh;                      //Define variable to store conversion of RPM to kilometers per hour

int motorPin = 6;                       //Define pin number to which motor is connected
int potPin = A0;                        //Define pin to which potentiometer that controls motor is connected  
int servoPin = 8;                       //Define pin number to which servo motor is connected
int potValue = 0;                       //Define variable to store values read from potentiometer

void setup() 
{
    lcd.begin();                        //Start the LCD display
    lcd.backlight();                    //Turn ON the LCD backlights
    lcd.clear();                        //Clear the LCD display

    servo.attach(servoPin);             //Set the pin to which servo motor is connected

    pinMode(motorPin, OUTPUT);          //Set motor pin as output
    Serial.begin(9600);                 //Start serial communication
    attachInterrupt(digitalPinToInterrupt(2), Interrupt_Function, RISING);    //Read interrupt from digital pin 2
                                                                             //Events inside Interrupt_Function occur on RISING edge
    lcd.setCursor(0, 0);               //Move cursor to first row 
    lcd.print("TEES ELECTRONICS");      //Write "TEES ELECTRONICS" on first row
    lcd.setCursor(0, 1);               //Switch to second row
    lcd.print("  SPEEDOMETER  ");       //Write "SPEEDOMETER" on LCD display
    delay(2000);                        //Wait for 2 seconds
    lcd.clear();                        //Clear LCD display 
    servo.write(180);                   //Initially set servo motor to 180-degree position
}

void loop() 
{   
    //The PWM value is limited to 100 so motor does not rotate at maximum speed
    potValue = map(analogRead(potPin), 0, 1023, 0, 100);    //Map analog values between 0-100 and save to potValue
    analogWrite(motorPin, potValue);                         //Send mapped value to motor 

    Last_Time_Measure = Last_Time;      //Save Last_Time to Last_Time_Measure
    Current_Time = micros();            //Read current time in microseconds

    if(Current_Time < Last_Time_Measure)    //If Current_Time is less than Last_Time_Measure
    {
        Last_Time_Measure = Current_Time;    //Save current time to Last_Time_Measure
    }
  
    Frequency_Decimal = 10000000000 / Average_Period;    //Save time between pulses in decimal

    //If motor stops/rotates too slowly, save frequency as 0
    if(Period_Between_Pulse > ZeroDebouncing - ZeroDebouncingExtra || 
       Current_Time - Last_Time_Measure > ZeroDebouncing - ZeroDebouncingExtra)
    {  
        Frequency_Decimal = 0;          //Set Frequency_Decimal to 0
        ZeroDebouncingExtra = 2000; 
    }
    else
    {
        ZeroDebouncingExtra = 0; 
    }

    Frequency_Integer = Frequency_Decimal / 10000;    //Convert Frequency_Decimal to integer

    //Calculate RPM (Rotation per Minute)
    //Divide by Propeller_Blades to avoid reading 3 pulses, multiply by 60 for per minute value
    RPM = Frequency_Decimal / Propeller_Blades * 60;    
    RPM = RPM / 10000;                 //Convert RPM from microseconds to seconds

    total = total - Reading[Read_Index];
    Reading[Read_Index] = RPM;
    total = total + Reading[Read_Index];
    Read_Index = Read_Index + 1;

    if(Read_Index >= read_count)        //If end of array reached
    {
        Read_Index = 0;                 //Reset Read_Index
    }
  
    average = total / read_count;       //Calculate average value
    
    //Convert RPM to KMh using formula: RPM * Wheel Diameter(9cm) * km/hr(0.001885)
    //Where 0.001885 = 3600/1000000 (3600 min/hr, 1000000mm = 1km)
    kmh = average * 0.001885 * 9;       

    newTime = millis();

    if(newTime - oldTime > 1000)
    {
        int mapping = map(kmh, 0, 20, 180, 0);    //Map kmh between 0-20 to servo angles 180-0
        servo.write(mapping);                      //Move servo to mapped position
  
        lcd.clear();                    //Clear LCD display
        lcd.setCursor(0, 0);            //Move to first row
        lcd.print("SPEED: ");           //Write "SPEED: "
        lcd.print(kmh);                 //Write speed value
        lcd.print(" km/h");             //Write units
        oldTime = newTime;
    }
    delay(200);
}  

void Interrupt_Function()               //Define interrupt function to read pulses
{
    Period_Between_Pulse = micros() - Last_Time;
    Last_Time = micros();              //Save time in microseconds

    if(PulseCounter >= Read_Quantity)   //If PulseCounter exceeds Read_Quantity
    {
        Average_Period = Total_Period / Read_Quantity;    //Calculate average period
        PulseCounter = 1;               //Reset pulse counter
        Total_Period = Period_Between_Pulse;    //Start new average calculation

        //Map period between 40000-5000 to 1-10
        int proportion = map(Period_Between_Pulse, 40000, 5000, 1, 10);
        
        proportion = constrain(proportion, 1, 10);    //Constrain proportion between 1-10
        Read_Quantity = proportion;                   //Save proportion as Read_Quantity
    }
    else
    {
        PulseCounter++;                             //Increment pulse counter
        Total_Period = Total_Period + Period_Between_Pulse;    //Add to total period
    }
}
