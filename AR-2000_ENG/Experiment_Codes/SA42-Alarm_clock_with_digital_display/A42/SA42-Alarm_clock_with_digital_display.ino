#include <LiquidCrystal_I2C.h>    //Add I2C LCD library
#include <Keypad.h>               //Add Keypad Library
#include <stdlib.h>               //Library to use the itoa function required for the integer-to-character transformation

const byte ROW = 4;               //Specify how many rows the keypad consists of 
const byte COLUMN = 4;            //Specify how many columns the keypad consists of 

//Define the keys on the keypad 
char pressedKeys[ROW][COLUMN] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//Define the pins to which the row and column pins of the keypad are connected
byte rowPins[ROW] = {13, 12, 11, 10}; 
byte columnPins[COLUMN] = {9, 8, 7, 6}; 

//Start the keypad
Keypad key_pad = Keypad(makeKeymap(pressedKeys), rowPins, columnPins, ROW, COLUMN); 

LiquidCrystal_I2C lcd(0x27, 16, 2);    //Define 1602 LCD display

int LEDPin = 5;                         //Define the digital pin number to which the LED is connected
int speakerPin = 4;                     //Define the pin number to which the Speaker is connected
int buttonPin = 3;                      //Define the pin number to which the Button is connected
int snoozeButtonPin = 2;                //Define the pin number to which the snooze button is connected
int Alarm_hour;                         //Define the variable to store the alarm hour
int Alarm_minute;                       //Define the variable to store the alarm minute
char Alarm_hour_char[2] = {};           //Define a variable that will store the hour values pressed from the alarm clock keypad as characters.
char Alarm_minute_char[2] = {};         //Define a variable that will store the minute values pressed from the alarm clock keypad as characters.
char Hour_char[2] = {};                 //Define the variable to store the hour value as character.
char Minute_char[2] = {};               //Define the variable to store the minute value as character
int hour;                               //Define the hour variable as an integer (whole number) so that the hour can be incremented
int minute;                             //Define minute variable as integer (whole number) so that minute can be incremented 
int second;                             //Define second variable as integer (whole number) so that second can be incremented 
char pressedKey;                        //Define the variable to store the key pressed on the keypad
bool buttonStatus = 0;                  //Define the variable to check if the button is pressed
bool snoozeButtonStatus = 0;            //Define the variable to check if the snooze button is pressed
int i = 0, j = 0, z = 0, x = 0;        //Define i, j, z and x variables to count the 0th and 1st values of Hour_char, Minute_char, 
                                       //Alarm_hour_char, Alarm_minute_char variables created as characters and set their initial values 
                                       //equal to zero.

void Interrupt_Function()               //Define interrupt function
//This function defines what the interrupt operation should do when the button is pressed
//this function is called using the attachInterrupt function
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if(interrupt_time - last_interrupt_time > 500)
  {
    buttonStatus = !buttonStatus;
  }
  last_interrupt_time = interrupt_time;
}

void Snooze_Function() 
{
  static unsigned long last_interrupt_time = 0;
  unsigned long interrupt_time = millis();
  if(interrupt_time - last_interrupt_time > 500)
  {
    if(hour == Alarm_hour && minute == Alarm_minute)
    {
      snoozeButtonStatus = 1;
      Alarm_minute = Alarm_minute + 3;
      if(Alarm_minute > 59)
      {
        Alarm_minute = Alarm_minute % 10;
        Alarm_hour++;
        if(Alarm_hour > 23)
        {
          Alarm_hour = 0; 
        }
      }
    }
  }
  last_interrupt_time = interrupt_time;
}

void setup() {
  pinMode(buttonPin, INPUT);              //Set the pin to which the Button is connected as input
  pinMode(snoozeButtonPin, INPUT_PULLUP); //Set the pin to which the Snooze Button is connected as input
  pinMode(LEDPin, OUTPUT);                //Set the pin to which the LED is connected as output
  pinMode(speakerPin, OUTPUT);            //Set the pin to which the Speaker is connected as output 
  
  attachInterrupt(digitalPinToInterrupt(buttonPin), Interrupt_Function, RISING);       //Make interrupt definitions
  attachInterrupt(digitalPinToInterrupt(snoozeButtonPin), Snooze_Function, RISING);   //Make interrupt definitions
  
  lcd.begin();                    //Start the LCD display
  lcd.backlight();               //Turn ON the LCD backlights
  lcd.clear();                   //Clear the LCD display
  lcd.setCursor(0, 0);           //Switch to the first row
  lcd.print("TEES ELECTRONICS"); //Write "TEES ELECTRONICS" on the LCD display
  lcd.setCursor(0, 1);           //Switch to the lower row
  lcd.print(" Alarm Clock ");    //Write to the LCD display
  delay(2000);                   //Wait for 2 seconds
  lcd.clear();                   //Clear the LCD display
}

void loop() {
  lcd.print("Enter Time");       //Print "Enter Time" on the LCD display
  delay(2000);                   //Wait for 2 seconds
  lcd.clear();                   //Clear the LCD display

  while(1) {                     //Enter infinite loop 
    pressedKey = key_pad.getKey();  //Save the key pressed from the keypad to the pressedKey character.
    if(pressedKey) {                //If the key is pressed 
      Hour_char[i] = pressedKey;    //Save the key pressed in the Hour_char[i] variable
      //Here, the i value will take the values 0 and 1. In this way, the 1st and 2nd values of the hour can be entered. (e.g. 23 or 09)
      lcd.setCursor(5+i, 0);        //Go to column 5+i on the first row of the LCD display If i is equal to 0, go to column 5. 
                                    //If i is equal to 1, go to column 6
      lcd.print(Hour_char[i]);      //Print the values entered from the keypad to the LCD display.
      i++;                          //Increment i value by one
      hour = atoi(Hour_char);       //Convert the Hour_char character, where the values entered from the keypad are recorded, to integer 
                                    //(whole number) with the atoi function and save it to the hour variable.
      if(i > 1) break;             //End infinite loop if i is greater than 1
    }
  }

  while(1)                          //Enter infinite cycle
  {
    pressedKey = key_pad.getKey();  //Save the key pressed from the keypad to the pressedKey character.
    if(pressedKey) {                //If the key is pressed 
      Minute_char[j] = pressedKey;  //Store the pressed key in the Minute_char[j] variable
      //Here, the j value will take the values 0 and 1. In this way, the 1st and 2nd values of the hour can be entered. (e.g. 23 or 09)
      lcd.print(":");               //Print ":" on the LCD display
      lcd.setCursor(8+j, 0);        //Go to column 8+j on the first row of the LCD display. If j is equal to 0, go to column 8. 
                                    //If j is equal to 1, go to column 9
      lcd.print(Minute_char[j]);    //Print the values entered from the keypad to the LCD display.
      j++;                          //Increment j value by one
      minute = atoi(Minute_char);   //Convert the Minute_char character, where the values entered from the keypad are recorded, to integer 
                                    //(whole number) with the atoi function and save it to the minute variable.
    }

    if(j >= 2) break;              //If j is greater than 2
                                   //That is, if minute is entered, exit the infinite loop
  }

  while(1)                         //Enter infinite loop
  {
    digital_clock();               //Call digital_clock function
    pressedKey = key_pad.getKey(); //Save the key pressed from the keypad to the pressedKey character.
    if(pressedKey == '*') break;   //If the * key is pressed from the Keypad, exit the infinite loop and go to the beginning of the loop
                                   //In other words, it will print "Enter Time" on the screen
                                   //This allows us to exit the infinite loop and re-enter the time

    if(buttonStatus == 1) {        //if button is pressed in infinite loop
      lcd.print("Please Enter");   //Write on the LCD display
      lcd.setCursor(0, 1);         //Switch to the lower row
      lcd.print("Alarm Time");     //Write on the LCD display
      delay(2000);                 //Wait for 2 seconds
      lcd.clear();                 //Clear the LCD display

      while(1) {                   //Enter infinite loop to set alarm clock
        pressedKey = key_pad.getKey(); //Save the key pressed from the keypad to the pressedKey character.
        if(pressedKey) {              //If the key is pressed 
          Alarm_hour_char[z] = pressedKey; //Save the key pressed in the variable Alarm_hour_char[z]
          //Here, the z value will take the values 0 and 1. In this way, the 1st and 2nd values of the hour can be entered. 
          //(e.g. 23 or 09)
          lcd.setCursor(5+z, 0);      //Go to column 5+z on the first row of the LCD display. If z is equal to 0, go to column 5. 
                                      //If z is equal to 1, go to column 6
          lcd.print(Alarm_hour_char[z]); //Print the values entered from the keypad to the LCD display.
          z++;                        //Increment z value by one
          Alarm_hour = atoi(Alarm_hour_char); //Convert the Alarm_hour_char character, where the values entered from the keypad are 
                                             //recorded, to integer (whole number) with the atoi function and save it to the Alarm_hour 
                                             //variable.
          if(z > 1) break;           //End infinite loop if z is greater than 1
        }
      }

      while(1) {                     //Enter infinite loop to set alarm clock
        pressedKey = key_pad.getKey(); //Save the key pressed from the keypad to the pressedKey character.
        if(pressedKey) {              //If the key is pressed 
          Alarm_minute_char[x] = pressedKey; //Save key pressed in the variable Alarm_minute_char[x]
          //Here, the x value will take the values 0 and 1. In this way, the 1st and 2nd values of the hour can be entered. 
          //(e.g. 23 or 09)
          lcd.print(":");             //Print ":" on the LCD display
          lcd.setCursor(8+x, 0);      //Go to column 8+x on the first row of the LCD display. If x is equal to 0, go to column 8. 
                                      //If x is equal to 1, go to column 9
          lcd.print(Alarm_minute_char[x]); //Print the values entered from the keypad to the LCD display.
          x++;                        //Increment x value by one
          Alarm_minute = atoi(Alarm_minute_char); //Convert the Alarm_minute_char character, where the values entered from the keypad are 
                                                 //recorded, to integer (whole number) with the atoi function and save it to the 
                                                 //Alarm_minute variable.
        }
        if(x >= 2) break;            //If x is greater than 2
                                     //That is, if minute is entered, exit the infinite loop
      }

      while(1) {                     //Enter the infinite loop to print the Clock and Alarm clock on the screen
        Alarm_digital_clock();       //Call alarm_digital_clock function
        pressedKey = key_pad.getKey(); //Save the key pressed from the keypad to the pressedKey character.
        if(buttonStatus == 0) 
        {
          Alarm_hour_char[2] = {}; 
          Alarm_minute_char[2] = {}; 
          break;                     //Exit infinite loop if * key is pressed from keypad
        }
        if(snoozeButtonStatus == 1)
        {
          lcd.setCursor(0, 0);
          lcd.clear();
          lcd.print("Snoozed for 3 min");
          delay(1000);
          snoozeButtonStatus = 0;
        }
      }
    }
  }
}

void digital_clock() {               //Define digital_clock() function 
  //Process the commands inside this function where they are called

  //We will follow the steps below to count
  //Primarily 1000 ms is 1 second
  //1 minute is 60 seconds
  //1 hour is 60 minutes
  //1 day is 24 hours

  second++;                          //Increment second variable by one
  //Below the program codes you will see delay(1000)
  //With the help of the delay there, we increase the second variable at intervals of 1 second

  if(second > 59) {                 //If the second variable is greater than 59 
    second = 0;                     //Reset the second variable
    minute++;                       //Increment the minute variable by one
  }
  if(minute > 59) {                //if the minute is greater than 59
    second = 0;                    //Reset the second variable
    minute = 0;                    //Reset the minute variable
    hour++;                        //Increment the hour variable by one
  }
  if(hour > 23)                    //If hour is greater than 23
  {
    second = 0;                    //Reset the second variable
    minute = 0;                    //Reset the minute variable
    hour = 0;                      //Reset the hour variable
  }

  lcd.setCursor(0, 0);
  lcd.print("      Time     ");    //Print "Time" on the LCD display
  lcd.setCursor(0, 1);             //Switch to the lower row

  if(hour < 10) {
    lcd.print("    ");            //When the hour is less than 10, put a 0 in front of it and a colon after it ( 01: )
    lcd.print("0");
    lcd.print(hour);
    lcd.print(":");
  }
  if(hour >= 10) {
    lcd.print("    ");            //When the hour is greater than 10, remove the 0 in front of it, just print the hour and put a colon 
                                  //( 23: )
    lcd.print(hour);
    lcd.print(":");
  }
  if(minute < 10) {
    lcd.print("0");               //When the minute is less than 10, put a 0 in front of it and a colon after it ( 07: )
    lcd.print(minute);
    lcd.print(":");
  }
  if(minute >= 10) {
    lcd.print(minute);            //When the minute is greater than 10, remove the 0 in front of it, just print the minute and put a 
                                 //colon ( 19: )
    lcd.print(":");
  }
  if(second < 10) {
    lcd.print("0");              //When the second is less than 10, put a 0 in front of it and a colon after it ( 02: )
    lcd.print(second);
  }
  if(second >= 10) {
    lcd.print(second);           //When the second is greater than 10, remove the 0 in front of it, just print the second ( 57 )
  }
  delay(954);                    //delay of 954 milliseconds
  //Approximately 46 milliseconds delay due to the operation of the program and the 954 milliseconds delay we have created here is a 
  //1000 milliseconds in total
  //In other words, it corresponds to a delay of 1 second. With this 1-second delay, our second variable increases one by one.
  lcd.clear();                   //Clear the LCD display
}

void Alarm_digital_clock() {      //Define Alarm_digital_clock function
  //Process the commands inside this function where they are called

  second++;                       //Increment second variable by one
  //Below the program codes you will see delay(1000)
  //With the help of the delay there, we increase the second variable at intervals of 1 second

  if(second > 59) {              //If the second variable is greater than 59 
    second = 0;                  //Reset the second variable
    minute++;                    //Increment the minute variable by one
  }
  if(minute > 59) {             //if the minute is greater than 59
    second = 0;                 //Reset the second variable
    minute = 0;                 //Reset the minute variable
    hour++;                     //Increment the hour variable by one
  }
  if(hour > 23)                 //If hour is greater than 23
  {
    second = 0;                 //Reset the second variable
    minute = 0;                 //Reset the minute variable
    hour = 0;                   //Reset the hour variable
  }
  
  lcd.setCursor(0, 0);
  lcd.print("Hour :");

  if(hour < 10) {
    lcd.print("0");             //When the hour is less than 10, put a 0 in front of it and a colon after it ( 01: )
    lcd.print(hour);
    lcd.print(":");
  }
  if(hour >= 10) {
    lcd.print(hour);            //When the hour is greater than 10, remove the 0 in front of it, just print the hour and put a colon 
                               //( 23: )
    lcd.print(":");
  }
  if(minute < 10) {
    lcd.print("0");            //When the minute is less than 10, put a 0 in front of it and a colon after it ( 07: )
    lcd.print(minute);
    lcd.print(":");
  }
  if(minute >= 10) {
    lcd.print(minute);         //When the minute is greater than 10, remove the 0 in front of it, just print the minute and put a colon 
                              //( 19: )
    lcd.print(":");
  }
  if(second < 10) {
    lcd.print("0");           //When the second is less than 10, put a 0 in front of it and a colon after it ( 02: )
    lcd.print(second);
  }
  if(second >= 10) {
    lcd.print(second);        //When the second is greater than 10, remove the 0 in front of it, just print the second ( 57 )
  }

  lcd.setCursor(0, 1);
  lcd.print("Alarm:");

  if(Alarm_hour < 10) {
    lcd.print("0");           //When the alarm hour is less than 10, put a 0 in front of it and a colon after it ( 01: )
    lcd.print(Alarm_hour);
    lcd.print(":");
  }
  if(Alarm_hour >= 10) {
    lcd.print(Alarm_hour);    //When the alarm hour is greater than 10, remove the 0 in front of it, just print the alarm hour and put 
                             //a colon ( 23: )
    lcd.print(":");
  }
  if(Alarm_minute < 10) {
    lcd.print("0");          //When the alarm minute is less than 10, put a 0 in front of it and a colon after it ( 07: )
    lcd.print(Alarm_minute);
    lcd.print(":");
  }
  if(Alarm_minute >= 10) {
    lcd.print(Alarm_minute); //When the alarm minute is greater than 10, remove the 0 in front of it, just print the alarm minute and 
                            //put a colon ( 19: )
    lcd.print(":");
  }
  lcd.print("00");          //We made 00 instead of the second variable.

  if(hour == Alarm_hour && minute == Alarm_minute) { //If the hour and minute are equal to the set alarm hour and alarm minute
    //Perform the following actions to make the alarm sound

    //SOUND THE ALARM
    for(int i=0; i<4; i++) {     //for loop to sound 3 times
      tone(speakerPin, 1000);    //Play audio tone from the Speaker
      digitalWrite(LEDPin, HIGH); //Turn ON the LED
      delay(35);                 //Wait for 35 ms
      noTone(speakerPin);        //Mute the Speaker
      digitalWrite(LEDPin, LOW);  //Turn OFF the LED 
      delay(120);                //Wait for 120 ms
      pressedKey = key_pad.getKey(); //Save the key pressed from the keypad to the pressedKey character.
    }
    delay(350);
  }
  //If hour and minute are not equal to set alarm hour and alarm minute
  digitalWrite(LEDPin, LOW);     //Turn OFF the LED 
  noTone(speakerPin);           //Mute the Speaker 

  delay(952);                   //Delay of 952 milliseconds
  //Approximately 100 milliseconds delay due to the operation of the program and the 900 milliseconds delay we have created here is a 
  //1000 milliseconds in total
  //In other words, it corresponds to a delay of 1 second. With this 1-second delay, our second variable increases one by one
  lcd.clear();                  //Clear the LCD display
}