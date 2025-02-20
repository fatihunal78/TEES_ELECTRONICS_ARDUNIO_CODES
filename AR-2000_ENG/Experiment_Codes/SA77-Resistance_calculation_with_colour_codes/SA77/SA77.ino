//SA77 - Resistance calculation with colour codes.ino

#include <LiquidCrystal_I2C.h>    //Add I2C LCD library
#include <Keypad.h>               //Add Keypad library

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
Keypad key_pad = Keypad(makeKeymap(keys), rowPins, columnPins, ROW, COLUMN); 

LiquidCrystal_I2C lcd(0x27, 16, 2);    //Define 1602 LCD display

uint8_t character0[8] = {0x4, 0x4, 0x1F, 0x4, 0x4, 0x1F, 0x0};      // + - characters on top of each other 
uint8_t character1[8] = {0x0, 0xE, 0x11, 0x11, 0x11, 0xA, 0x1B, 0x0}; //ohm symbol 

//Define the variables that will store the values in the bands on the resistor
int first_band;          //The variable to store the first band
int second_band;         //The variable to store the second band
int multiplier_value;    //The variable to store multiplier value (3rd band) 
int tolerance_value;     //The variable to store the tolerance value (4th band) 
float Resistance_Value;  //The variable to store the calculated resistance value

char pressedKey;         //Define the variable to store the key pressed on the keypad 
int value;              //Define the variable that the key pressed from the keypad will be kept as an integer 

int band = 1;           //Define state variable for input of band values respectively in switch case structure 

int buzzerPin = 8;      //Define the pin number to which the Buzzer is connected

void setup() {
    pinMode(buzzerPin, OUTPUT);    //Define the pin number to which the Buzzer is connected
    lcd.begin();                   //Start the LCD display
    lcd.backlight();              //Turn ON the LCD backlights

    lcd.createChar(0, character0); //Create + - character on the top of one another and define it to address 0
    lcd.createChar(1, character1); //Create the ohm symbol and define it to address 1
  
    lcd.clear();                   //Clear the LCD display
    lcd.setCursor(0, 0);          //Switch to the first row 
    lcd.print("TEES ELECTRONICS"); //Write "TEES ELECTRONICS" on the LCD display
    lcd.setCursor(0, 1);          //Switch to the second row
    lcd.print("RESISTANCE CALCULATION"); //Write "RESISTANCE CALCULATION" on the LCD display 
    delay(2000);                  //Wait for 2 seconds
}

void loop() {
    switch(band) {    //Define the switch case structure to ensure that the colours in the bands are entered respectively
        case 1:       //Case 1 (band 1)
            lcd.clear();              //Clear the LCD display 
            lcd.setCursor(0, 0);      //Switch to the first row on the LCD display 
            lcd.print("1st Bant Colour: "); //Write "1st Band Colour: " on the LCD display
            lcd.setCursor(0, 1);      //Switch to the lower row 
            
            while(1) {    //Wait until the data for the colour of the 1st band is entered in an infinite loop 
                Value_Input();        //Call Value_Input to read the entered value 
                first_band = value;   //Save key pressed from keypad to the first_band variable 
                
                if(pressedKey == '#') {    //If # key is pressed from the keypad 
                    //Buzzer makes a beep sound
                    digitalWrite(buzzerPin, HIGH);
                    delay(50);
                    digitalWrite(buzzerPin, LOW);
                    delay(50);
                    break;            //End infinite loop 
                }
            }
            band = 2;                //Make the band variable 2 for 2nd band input
            break;                   //End case 1
  
        case 2:       //In case 2 (band 2)
            lcd.clear();              //Clear the LCD display 
            lcd.setCursor(0, 0);      //Switch to the first row on the LCD display 
            lcd.print("2nd Band Colour: "); //Write "2nd Band Colour: " on the LCD display
            lcd.setCursor(0, 1);      //Switch to the lower row 
            
            while(1) {    //Wait until the data for the colour of the 2nd band is entered in an infinite loop 
                Value_Input();         //Call Value_Input to read the entered value 
                second_band = value;   //Save key pressed from keypad to the second_band variable 
      
                if(pressedKey == '#') {    //If # key is pressed from the keypad 
                    //Buzzer makes a beep sound
                    digitalWrite(buzzerPin, HIGH);
                    delay(50);
                    digitalWrite(buzzerPin, LOW);
                    delay(50);
                    break;             //End infinite loop 
                }    
            }
            band = 3;                 //Make band variable 3 for 3rd band input
            break;                    //End case 2
  
        case 3:       //In case 3 (band 3)
            lcd.clear();              //Clear the LCD display 
            lcd.setCursor(0, 0);      //Switch to the first row on the LCD display 
            lcd.print("Multiplier Colour"); //Write "Multiplier Colour" on the LCD display
            lcd.setCursor(0, 1);      //Switch to the lower row 
            
            while(1) {    //Wait until the data for the colour of the 3rd band is entered in an infinite loop 
                Value_Input();              //Call Value_Input to read the entered value 
                multiplier_value = value;   //Save key pressed from keypad to the multiplier_value variable 
      
                if(pressedKey == '#') {     //If # key is pressed from the keypad 
                    //Buzzer makes a beep sound
                    digitalWrite(buzzerPin, HIGH);
                    delay(50);
                    digitalWrite(buzzerPin, LOW);
                    delay(50);
                    break;             //End infinite loop 
                }
            }
            band = 4;                 //Make band variable 4 for 4th band input
            break;                    //End case 3
  
        case 4:       //In case 4 (band 4)
            lcd.clear();              //Clear the LCD display 
            lcd.setCursor(0, 0);      //Switch to the first row on the LCD display 
            lcd.print("Tolerance Colour"); //Write "Tolerance Colour" on the LCD display
            lcd.setCursor(0, 1);      //Switch to the lower row 
            
            while(1) {    //Wait until the data for the colour of the 4th band is entered in an infinite loop 
                Value_Input();              //Call Value_Input to read the entered value 
                tolerance_value = value;    //Save key pressed from keypad to tolerance_value variable 
                
                if(pressedKey == '#') {     //If # key is pressed from the keypad 
                    //Buzzer makes a beep sound
                    for(int i=0; i<2; i++) {
                        digitalWrite(buzzerPin, HIGH);
                        delay(50);
                        digitalWrite(buzzerPin, LOW);
                        delay(50);
                    }
                    break;            //End infinite loop 
                }
            }
            band = 5;                //Set band variable to 5 for resistance calculation 
            break;                   //End case 4
    
        case 5:       //For calculation process 
            //Calculate resistance value
            Resistance_Value = (10 * first_band + second_band) * pow(10, multiplier_value);  
            lcd.clear();             //Clear LCD display 
            lcd.setCursor(0, 0);     //Switch to the first row on the LCD display 
            lcd.print("Resistance: "); //Write "Resistance:" on the LCD display
            
            //To write KOhm if the calculated resistance value is greater than or equal to 1000 and less than 1000000
            if(Resistance_Value >= 1000 && Resistance_Value < 1000000) { 
                Resistance_Value = Resistance_Value / 1000;  //Divide the calculated resistance value by 1000
                lcd.print(Resistance_Value);                 //Print resistance value on the LCD display 
                lcd.print(" k");                            //write k on the LCD display 
                lcd.print((char)1);                         //Write Ohm symbol on the LCD display 
            } 
            //To write Mohm if the calculated resistance value is greater than or equal to 1000000
            else if(Resistance_Value >= 1000000) { 
                Resistance_Value = Resistance_Value / 1000000; //Divide the calculated resistance value by 1000000
                lcd.print(Resistance_Value);                  //Print resistance value on the LCD display 
                lcd.print("M");                              //Write M on the LCD display 
                lcd.print((char)1);                          //Write Ohm symbol on the LCD display 
            }
            else {    //If the calculated resistance value is less than 1000 
                lcd.print(Resistance_Value);                  //Print Resistance value on the LCD display 
                lcd.print(" ");                              //Leave a space 
                lcd.print((char)1);                          //Write Ohm symbol on the LCD display 
            }
            
            lcd.setCursor(0, 1);      //Switch to 2nd row on the LCD display 
            lcd.print("Tolerance: ");  //Write "Tolerance: " on the LCD display 
            
            //If tolerance_value is 10, that is, if the 'A' key is pressed from the keypad
            if(tolerance_value == 10) {
                lcd.print((char)0);    //Type + - on each other on the LCD display
                lcd.print(" 5%");      //Write 5% on the LCD display
            }
            //If tolerance_value is 11, that is, if the 'B' key is pressed from the keypad
            if(tolerance_value == 11) {
                lcd.print((char)0);    //Type + - on each other on the LCD display
                lcd.print(" 10%");     //write 10% on the LCD display
            }  
            
            while(1) {                 //Enter infinite loop 
                Value_Input();         //Call Value_Input() function 
                if(pressedKey == '#')  //Wait for # key to be pressed for new resistance calculation
                    break;             
            }
            //Make band variable 1 for new resistance calculation and go to case 1 in the switch case structure
            band = 1;                  
            break;                     //End case 5 
    }
}

int Value_Input() {    //Create Value_Input() function to detect keys pressed from the keypad
    pressedKey = key_pad.getKey();    //Save the key pressed from the keypad to the pressedKey character
    
    if(pressedKey) {                  //If any key is pressed
        if(pressedKey == '0') { 
            lcd.setCursor(0, 1); 
            lcd.print("Black      "); 
            value = 0; 
        }
        else if(pressedKey == '1') { 
            lcd.setCursor(0, 1); 
            lcd.print("Brown      "); 
            value = 1; 
        }
        else if(pressedKey == '2') { 
            lcd.setCursor(0, 1); 
            lcd.print("Red      "); 
            value = 2; 
        }
        else if(pressedKey == '3') { 
            lcd.setCursor(0, 1); 
            lcd.print("Orange      "); 
            value = 3; 
        }
        else if(pressedKey == '4') { 
            lcd.setCursor(0, 1); 
            lcd.print("Yellow      "); 
            value = 4; 
        }
        else if(pressedKey == '5') { 
            lcd.setCursor(0, 1); 
            lcd.print("Green      "); 
            value = 5; 
        }
        else if(pressedKey == '6') { 
            lcd.setCursor(0, 1); 
            lcd.print("Blue      "); 
            value = 6; 
        }
        else if(pressedKey == '7') { 
            lcd.setCursor(0, 1); 
            lcd.print("Purple      "); 
            value = 7; 
        }
        else if(pressedKey == '8') { 
            lcd.setCursor(0, 1); 
            lcd.print("Grey      "); 
            value = 8; 
        }
        else if(pressedKey == '9') { 
            lcd.setCursor(0, 1); 
            lcd.print("White      "); 
            value = 9; 
        }
        else if(pressedKey == 'A') { 
            lcd.setCursor(0, 1); 
            lcd.print("Gold      "); 
            value = 10; 
        }
        else if(pressedKey == 'B') { 
            lcd.setCursor(0, 1); 
            lcd.print("Silver      "); 
            value = 11; 
        }
    }
    else return -1;
}
