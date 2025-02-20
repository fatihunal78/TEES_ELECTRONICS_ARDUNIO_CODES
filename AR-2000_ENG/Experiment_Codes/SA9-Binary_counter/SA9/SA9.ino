//SA9 - Binary counter

#include <LiquidCrystal_I2C.h> //Add I2C LCD library

int LEDs[] = {3,4,5,6,7}; //Define the digital pin numbers to which the LEDs are connected
int buttonPin = 2; //Define the pin number to which the Button is connected 
int number = 0; //Define the variable to store the number

LiquidCrystal_I2C lcd(0x27, 16, 2); //Define 1602 LCD display

void setup() {
    //With for loop, set the pins to which the LEDs are connected as output
    for(int i=0; i<4; i++) {
        pinMode(LEDs[i], OUTPUT);
    }
  
    pinMode(buttonPin, INPUT_PULLUP); //Set the pin to which the Button is connected as input
    lcd.begin(); //Start the LCD
    lcd.backlight(); //Turn ON LCD backlights
  
    lcd.clear(); //Clear the LCD display
    lcd.setCursor(0, 0); //Go to the first line, first character on the LCD
    lcd.print("TEES ELECTRONICS");
    lcd.setCursor(1, 1); //Go to the second line, second character on the LCD display
    lcd.print("BINARY COUNTER");
    delay(3000); //Wait for 3 seconds
    lcd.clear(); //Clear the LCD display
}

void loop() {
    if(digitalRead(buttonPin) == LOW) { //Check if the button is pressed
        while(digitalRead(buttonPin) == LOW); //Wait as long as the Button is pressed
        number++; //increment number variable by one
        if(number > 15) { //If the value of the number variable is over 15
            number = 0; //Reset number value to zero
            lcd.clear(); //Clear the LCD display
        }
    }
    
    switch(number) {
        case 0: //If the number variable is zero
            //Turn OFF all LEDs
            for(int i=0; i<4; i++) {
                digitalWrite(LEDs[i], LOW);
            }
            lcd.clear(); //Clear LCD display
            break;
            
        case 1: //If the number variable is one
            //Turn OFF all LEDs
            for(int i=0; i<4; i++) {
                digitalWrite(LEDs[i], LOW);
            }
            //Show the number in binary on LEDs
            digitalWrite(LEDs[0], HIGH);
      
            lcd.clear(); //Clear the LCD display
            lcd.setCursor(0, 0); //Go to the first line, first character on the LCD
            lcd.print("Decimal: "); //Write on the LCD display
            lcd.print(number); //Write number value on the LCD display
            lcd.setCursor(0, 1); //Go to the second line, first character
            lcd.print("Binary  : ");
            lcd.print("000");
            lcd.print(number, BIN);
            break;
            
        case 2: //If the number value is two
            //Turn OFF all LEDs
            for(int i=0; i<4; i++) {
                digitalWrite(LEDs[i], LOW);
            }
            //Show the number in binary on LEDs  
            digitalWrite(LEDs[1], HIGH);
      
            lcd.clear(); //Clear the LCD display
            lcd.setCursor(0, 0); //Go to the first line, first character on the LCD
            lcd.print("Decimal: "); //Write on the LCD display
            lcd.print(number); //Write number value on the LCD display
            lcd.setCursor(0, 1); //Go to the second line, first character
            lcd.print("Binary  : ");
            lcd.print("00");
            lcd.print(number, BIN);
            break;
            
        case 3: //If the numeric value is three
            //Turn OFF all LEDs
            for(int i=0; i<4; i++) {
                digitalWrite(LEDs[i], LOW);
            }
            //Show the number in binary on LEDs
            digitalWrite(LEDs[0], HIGH);
            digitalWrite(LEDs[1], HIGH);

            lcd.clear(); //Clear the LCD display
            lcd.setCursor(0, 0); //Go to the first line, first character on the LCD
            lcd.print("Decimal: "); //Write on the LCD display
            lcd.print(number); //Write number value on the LCD display
            lcd.setCursor(0, 1); //Go to the second line, first character
            lcd.print("Binary  : ");
            lcd.print("00");
            lcd.print(number, BIN);
            break;
            
        case 4: //If the number value is four
            //Turn OFF all LEDs
            for(int i=0; i<4; i++) {
                digitalWrite(LEDs[i], LOW);
            }
            //Show the number in binary on LEDs
            digitalWrite(LEDs[2], HIGH);

            lcd.clear(); //Clear the LCD display
            lcd.setCursor(0, 0); //Go to the first line, first character on the LCD
            lcd.print("Decimal: "); //Write on the LCD display
            lcd.print(number); //Write number value on the LCD display
            lcd.setCursor(0, 1); //Go to the second line, first character
            lcd.print("Binary  : ");
            lcd.print("0");
            lcd.print(number, BIN);
            break;
            
        case 5: //If the number value is five
            //Turn OFF all LEDs
            for(int i=0; i<4; i++) {
                digitalWrite(LEDs[i], LOW);
            }
            //Show the number in binary on LEDs
            digitalWrite(LEDs[0], HIGH);
            digitalWrite(LEDs[2], HIGH);

            lcd.clear(); //Clear the LCD display
            lcd.setCursor(0, 0); //Go to the first line, first character on the LCD
            lcd.print("Decimal: "); //Write on the LCD display
            lcd.print(number); //Write number value on the LCD display
            lcd.setCursor(0, 1); //Go to the second line, first character
            lcd.print("Binary  : ");
            lcd.print("0");
            lcd.print(number, BIN);
            break;
            
        case 6: //If the number value is six
            //Turn OFF all LEDs
            for(int i=0; i<4; i++) {
                digitalWrite(LEDs[i], LOW);
            }
            //Show the number in binary on LEDs
            digitalWrite(LEDs[1], HIGH);
            digitalWrite(LEDs[2], HIGH);
      
            lcd.clear(); //Clear the LCD display
            lcd.setCursor(0, 0); //Go to the first line, first character on the LCD
            lcd.print("Decimal: "); //Write on the LCD display
            lcd.print(number); //Write number value on the LCD display
            lcd.setCursor(0, 1); //Go to the second line, first character
            lcd.print("Binary  : ");
            lcd.print("0");
            lcd.print(number, BIN);
            break;
            
        case 7: //If the number value is seven
            //Turn OFF all LEDs
            for(int i=0; i<4; i++) {
                digitalWrite(LEDs[i], LOW);
            }
            //Show the number in binary on LEDs
            digitalWrite(LEDs[0], HIGH);
            digitalWrite(LEDs[1], HIGH);
            digitalWrite(LEDs[2], HIGH);

            lcd.clear(); //Clear the LCD display
            lcd.setCursor(0, 0); //Go to the first line, first character on the LCD
            lcd.print("Decimal: "); //Write on the LCD display
            lcd.print(number); //Write number value on the LCD display
            lcd.setCursor(0, 1); //Go to the second line, first character
            lcd.print("Binary  : ");
            lcd.print("0");
            lcd.print(number, BIN);
            break;
            
        case 8: //If the number value is eight
            //Turn OFF all LEDs
            for(int i=0; i<4; i++) {
                digitalWrite(LEDs[i], LOW);
            }
            //Show the number in binary on LEDs
            digitalWrite(LEDs[3], HIGH);

            lcd.clear(); //Clear the LCD display
            lcd.setCursor(0, 0); //Go to the first line, first character on the LCD
            lcd.print("Decimal: "); //Write on the LCD display
            lcd.print(number); //Write number value on the LCD display
            lcd.setCursor(0, 1); //Go to the second line, first character
            lcd.print("Binary  : ");
            lcd.print(number, BIN);
            break;
            
        case 9: //If the number value is nine
            //Turn OFF all LEDs
            for(int i=0; i<4; i++) {
                digitalWrite(LEDs[i], LOW);
            }
            //Show the number in binary on LEDs
            digitalWrite(LEDs[0], HIGH);
            digitalWrite(LEDs[3], HIGH);

            lcd.clear(); //Clear the LCD display
            lcd.setCursor(0, 0); //Go to the first line, first character on the LCD
            lcd.print("Decimal: "); //Write on the LCD display
            lcd.print(number); //Write number value on the LCD display
            lcd.setCursor(0, 1); //Go to the second line, first character
            lcd.print("Binary  : ");
            lcd.print(number, BIN);
            break;
            
        case 10: //If the number value is ten
            //Turn OFF all LEDs
            for(int i=0; i<4; i++) {
                digitalWrite(LEDs[i], LOW);
            }
            //Show the number in binary on LEDs
            digitalWrite(LEDs[1], HIGH);
            digitalWrite(LEDs[3], HIGH);

            lcd.clear(); //Clear the LCD display
            lcd.setCursor(0, 0); //Go to the first line, first character on the LCD
            lcd.print("Decimal: "); //Write on the LCD display
            lcd.print(number); //Write number value on the LCD display
            lcd.setCursor(0, 1); //Go to the second line, first character
            lcd.print("Binary  : ");
            lcd.print(number, BIN);
            break;
            
        case 11: //If the number value is eleven
            //Turn OFF all LEDs
            for(int i=0; i<4; i++) {
                digitalWrite(LEDs[i], LOW);
            }
            //Show the number in binary on LEDs
            digitalWrite(LEDs[0], HIGH);
            digitalWrite(LEDs[1], HIGH);
            digitalWrite(LEDs[3], HIGH);

            lcd.clear(); //Clear the LCD display
            lcd.setCursor(0, 0); //Go to the first line, first character on the LCD
            lcd.print("Decimal: "); //Write on the LCD display
            lcd.print(number); //Write number value on the LCD display
            lcd.setCursor(0, 1); //Go to the second line, first character
            lcd.print("Binary  : ");
            lcd.print(number, BIN);
            break;
            
        case 12: //If the number value is twelve
            //Turn OFF all LEDs
            for(int i=0; i<4; i++) {
                digitalWrite(LEDs[i], LOW);
            }
            //Show the number in binary on LEDs
            digitalWrite(LEDs[2], HIGH);
            digitalWrite(LEDs[3], HIGH);

            lcd.clear(); //Clear the LCD display
            lcd.setCursor(0, 0); //Go to the first line, first character on the LCD
            lcd.print("Decimal: "); //Write on the LCD display
            lcd.print(number); //Write number value on the LCD display
            lcd.setCursor(0, 1); //Go to the second line, first character
            lcd.print("Binary  : ");
            lcd.print(number, BIN);
            break;
            
        case 13: //If the number value is thirteen
            //Turn OFF all LEDs
            for(int i=0; i<4; i++) {
                digitalWrite(LEDs[i], LOW);
            }
            //Show the number in binary on LEDs
            digitalWrite(LEDs[0], HIGH);
            digitalWrite(LEDs[2], HIGH);
            digitalWrite(LEDs[3], HIGH);
      
            lcd.clear(); //Clear the LCD display
            lcd.setCursor(0, 0); //Go to the first line, first character on the LCD
            lcd.print("Decimal: "); //Write on the LCD display
            lcd.print(number); //Write number value on the LCD display
            lcd.setCursor(0, 1); //Go to the second line, first character
            lcd.print("Binary  : ");
            lcd.print(number, BIN);
            break;
            
        case 14: //If the number value is fourteen
            //Turn OFF all LEDs
            for(int i=0; i<4; i++) {
                digitalWrite(LEDs[i], LOW);
            }
            //Show the number in binary on LEDs
            digitalWrite(LEDs[1], HIGH);
            digitalWrite(LEDs[2], HIGH);
            digitalWrite(LEDs[3], HIGH);

            lcd.clear(); //Clear the LCD display
            lcd.setCursor(0, 0); //Go to the first line, first character on the LCD
            lcd.print("Decimal: "); //Write on the LCD display
            lcd.print(number); //Write number value on the LCD display
            lcd.setCursor(0, 1); //Go to the second line, first character
            lcd.print("Binary  : ");
            lcd.print(number, BIN);
            break;
            
        case 15: //If the number value is fifteen
            //Turn OFF all LEDs
            for(int i=0; i<5; i++) {
                digitalWrite(LEDs[i], HIGH);
            }

            lcd.clear(); //Clear the LCD display
            lcd.setCursor(0, 0); //Go to the first line, first character on the LCD
            lcd.print("Decimal: "); //Write on the LCD display
            lcd.print(number); //Write number value on the LCD display
            lcd.setCursor(0, 1); //Go to the second line, first character
            lcd.print("Binary  : ");
            lcd.print(number, BIN);
            break;
    }
    delay(200); //Wait for 200ms
}
