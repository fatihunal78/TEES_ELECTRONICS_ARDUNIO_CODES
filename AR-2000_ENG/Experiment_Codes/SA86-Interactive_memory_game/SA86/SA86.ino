//SA86 - Interactive memory game

#include <CapacitiveSensor.h>                                //Add capacitive sensor library 

//Add the pin numbers to which the fruits are connected to the capacitive sensor library
CapacitiveSensor cs_2_3 = CapacitiveSensor(2, 3); 
CapacitiveSensor cs_2_4 = CapacitiveSensor(2, 4); 
CapacitiveSensor cs_2_5 = CapacitiveSensor(2, 5); 
CapacitiveSensor cs_2_6 = CapacitiveSensor(2, 6); 

const int Maximum_Level = 100;                              //Define the variable that will determine the maximum level of the game and set the maximum level to 100
int ranking[Maximum_Level];                                 //Define the variable to which the ranking will be saved as an array with maximum level of elements 
int player_level[Maximum_Level];                           //Define a variable that will store the player's level
int level = 1;                                             //Define the variable to store the level of the game and set the first level value to 1

//The speed of the game will increase as the level increases, so define the game_speed variable
//And set the initial value of this variable to 1000
int game_speed = 1000;                                     

int buzzerPin = 12;                                        //Define the pin number to which the Buzzer is connected
int red_LEDPin = 11;                                       //Define the pin to which the red LED is connected 
int green_LEDPin = 10;                                     //Define the pin to which the green LED is connected
int blue_LEDPin = 9;                                       //Define the pin to which the blue LED is connected 
int yellow_LEDPin = 8;                                     //Define the pin to which the yellow LED is connected 

long red_button;                                           //Define button variable representing the Red LED on capacitive fruit button 
long green_button;                                         //Define button variable representing the Green LED on capacitive fruit button
long blue_button;                                          //Define button variable representing the Blue LED on capacitive fruit button
long yellow_button;                                        //Define button variable representing the Yellow LED on capacitive fruit button 

int red_status = 0;                                        //Define the variable to store whether the red button is pressed or not
int green_status = 0;                                      //Define the variable to store whether the green button is pressed or not
int blue_status = 0;                                       //Define the variable to store whether the blue button is pressed or not
int yellow_status = 0;                                     //Define the variable to store whether the yellow button is pressed or not

void setup() {
    pinMode(red_LEDPin, OUTPUT);                          //Set the pin to which the red LED is connected as output
    pinMode(green_LEDPin, OUTPUT);                        //Set the pin to which the green LED is connected as output
    pinMode(blue_LEDPin, OUTPUT);                         //Set the pin to which the blue LED is connected as output
    pinMode(yellow_LEDPin, OUTPUT);                       //Set the pin to which the yellow LED is connected as output
    pinMode(buzzerPin, OUTPUT);                           //Set the pin to which the Buzzer is connected as output 

    //Initially, we made all the LEDs and buzzer LOW.
    digitalWrite(red_LEDPin, LOW); 
    digitalWrite(green_LEDPin, LOW);
    digitalWrite(blue_LEDPin, LOW);
    digitalWrite(yellow_LEDPin, LOW);
    digitalWrite(buzzerPin, LOW); 
}

void loop() {
    button_control();                                     //Call the function that checks whether the buttons are pressed or not
  
    if(level == 1)                                       //If the level of the game is 1, that is, at the first level
        createRanking();                                 //Call the createRanking() function

    //If the button controlling the Red LED is pressed or the game level is different from 1 
    if(digitalRead(red_LEDPin) == LOW || level != 1) {   
        button_control();
        showRanking();                                   //Call the showRanking() function
        increaseRanking();                               //Call the increaseRanking() function
    }
}

void button_control() {                                  //Create the function that checks whether the buttons are pressed or not
    //Set the touch sensitivity of the fruits to be used as sensors
    //And when the fruits are touched, save the read values to the fruit variables
    red_button = cs_2_3.capacitiveSensor(10000);
    green_button = cs_2_4.capacitiveSensor(10000);
    blue_button = cs_2_5.capacitiveSensor(10000);
    yellow_button = cs_2_6.capacitiveSensor(10000);
  
    if(red_button > 300) {                              //If the fruit controlling the Red LED is touched, set the red_status variable to 1 
        red_status = 1; 
    }
    else if(green_button > 300) {                       //If the fruit controlling the Green LED is touched, set the green_status variable to 1 
        green_status = 1; 
    }
    else if(blue_button > 300) {                        //If the fruit controlling the Blue LED is touched, set the blue_status variable to 1 
        blue_status = 1; 
    }
    else if(yellow_button > 300) {                      //If the fruit controlling the Yellow LED is touched, set the yellow_status variable to 1 
        yellow_status = 1; 
    }
    else {                                              //If the fruits are not touched, set the value of the status variables to 0
        red_status = 0; 
        green_status = 0; 
        blue_status = 0; 
        yellow_status = 0; 
    }
}

void showRanking() {                                    //Create showRanking() function 
    //Turn OFF all LEDs
    digitalWrite(red_LEDPin, LOW); 
    digitalWrite(green_LEDPin, LOW);
    digitalWrite(blue_LEDPin, LOW);
    digitalWrite(yellow_LEDPin, LOW);
    
    for(int i=0; i<level; i++) {                       //Increment the value of i one by one from 0 to the level of the game
        digitalWrite(ranking[i], HIGH);                 //Set the i-th value of the ranking variable to HIGH 
        delay(game_speed);                             //Delay by game_speed

        digitalWrite(ranking[i], LOW);                  //Set i. value of ranking variable to LOW 
        delay(200);                                    //Delay for 200ms 
    }
}

void increaseRanking() {                               //Create increaseRanking() function 
    int flag = 0;                                      //Create the flag variable and set its initial value to 0 

    for(int i=0; i<level; i++) {                      //Increase the value of i one by one from 0 to the level of the game 
        flag = 0;                                      //Set flag value to zero 

        while(flag == 0) {                            //As long as the flag value is zero 
            button_control();                          //Call the function that checks whether the buttons are pressed or not
          
            if(red_status == 1) {                     //If the button controlling the Red LED is pressed 
                digitalWrite(red_LEDPin, HIGH);        //Turn ON the Red LED 
                player_level[i] = 11;                  //Store the value 11 in the i-th value of the player_level variable 
                flag = 1;                              //Set flag value to 1 
                delay(200);                            //Wait for 200ms 

                //If the i-th value of player_level and the i-th value of ranking are not the same 
                //This means that the wrong button was pressed 
                if(player_level[i] != ranking[i]) {
                    youLost();                         //Call the youLost() function because you lost the game
                    return; 
                }

                digitalWrite(red_LEDPin, LOW);         //Turn OFF the Red LED 
            }

            if(green_status == 1) {                   //If the button controlling the Green LED is pressed 
                digitalWrite(green_LEDPin, HIGH);      //Turn ON the Green LED 
                player_level[i] = 10;                  //Store the value 10 in the i-th value of the player_level variable 
                flag = 1;                              //Set flag value to 1 
                delay(200);                            //Wait for 200ms

                //If the i-th value of player_level and the i-th value of ranking are not the same 
                //This means that the wrong button was pressed
                if(player_level[i] != ranking[i]) {
                    youLost();                         //Call the youLost() function
                    return;
                }

                digitalWrite(green_LEDPin, LOW);       //Turn OFF the Green LED 
            }

            if(blue_status == 1) {                    //If the button controlling the Blue LED is pressed 
                digitalWrite(blue_LEDPin, HIGH);       //Turn ON the Blue LED
                player_level[i] = 9;                   //Store the value 9 in the i-th value of the player_level variable 
                flag = 1;                              //Set flag value to 1 
                delay(200);                            //Wait for 200ms

                //If the i-th value of player_level and the i-th value of ranking are not the same 
                //This means that the wrong button was pressed
                if(player_level[i] != ranking[i]) {
                    youLost();                         //Call the youLost() function
                    return;
                }

                digitalWrite(blue_LEDPin, LOW);        //Turn OFF the Blue LED 
            }

            if(yellow_status == 1) {                  //If the button controlling the Yellow LED is pressed 
                digitalWrite(yellow_LEDPin, HIGH);     //Turn ON the Yellow LED 
                player_level[i] = 8;                   //Store the value 8 in the i-th value of the player_level variable 
                flag = 1;                              //Set flag value to 1 
                delay(200);                            //Wait for 200ms

                //If the i-th value of player_level and the i-th value of ranking are not the same 
                //This means that the wrong button was pressed
                if(player_level[i] != ranking[i]) {
                    youLost();                         //Call the youLost() function
                    return;
                }

                digitalWrite(yellow_LEDPin, LOW);      //Turn OFF the Yellow LED 
            }
        }
    }

    rankingCheck();                                   //Call ranking_check() function 
}

void createRanking() {                               //Create the createRanking() function 
    randomSeed(millis()); 

    for(int i=0; i<Maximum_Level; i++) {             //Increment the value of i one by one from zero to maximum level 
        ranking[i] = random(8, 12);                  //Assign a random number between 8 and 12 to the i-th value of the ranking variable
    }
}

void youLost() {                                     //Create youLost() function 
    for(int i=0; i<6; i++) {                        //Loop 6 times 
        //We have performed the following operations for turning the LEDs ON and OFF

        //Turn ON the LEDs and make a sound from the Buzzer 
        digitalWrite(red_LEDPin, HIGH); 
        digitalWrite(green_LEDPin, HIGH);
        digitalWrite(blue_LEDPin, HIGH);
        digitalWrite(yellow_LEDPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(250);

        //Turn OFF the LEDs and mute the Buzzer
        digitalWrite(red_LEDPin, LOW); 
        digitalWrite(green_LEDPin, LOW);
        digitalWrite(blue_LEDPin, LOW);
        digitalWrite(yellow_LEDPin, LOW);
        digitalWrite(buzzerPin, LOW); 
        delay(250);
    }
    level = 1;                                       //Set level value equal to 1 
    game_speed = 1000;                              //Set the game speed to 1000 
}

void rankingControl() {                             //Create rankingControl() function 
    digitalWrite(buzzerPin, LOW);                   //Mute the Buzzer 
    delay(250);                                     //Wait for 250ms 
    digitalWrite(buzzerPin, HIGH);                  //Make a sound from the Buzzer 
    delay(250);                                     //Wait for 250ms 
    digitalWrite(buzzerPin, LOW);                   //Mute the Buzzer 
    delay(500);                                     //Wait for 500ms 

    if(level < Maximum_Level) {                     //If the level is less than Maximum Level 
        level++;                                    //Increment the level variable by one
        game_speed -= 50;                          //Decrement game_speed variable by 50
    }
}
