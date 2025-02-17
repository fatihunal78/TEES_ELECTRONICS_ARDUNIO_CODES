//SA20 - Garage door with LCD screen and password protection

#include <EEPROM.h> //Add EEPROM library
#include <IRremote.h> //Add IR receiver library
#include <Servo.h> //Add servo motor library
#include <LiquidCrystal_I2C.h> //Add I2C LCD library

//Define the EEPROM addresses where the password will be stored
#define addr_password1 0
#define addr_password2 1
#define addr_password3 2
#define addr_password4 3

//Define the variable to keep the password
int password[4];

//Define IR control codes
#define oneKey 0xFFA25D //IR Control key 1
#define twoKey 0xFF629D //IR Control key 2
#define threeKey 0xFFE21D //IR Control key 3
#define fourKey 0xFF22DD //IR Control key 4
#define fiveKey 0xFF02FD //IR Control key 5
#define sixKey 0xFFC23D //IR Control key 6
#define sevenKey 0xFFE01F //IR Control key 7
#define eightKey 0xFFA857 //IR Control key 8
#define nineKey 0xFF906F //IR Control key 9
#define zeroKey 0xFF9867 //IR Control key 0
#define doorOpenClose 0xFF38C7 //IR Control Key OK
#define hashKey 0xFFB04F //IR Control key #

//Define the variable to store the incoming number
int incomingDigit = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2); //Define 1602 LCD display

int IRPin = 2; //Define the pin to which the IR receiver signal leg is connected
int buzzerPin = 7; //Define the pin to which the Buzzer is connected
int servoPin = 5; //Define the pin number to which the servo motor is connected

IRrecv IRReceive(IRPin); //Define an IR Receiver named IRReceive
decode_results result; //Define variable to store values received from IR receiver
Servo servo; //Define servo motor

//Define the variable to store the angle of servo motor
int servoStep = 90;
//Define the variable to store the password counter value
int passwordCounter = 0;
//Define the variable to keep the password change counter
int passwordChangeCounter = 0;
//Define the variable to keep the lock state
int passwordInputStatus = 0;

void setup() {
    //Start IR receiver
    IRReceive.enableIRIn();
    //Set the pin to which the Buzzer is connected as output
    pinMode(buzzerPin, OUTPUT);
    servo.attach(servoPin); //Define the pin to which the servo motor is connected
    //Move servo motor to 90-degree position
    servo.write(90);
    //Read password values from EEPROM
    password[0] = EEPROM.read(addr_password1);
    password[1] = EEPROM.read(addr_password2);
    password[2] = EEPROM.read(addr_password3);
    password[3] = EEPROM.read(addr_password4);
    //Has a value been stored in the EEPROM before?
    if(password[0] > 9)
        password[0] = 1;
    if(password[1] > 9)
        password[1] = 2;
    if(password[2] > 9)
        password[2] = 3;
    if(password[3] > 9)
        password[3] = 4;
    lcd.begin(); //Start the LCD
    lcd.backlight(); //Turn ON the LCD backlights
    lcd.clear(); //Clear the LCD display
    lcd.setCursor(0, 0);
    lcd.print("TEES Electronics");
    lcd.setCursor(0, 1);
    lcd.print("Lock Application");
    delay(3000);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Password can be");
    lcd.setCursor(0, 1);
    lcd.print("changed with #");
    delay(3000);
    lcd.clear();
    lcd.setCursor(2, 0);
    lcd.print("Door is Locked");
    lcd.setCursor(6, 1);
    lcd.print("----");
}

void loop() {
    servo.detach();
    //Query password change status
    if(passwordInputStatus == 0) { //If password change status is not active
        //Check if there is any data coming from IR receiver
        if(IRReceive.decode(&result)) {
            if(result.value == hashKey) { //If the # key is pressed
                passwordInputStatus = 1; //Activate password change
                lcd.setCursor(2, 0);
                lcd.print("Enter Password");
            }
            else { //Detect password if hash key is not pressed
                incomingDigit = digitSolve(result.value); //Solve the incoming digit
                switch(passwordCounter) {
                    case 0:
                        if(incomingDigit == password[0]) { //If the password character is correct
                            passwordCounter++; //Switch to next password character
                            digitalWrite(buzzerPin, HIGH);
                            delay(300); //Wait for 300ms
                            digitalWrite(buzzerPin, LOW);
                            lcd.setCursor(6, 1);
                            lcd.print("*---");
                        }
                        else { //If the password character is incorrect
                            digitalWrite(buzzerPin, HIGH);
                            delay(50); //Wait for 50ms
                            digitalWrite(buzzerPin, LOW);
                            delay(50); //Wait for 50ms
                            digitalWrite(buzzerPin, HIGH);
                            delay(50); //Wait for 50ms
                            digitalWrite(buzzerPin, LOW);
                        }
                        break;
                    case 1:
                        if(incomingDigit == password[1]) { //If the next password character is correct
                            passwordCounter++; //Switch to next password character
                            digitalWrite(buzzerPin, HIGH);
                            delay(300); //Wait for 300ms
                            digitalWrite(buzzerPin, LOW);
                            lcd.setCursor(6, 1);
                            lcd.print("**--");
                        }
                        else {
                            digitalWrite(buzzerPin, HIGH);
                            delay(50); //Wait for 50ms
                            digitalWrite(buzzerPin, LOW);
                            delay(50); //Wait for 50ms
                            digitalWrite(buzzerPin, HIGH);
                            delay(50); //Wait for 50ms
                            digitalWrite(buzzerPin, LOW);
                            passwordCounter = 0; //Reset password to first character
                            lcd.setCursor(6, 1);
                            lcd.print("----");
                        }
                        break;
                    case 2:
                        if(incomingDigit == password[2]) { //If the next password character is correct
                            passwordCounter++; //Switch to next password character
                            digitalWrite(buzzerPin, HIGH);
                            delay(300); //Wait for 300ms
                            digitalWrite(buzzerPin, LOW);
                            lcd.setCursor(6, 1);
                            lcd.print("***-");
                        }
                        else {
                            digitalWrite(buzzerPin, HIGH);
                            delay(50); //Wait for 50ms
                            digitalWrite(buzzerPin, LOW);
                            delay(50); //Wait for 50ms
                            digitalWrite(buzzerPin, HIGH);
                            delay(50); //Wait for 50ms
                            digitalWrite(buzzerPin, LOW);
                            passwordCounter = 0; //Reset password to first character
                            lcd.setCursor(6, 1);
                            lcd.print("----");
                        }
                        break;
                    case 3:
                        if(incomingDigit == password[3]) { //If the next password character is correct
                            passwordCounter++; //Switch to next password character
                            digitalWrite(buzzerPin, HIGH);
                            delay(300); //Wait for 300ms
                            digitalWrite(buzzerPin, LOW);
                            lcd.setCursor(6, 1);
                            lcd.print("****");
                            lcd.setCursor(2, 0);
                            lcd.print("Door is Unlocked");
                            lcd.write(byte(1));
                            lcd.print(" A");
                            lcd.write(byte(2));
                            lcd.write(byte(1));
                            lcd.print("ld");
                            lcd.write(byte(1));
                            lcd.print(" ");
                            lcd.setCursor(6, 1);
                            lcd.print("    ");
                            digitalWrite(buzzerPin, HIGH);
                            delay(100); //Wait for 100ms
                            digitalWrite(buzzerPin, LOW);
                            delay(100); //Wait for 100ms
                            digitalWrite(buzzerPin, HIGH);
                            delay(100); //Wait for 100ms
                            digitalWrite(buzzerPin, LOW);
                            //Define the pin to which the servo motor is connected
                            servo.attach(servoPin);
                            for(servoStep; servoStep<181; servoStep++) {
                                servo.write(servoStep);
                                delay(25); //Wait for 25ms
                            }
                            IRReceive.resume();
                            for(int j=0; j<100; j++) {
                                delay(50); //Wait for 50ms
                                if(IRReceive.decode(&result)) {
                                    if(result.value == doorOpenClose) { //If key OK is pressed
                                        j = 100;
                                        delay(200); //Wait for 200ms
                                    }
                                    IRReceive.resume();
                                }
                            }
                            for(servoStep; servoStep>89; servoStep--) {
                                servo.write(servoStep);
                                delay(25); //Wait for 25ms
                            }
                            passwordCounter = 0; //Password return to first character
                            lcd.setCursor(2, 0);
                            lcd.print("Door is Locked");
                            lcd.write(byte(1));
                            lcd.print(" Kilitli");
                            lcd.setCursor(6, 1);
                            lcd.print("----");
                        }
                        else {
                            digitalWrite(buzzerPin, HIGH);
                            delay(50); //Wait for 50ms
                            digitalWrite(buzzerPin, LOW);
                            delay(50); //Wait for 50ms
                            digitalWrite(buzzerPin, HIGH);
                            delay(50); //Wait for 50ms
                            digitalWrite(buzzerPin, LOW);
                            passwordCounter = 0; //Password return to first character
                            lcd.setCursor(6, 1);
                            lcd.print("----");
                        }
                        break;
                    case 4:
                        lcd.setCursor(2, 0);
                        lcd.print("Door is Unlocked");
                        lcd.write(byte(1));
                        lcd.print(" A");
                        lcd.write(byte(2));
                        lcd.write(byte(1));
                        lcd.print("ld");
                        lcd.write(byte(1));
                        lcd.print(" ");
                        lcd.setCursor(6, 1);
                        lcd.print("----");
                        digitalWrite(buzzerPin, HIGH);
                        delay(100); //Wait for 100ms
                        digitalWrite(buzzerPin, LOW);
                        delay(100); //Wait for 100ms
                        digitalWrite(buzzerPin, HIGH);
                        delay(100); //Wait for 100ms
                        digitalWrite(buzzerPin, LOW);
                        for(servoStep; servoStep<181; servoStep++) {
                            servo.write(servoStep);
                            delay(25); //Wait for 25ms
                        }
                        IRReceive.resume();
                        for(int j=0; j<100; j++) {
                            delay(50); //Wait for 50ms
                            if(IRReceive.decode(&result)) {
                                if(result.value == doorOpenClose) { //If key OK is pressed
                                    j = 100;
                                    delay(200); //Wait for 200ms
                                }
                                IRReceive.resume();
                            }
                        }
                        for(servoStep; servoStep>89; servoStep--) {
                            servo.write(servoStep);
                            delay(25); //Wait for 25ms
                        }
                        passwordCounter = 0; //Password return to first character
                        break;
                }
            }
            IRReceive.resume();
        }
    }
    else { //If password change is active
        if(IRReceive.decode(&result)) {
            incomingDigit = digitSolve(result.value); //Solve the incoming digit
            switch(passwordChangeCounter) {
                case 0:
                    if(incomingDigit != 10) { //If incoming number is a valid number
                        password[0] = incomingDigit; //Write the number that comes as the first digit of your password
                        EEPROM.write(addr_password1, incomingDigit); //Save to EEPROM
                        digitalWrite(buzzerPin, HIGH);
                        delay(300); //Wait for 300ms
                        digitalWrite(buzzerPin, LOW);
                        lcd.setCursor(6, 1);
                        lcd.print("*---");
                        passwordChangeCounter++; //Switch to the next character detection
                    }
                    else {
                        digitalWrite(buzzerPin, HIGH);
                        delay(50); //Wait for 50ms
                        digitalWrite(buzzerPin, LOW);
                        delay(50); //Wait for 50ms
                        digitalWrite(buzzerPin, HIGH);
                        delay(50); //Wait for 50ms
                        digitalWrite(buzzerPin, LOW);
                    }
                    break;
                case 1:
                    if(incomingDigit != 10) {
                        password[1] = incomingDigit; //Write the number that comes as the second digit of your password
                        EEPROM.write(addr_password2, incomingDigit); //Save to EEPROM
                        digitalWrite(buzzerPin, HIGH);
                        delay(300); //Wait for 300ms
                        digitalWrite(buzzerPin, LOW);
                        lcd.setCursor(6, 1);
                        lcd.print("**--");
                        passwordChangeCounter++;
                    }
                    else {
                        digitalWrite(buzzerPin, HIGH);
                        delay(50); //Wait for 50ms
                        digitalWrite(buzzerPin, LOW);
                        delay(50); //Wait for 50ms
                        digitalWrite(buzzerPin, HIGH);
                        delay(50); //Wait for 50ms
                        digitalWrite(buzzerPin, LOW);
                    }
                    break;
                case 2:
                    if(incomingDigit != 10) {
                        password[2] = incomingDigit; //Write the number that comes as the third digit of your password
                        EEPROM.write(addr_password3, incomingDigit); //Save to EEPROM
                        digitalWrite(buzzerPin, HIGH);
                        delay(300); //Wait for 300ms
                        digitalWrite(buzzerPin, LOW);
                        lcd.setCursor(6, 1);
                        lcd.print("***-");
                        passwordChangeCounter++;
                    }
                    else {
                        digitalWrite(buzzerPin, HIGH);
                        delay(50); //Wait for 50ms
                        digitalWrite(buzzerPin, LOW);
                        delay(50); //Wait for 50ms
                        digitalWrite(buzzerPin, HIGH);
                        delay(50); //Wait for 50ms
                        digitalWrite(buzzerPin, LOW);
                    }
                    break;
                case 3:
                    if(incomingDigit != 10) {
                        password[3] = incomingDigit; //Write the number that comes as the fourth digit of your password
                        EEPROM.write(addr_password4, incomingDigit); //Save to EEPROM
                        digitalWrite(buzzerPin, HIGH);
                        delay(300); //Wait for 300ms
                        digitalWrite(buzzerPin, LOW);
                        lcd.setCursor(6, 1);
                        lcd.print("****");
                        delay(500); //Wait for 500ms
                        lcd.setCursor(1, 0);
                        lcd.print("Password Changed");
                        lcd.setCursor(2, 1);
                        lcd.print("Successfully");
                        passwordChangeCounter = 0; //Set password change counter to first character
                        passwordInputStatus = 0; //Finish password change process
                        delay(2000); //Wait for 2 seconds
                        lcd.clear();
                        lcd.setCursor(2, 0);
                        lcd.print("Door is Locked");
                        lcd.write(byte(1));
                        lcd.print(" Kilitli");
                        lcd.setCursor(6, 1);
                        lcd.print("----");
                    }
                    else {
                        digitalWrite(buzzerPin, HIGH);
                        delay(50); //Wait for 50ms
                        digitalWrite(buzzerPin, LOW);
                        delay(50); //Wait for 50ms
                        digitalWrite(buzzerPin, HIGH);
                        delay(50); //Wait for 50ms
                        digitalWrite(buzzerPin, LOW);
                    }
                    break;
            }
            IRReceive.resume();
        }
    }
}

//Define the digitSolve function
int digitSolve(long incomingData) {
    //Decide which number the incoming key data is
    if(incomingData == zeroKey) {
        return 0;
    }
    else if(incomingData == oneKey) {
        return 1;
    }
    else if(incomingData == twoKey) {
        return 2;
    }
    else if(incomingData == threeKey) {
        return 3;
    }
    else if(incomingData == fourKey) {
        return 4;
    }
    else if(incomingData == fiveKey) {
        return 5;
    }
    else if(incomingData == sixKey) {
        return 6;
    }
    else if(incomingData == sevenKey) {
        return 7;
    }
    else if(incomingData == eightKey) {
        return 8;
    }
    else if(incomingData == nineKey) {
        return 9;
    }
    else { //If the incoming data is not a digit
        return 10;
    }
}
