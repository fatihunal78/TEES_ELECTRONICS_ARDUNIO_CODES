//SA92 - FM Discotheque

#include <Wire.h>              //Add communication library
#include <TEA5767N.h>         //Add FM radio library
#include <LiquidCrystal_I2C.h> //Add I2C LCD library
#include <FreqCount.h>         //Add library required to measure frequency 

LiquidCrystal_I2C lcd(0x27, 16, 2);  //Define 1602 LCD display

int red_LED = 11;              //Define the pin number to which the Disco Light module Red LED is connected
int yellow_LED = 10;           //Define the pin number to which the Disco Light module Yellow LED is connected
int green_LED = 9;             //Define the pin number to which the Disco Light module Green LED is connected 
int blue_LED = 8;              //Define the pin number to which the Disco Light module Blue LED is connected

int forward_searchButton = 3;   //Define the pin to which the button is connected for FM RADIO forward channel search
int backward_searchButton = 2;  //Define the pin to which the button is connected for FM RADIO backward channel search
float frequency;               //Define the variable to store the frequency value
TEA5767N radio = TEA5767N();   //Create an object named radio
float radio_frequency = 87.5;   //Define the variable named radio_frequency and set its initial value to 87.5

void setup() {
    pinMode(forward_searchButton, INPUT_PULLUP);  //The pin to which the forward_searchButton is connected is set as input pin
    pinMode(backward_searchButton, INPUT_PULLUP); //The pin to which the backward_searchButton is connected is set as input pin
    pinMode(red_LED, OUTPUT);                     //Set the pin to which the Red LED is connected as output
    pinMode(yellow_LED, OUTPUT);                  //Set the pin to which the Yellow LED is connected as output
    pinMode(green_LED, OUTPUT);                   //Set the pin to which the Green LED is connected as output
    pinMode(blue_LED, OUTPUT);                    //Set the pin to which the Blue LED is connected as the output
  
    FreqCount.begin(100);                        //Start frequency measurement and take 100 sample values 
    lcd.begin();                                 //Start the LCD display
    lcd.backlight();                            //Turn ON the LCD backlights
    lcd.clear();                                //Clear the LCD display 
    delay(250); 
    radio.selectFrequency(radio_frequency);     //Set radio to 87.5
    delay(250);
    radio.setStereoReception();
    lcd.setCursor(0, 0);                        //Switch to the first row on the LCD display
    lcd.print("TEES ELECTRONICS");
    lcd.setCursor(0, 1);                        //Switch to 2nd row on the LCD display 
    lcd.print("    FM RADIO    ");              //Write "FM RADIO" on the LCD display
    delay(2000);                                //Wait for 2 seconds 
    lcd.clear(); 
    lcd.setCursor(0, 0);                        //Switch to the first row on the LCD display
    lcd.print("Radio Frequency");
    lcd.setCursor(0, 1);                        //Switch to 2nd row on the LCD display 
    lcd.print("FM : ");
    lcd.print(radio_frequency);                 //Write the frequency value
    lcd.print(" MHz");
}
 
void loop() {
    if(digitalRead(forward_searchButton) == LOW) { //If the forward channel search button is pressed, perform the following 
                                                  //actions to change the channel
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
  
    if(digitalRead(backward_searchButton) == LOW) { //If the backward channel search button is pressed 
        radio_frequency -= 0.1;                     //Decrement the radio_frequency variable by 0.1 
        radio.selectFrequency(radio_frequency);     //Write the radio_frequency variable to the radio and open the channel
     
        if(radio_frequency < 87.5) {
            radio_frequency = 108.0; 
            radio.selectFrequency(radio_frequency);
        }
        
        lcd.clear(); 
        lcd.setCursor(0, 0);                       //Switch to the first row on the LCDs screen
        lcd.print("Radio Frequency");
        lcd.setCursor(0, 1);                       //Switch to 2nd row on the LCD display 
        lcd.print("FM : ");
        lcd.print(radio_frequency);                //Write the frequency value
        lcd.print(" MHz");
    }

    if(FreqCount.available()) { 
        frequency = FreqCount.read()*10;           //Perform frequency reading on pin 5 
    }
    
    //Proportion the values between 20 and 2000 in the frequency variable to the values between 0 and 16
    int proportion = map(frequency, 20, 2000, 0, 16); 

    switch(proportion) {
        case 0:                                    //When proportion value is 0 
            //Turn OFF all LEDs 
            digitalWrite(red_LED, LOW);
            digitalWrite(yellow_LED, LOW);
            digitalWrite(green_LED, LOW);
            digitalWrite(blue_LED, LOW);
            break;

        case 1:                                    //When proportion value is 1 
            //Turn ON the Red LED, turn OFF the others 
            digitalWrite(red_LED, HIGH);
            digitalWrite(yellow_LED, LOW);
            digitalWrite(green_LED, LOW);
            digitalWrite(blue_LED, LOW); 
            break;

        case 2:                                    //When proportion value is 2 
            //Turn ON the Yellow LED, turn OFF the others. 
            digitalWrite(red_LED, LOW);
            digitalWrite(yellow_LED, HIGH);
            digitalWrite(green_LED, LOW);
            digitalWrite(blue_LED, LOW);
            break;

        case 3:                                    //When proportion value is 3 
            //Turn ON the Green LED, turn OFF the others 
            digitalWrite(red_LED, LOW);
            digitalWrite(yellow_LED, LOW);
            digitalWrite(green_LED, HIGH);
            digitalWrite(blue_LED, LOW);
            break;

        case 4:                                    //When proportion value is 4 
            //Turn ON the Blue LED, turn OFF the others 
            digitalWrite(red_LED, LOW);
            digitalWrite(yellow_LED, LOW);
            digitalWrite(green_LED, LOW);
            digitalWrite(blue_LED, HIGH);
            break;

        case 5:                                    //When proportion value is 5 
            //Turn ON the Red and Yellow LED, turn OFF the others 
            digitalWrite(red_LED, HIGH);
            digitalWrite(yellow_LED, HIGH);
            digitalWrite(green_LED, LOW);
            digitalWrite(blue_LED, LOW);
            break;

        case 6:                                    //When proportion value is 6 
            //Turn ON the Red and Green LED, turn OFF the others 
            digitalWrite(red_LED, HIGH);
            digitalWrite(yellow_LED, LOW);
            digitalWrite(green_LED, HIGH);
            digitalWrite(blue_LED, LOW);
            break;

        case 7:                                    //When proportion value is 7 
            //Turn ON the Red and Blue LED, turn OFF the others 
            digitalWrite(red_LED, HIGH);
            digitalWrite(yellow_LED, LOW);
            digitalWrite(green_LED, LOW);
            digitalWrite(blue_LED, HIGH);
            break;

        case 8:                                    //When proportion value is 8 
            //Turn ON the Yellow and Green LED, turn OFF the others 
            digitalWrite(red_LED, LOW);
            digitalWrite(yellow_LED, HIGH);
            digitalWrite(green_LED, HIGH);
            digitalWrite(blue_LED, LOW);
            break;

        case 9:                                    //When proportion value is 9 
            //Turn ON the Yellow and Blue LED, turn OFF the others 
            digitalWrite(red_LED, LOW);
            digitalWrite(yellow_LED, HIGH);
            digitalWrite(green_LED, LOW);
            digitalWrite(blue_LED, HIGH);
            break;

        case 10:                                   //When proportion value is 10 
            //Turn ON the Green and Blue LED, turn OFF the others 
            digitalWrite(red_LED, LOW);
            digitalWrite(yellow_LED, LOW);
            digitalWrite(green_LED, HIGH);
            digitalWrite(blue_LED, HIGH);
            break;

        case 11:                                   //When proportion value is 11 
            //Turn ON the Red, Yellow and Green LED and turn OFF the others 
            digitalWrite(red_LED, HIGH);
            digitalWrite(yellow_LED, HIGH);
            digitalWrite(green_LED, HIGH);
            digitalWrite(blue_LED, LOW);
            break;

        case 12:                                   //When proportion value is 12 
            //Turn ON the Red, Yellow and Blue LED, turn OFF the others 
            digitalWrite(red_LED, HIGH);
            digitalWrite(yellow_LED, HIGH);
            digitalWrite(green_LED, LOW);
            digitalWrite(blue_LED, HIGH);
            break;

        case 13:                                   //When proportion value is 13 
            //Turn ON the Red, Green and Blue LED, turn OFF the others 
            digitalWrite(red_LED, HIGH);
            digitalWrite(yellow_LED, LOW);
            digitalWrite(green_LED, HIGH);
            digitalWrite(blue_LED, HIGH);
            break;

        case 14:                                   //When proportion value is 14 
            //Turn ON the Yellow, Green and Blue LED, turn OFF the others 
            digitalWrite(red_LED, LOW);
            digitalWrite(yellow_LED, HIGH);
            digitalWrite(green_LED, HIGH);
            digitalWrite(blue_LED, HIGH);
            break;

        case 15:                                   //When proportion value is 15 
            //Turn ON all LEDs
            digitalWrite(red_LED, HIGH);
            digitalWrite(yellow_LED, HIGH);
            digitalWrite(green_LED, HIGH);
            digitalWrite(blue_LED, HIGH);
            break;
    }
    delay(10);
}
