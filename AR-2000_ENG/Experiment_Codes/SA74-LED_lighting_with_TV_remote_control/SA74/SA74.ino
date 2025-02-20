//SA74 - LED lighting with TV remote control

#include <IRremote.h>          //Add IR receiver library
#include <LiquidCrystal_I2C.h> //Add I2C LCD library

int IRPin = 3;                 //Define the pin to which the IR receiver signal leg is connected
int LEDPin = 7;               //Define the pin to which the LED is connected
int buttonPin = 2;            //Define the pin number to which the Button is connected

int LEDStatus = 0;            //Define the variable to store the LED status either ON or OFF

unsigned long Pressed_Key;     //Define the variable to save the pressed key

LiquidCrystal_I2C lcd(0x27, 16, 2);  //Define 1602 LCD display

IRrecv IRReceive(IRPin);      //Define an IR Receiver named IRReceive
decode_results result;        //Define variable to store values received from IR receiver

void setup() {
    pinMode(LEDPin, OUTPUT);         //Set the pin to which the LED is connected as output
    pinMode(buttonPin, INPUT_PULLUP); //Set the pin to which the Button is connected as input
    
    lcd.begin();                     //Start the LCD display
    lcd.backlight();                 //Turn ON the LCD backlights
    lcd.clear();                     //Clear the LCD display
    
    IRReceive.enableIRIn();          //Start IR receiver

    lcd.setCursor(0, 0);             //Switch to the first row on the LCD display 
    lcd.print("TURN ON LED WITH");    //Write on the LCD display
    lcd.setCursor(0, 1);             //Switch to the lower row 
    lcd.print("TV REMOTE CONTROL");   //Write on the LCD display 
    delay(3000);                     //Wait for 3 seconds 
    lcd.clear();                     //Clear the LCD display 
}

void loop() {
    while(1) {
        lcd.setCursor(0, 0);         //Switch to the first row on the LCD display 
        lcd.print("Press any key on "); 
        lcd.setCursor(0, 1);         //Switch to the lower row 
        lcd.print("TV remote control"); //Write the messge on the LCD display 
         
        //Check if there is any data coming from IR receiver
        if(IRReceive.decode(&result)) { //If data has arrived
            if(&result.value) {
                Pressed_Key = result.value;
                lcd.clear();
                lcd.print("0x");
                lcd.print(Pressed_Key, HEX); //Send incoming data to the LCD display in HEX format
                break;
            }
        }
    }

    while(1) {
        if(digitalRead(buttonPin) == LOW) break; //If the button is pressed, exit the infinite loop
         
        if(IRReceive.decode(&result)) { //If data has arrived
            if(result.value == Pressed_Key && LEDStatus == 1) {
                digitalWrite(LEDPin, HIGH);
                LEDStatus = 0;
                lcd.clear();
                lcd.print("LED IS ON");
            }
            else if(result.value == Pressed_Key && LEDStatus == 0) {
                digitalWrite(LEDPin, LOW);
                LEDStatus = 1;
                lcd.clear();
                lcd.print("LED IS OFF");
            }
            IRReceive.resume();          //Reset IR receiver to get other values
        }
        delay(50);                      //Wait for 50ms
    }
}
