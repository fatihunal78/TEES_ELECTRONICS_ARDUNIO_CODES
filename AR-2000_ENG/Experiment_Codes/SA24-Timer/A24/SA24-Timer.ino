//Add IR receiver library
#include <IRremote.h>

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
#define hashKey 0xFFB04F //IR Control key #
#define starKey 0xFF6897 //Star Key
#define leftKey 0xFF10EF //Left Key
#define rightKey 0xFF5AA5 //Right Key

//Define 1602 LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

//Define the pin to which the IR receiver signal pin is connected
int IRPin = 2;

//Define the pin to which the Buzzer is connected
int buzzerPin = 7;

//Define an IR receiver named IRReceive
IRrecv IRReceive(IRPin);

//Define the variable to store the values received from the IR receiver
decode_results result;

//Define the variable to store the seconds counter value
int secondCounter = 0;
int secondTensDigit = 0;
int secondOnesDigit = 0;
int counterValue = 0;

void setup() {
  //Start IR receiver
  IRReceive.enableIRIn();

  //Set the pin to which the Buzzer is connected as output
  pinMode(buzzerPin, OUTPUT);

  lcd.begin();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TEES Electronics");
  lcd.setCursor(2, 1);
  lcd.print("Timer");
  delay(3000);
  lcd.clear();
}

void increaseCounter() {
  secondCounter++;
  digitalWrite(buzzerPin, HIGH);
  delay(150);
  digitalWrite(buzzerPin, LOW);
}

void loop() {
  switch (secondCounter) {
    case 0: //Second tens digit input
      lcd.setCursor(2, 0);
      lcd.print("Counter Value");
      lcd.setCursor(3, 1);
      lcd.print(secondTensDigit);
      lcd.print(secondOnesDigit);
      lcd.print(" second");
      delay(500);
      lcd.setCursor(3, 1);
      lcd.print(" ");
      delay(500);

      //Check if there is any data coming from the IR receiver
      if (IRReceive.decode(&result)) {
        if (result.value == oneKey) {
          secondTensDigit = 1;
          increaseCounter();
        } else if (result.value == twoKey) {
          secondTensDigit = 2;
          increaseCounter();
        } else if (result.value == threeKey) {
          secondTensDigit = 3;
          increaseCounter();
        } else if (result.value == fourKey) {
          secondTensDigit = 4;
          increaseCounter();
        } else if (result.value == fiveKey) {
          secondTensDigit = 5;
          increaseCounter();
        } else if (result.value == sixKey) {
          secondTensDigit = 6;
          increaseCounter();
        } else if (result.value == sevenKey) {
          secondTensDigit = 7;
          increaseCounter();
        } else if (result.value == eightKey) {
          secondTensDigit = 8;
          increaseCounter();
        } else if (result.value == nineKey) {
          secondTensDigit = 9;
          increaseCounter();
        } else if (result.value == zeroKey) {
          secondTensDigit = 0;
          increaseCounter();
        } else if (result.value == rightKey) {
          increaseCounter();
        }

        if (secondCounter == 1) lcd.clear();

        IRReceive.resume();
      }
      break;

    case 1: //Second ones digit input
      lcd.setCursor(2, 0);
      lcd.print("Counter Value");
      lcd.setCursor(3, 1);
      lcd.print(secondTensDigit);
      lcd.print(secondOnesDigit);
      lcd.print(" second");
      delay(500);
      lcd.setCursor(4, 1);
      lcd.print(" ");
      delay(500);

      if (IRReceive.decode(&result)) {
        if (result.value == oneKey) {
          secondOnesDigit = 1;
          increaseCounter();
        } else if (result.value == twoKey) {
          secondOnesDigit = 2;
          increaseCounter();
        } else if (result.value == threeKey) {
          secondOnesDigit = 3;
          increaseCounter();
        } else if (result.value == fourKey) {
          secondOnesDigit = 4;
          increaseCounter();
        } else if (result.value == fiveKey) {
          secondOnesDigit = 5;
          increaseCounter();
        } else if (result.value == sixKey) {
          secondOnesDigit = 6;
          increaseCounter();
        } else if (result.value == sevenKey) {
          secondOnesDigit = 7;
          increaseCounter();
        } else if (result.value == eightKey) {
          secondOnesDigit = 8;
          increaseCounter();
        } else if (result.value == nineKey) {
          secondOnesDigit = 9;
          increaseCounter();
        } else if (result.value == zeroKey) {
          secondOnesDigit = 0;
          increaseCounter();
        } else if (result.value == leftKey) {
          secondCounter--;
          digitalWrite(buzzerPin, HIGH);
          delay(150);
          digitalWrite(buzzerPin, LOW);
          lcd.clear();
        }

        if (secondCounter == 2) {
          counterValue = 10 * secondTensDigit + secondOnesDigit;
          lcd.clear();
        }

        IRReceive.resume();
      }
      break;

    case 2: //Expected key input to start
      lcd.setCursor(0, 0);
      lcd.print("Time: ");
      lcd.print(counterValue);
      lcd.print(" sec");
      lcd.setCursor(0, 1);
      lcd.print("Press * to Start");

      if (IRReceive.decode(&result)) {
        if (result.value == starKey) { //If the key pressed is star
          secondCounter++;
          digitalWrite(buzzerPin, HIGH);
          delay(150);
          digitalWrite(buzzerPin, LOW);
          lcd.clear();
        }
        IRReceive.resume();
      }
      break;

    case 3: //Count down
      secondTensDigit = counterValue / 10;
      secondOnesDigit = counterValue % 10;
      lcd.setCursor(0, 0);
      lcd.print("Counting Down...");
      lcd.setCursor(3, 1);
      lcd.print(secondTensDigit);
      lcd.print(secondOnesDigit);
      lcd.print(" second");
      delay(1000);
      counterValue--;

      if (counterValue < 0) {
        lcd.clear();
        lcd.setCursor(2, 0);
        lcd.print("Countdown is over");
        lcd.setCursor(3, 1);
        lcd.print("Press #");

        while (1) {
          digitalWrite(buzzerPin, HIGH);
          delay(150);
          digitalWrite(buzzerPin, LOW);
          delay(150);

          if (IRReceive.decode(&result)) {
            if (result.value == hashKey) {
              secondCounter = 0;
              lcd.clear();
              break;
            }
            IRReceive.resume();
          }
        }
      }
      break;
  }
}