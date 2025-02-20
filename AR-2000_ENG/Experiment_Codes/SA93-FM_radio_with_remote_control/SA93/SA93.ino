//SA93 - FM radio with remote control

#include <Wire.h>                                     //Add libraries
#include <TEA5767N.h>
#include <LiquidCrystal_I2C.h>                       //Add I2C LCD library  
#include <IRremote.h>                                //Add IR receiver library

#define upKey    0xFF18E7                            //IR Control up arrow key 
#define downKey  0xFF4AB5                            //IR Control down arrow key 
#define okKey    0xFF38C7                            //IR Control OK key

LiquidCrystal_I2C lcd(0x27, 16, 2);                 //Define 1602 LCD display

int IRPin = 2;                                       //Define the pin to which the IR receiver signal leg is connected

IRrecv IRReceive(IRPin);                            //Define an IR Receiver named IRReceive
decode_results result;                               //Define variable to store values received from IR receiver

TEA5767N radio = TEA5767N();
float radio_frequency = 87.5;

void setup() {
    IRReceive.enableIRIn();                          //Start IR receiver 
    
    lcd.begin();                                     //Start the LCD display
    lcd.backlight();                                 //Turn ON the LCD backlights
    lcd.clear();                                     //Clear the LCD display
    
    delay(250);
    radio.selectFrequency(radio_frequency);
    delay(250);
    radio.setMonoReception();
    
    lcd.setCursor(0, 0);                            //Switch to the first row on the LCD display
    lcd.print("TEES ELECTRONICS");
    lcd.setCursor(0, 1);                            //Switch to 2nd row on the LCD display 
    lcd.print("    FM RADIO    ");                  //Write "FM RADIO" on the LCD display
    
    lcd.clear();
    lcd.setCursor(0, 0);                            //Switch to the first row on the LCD display
    lcd.print("Radio Frequency");
    lcd.setCursor(0, 1);                            //Switch to 2nd row on the LCD display 
    lcd.print("FM : ");
    lcd.print(radio_frequency);                      //Write the frequency value
    lcd.print(" MHz");
}

void loop() {
    if(IRReceive.decode(&result)) {                 //Check if there is any data coming from the IR receiver
        if(result.value == okKey) {                 //if OK key is pressed to bring it back to initial position
            radio_frequency = 87.5;                  //Set the radio_frequency variable to the first radio channel
            radio.selectFrequency(radio_frequency);  //Write the radio_frequency variable to the radio and open the channel
            
            lcd.clear();                            //Clear the LCD display
            lcd.setCursor(0, 0);                    //Switch to the first row on the LCD display
            lcd.print("Radio Frequency: ");
            lcd.setCursor(0, 1);                    //Switch to 2nd row on the LCD display 
            lcd.print("FM : ");
            lcd.print(radio_frequency);             //Write the frequency value
            lcd.print(" MHz");
        }
        
        if(result.value == upKey) {                 //If Up arrow key is pressed 
            radio_frequency += 0.1;                 //Increment the radio_frequency variable by 0.1 
            radio.selectFrequency(radio_frequency); //Write the radio_frequency variable to the radio and open the channel
            
            lcd.clear();                           //Clear the LCD display
            lcd.setCursor(0, 0);                   //Switch to the first row on the LCD display
            lcd.print("Radio Frequency: ");
            lcd.setCursor(0, 1);                   //Switch to 2nd row on the LCD display 
            lcd.print("FM : ");
            lcd.print(radio_frequency);            //Write the frequency value
            lcd.print(" MHz");
            
            if(radio_frequency > 108.0) {          //If the frequency value is greater than 108 
                radio_frequency = 87.5;            //Set the radio_frequency value to 87.5 
                radio.selectFrequency(radio_frequency); //Send the set value to the radio
            }
            delay(250);
        }
        else if(result.value == downKey) {         //If Down arrow key is pressed 
            radio_frequency -= 0.1;                //Decrement the radio_frequency variable by 0.1
            radio.selectFrequency(radio_frequency); //Write the radio_frequency variable to the radio and open the channel
            
            lcd.clear();                          //Clear LCD display 
            lcd.setCursor(0, 0);                  //Switch to the first row on the LCD display
            lcd.print("Radio Frequency: ");
            lcd.setCursor(0, 1);                  //Switch to 2nd row on the LCD display 
            lcd.print("FM : ");
            lcd.print(radio_frequency);           //Write the frequency value
            lcd.print(" MHz");
            
            if(radio_frequency < 87.5) {          //If the frequency value is less than 87.5 
                radio_frequency = 108.0;          //Set radio_frequency variable to 108 
                radio.selectFrequency(radio_frequency); //Send the set value to the radio
            }
            delay(250);
        }
        IRReceive.resume();                       //Reset IR receiver to get other values
        delay(250);
    }
}
