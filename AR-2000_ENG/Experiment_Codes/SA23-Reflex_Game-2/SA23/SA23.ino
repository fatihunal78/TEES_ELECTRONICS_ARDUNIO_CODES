//SA23 - Reflex Game-2

//Add I2C LCD library
#include <LiquidCrystal_I2C.h>

//Define 1602 LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte characterk[8] = {
  0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F
}; //Box character

byte characterarrow[8] = {
  0x00, 0x04, 0x04, 0x04, 0x04, 0x1F, 0x0E, 0x04
}; //Arrow character

#define target 8

int music[] = {
  262, 196, 196, 220, 196, 0, 247, 262
};

int noteTimes[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

//Define the variable in which the character will be stored
int character = 0;

//Define the digital pin number to which the PB2 Button is connected
int ButtonPB2 = 2;

//Define the digital pin number to which the PB1 Button is connected
int ButtonPB1 = 3;

//Define the pin number to which the Speaker is connected
int speakerPin = 4;

int difficultyLevel = 3; //1 - hard, 2 - moderate, 3 - simple

long level;

//Define the variable to store the last time
unsigned long long lastTime;

void setup() {
  //Set the pin to which the PB2 Button is connected as input
  pinMode(ButtonPB2, INPUT_PULLUP);
  //Set the pin to which the PB1 Button is connected as input
  pinMode(ButtonPB1, INPUT_PULLUP);
  //Set the pin to which the Speaker is connected as output
  pinMode(speakerPin, OUTPUT);

  lcd.begin(); //Start the LCD display
  lcd.backlight(); //Turn ON the LCD backlights
  lcd.createChar(1, characterk); //Create box character
  lcd.createChar(2, characterarrow); //Create arrow character
  lcd.clear(); //Clear the LCD display
  lcd.setCursor(0, 0);
  lcd.print("TEES Electronics");
  lcd.setCursor(0, 1);
  lcd.print("Reflex Game 2");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0); //Go to the first row and first column on the LCD display
  lcd.print("Difficulty Level");
  lcd.setCursor(6, 1); //Go to lower row and sixth column on the LCD display
  lcd.print("Easy");
}

void loop() {
  lcd.setCursor(0, 0); //Go to the first row and first column on the LCD display
  lcd.print("Difficulty Level");

  if (digitalRead(ButtonPB1) == LOW) { //If PB1 button is pressed 
    difficultyLevel--; //Increase difficulty level
    if (difficultyLevel < 1) difficultyLevel = 3;
    delay(200); //Wait for 200ms 
    if (difficultyLevel == 3) {
      lcd.clear(); 
      lcd.setCursor(6, 1); 
      lcd.print("Easy");
    } //If the difficultyLevel variable is 3, write "Easy" at the bottom row of the LCD display
    else if (difficultyLevel == 2) {
      lcd.clear(); 
      lcd.setCursor(6, 1); 
      lcd.print("Moderate");
    } //If the difficultyLevel variable is 2, write "Medium" at the bottom row of the LCD display
    else if (difficultyLevel == 1) {
      lcd.clear(); 
      lcd.setCursor(6, 1); 
      lcd.print("Hard");
    } //If the difficultyLevel variable is 3, type "Hard" in the bottom row of the LCD display
  }

  if (digitalRead(ButtonPB2) == LOW) { //If PB2 button is pressed 
    lcd.clear(); //Clear LCD display 
    while (1) { //Enter infinite loop 
      lcd.setCursor(8, 0);
      lcd.write(byte(2));
      lcd.setCursor(character, 1);
      lcd.print(" ");
      character = random(0, 16); //Randomly determine where your character will go
      lcd.setCursor(character, 1);
      lcd.write(byte(1));
      lastTime = micros(); //Save last time
      level = 250000 * difficultyLevel; //Determine the level variable by multiplying the 
                                        //difficulty level by 25000 
      while (micros() - lastTime <= level) { //Determine key press
        if (digitalRead(ButtonPB2) == LOW) { //If button is pressed
          if (character == target) { //If pressed when it comes to the specified character
            won(); //Run the won function
            break; //Exit the loop
          } else { //If it is not pressed when it reaches the specified character
            lost(); //Run the lost function
            break; //Exit the loop
          }
        }
      }
      if (digitalRead(ButtonPB1) == LOW) //If PB1 button is pressed 
        break; //Exit infinite loop
    }
  }
}

//Define the lost animation function
void lost() {
  lcd.setCursor(0, 1);
  lcd.print("                ");
  for (int j = 1; j < 4; j++) {
    lcd.setCursor(0, 1);
    for (int i = 0; i < 16; i++)
      lcd.write(byte(1));
    tone(speakerPin, 100);
    delay(500);
    noTone(speakerPin);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    delay(500);
  }
}

//Define the winning animation function
void won() {
  lcd.setCursor(0, 1);
  lcd.print("                ");
  for (int i = 0; i < 8; i++) {
    int noteTime = 1000 / noteTimes[i];
    tone(speakerPin, music[i], noteTime);
    int waitBetweenNotes = noteTime * 1.30;
    lcd.setCursor(0, 1);
    for (int i = 0; i < 8; i++)
      lcd.write(byte(1));
    delay(waitBetweenNotes / 2);
    lcd.setCursor(0, 1);
    lcd.print("        ");
    lcd.setCursor(8, 1);
    for (int i = 0; i < 8; i++)
      lcd.write(byte(1));
    delay(waitBetweenNotes / 2);
    lcd.setCursor(0, 1);
    lcd.print("                ");
    noTone(speakerPin);
  }
}