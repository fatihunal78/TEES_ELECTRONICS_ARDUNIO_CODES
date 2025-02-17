//SA16 - Parking sensor with LCD display

#include <LiquidCrystal_I2C.h> //Add I2C LCD library

//Define the pin number to which the Speaker is attached
int speakerPin = 2;

//Define the pin to which the HC-SR04 Trigger leg is connected
#define triggerPin 4

//Define the pin to which the HC-SR04 Echo pin is connected  
#define echoPin 5

//Define time and distance variables
long time, distance;

//Define the variable to store the warning tone duration
int beepTime = 300;

//Define Turkish characters for LCD
byte characteru[8] = {0x00, 0x0A, 0x00, 0x0A, 0x0A, 0x0A, 0x0E, 0x00}; //ü
byte charactero[8] = {0x0A, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00}; //ö
byte characterbar[8] = {0x00, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x00}; //Bar

//Define 1602 LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    //Set the pin to which the trigger leg is connected as output
    pinMode(triggerPin, OUTPUT);
    
    //Set the pin to which the echo leg is connected as input
    pinMode(echoPin, INPUT);
    
    lcd.begin(); //Start the LCD
    lcd.backlight(); //Turn ON the LCD backlights
    
    //Define added characters
    lcd.createChar(1, characteru); //Create ü character
    lcd.createChar(2, charactero); //Create ö character
    lcd.createChar(3, characterbar); //Create bar
    
    lcd.clear(); //Clear the LCD display
    lcd.setCursor(0, 0); //Go to the first row, first character on the LCD display
    lcd.print("TEES Electronics"); //Write "TEES Electronics" on the LCD display
    lcd.setCursor(2,1); //Select LCD lower line second character
    lcd.print("Park Sensor"); //Write on the LCD display
    
    delay(3000); //Wait for 3 seconds
    lcd.clear(); //Clear the LCD display
}

void loop() {
    //Pull the trigger leg to zero
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2); //Wait for 2 microseconds
    
    //Pull the trigger leg to 5V
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10); //Wait for 10 microseconds
    
    //Pull the trigger leg to zero
    digitalWrite(triggerPin, LOW);
    
    //Measure the return time of the audio signal from the echo pin
    time = pulseIn(echoPin, HIGH);
    
    //Calculate the distance in cm by multiplying the measured time by the speed of sound
    distance = (time/2) * 0.034;
    
    lcd.setCursor(0, 0); //Go to the first row, first character on the LCD display
    lcd.print("Distance: "); //Write to the LCD display
    
    if(distance > 50 || distance < 0) { //If the distance is greater than 50 or less than 0
        lcd.print("--"); //Write to the LCD display
    } else {
        if(distance > 9) { //If the distance is greater than 9
            //If the distance is 2 digits, write the distance to the LCD display
            lcd.print(distance);
        } else {
            //If the distance is single digit, write the distance by leaving a space on the LCD
            lcd.print(" ");
            lcd.print(distance);
        }
    }
    
    lcd.print(" cm"); //Write to the LCD display
    lcd.setCursor(0, 1); //Go to the lower row, first character on the LCD display
    
    if(distance > 50) { //If distance is greater than 50cm
        //Show the distance as bar
        for(int i=0; i<1; i++) {
            lcd.write(byte(3));
        }
        for(int j=0; j<5; j++) {
            lcd.print(" ");
        }
    } else if(distance > 40) { //If distance is greater than 40
        //Show the distance as bar
        for(int i=0; i<4; i++) {
            lcd.write(byte(3));
        }
        for(int j=0; j<10; j++) {
            lcd.print(" ");
        }
    } else if(distance > 30) { //If the distance is greater than 30
        //Show the distance as bar
        for(int i=0; i<7; i++) {
            lcd.write(byte(3));
        }
        for(int j=0; j<9; j++) {
            lcd.print(" ");
        }
        //A warning tone comes from the Speaker
        tone(speakerPin, 440);
        delay(beepTime / 3);
        noTone(speakerPin);
        delay(beepTime / 3);
    } else if(distance > 20) { //If the distance is greater than 20
        //Show the distance as bar
        for(int i=0; i<10; i++) {
            lcd.write(byte(3));
        }
        for(int j=0; j<6; j++) {
            lcd.print(" ");
        }
        //A warning tone comes from the Speaker
        tone(speakerPin, 440);
        delay(beepTime / 4);
        noTone(speakerPin);
        delay(beepTime / 4);
    } else if(distance > 10) { //If the distance is greater than 10
        //Show the distance as bar
        for(int i=0; i<13; i++) {
            lcd.write(byte(3));
        }
        for(int j=0; j<3; j++) {
            lcd.print(" ");
        }
        //A warning tone comes from the Speaker
        tone(speakerPin, 440);
        delay(beepTime / 5);
        noTone(speakerPin);
        delay(beepTime / 5);
    } else if(distance > 5) { //If the distance is greater than 5
        //Show the distance as bar
        for(int i=0; i<16; i++) {
            lcd.write(byte(3));
        }
        //A warning tone comes from the Speaker
        tone(speakerPin, 440);
    }
}
