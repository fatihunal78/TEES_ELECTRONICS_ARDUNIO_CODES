//SA91 - FM radio

#include <Wire.h>                                     //Add communication library
#include <TEA5767N.h>                                //Add FM radio library  
#include <LiquidCrystal_I2C.h>                       //Add I2C LCD library

LiquidCrystal_I2C lcd(0x27, 16, 2);                 //Define 1602 LCD display

int searchButton = 2;                                //Button for FM RADIO channel search 
int resetButton = 3;                                 //Button to switch to FM Radio first channel (87.50)

TEA5767N radio = TEA5767N();                        //Create an object named radio
float radio_frequency = 87.5;                        //Define the variable named radio_frequency and set its initial value to 87.5

void setup() {
    pinMode(searchButton, INPUT_PULLUP);             //Set the pin to which the searchButton is connected as input
    pinMode(resetButton, INPUT_PULLUP);              //Set the pin to which the resetButton is connected as input
  
    lcd.begin();                                     //Start the LCD display
    lcd.backlight();                                //Turn ON the LCD backlights
    lcd.clear();                                    //Clear the LCD display 
    delay(250); 
    radio.selectFrequency(radio_frequency);         //Set radio to 87.5
    delay(250);
    radio.setStereoReception();
    lcd.setCursor(0, 0);                           //Switch to the first row on the LCD display
    lcd.print("TEES ELECTRONICS");
    lcd.setCursor(0, 1);                           //Switch to 2nd row on the LCD display 
    lcd.print("    FM RADIO    ");                 //Write "FM RADIO" on the LCD display
    delay(2000);                                   //Wait for 2 seconds 
    lcd.clear(); 
    lcd.setCursor(0, 0);                          //Switch to the first row on the LCD display
    lcd.print("Radio Frequency");
    lcd.setCursor(0, 1);                          //Switch to 2nd row on the LCD display 
    lcd.print("FM : ");
    lcd.print(radio_frequency);                   //Write the frequency value
    lcd.print(" MHz");
}
 
void loop() {
    if(digitalRead(searchButton) == LOW) {         //If the button is pressed, perform the following actions to change the channel 
        radio_frequency += 0.1;                    //Increment the radio_frequency variable by 0.1 
        radio.selectFrequency(radio_frequency);    //Write the radio_frequency variable to the radio and open the channel
    
        lcd.clear(); 
        lcd.setCursor(0, 0);                      //Switch to the first row on the LCDs screen
        lcd.print("Radio Frequency");
        lcd.setCursor(0, 1);                      //Switch to 2nd row on the LCD display 
        lcd.print("FM : ");
        lcd.print(radio_frequency);               //Write the frequency value
        lcd.print(" MHz");
  
        if(radio_frequency > 108.0) {
            radio_frequency = 87.5; 
            radio.selectFrequency(radio_frequency);
        }
    }

    if(digitalRead(resetButton) == LOW) {          //If the reset button is pressed 
        radio_frequency = 87.5;                    //Set radio_frequency variable to 87.5 MHz
        radio.selectFrequency(radio_frequency);    //Write the incremented radio_frequency variable to the radio and open the channel
  
        lcd.clear(); 
        lcd.setCursor(0, 0);                      //Switch to the first row on the LCDs screen
        lcd.print("Radio Frequency");
        lcd.setCursor(0, 1);                      //Switch to 2nd row on the LCD display 
        lcd.print("FM : ");
        lcd.print(radio_frequency);               //Write the frequency value
        lcd.print(" MHz");
    }
    delay(250);
}
