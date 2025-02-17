//SA61 - Password protected vault lock

#include <Servo.h>                  //Add servo library
#include <LiquidCrystal_I2C.h>     //Add I2C LCD library
#include <Keypad.h>                 //Add Keypad Library

//We need to specify how many rows and columns there are on the keypad we use
//The keypad on the panel is 4x4, that is, there are 4 rows and 4 columns
const byte ROW = 4;
const byte COLUMN = 4;
int buzzerPin = 4;                  //Define the pin number to which the Buzzer is connected

//Define the position and order of the keys in the row and column
char keys[ROW][COLUMN] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

//Define the pins to which the row and column pins of the keypad are connected
byte rowPins[ROW] = {13, 12, 11, 10};
byte columnPins[COLUMN] = {9, 8, 7, 6};

//Start the keypad
Keypad keyPad = Keypad(makeKeymap(keys), rowPins, columnPins, ROW, COLUMN);

LiquidCrystal_I2C lcd(0x27, 16, 2);    //Define 1602 LCD display

Servo servo;                            //We created a Servo object named servo

int lock = HIGH;

/* 
* string is a type of variable that stores multiple characters in the memory. 
* Features such as string splitting, merging, finding/deleting/changing the desired letter are used frequently. 
*/

String enteredPassword = "";            //Define the variable to store the entered password
String password = "1234";               //Define the variable to sore the initial password and set it 1234
int Servo_position;                     //Define the variable to store the position of the servo motor

int buttonPin = 2;                      //Define the pin number to which the Button is connected
int servoPin = 3;                       //Define the pin number to which the servo motor is connected

void setup() {
    servo.attach(servoPin);             //Set the pin to which the servo motor is connected
    servo.write(0);                     //Set the starting position of the servo motor to 0-degree
    pinMode(buttonPin, INPUT_PULLUP);   //Set the pin to which the Button is connected as input
    pinMode(buzzerPin, OUTPUT);         //Set the pin to which the Buzzer is connected as output
    lcd.begin();                        //Start the LCD display
    lcd.backlight();                    //Turn ON the LCD backlights
    lcd.clear();                        //Clear the LCD display
    lcd.setCursor(0, 0);               //Switch to the first row
    lcd.print("TEES ELECTRONICS");      //Write "TEES ELECTRONICS"
    lcd.setCursor(0, 1);               //Switch to the lower row
    lcd.print("Vault Lock Project");
    delay(2000);                        //Wait for 2 seconds
    lcd.clear();                        //Clear the LCD display
    lcd.setCursor(0, 0);               //Switch to the first row
    lcd.print("Enter Password");        //Write Enter Password on the LCD display
    delay(1000);                        //Wait for 1 second
    lcd.clear();                        //Clear the LCD display
}

void loop() {
    char key = keyPad.getKey();         //Save the values pressed from the Keypad to the key variable

    if (key != NO_KEY) {                //If any key is pressed
        switch (key) {                   //Go to the case in the switch case structure that corresponds to which key was pressed
            case '*':                    //If the star key is pressed
                lcd.clear();             //Clear LCD display
                enteredPassword = "";    //Reset the password entered
                if (Servo_position == 0) {   //If servo_position is 0, that is, locked
                    servo.write(0);          //Keep servo motor at 0-degree position
                } else {                     //If servo position is different from 0
                    for (Servo_position = 90; Servo_position >= 0; Servo_position = Servo_position - 1) {
                        servo.write(Servo_position);   //Bring the servo to the 0-degree position by decreasing it by one step each
                        delay(10);
                    }
                    Servo_position = 0;      //Set servo position to 0-degree
                }
                digitalWrite(buzzerPin, HIGH);
                delay(50);
                digitalWrite(buzzerPin, LOW);
                delay(50);
                lcd.setCursor(0, 0);         //Switch to the first row
                lcd.print("Vault is Locked"); //Write "Vault is Locked" to the LCD display
                delay(1000);                 //Wait for 1 second
                lcd.clear();                 //Clear LCD display
                lock = HIGH;                 //Make lock variable high
                break;                       //Finish the case '*'

            case 'A':                       //If A is pressed
                if (!lock) {                //If the vault is not locked
                    lcd.setCursor(0, 1);    //Switch to the lower row
                    for (int i = 0; i < 2; i++) {
                        digitalWrite(buzzerPin, HIGH);
                        delay(50);
                        digitalWrite(buzzerPin, LOW);
                        delay(50);
                    }
                    lcd.print("Password Changed!");    //Write "Password Changed" to the LCD display!
                    password = enteredPassword;        //Set password variable equal to enteredPassword variable
                } else {                              //If the vault is locked
                    lcd.print("Unlock to Change");    //Write "Unlock to Change Password" on the LCD display
                    lcd.setCursor(0, 1);
                    lcd.print("    Password    ");
                }
                enteredPassword = "";                 //Reset the password entered
                delay(1000);                         //Wait for 1 second
                lcd.clear();                         //Clear the LCD display
                break;                              //Finish case 'A'

            case '#':                              //If # key is pressed
                if (enteredPassword == password) { //If the password entered is the same as the password
                    lcd.clear();                  //Clear LCD display
                    lcd.print("Lock is Opened");  //Write "Lock is Opened" on the LCD display
                    for (int i = 0; i < 2; i++) {
                        digitalWrite(buzzerPin, HIGH);
                        delay(50);
                        digitalWrite(buzzerPin, LOW);
                        delay(50);
                    }
                    delay(1000);                  //Wait for 1 second
                    lcd.clear();                  //Clear the LCD display
                    lcd.setCursor(0, 0);          //Switch to the first row
                    lcd.print("Press PB2 Button"); //Write "Press PB2 Button to Open" to the LCD display
                    lcd.setCursor(0, 1);          //Switch to the lower row
                    lcd.print("   to Open   ");
                    delay(1500);                  //Wait for 1.5 second
                    lock = LOW;                   //Make lock variable LOW
                } else {                          //If the entered password variable is not equal to the password variable
                    lcd.setCursor(0, 0);          //Switch to the first row
                    lcd.print("Wrong Password");  //Write "Wrong Password" on the LCD display
                    lcd.setCursor(0, 1);          //Switch to the lower row
                    lcd.print(" Try Again ");     //Write "Try Again" on the LCD display
                }
                delay(1000);                      //Wait for 1 second
                enteredPassword = "";             //Reset the password entered
                break;                            //Exit the case '#'

            default:                              //If it cannot enter any case state, it remains in the default state
                lcd.print(key);                   //Write the keys entered on the LCD display
                enteredPassword += key;           //Write the entered password side by side consecutively
                break;
        }
    }

    if (digitalRead(buttonPin) == LOW && lock == LOW) {   //If the button is pressed and the lock is opened
        if (Servo_position == 90) {                       //If servo motor is at 90 degree position
            servo.write(90);                              //Keep servo motor in 90 degree position
        } else {                                          //If servo motor is not at 90-degree position
            for (Servo_position = 0; Servo_position <= 90; Servo_position = Servo_position + 1) {
                servo.write(Servo_position);              //Write the position to servo motor
                delay(10);
            }
            Servo_position = 90;                          //Set Servo_position variable to 90-degree
            lcd.clear();                                  //Clear the LCD display
            lcd.setCursor(0, 0);                          //move the LCD cursor to the top row
            lcd.print("Vault is Opened");                 //Write "Vault is Opened" on the LCD display
            lcd.setCursor(0, 1);                          //Switch to 2nd row on the LCD display
        }
    }
}
