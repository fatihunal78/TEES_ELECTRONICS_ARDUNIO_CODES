//S81 - Illuminated memory game

const int Maximum_Level = 100;    //Define the variable that will determine the maximum level of the game and set the 
                                 //maximum level to 100

int ranking[Maximum_Level];       //Define the array variable where the ranking will be stored, with items up to the 
                                 //maximum level
int player_level[Maximum_Level];  //Define a variable that will store the player's level
int level = 1;                   //Define the variable to store the level of the game and set the first level value to 1
int game_speed = 1000;           //Define the variable game_speed as the game speed will increase as the level of the game 
                                 //increases. Initial value of game_speed variable is set to 1000

//Define the pin numbers to which the LEDs are connected
int red_LEDPin = 13;
int green_LEDPin = 12;
int buzzerPin = 9;               //Define the pin number to which the buzzer is connected

int redLED_button = 2;           //Define the pin number to which the button that will control the red LED is connected
int greenLED_button = 3;         //Define the pin number to which the button that will control the green LED is connected

void setup()
{
    pinMode(red_LEDPin, OUTPUT);          //Set the pin to which the red LED is connected as output
    pinMode(green_LEDPin, OUTPUT);        //Set the pin to which the green LED is connected as output
    pinMode(buzzerPin, OUTPUT);           //Set the pin to which the Buzzer is connected as output

    pinMode(redLED_button, INPUT_PULLUP); //Set the pin to which the button that will control the red LED is connected as 
                                         //input and activate the pull-up resistor
    pinMode(greenLED_button, INPUT);      //Set the pin to which the button that will control the green LED is connected 
                                         //as input

    //Initially Turn OFF all LEDs and mute the Buzzer
    digitalWrite(red_LEDPin, LOW);
    digitalWrite(green_LEDPin, LOW);
    digitalWrite(buzzerPin, LOW);
}

void loop()
{
    if(level == 1)                                    //If the game is at level 1, namely first level
        createRanking();                              //Call the createRanking() function

    if(digitalRead(red_LEDPin) == LOW || level != 1)  //If the button controlling the Red LED is pressed or the game level 
                                                      //is different from 1
    {
        showRanking();                                //Call the showRanking() function
        increaseRanking();                            //Call the increaseRanking() function
    }
}

void showRanking()                                    //Create showRanking() function
{
    //Turn OFF all LEDs
    digitalWrite(red_LEDPin, LOW);
    digitalWrite(green_LEDPin, LOW);

    for(int i=0; i<level; i++)                       //Increment the value of i one by one from 0 to the level of the game
    {
        digitalWrite(ranking[i], HIGH);               //set the i-th value of the ranking variable to HIGH
        delay(game_speed);                           //Delay by game_speed
        digitalWrite(ranking[i], LOW);                //set i-th value of ranking variable to LOW
        delay(200);                                  //200ms delay
    }
}

void increaseRanking()                               //Create increaseRanking() function
{
    int flag = 0;                                    //Create the flag variable and set its initial value to 0
    for(int i=0; i<level; i++)                      //Increment the value of i one by one from 0 to the level of the game
    {
        flag = 0;                                    //Set flag value to zero

        while(flag == 0)                             //As long as the flag value is zero
        {
            if(digitalRead(redLED_button) == LOW)    //If the button controlling the Red LED is pressed
            {
                digitalWrite(red_LEDPin, HIGH);      //Turn ON the Red LED
                while(digitalRead(redLED_button) == LOW); //Wait as long as the button is pressed
                player_level[i] = 13;                //Store the value 13 in the i-th value of the player_level variable
                flag = 1;                            //Set flag value to 1

                if(player_level[i] != ranking[i])    //If the i-th value of player_level and the i-th value of ranking are 
                                                    //not the same. If the player pressed the wrong button
                {
                    youLost();                      //Call the youLost() function because you lost the game
                    return;
                }
                digitalWrite(red_LEDPin, LOW);      //Turn OFF the Red LED
            }

            if(digitalRead(greenLED_button) == HIGH) //If the button controlling the Green LED is pressed
            {
                digitalWrite(green_LEDPin, HIGH);    //Turn ON the Green LED
                while(digitalRead(greenLED_button) == HIGH); //Wait as long as the button is pressed
                player_level[i] = 12;                //Store the value 12 in the i-th value of the player_level variable
                flag = 1;                            //Set flag value to 1

                if(player_level[i] != ranking[i])    //If the i-th value of player_level and the i-th value of ranking are 
                                                    //not the same. If the player pressed the wrong button
                {
                    youLost();                      //Call the youLost() function because you lost the game
                    return;
                }
                digitalWrite(green_LEDPin, LOW);    //Turn OFF the Green LED
            }
        }
    }

    rankingControl();                              //Call rankingControl() function
}

void createRanking()                              //Create the createRanking() function
{
    randomSeed(millis());

    for(int i=0; i<Maximum_Level; i++)           //Increment the value of i one by one from zero to maximum level
    {
        ranking[i] = random(12, 14);             //Assign a random number between 12 and 14 to the i-th value of the 
                                                //ranking variable
    }
}

void youLost()                                  //Create youLost() function
{
    for(int i=0; i<3; i++)                     //Loop 3 times
    {
        //Turn ON the LEDs three times and follow the steps below to turn them OFF
        //Turn ON the LEDs and make a sound from the Buzzer
        digitalWrite(red_LEDPin, HIGH);
        digitalWrite(green_LEDPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(250);

        //turn OFF the LEDs and mute the buzzer
        digitalWrite(red_LEDPin, LOW);
        digitalWrite(green_LEDPin, LOW);
        digitalWrite(buzzerPin, LOW);
        delay(250);

        digitalWrite(red_LEDPin, HIGH);
        digitalWrite(green_LEDPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(250);

        digitalWrite(red_LEDPin, LOW);
        digitalWrite(green_LEDPin, LOW);
        digitalWrite(buzzerPin, LOW);
        delay(250);

        digitalWrite(red_LEDPin, HIGH);
        digitalWrite(green_LEDPin, HIGH);
        digitalWrite(buzzerPin, HIGH);
        delay(250);

        digitalWrite(red_LEDPin, LOW);
        digitalWrite(green_LEDPin, LOW);
        digitalWrite(buzzerPin, LOW);
        delay(250);
    }

    level = 1;                                 //Set level value equal to 1
    game_speed = 1000;                        //Set the game speed to 1000
}

void rankingControl()                         //Create rankingControl() function
{
    digitalWrite(buzzerPin, LOW);             //Mute the Buzzer
    delay(250);                              //Wait for 250ms

    digitalWrite(buzzerPin, HIGH);            //Make a sound from the Buzzer
    delay(250);                              //Wait for 250ms

    digitalWrite(buzzerPin, LOW);             //Mute the Buzzer
    delay(500);                              //Wait for 500ms

    if(level < Maximum_Level)                 //If the level is less than Maximum Level
        level++;                             //Increment the level variable by one

    game_speed -= 50;                        //Decrease game_speed variable by 50
}
