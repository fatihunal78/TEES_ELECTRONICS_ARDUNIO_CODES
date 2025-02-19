//SA69 - LED matrix backgammon dice

#include "LedControl.h"                    //Add LED matrix library

int buttonPin = 2;                         //Define the pin number to which the Button is connected
int buzzerPin = 8;                         //Define the pin to which the Buzzer is connected
int randomNumber;                          //Define the variable to store the randomly generated number

LedControl lc=LedControl(7, 5, 6, 1);      //Define that DATAIN is connected to pin 7, CS to 5, CLK to 6 
                                          //The 1 at the end indicates the number of matrices

byte six[8]={                              //Codes to show 6 on dice 
    B11011011,
    B11011011,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11011011,
    B11011011
}; 
  
byte five[8]={                             //Codes to show 5 on dice 
    B11000011,
    B11000011,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B11000011,
    B11000011
};
  
byte four[8]={                             //Codes to show 4 on dice 
    B11000011,
    B11000011,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B11000011,
    B11000011
};
  
byte three[8]={                            //Codes to show 3 on dice 
    B00000011,
    B00000011,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B11000000,
    B11000000
};

byte two[8]={                              //Codes to show 2 on dice 
    B00011000,
    B00011000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000
};

byte one[8]={                              //Codes to show 1 on dice 
    B00000000,
    B00000000,
    B00000000,
    B00011000,
    B00011000,
    B00000000,
    B00000000,
    B00000000
};

void setup() {
    pinMode(buttonPin, INPUT_PULLUP);      //Set the pin to which the Button is connected as input
    pinMode(buzzerPin, OUTPUT);            //Set the pin to which the Buzzer is connected as output
  
    lc.shutdown(0, false);                 //Command for the integrated circuit located next to the LED matrix to exit sleep mode 
    lc.setIntensity(0, 8);                //Brightness adjustment 
    lc.clearDisplay(0);                    //Clear the LED Matrix
}

void loop() { 
    //Perform the following actions to generate random numbers 
    //A number will be continuously assigned to the random number variable with the for loop
    //When the button is pressed, the value of i will be in a random place, so there will be a random number in 
    //the randomNumber variable 

    while(1) {                             //Enter infinite loop 
        for(int i=1; i<7; i++) {          //i value will change from 1 to 6 
            randomNumber = i;              //Assign the value i to the randomNumber variable 
    
            if(digitalRead(buttonPin) == LOW) //If the Button is pressed
                break;                     //End for loop 
        }
        if(digitalRead(buttonPin) == LOW)  //If the Button is pressed
            break;                         //Exit while loop 
    }

    if(digitalRead(buttonPin) == LOW) {    //If the Button is pressed
        //randonNumber = random(1, 7);     //Generate a random number between 1 and 7 (not including 7) 
                                          //So the randomly generated number will be from 1 to 6
                             
        for(int delayTime=100; delayTime<=300; delayTime=delayTime+100) { //Animating loop
            one1();
            tone(buzzerPin, 100);
            delay(delayTime);
            noTone(buzzerPin);
            two2(); 
            tone(buzzerPin, 200);
            delay(delayTime);
            noTone(buzzerPin);
            three3();
            tone(buzzerPin, 300);
            delay(delayTime);
            noTone(buzzerPin);
            four4();
            tone(buzzerPin, 400);
            delay(delayTime);
            noTone(buzzerPin);
            five5();
            tone(buzzerPin, 500);
            delay(delayTime);
            noTone(buzzerPin);
            six6();
            tone(buzzerPin, 100);
            delay(delayTime);
            noTone(buzzerPin);
        }
    }

    //Select one of the following cases according to the randomly generated number and transfer it to the LED matrix 
    //The transferred result will represent the dice 
    switch(randomNumber) {
        case 1: one1();
            break;
        case 2: two2();
            break;
        case 3: three3();
            break;
        case 4: four4();
            break;
        case 5: five5();
            break;
        case 6: six6();
            break;
    }
} 

void one1() { 
    lc.setRow(0, 0, one[0]);
    lc.setRow(0, 1, one[1]);
    lc.setRow(0, 2, one[2]);
    lc.setRow(0, 3, one[3]);
    lc.setRow(0, 4, one[4]);
    lc.setRow(0, 5, one[5]);
    lc.setRow(0, 6, one[6]);
    lc.setRow(0, 7, one[7]);
}

void two2() {
    lc.setRow(0, 0, two[0]);
    lc.setRow(0, 1, two[1]);
    lc.setRow(0, 2, two[2]);
    lc.setRow(0, 3, two[3]);
    lc.setRow(0, 4, two[4]);
    lc.setRow(0, 5, two[5]);
    lc.setRow(0, 6, two[6]);
    lc.setRow(0, 7, two[7]);
}

void three3() {
    lc.setRow(0, 0, three[0]);
    lc.setRow(0, 1, three[1]);
    lc.setRow(0, 2, three[2]);
    lc.setRow(0, 3, three[3]);
    lc.setRow(0, 4, three[4]);
    lc.setRow(0, 5, three[5]);
    lc.setRow(0, 6, three[6]);
    lc.setRow(0, 7, three[7]);
}

void four4() {
    lc.setRow(0, 0, four[0]);
    lc.setRow(0, 1, four[1]);
    lc.setRow(0, 2, four[2]);
    lc.setRow(0, 3, four[3]);
    lc.setRow(0, 4, four[4]);
    lc.setRow(0, 5, four[5]);
    lc.setRow(0, 6, four[6]);
    lc.setRow(0, 7, four[7]);
}

void five5() {
    lc.setRow(0, 0, five[0]);
    lc.setRow(0, 1, five[1]);
    lc.setRow(0, 2, five[2]);
    lc.setRow(0, 3, five[3]);
    lc.setRow(0, 4, five[4]);
    lc.setRow(0, 5, five[5]);
    lc.setRow(0, 6, five[6]);
    lc.setRow(0, 7, five[7]);
}

void six6() {
    lc.setRow(0, 0, six[0]);
    lc.setRow(0, 1, six[1]);
    lc.setRow(0, 2, six[2]);
    lc.setRow(0, 3, six[3]);
    lc.setRow(0, 4, six[4]);
    lc.setRow(0, 5, six[5]);
    lc.setRow(0, 6, six[6]);
    lc.setRow(0, 7, six[7]); 
}
