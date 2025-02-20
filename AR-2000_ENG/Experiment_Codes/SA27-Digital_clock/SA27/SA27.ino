//SA27 - Digital clock

#include <LiquidCrystal_I2C.h> //Add I2C LCD library
#include <Keypad.h>           //Keypad Library added
#include <stdlib.h>           //Library to use the itoa function required for the integer-to-character transformation

//Define how many rows and columns are on the keypad we use 
//The keypad on the panel is 4x4, that is, there are 4 rows and 4 columns
const byte ROW = 4; 
const byte COLUMN = 4;

//Define the position and order of the keys in the row and column
char pressedKeys[ROW][COLUMN] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//Define which pins the row and column pins are connected to on the Arduino board
//We made our connection in order from left to right 
//The first four connections of the keypad are the connections of the ROWS
//The last four connections are the connection of the COLUMNS
byte rowPins[ROW] = {13, 12, 11, 10}; //Define the pins to which the row connections are connected on the Arduino board.
byte columnPins[COLUMN] = {9, 8, 7, 6}; //Define the pins to which the column connections are connected on the Arduino board.

Keypad key_pad = Keypad(makeKeymap(pressedKeys), rowPins, columnPins, ROW, COLUMN); //Define Keypad for the keypad

LiquidCrystal_I2C lcd(0x27, 16, 2); //Define 1602 LCD display

char hour_char[2] = {};   //Define the variable required to store the hour value as character 
char minute_char[2] = {}; //Define the variable required to store the minute value as character 

int hour;   //Define the hour variable as an integer (whole number) so that the hour can be incremented
int minute; //Define minute variable as integer (whole number) so that minute can be incremented 
int second; //Define second variable as integer (whole number) so that second can be incremented 

char pressedKey; //Define the variable to store the key pressed on the keypad

int i = 0, j = 0; //Define i and j variables to count the 0th and 1st values of hour_char and minute_char variables 
                  //created as characters and set their initial values equal to zero

void setup() {
  lcd.begin(); //Start the LCD display
  lcd.backlight(); //Turn ON the LCD backlights
  lcd.clear(); //Clear the LCD display
  lcd.setCursor(0, 0); //Switch to the first row 
  lcd.print("TEES ELECTRONICS"); //Write "TEES ELECTRONICS" 
  lcd.setCursor(0, 1); //Switch to lower row
  lcd.print("Digital Clock"); //Write Digital Clock on the LCD display
  delay(2000); //Keep text on the screen for 2 seconds 
  lcd.clear(); //Clear text
}

void loop() {
  lcd.print("Enter Hour"); //Print "Enter Hour" on the LCD display
  delay(2000); //Wait for 2 seconds 
  lcd.clear(); //Clear LCD display 

  while (1) { //Enter infinite loop 
    pressedKey = key_pad.getKey(); //Save the key pressed from the keypad to the pressedKey character
    if (pressedKey) { //If the key is pressed
      hour_char[i] = pressedKey; //Save the key pressed in the hour_char[i] variable
                                 //The i value will take the values 0 and 1. In this way, the 1st and 2nd values of the hour 
                                 //can be entered. (e.g. 23 or 09)
      lcd.setCursor(5 + i, 0); //Go to column 5 + i on the first row of the LCD Display. If i is equal to 0, go to column 5. 
                               //If i is equal to 1, go to column 6
      lcd.print(hour_char[i]); //Print the values entered from the keypad to the LCD display
      
      i++; //Increment i value by one
      
      hour = atoi(hour_char); //Convert the hour_char character, where the values entered from the keypad are recorded, 
                              //to integer (whole number) with the atoi function and save it to the hour variable
                              //Now perform the necessary operations with the hour variable converted to integer
                              //Increment and decrement the hour_char variable in character type
                              //So we need to convert it to an integer
      
      if (i > 1) break; //End infinite loop if i is greater than 1 
    }
  }
  
  while (1) { //Enter infinite loop 
    pressedKey = key_pad.getKey(); //Save the key pressed from the keypad to the pressedKey character
    if (pressedKey) { //If the key is pressed 
      minute_char[j] = pressedKey; //Store the pressed key in the minute_char[j] variable
                                   //The j value will take the values 0 and 1. In this way, the 1st and 2nd values of the 
                                   //hour can be entered. (e.g. 23 or 09)
      lcd.print(":"); //Print ":" on the LCD display 
      lcd.setCursor(8 + j, 0); //Go to column 8 + j on the first row of the LCD display. If j is equal to 0, go to column 8. 
                               //If j is equal to 1, go to column 9
      lcd.print(minute_char[j]); //Print the values entered from the keypad to the LCD display
      j++; //Increment j value by one
      minute = atoi(minute_char); //Convert the minute_char character, where the values entered from the keypad are recorded, 
                                  //to integer (whole number) with the atoi function and save it to the minute variable
                                  //Now perform the necessary operations with the hour variable converted to integer
                                  //Increment and decrement the minute_char variable in character type
                                  //So we need to convert it to an integer
    }               
    if (j >= 2) break; //If j is greater than 2, that is, if minute is entered, exit the infinite loop
  }

  while (1) { //Enter infinite loop 
    digital_clock(); //Call digital_clock function
    for (int i = 0; i < 100; i++) {
      delay(10);
      pressedKey = key_pad.getKey(); //Save the key pressed from the keypad to the pressedKey character
      if (pressedKey == '*') { 
        i = 0; j = 0; second = 0; //Reset i, j and second variables
        pressedKey = '*';
        break; //If the * key is pressed on the keypad exit the infinite loop and go to the beginning of the loop cycle
               //That is print "Enter Time" on the screen again 
               //This allows us to exit the infinite loop and re-enter the time
      }
    }
    lcd.clear();
     
    if (pressedKey == '*') { 
      i = 0; j = 0; second = 0; //Reset i, j and second variables
      
      break; //If the * key is pressed on the keypad exit the infinite loop and go to the beginning of the loop cycle
             //That is print "Enter Time" on the screen again 
             //This allows us to exit the infinite loop and re-enter the time
    }
  }
}

void digital_clock() { //Define digital_clock() function 
                       //Process the commands inside this function where they are called
  //** We will follow the steps below to count
  //Primarily 1000 ms is 1 second
  //1 minute is 60 seconds
  //1 hour is 60 minutes
  //1 day is 24 hours

  second++; //Increment second variable by one

  if (second > 59) { //If the second variable is greater than 59 
    second = 0; //Reset the second variable 
    minute++; //Increment the minute variable by one 
  }
  if (minute > 59) { //if the minute is greater than 59 
    second = 0; //Reset the second variable
    minute = 0; //Reset the minute variable
    hour++; //Increment the hour by one
  }
  if (hour > 23) { //If hour is greater than 23 
    second = 0; //Reset the second variable 
    minute = 0; //Reset the minute variable
    hour = 0; //Reset the hour variable 
  }

  //*** The following lines of code are for printing text on the LCD display
  lcd.setCursor(0, 0);
  lcd.print("      Time     "); // Print "Time" on the LCD display
  lcd.setCursor(0, 1); //Switch to the lower row
   
  if (hour < 10) { 
    lcd.print("    "); 
    lcd.print("0"); 
    lcd.print(hour); 
    lcd.print(":"); 
  } //When the hour is less than 10, put a 0 before it and a colon after it. ( 01:  )
  if (hour >= 10) { 
    lcd.print("    "); 
    lcd.print(hour); 
    lcd.print(":"); 
  } //When the hour is greater than 10, remove the 0 in front of it, just print the hour and put a colon after it ( 23: ) 
  if (minute < 10) { 
    lcd.print("0"); 
    lcd.print(minute); 
    lcd.print(":"); 
  } //When the minute is less than 10, put a 0 before it and a colon after it. ( 07:  )
  if (minute >= 10) { 
    lcd.print(minute); 
    lcd.print(":"); 
  } //When minute is greater than 10, remove the 0 in front of it, just print the minute and put a colon after it ( 19: ) 
  if (second < 10) { 
    lcd.print("0"); 
    lcd.print(second); 
  } //When second is less than 10, put a 0 before and a colon after it ( 02:  )
  if (second >= 10) { 
    lcd.print(second); 
  } //When the second is greater than 10, remove the 0 in front of it, just print the second ( 57 ) 
}