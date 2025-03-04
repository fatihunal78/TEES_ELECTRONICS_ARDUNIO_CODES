//SA68 - Tennis game

#include <LedControl.h>          //Add LedControl library 
#include <LiquidCrystal_I2C.h>  //Add I2C LCD library

LiquidCrystal_I2C lcd(0x27, 16, 2);         //Define 1602 LCD display
                                    
LedControl lc = LedControl(4, 2, 3, 1);     //LED Matrix ( DIN pin: 4; CLK pin: 2; CS pin: 3) is connected 

int potVR2 = A1;                //Define the pin to which the potentiometer VR2 is connected
int potVR1 = A0;                //Define the pin to which the potentiometer VR1 is connected
int speakerPin = 7;             //Define the pin number to which the Speaker is connected
int VR1ReadValue = 0;           //Define the variable in which the values read from the VR1 potentiometer will be stored 
int VR2ReadValue = 0;           //Define the variable in which the values read from the VR2 potentiometer will be stored
int proportionVR1;              //Define the variable in which the values read from the VR1 potentiometer will be proportioned 
int proportionVR2;              //Define the variable in which the values read from the VR2 potentiometer will be proportioned
int player1_score = 0;          //Define the variable to store player 1's score 
int player2_score = 0;          //Define the variable to store player 2's score 
int x = 2;                      //Coordinate of the ball on the x-axis 
int y = 4;                      //Coordinate of the ball on the y-axis 
boolean down_up = true;         //Variable defined for up and down movement of the ball 
boolean right_left = false;     //Variable defined for the right and left movement of the ball
int game_speed = 300;           //Game start speed is set to 300 

unsigned long counter = 0;

int player1_leftMove = 4;
int player1_midMove = 0;        //Fixed syntax error: intplayer1_midMove -> int player1_midMove
int player1_rightMove = 5;
int player2_leftMove = 4;
int player2_midMove = 0;
int player2_rightMove = 5;

byte New[] = {
    B00000000,
    B01111110,
    B00010010,
    B00011110,
    B00000000,
    B01111110,
    B01000000,
    B01000000
};

void setup() {
    pinMode(potVR1, INPUT);         //Set Analog A1 pin as input 
    pinMode(potVR2, INPUT);         //Set analog A0 pin as input
    pinMode(speakerPin, OUTPUT);    //Set the pin to which the Speaker is connected as output
  
    lcd.begin();                    //Start the LCD display
    lcd.backlight();               //Turn ON the LCD backlights
    lcd.clear();                   //Clear the LCD display
  
    lc.shutdown(0, false);
    lc.setIntensity(0, 3);         //Set LED Matrix display brightness to 3
    lc.clearDisplay(0);       //Clear the LED Matrix screen

    lcd.setCursor(0, 0);           //Move cursor to the first row of the LCD display
    lcd.print("TEES ELECTRONICS"); //Write "TEES ELECTRONICS" on the LCD display
    lcd.setCursor(0, 1);           //Switch to the lower row
    lcd.print(" TENNIS GAME ");    //Write "TENNIS GAME" on the LCD display
    delay(1500);                   //Wait for 1.5 second
    lcd.clear();                   //Clear the LCD display 
}

void loop() {
    VR1ReadValue = analogRead(potVR1);    //Read the values in the analog pin to which the VR1 potentiometer is connected 
    VR2ReadValue = analogRead(potVR2);    //Read the values in the analog pin to which the VR2 potentiometer is connected 

    proportionVR1 = map(VR1ReadValue, 0, 1023, 0, 6);    //Proportion the values read from the VR1 potentiometer between 0 and 6 
    proportionVR2 = map(VR2ReadValue, 0, 1023, 0, 6);    //Proportion the values read from the VR2 potentiometer between 0 and 6 

    player1_leftMove = proportionVR1 - 1;
    player1_midMove = proportionVR1;
    player1_rightMove = proportionVR1 + 1;
    player2_leftMove = proportionVR2 - 1;
    player2_midMove = proportionVR2;
    player2_rightMove = proportionVR2 + 1;

    lc.setLed(0, x, y, true);
    lc.setLed(0, player1_leftMove, 0, true);
    lc.setLed(0, player1_midMove, 0, true);
    lc.setLed(0, player1_rightMove, 0, true);
    lc.setLed(0, player2_leftMove, 7, true);
    lc.setLed(0, player2_midMove, 7, true);
    lc.setLed(0, player2_rightMove, 7, true);
   
    if(x == player2_rightMove && y == 6) { 
        down_up = true; 
        tone(speakerPin, 800); 
        delay(20); 
        noTone(speakerPin); 
        delay(20); 
    }
    if(x == player2_midMove && y == 6) { 
        down_up = true; 
        tone(speakerPin, 800); 
        delay(20); 
        noTone(speakerPin); 
        delay(20); 
    }
    if(x == player2_leftMove && y == 6) { 
        down_up = true; 
        tone(speakerPin, 800); 
        delay(20); 
        noTone(speakerPin); 
        delay(20); 
    }
  
    if(x == player1_rightMove && y == 1) { 
        down_up = false; 
        tone(speakerPin, 1800); 
        delay(20); 
        noTone(speakerPin); 
        delay(20); 
    }
    if(x == player1_leftMove && y == 1) { 
        down_up = false; 
        tone(speakerPin, 1800); 
        delay(20); 
        noTone(speakerPin); 
        delay(20); 
    }
    if(x == player1_midMove && y == 1) { 
        down_up = false; 
        tone(speakerPin, 1800); 
        delay(20); 
        noTone(speakerPin); 
        delay(20); 
    }
  
    if(x < 1) { 
        right_left = false; 
    }
  
    if(right_left == false) {
        x++;
    }
    if(x > 7) {
        right_left = true; 
        x--;
    }
    if(right_left == true) { 
        x--; 
    }
 
    if(down_up == false) {
        y++;
    }
    if(down_up == true) {
        y--;
    }
    if(y == -1 || y == 8) {
        lcd.clear();
    
        if(y == -1) {                //If the ball touches the upper base 
            player2_score++;         //Increment player2_score variable by one 
        }
        else if(y == 8) {           //If the ball touches the lower base 
            player1_score++;         //Increment player1_score variable by one 
        }
    
        lcd.setCursor(0, 0);
        lcd.print("1st Player: ");
        lcd.setCursor(11, 0);        //Set LCD cursor to column 11 
        lcd.print(player1_score); 
        lcd.setCursor(0, 1);
        lcd.print("2nd Player: ");
        lcd.setCursor(11, 1);        //Set LCD cursor to column 11 
        lcd.print(player2_score); 

        //Set variables to initial state 
        x = 2;
        y = 4;
        player1_leftMove = 3;
        player1_rightMove = 4;
        player2_rightMove = 4;
        player2_leftMove = 3;
    
        lost();                      //Call lost() function 
        for(int i = 0; i < 3; i++) {
            tone(speakerPin, 1200);
            delay(30);
            noTone(speakerPin);
            delay(30);
        }
        delay(1000);                 //Wait for 1 second 
    }

    counter++;
    if(counter % 30 == 0) {
        game_speed = game_speed - 20;
        if(game_speed < 100) 
            game_speed = 100;
    }
    delay(game_speed);
    lc.clearDisplay(0);
}

void lost() {                        //Define function for LED flashing effect in sequence when either player scores
    lc.clearDisplay(0);
    lc.setColumn(0, 7, B11111111);
    delay(10);
    lc.setColumn(0, 6, B11111111);
    delay(10);
    lc.setColumn(0, 5, B11111111);
    delay(10);
    lc.setColumn(0, 4, B11111111);
    delay(10);
    lc.setColumn(0, 3, B11111111);
    delay(10);
    lc.setColumn(0, 2, B11111111);
    delay(10);
    lc.setColumn(0, 1, B11111111);
    delay(10);
    lc.setColumn(0, 0, B11111111);
    delay(10);
    lc.setColumn(0, 7, B00000000);
    delay(10);
    lc.setColumn(0, 6, B00000000);
    delay(10);
    lc.setColumn(0, 5, B00000000);
    delay(10);
    lc.setColumn(0, 4, B00000000);
    delay(10);
    lc.setColumn(0, 3, B00000000);
    delay(10);
    lc.setColumn(0, 2, B00000000);
    delay(10);
    lc.setColumn(0, 1, B00000000);
    delay(10);
    lc.setColumn(0, 0, B00000000);
    delay(10);
    game_speed = 300;
}
