//SA83 - Number guessing game

#include <LiquidCrystal_I2C.h>    //Add I2C LCD library
#include <Keypad.h>               //Add Keypad Library
#include <stdlib.h>               //Library to use the itoa function required for the integer-to-character transformation

const byte ROW = 4;               //Specify how many rows the keypad consists of 
const byte COLUMN = 4;            //Specify how many columns the keypad consists of 

//Define the position and order of the keys in the row and column
char keys[ROW][COLUMN] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

//Define the pins to which the row and column pins of the keypad are connected
byte rowPins[ROW] = {7, 6, 5, 4}; 
byte columnPins[COLUMN] = {3, 2, 1, 0}; 

//Start the keypad
Keypad keyPad = Keypad(makeKeymap(keys), rowPins, columnPins, ROW, COLUMN);

LiquidCrystal_I2C lcd(0x27, 16, 2);     //Define 1602 LCD display

int music[] = {
    262, 196, 196, 220, 196, 0, 247, 262
};

int noteTimes[] = {
    4, 8, 8, 4, 4, 4, 4, 4
};
  
int buttonPin = 8;                       //Define the pin number to which the Button is connected
int speakerPin = 9;                      //Define the pin number to which the Speaker is connected
int red_LED = 12;                        //Define the pin to which the red LED is connected
int green_LED = 11;                      //Define the pin number to which the Green LED is connected

char Entered_Number_Char[4] = {};        //Define the variable required to store the number value entered from keypad as character
int Entered_Number;                      //Variable that will store the entered number as integer
char pressedKey;                         //Define the variable to store the key pressed on the keypad
int randomNumber;                        //Define the variable to store the randomly generated number
int i = 0;
int guessing = 10;                       //Define the variable in which the guessing right will be stored and set its value to 10

void setup() {
    pinMode(buttonPin, INPUT);           //Set the pin to which the Button is connected as input
    pinMode(speakerPin, OUTPUT);         //Set the pin to which the Speaker is connected as output 
    pinMode(red_LED, OUTPUT);            //Set the pin to which the Red LED is connected as output 
    pinMode(green_LED, OUTPUT);          //Set the pin to which the Green LED is connected as output 
  
    lcd.begin();                         //Start the LCD display
    lcd.backlight();                     //Turn ON the LCD backlights
    lcd.clear();                         //Clear the LCD display
    lcd.setCursor(0, 0);                 //Switch to the first row
    lcd.print("TEES ELECTRONICS");       //Write "TEES ELECTRONICS" on the LCD display
    lcd.setCursor(0, 1);                 //Switch to the lower row
    lcd.print("Number Guessing");        //Write "Number Guessing" on the LCD display
    delay(2000);                         //Wait for 2 seconds
    lcd.clear();                         //Clear the LCD display

    lcd.setCursor(0, 0);                 //Switch to the first row on the LCD display
    lcd.print("Press Button and");       //Write "Press Button and"
    lcd.setCursor(0, 1);                 //Switch to 2nd row on the LCD display
    lcd.print("Guess the Number");       //Write "Guess the Number" on the LCD display
}

void loop() { 
    randomSeed(analogRead(A0));          //Take pin A0 as reference to generate random number
    randomNumber = random(0, 100);       //Generate a random number between 0 and 100 and save to randomNumber variable
  
    if(digitalRead(buttonPin) == HIGH) {
        lcd.clear();                     //Clear the LCD display 
        digitalWrite(green_LED, HIGH);    //Turn ON the Green LED
        
        while(1) {                       //Enter infinite loop
            pressedKey = keyPad.getKey(); //Save keys pressed from the keypad
            if(pressedKey != NO_KEY) {    //If any key is pressed
                lcd.clear();              //Clear LCD display
                Entered_Number_Char[i] = pressedKey;  //Save the pressed key to the Entered_Number_Char[i] variable
                i++;                      //Increment i value by one
                Entered_Number = atoi(Entered_Number_Char); //Convert values entered from keypad to integer

                lcd.setCursor(0, 1);
                lcd.print("You Entered: ");
                lcd.print(Entered_Number);

                if(pressedKey == '#') {
                    i = 0;
                    if(Entered_Number == randomNumber) {  //If number entered equals random number (correct guess)
                        lcd.clear();                      //Clear the LCD display
                        lcd.setCursor(0, 0);              //Switch to the first row on the LCD display
                        lcd.print("** Congrats **");      //Write "Congratulations" on the LCD display
                        guessing = 10;                    //Make guessing variable 10 for the new game
                        clean();                          //Call the clean() function to clear entered number data
                        digitalWrite(green_LED, HIGH);
                        won();                            //Call the won() function to indicate game has been won
                        break;
                    }
                    else if(Entered_Number < randomNumber) {  //If entered number is smaller than random number
                        lcd.clear();                          //Clear the LCD display
                        lcd.setCursor(0, 0);                  //Switch to the first row on the LCD display
                        lcd.print("Wrong! Number");           
                        lcd.setCursor(0, 1);                  //Switch to 2nd row on the LCD display
                        lcd.print("Is Greater");
                        guessing--;                           //Decrement the guessing value by 1
                        lcd.setCursor(13, 1);                 //Go to column 13 in the bottom row
                        lcd.print("G:");                      //Write G: on the LCD display
                        lcd.print(guessing);                  //Print the remaining guessing number
                        clean();
                    }
                    else {                                    //If entered number is greater than random number
                        lcd.clear();                          //Clear the LCD display
                        lcd.setCursor(0, 0);                  //Switch to the first row on the LCD display
                        lcd.print("Wrong! Number");           
                        lcd.setCursor(0, 1);                  //Switch to 2nd row on the LCD display
                        lcd.print("Is Smaller");
                        guessing--;                           //Decrement the guessing value by 1
                        lcd.setCursor(13, 1);                 //Go to column 13 in the bottom row
                        lcd.print("G:");                      //Write G: on the LCD display
                        lcd.print(guessing);                  //Print the remaining guessing number
                        clean();
                    }

                    if(guessing == 0) {                       //If the number of guessing is over 
                        lost();                               //Call lost() function
                        guessing = 10;                        //Make guessing variable 10 for the new game
                        break;
                    }
                }
            }
        }
    }
}

void clean() {                                               //Create a clean() function to clear entered keypad number
    for(int j=0; j<=5; j++) {                               //Increment j value from 0 to 5 one by one
        Entered_Number_Char[j] = 0;                          //Equalize each value in Entered_Number_Char array to 0
    }
}

void lost() {                                               //Create lost() function 
    for(int j=1; j<4; j++) { 
        lcd.setCursor(0, 0);
        lcd.print("You Lost!   ");
        lcd.setCursor(0, 1);
        lcd.print("Restart Game");
        digitalWrite(green_LED, LOW); 
        tone(speakerPin, 100); 
        digitalWrite(red_LED, HIGH); 
        delay(500);
        noTone(speakerPin); 
        digitalWrite(red_LED, LOW); 
        delay(500);
    }
}

void won() {                                                //Define the winning animation function
    for(int i=0; i<8; i++) {
        int noteTime = 1000/noteTimes[i];
        tone(speakerPin, music[i], noteTime);
        digitalWrite(green_LED, HIGH);
        int waitBetweenNotes = noteTime * 1.30; 
        delay(waitBetweenNotes / 2);
        digitalWrite(green_LED, LOW);
        noTone(speakerPin);
    }
}
