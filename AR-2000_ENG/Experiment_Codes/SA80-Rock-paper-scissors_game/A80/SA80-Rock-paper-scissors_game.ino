//SA80 - Rock-paper-scissors game

#include <LiquidCrystal_I2C.h>                    //Add I2C LCD library

LiquidCrystal_I2C lcd(0x27, 16, 2);              //Define 1602 LCD display

int RGB_Red = 5;                                  //Define the pin number to which the RGB Red LED is connected 
int RGB_Green = 4;                               //Define the pin number to which the RGB Green LED is connected 
int RGB_Blue = 3;                                //Define the pin number to which the RGB Blue LED is connected 

int First_Player_Button = 6;                      //Define the pin number to which the first player button is connected
int Second_Player_Button = 2;                     //Define the pin number to which the second player button is connected 

int speakerPin = 8;                              //Define the pin number to which the Speaker is connected

int counter = 1;                                  //Counter variable is defined
int firstValue;                                   //Define the variable to store the data of the first player 
int secondValue;                                  //Define the variable to store the data of the second player 

void setup() {
    //Set the pins to which LEDs on RGB LED are connected as output
    pinMode(RGB_Red, OUTPUT);
    pinMode(RGB_Green, OUTPUT);
    pinMode(RGB_Blue, OUTPUT);
    
    //Set the pin to which the button is connected as input
    pinMode(First_Player_Button, INPUT);
    pinMode(Second_Player_Button, INPUT_PULLUP);
    
    pinMode(speakerPin, OUTPUT);                  //Set the pin to which the Speaker is connected as output 

    lcd.begin();                                  //Start the LCD display
    lcd.backlight();                             //Turn ON the LCD backlights
    lcd.clear();                                 //Clear the LCD display

    lcd.setCursor(0, 0);                         //Switch to the first row on the LCDs screen 
    lcd.print("TEES ELECTRONICS");
    lcd.setCursor(0, 1);                         //Switch to the lower row
    lcd.print("ROCK PAPER SCISSORS");
    delay(2000);                                 //Wait for 2 seconds
    lcd.clear();                                 //Clear the LCD display 
    randomSeed(analogRead(A0)); 
}

void loop() {
    //If the counter variable is 1, it means that it is the first player's turn to press the button 
    //If the counter variable is 2, it means that it is the second player's turn to press the button
    
    if(digitalRead(First_Player_Button) == HIGH && counter == 1) {  //If it is first player's turn and first player pressed button
        lcd.clear();                             //Clear the LCD display 
        firstValue = 0;                          //Reset the firstValue variable where the data of the first player will be stored 
        secondValue = 0;                         //Reset the secondValue variable where the data of the second player will be stored 
        
        for(int i=0; i<5; i++) {                //Repeat 5 times 
            firstValue = random(1, 4);           //Generate a random number between 1 and 4 and save it to firstValue variable
            //Call RGB animation function to make RGB LED light up according to random number and save to randomly generated first value
            RGB_animation(firstValue);           
            //Call result function to show result on LCD display and give firstValue and secondValue variables as parameters
            result(firstValue, secondValue);     
            //Multiply randomly generated first value by 220 and transfer Hertz value of tone to speaker
            tone(speakerPin, firstValue * 220);  
            delay(150);                          //Wait for 150ms
            noTone(speakerPin);                  //Mute the Speaker 
            counter = 2;                         //Set counter variable to 2 to indicate second player's turn 
        }
    }

    if(digitalRead(Second_Player_Button) == HIGH && counter == 2) { //If second player's turn and second player pressed button
        lcd.clear();                            //Clear LCD display 
        for(int i=0; i<5; i++) {               //Repeat 5 times 
            secondValue = random(1, 4);         //Generate random number between 1 and 4 and save to secondValue variable
            //Call RGB animation function to make RGB LED light up according to random number and save to randomly generated value
            RGB_animation(secondValue);         
            //Call result function to show result on LCD display and give firstValue and secondValue variables as parameters
            result(firstValue, secondValue);    
            //Multiply randomly generated second value by 220 and transfer Hertz value of tone to speaker
            tone(speakerPin, secondValue * 220);
            delay(150);                         //Wait for 150ms
            noTone(speakerPin);                //Mute the Speaker 
            counter = 1;                        //Set counter variable to 1 to indicate first player's turn 
        }
    }
}

//Create result function to show winner and get data of first player and second player as parameters
void result(int first, int second) {
    //Go to first row of LCD display and print 1: then print Rock Paper or Scissors according to random value
    lcd.setCursor(0, 0);
    lcd.print("1:"); 
    if(first == 1) { lcd.setCursor(2,0); lcd.print("Rock"); }
    if(first == 2) { lcd.setCursor(2,0); lcd.print("Paper"); }
    if(first == 3) { lcd.setCursor(2,0); lcd.print("Scissors"); }

    //Go to column 9 of first row and print 2: then print Rock Paper or Scissors according to random value
    lcd.setCursor(9, 0);
    lcd.print("2:"); 
    if(second == 1) { lcd.setCursor(11,0); lcd.print("Rock"); }
    if(second == 2) { lcd.setCursor(11,0); lcd.print("Paper"); }
    if(second == 3) { lcd.setCursor(11,0); lcd.print("Scissors"); }
  
    if(firstValue == secondValue) {             //If values of first and second players are equal (draw)
        lcd.setCursor(0, 1);                    //Print "DRAW" at bottom row of LCD display
        lcd.print("DRAW    ");
    }
    //If first player gets ROCK and second player gets PAPER - Second player wins
    else if(firstValue == 1 && secondValue == 2) {
        lcd.setCursor(0, 1);                    //Write "2nd Player Wins" on bottom row of LCD display
        lcd.print("2nd Player Wins");
    }
    //If first player gets ROCK and second player gets SCISSORS - First player wins  
    else if(firstValue == 1 && secondValue == 3) {
        lcd.setCursor(0, 1);                    //Write "1st Player Wins" on bottom row of LCD display
        lcd.print("1st Player Wins");
    }
    //If first player gets PAPER and second player gets ROCK - First player wins
    else if(firstValue == 2 && secondValue == 1) {
        lcd.setCursor(0, 1);                    //Write "1st Player Wins" on bottom row of LCD display
        lcd.print("1st Player Wins");
    }
    //If first player gets PAPER and second player gets SCISSORS - Second player wins
    else if(firstValue == 2 && secondValue == 3) {
        lcd.setCursor(0, 1);                    //Write "2nd Player Wins" on bottom row of LCD display
        lcd.print("2nd Player Wins");
    }
    //If first player gets SCISSORS and second player gets ROCK - Second player wins
    else if(firstValue == 3 && secondValue == 1) {
        lcd.setCursor(0, 1);                    //Write "2nd Player Wins" on bottom row of LCD display
        lcd.print("2nd Player Wins");
    }
    //If first player gets SCISSORS and second player gets PAPER - First player wins
    else if(firstValue == 3 && secondValue == 2) {
        lcd.setCursor(0, 1);                    //Write "1st Player Wins" on bottom row of LCD display
        lcd.print("1st Player Wins");
    }
}

//Create RGB_animation function to animate RGB according to randomly assigned values and display rock, paper or scissors
void RGB_animation(int status) {
    //Determine rock paper scissors status based on data in status variable:
    //1 = rock, 2 = paper, 3 = scissors
    switch(status) {
        case 1:                                 //When rock state comes, turn ON RGB Red LED and turn OFF others
            digitalWrite(RGB_Red, LOW);
            digitalWrite(RGB_Green, HIGH);
            digitalWrite(RGB_Blue, HIGH);
            break;
            
        case 2:                                //When paper state comes, turn ON RGB Green LED and turn OFF others
            digitalWrite(RGB_Red, HIGH);
            digitalWrite(RGB_Green, LOW);
            digitalWrite(RGB_Blue, HIGH);
            break;
            
        case 3:                                //When scissors state comes, turn ON RGB Blue LED and turn OFF others
            digitalWrite(RGB_Red, HIGH);
            digitalWrite(RGB_Green, HIGH);
            digitalWrite(RGB_Blue, LOW);
            break;
    }
}
