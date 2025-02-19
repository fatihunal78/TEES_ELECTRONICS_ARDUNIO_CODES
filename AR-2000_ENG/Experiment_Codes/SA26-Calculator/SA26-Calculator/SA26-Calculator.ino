//SA26 - Calculator

//Add keypad library
#include <Keypad.h>
//Add I2C LCD display library
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); //Define 1602 LCD display

long first_number = 0; //Define the variable to store the first number
long second_number = 0; //Define the variable to store the second number
double result = 0; //Define the variable to store the result

char pressedKey;       //Define the variable to store the key pressed on the keypad
const byte Row = 4;    //Specify how many rows the keypad consists of
const byte Column = 4; //Specify how many columns the keypad consists of
int lcdCursor = 0;     

//Define the keys on the keypad
//Mathematical operations were written instead of A-B-C-D keys
//In this way, we will not need to make extra definitions
char keys[Row][Column] = {
  {'1', '2', '3', '+'},
  {'4', '5', '6', '-'},
  {'7', '8', '9', '*'},
  {'C', '0', '=', '/'}
};

//Define the pins to which the row and column pins of the keypad are connected
byte rowPins[Row] = {7, 6, 5, 4};
byte columnPins[Column] = {3, 2, 1, 0};

//Start the keypad
Keypad keyPad = Keypad(makeKeymap(keys), rowPins, columnPins, Row, Column);

void setup() {
  lcd.begin();        //Start the LCD display
  lcd.backlight();    //Turn ON LCD backlights

  lcd.clear();        //Clear the LCD display
  lcd.setCursor(0, 0);//Switch to first row first column
  lcd.print("TEES ELECTRONICS"); //Write "TEES ELECTRONICS"
  lcd.setCursor(0, 1);//Switch lower row first column
  lcd.print("CALCULATOR");       //Write CALCULATOR
  delay(2000);        //Wait for 2 seconds
  lcd.clear();        //Clear the LCD display
}

void loop() {
  pressedKey = keyPad.getKey(); //Save the key entered from the keypad to the pressedKey variable

  switch (pressedKey) { //Using switch case structure
    case '0' ... '9': //Perform the following operation until one of the operator (+ , - , * , /) keys is pressed
      lcd.setCursor(0, 0); //Go to the first row first column on the LCD display
      first_number = first_number * 10 + (pressedKey - '0'); //Take the necessary actions to obtain the first number
      lcd.print(first_number); //Print the first number on the LCD display
      lcdCursor++;
      break; //End the case

    case '+': //If the pressed key is + (i.e. keypad key A) has been pressed, perform the following operations for addition
      first_number = (result != 0 ? result : first_number); // if the result is other than zero, save the value 
                                                            // in the first_number variable to the result variable
      lcd.print("+"); //print + on the LCD display
      second_number = second_number_function(); //Save the number returned in the second_number_function to the 
                                                //second_number variable
      result = first_number + second_number; //Save the sum of two numbers in the result variable
      lcd.setCursor(0, 1); //Go to the lower row and first column on the LCD display
      lcd.print("="); //Print = on the LCD display
      lcd.print(long(result)); //Print result on the LCD display
      first_number = 0, second_number = 0; //Reset first_number and second_number variables for other operations
      lcdCursor++; //Increment lcdCursor variable by one
      break; //End the case

    case '-': //If the pressed key is - (i.e. keypad key B) has been pressed, perform the following operations for subtraction
      first_number = (result != 0 ? result : first_number); // if the result is other than zero, save the value 
                                                            // in the first_number variable to the result variable
      lcd.print("-"); //Print - on the LCD display
      second_number = second_number_function(); //Save the number returned in the second_number_function to the 
                                                //second_number variable
      result = first_number - second_number; //Save the difference of two numbers in the result variable
      lcd.setCursor(0, 1); //Go to the lower row and first column on the LCD display
      lcd.print("="); //Print = on the LCD display
      lcd.print(long(result)); //Print result on the LCD display
      first_number = 0, second_number = 0; //Reset first_number and second_number variables for other operations
      lcdCursor++; //Increment lcdCursor variable by one
      break; //End the case

    case '*': //If the pressed key * (i.e. keypad key C) has been pressed, perform the following operations for multiplication
      first_number = (result != 0 ? result : first_number); // if the result is other than zero, save the value 
                                                            // in the first_number variable to the result variable
      lcd.print("*"); //Print * on the LCD display
      second_number = second_number_function(); //save the number returned in the second_number_function to the 
                                                //second_number variable
      result = first_number * second_number; //Save the product of two numbers in the result variable
      lcd.setCursor(0, 1); //Go to the lower row and first column on the LCD display
      lcd.print("="); //Print = on the LCD display
      lcd.print(long(result)); //Print result on the LCD display
      first_number = 0, second_number = 0; //Reset first_number and second_number variables for other operations
      lcdCursor++; //Increment lcdCursor variable by one
      break; //End the case

    case '/': //If the pressed key is / (i.e. D key from the keypad) has been pressed, perform the following operations for division
      first_number = (result != 0 ? result : first_number); // if the result is other than zero, save the value 
                                                            // in the first_number variable to the result variable
      lcd.print("/"); //Print / on the LCD display
      second_number = second_number_function(); //Save the product of two numbers in the result variable
      if (second_number == 0) {
        lcd.print("Undefined"); //If the second_number variable is zero, print "undefined" on the LCD display
      } else {
        result = (float) first_number / (float) second_number; //if non-zero, save the division of the first number 
                                                               //and the second number in the result variable
        lcd.setCursor(0, 1); //Go to the lower row and first column on the LCD display
        lcd.print("="); //Print = on the LCD display
        lcd.print(result); //Print result on the LCD display
      }
      first_number = 0, second_number = 0; //Reset first_number and second_number variables for other operations
      lcdCursor++; //Increment lcdCursor variable by one
      break; //End the case

    case 'C': //If the key pressed is C (i.e. the * key from the keypad)
      result = 0; //Reset result variable
      first_number = 0, second_number = 0; //Reset first_number and second_number variables
      lcdCursor = 0; //Reset lcdCursor variable
      lcd.clear(); //Clear the LCD display
      break; //End the case
  }
}

long second_number_function() { //create function to get the second number
  while (1) { //Enter infinite loop
    pressedKey = keyPad.getKey(); //Assign key pressed from keypad to the pressedKey variable
    if (pressedKey >= '0' && pressedKey <= '9') { //If the pressed key is between 0 and 9
      second_number = second_number * 10 + (pressedKey - '0'); //Take the necessary actions to obtain the second number
      lcd.setCursor(lcdCursor + 1, 0);
      lcd.print(second_number); //Print second number on the LCD display
    }
    if (pressedKey == '=') {
      lcdCursor = 0;
      break; //If the key is = ( i.e. # key pressed from the keypad) end infinite loop
    }
  }
  return second_number; //Return the second_number variable obtained
}