//SA94 - Programmable FM radio

#include <TEA5767N.h>          //Add FM radio library
#include <Keypad.h>            //Add Keypad library
#include <stdlib.h>            //Library to use the itoa function required for the integer-to-character transformation                    
#include <LiquidCrystal_I2C.h> //Add I2C LCD library

const byte ROW = 4;            //Specify how many rows the keypad consists of 
const byte COLUMN = 4;         //Specify how many columns the keypad consists of

//Define the keys on the keypad 
char keys[ROW][COLUMN] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

//Define the pins to which the row and column pins of the keypad are connected
byte rowPins[ROW] = {13, 12, 11, 10}; 
byte columnPins[COLUMN] = {9, 8, 7, 6}; 

//Start the keypad
Keypad key_pad = Keypad(makeKeymap(keys), rowPins, columnPins, ROW, COLUMN); 

LiquidCrystal_I2C lcd(0x27, 16, 2);    //Define 1602 LCD display
TEA5767N radio = TEA5767N();            //Create object named radio to control TEA5767 module
float radio_frequency = 87.5;            //Define the variable named radio_frequency and set its initial value to 87.5 
                                        //This variable will be the variable to keep the frequencies

char Entered_Frequency[5] = {};          //The variable to which the frequency entered from the keypad will be stored is defined
                                        //The values entered from the keypad are saved as characters
                            
int i = 0;                              //The variable required to enter values sequentially from the keypad

void setup() {
    lcd.begin();                        //Start the LCD display
    lcd.backlight();                    //Turn ON the LCD backlights
    lcd.clear();                        //Clear the LCD display
  
    delay(250); 
    radio.selectFrequency(radio_frequency);
    delay(250);
    lcd.setCursor(0, 0);               //Switch to the first row on the LCD display
    lcd.print("TEES ELECTRONICS");
    lcd.setCursor(0, 1);               //Switch to 2nd row on the LCD display 
    lcd.print("    FM RADIO    ");     //Write "FM RADIO" on the LCD display
    lcd.clear(); 
    lcd.setCursor(0, 0);               //Switch to the first row on the LCD display
    lcd.print("Radio Frequency");
    lcd.setCursor(0, 1);               //Switch to 2nd row on the LCD display 
    lcd.print("FM : ");
    lcd.print(radio_frequency);         //Write the frequency value
    lcd.print(" MHz");
}
 
void loop() {
    char pressedKey = key_pad.getKey(); //Save the key pressed from the keypad to the pressedKey character
  
    if(pressedKey) {                    //If any key is pressed
        if(pressedKey == 'A') {         //If 'A' key is pressed from the keypad 
                                        //To increase the frequency and change the channel, follow the steps below:          
            radio_frequency += 0.1;      //Increment the radio_frequency variable by 0.1 
            radio.selectFrequency(radio_frequency); //Write the radio_frequency variable to the radio and open the channel
  
            lcd.clear();                //Clear the LCD display
            lcd.setCursor(0, 0);        //Switch to the first row on the LCD display
            lcd.print("Radio Frequency: ");
            lcd.setCursor(0, 1);        //Switch to 2nd row on the LCD display 
            lcd.print("FM : ");
            lcd.print(radio_frequency); //Write the frequency value
            lcd.print(" MHz");
        
            Serial.print("Frequency  :"); 
            Serial.println(radio_frequency); //Type frequency value on the Serial port screen

            if(radio_frequency > 108.0) { //If the frequency value is greater than 108 
                radio_frequency = 87.5;   //Set the radio_frequency value to 87.5 
                radio.selectFrequency(radio_frequency); //Send the set value to the radio
            }
            delay(250); 
        }
        else if(pressedKey == 'B') {     //If 'B' key is pressed from the keypad 
                                        //To decrease the frequency and change the channel, follow the steps below:
            radio_frequency -= 0.1;      //Decrement the radio_frequency variable by 0.1
            radio.selectFrequency(radio_frequency); //Write the radio_frequency variable to the radio and open the channel
  
            lcd.clear();                //Clear LCD display 
            lcd.setCursor(0, 0);        //Switch to the first row on the LCD display
            lcd.print("Radio Frequency: ");
            lcd.setCursor(0, 1);        //Switch to 2nd row on the LCD display 
            lcd.print("FM : ");
            lcd.print(radio_frequency); //Write the frequency value
            lcd.print(" MHz");
      
            if(radio_frequency < 87.5) { //If the frequency value is less than 87.5 
                radio_frequency = 108.0; //Set radio_frequency variable to 108 
                radio.selectFrequency(radio_frequency); //Send the set value to the radio
            }
            delay(250);
        }
        else if(pressedKey != 'A' || pressedKey != 'B' || pressedKey != 'C' || pressedKey != 'D' || 
                pressedKey != '*' || pressedKey != '#') {
      
            Entered_Frequency[i] = pressedKey; //Save the key pressed in the Entered_Frequency[i] variable
                                             //Here, i variable will take the values 0, 1, 2 and 3 In this way, frequency 
                                             //value can be entered (Ex: When you enter 1060 it will be 106.0 or when you 
                                             //enter 9750 it will be 97.50)
                                       
            lcd.clear();                     //Clear the LCD display 
            lcd.setCursor(7+i, 0);          //Go to column 7+i on first row of LCD display. If i=0, go to column 7. If i=1, 
                                           //go to column 8
      
            lcd.print(Entered_Frequency[i]); //Write the values pressed from the keypad on the LCD display
            i++;                            //Increment i value by one
            if(i > 4) i = 0;               //If the value of i is greater than 4, set the value of i equal to zero.

            for(int i=0; i<4; i++) {        //With the for loop, print the entered values on the LCD Display
                lcd.setCursor(7+i, 0);      //Set Row and Column 
                lcd.print(Entered_Frequency[i]); //Write values on the LCD display 
            }
      
            radio_frequency = atoi(Entered_Frequency); //Convert value entered from keypad to integer
                      
            if(pressedKey == '#') {         //If # is pressed, set i to zero 
                i = 0;
                if(Entered_Frequency[0] == '1') { //If first value of Entered_Frequency variable starts with 1, this means
                                                //The frequency value entered must be something like 1060 
                                     
                    radio_frequency = radio_frequency / 10; //Divide entered frequency by 10 to get actual decimal number
                                                         //If 1060 entered then 1060/10=106.0. If 1062 entered, then 106.2
                                                         //Appropriate frequency values will be determined
                    radio.selectFrequency(radio_frequency); //Send the set value to the radio 
                    lcd.clear();                //Clear the LCD display 
                    lcd.setCursor(0, 0);        //Switch to the first row on the LCD display
                    lcd.print("Radio Frequency: ");
                    lcd.setCursor(0, 1);        //Switch to 2nd row on the LCD display 
                    lcd.print("FM : ");
                    lcd.print(radio_frequency); //Write the frequency value
                    lcd.print(" MHz");
                }
                else {                          //If first value of Entered_Frequency variable starts with number other than 1
                                              //These values can be 8750, 9500 and so on
              
                    radio_frequency = radio_frequency / 100; //Divide entered frequency by 100 to get actual decimal number 
                                                          //If 8750 entered, then value will be 8750/100=87.50
                                                          //Appropriate frequency values will be determined
         
                    radio.selectFrequency(radio_frequency); //Send the set value to the radio 
                    lcd.clear();                //Clear the LCD display 
                    lcd.setCursor(0, 0);        //Switch to the first row on the LCD display
                    lcd.print("Radio Frequency: ");
                    lcd.setCursor(0, 1);        //Switch to 2nd row on the LCD display 
                    lcd.print("FM : ");
                    lcd.print(radio_frequency); //Write the frequency value
                    lcd.print(" MHz");
                }
        
                for(int i=0; i<4; i++)          //By using for loop 
                    Entered_Frequency[i] = '-';  //Turn the data in the entered_Frequency variable to ----
            }
        }          
    }
    delay(250);
}
