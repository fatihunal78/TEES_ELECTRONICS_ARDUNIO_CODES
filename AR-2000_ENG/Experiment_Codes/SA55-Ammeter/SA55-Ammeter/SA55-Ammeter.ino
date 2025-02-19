// SA55 - Ammeter

#include <LiquidCrystal_I2C.h> // Add I2C LCD library

LiquidCrystal_I2C lcd(0x27, 16, 2); // Define 1602 LCD display

// Define variables
int ADCPin = 0;          // Define the pin number to which the ADC is connected
float Vout = 0.0;        // Define the variable to store the output voltage
float Current_Value = 0.0; // Define the variable to store the calculated current value
int readValue = 0;       // Define the variable to store the ADC read value

void setup() {
  lcd.begin();           // Start the LCD display
  lcd.backlight();       // Turn ON LCD backlights
  pinMode(ADCPin, INPUT); // Define ADC pin as input

  lcd.clear();           // Clear the LCD display
  lcd.setCursor(0, 0);   // Go to the first row, first character on the LCD display
  lcd.print("TEES ELECTRONICS"); // Write "TEES ELECTRONICS" on the LCD display
  lcd.setCursor(2, 1);   // Select LCD lower row, third character
  lcd.print("AMMETER");  // Write "AMMETER" on the LCD display
  delay(3000);           // Wait for 3 seconds
  lcd.clear();           // Clear the LCD display
}

void loop() {
  readValue = analogRead(ADCPin); // Read the value on ADCPin and save it to the readValue variable
  Vout = (readValue * 5.0) / 1024.0; // Convert the ADC value to voltage (Vout = (readValue * Vref) / 1024)

  // Calculate the current value using the formula I = Vout / R, where R = 32 ohms
  // Convert to milliamperes by multiplying by 1000: I = (Vout / 32) * 1000 = Vout * 31.25
  Current_Value = Vout * 31.25;

  lcd.clear();           // Clear the LCD display
  lcd.setCursor(0, 1);   // Switch to the second row on the LCD display
  lcd.print("CURRENT:"); // Write "CURRENT:" on the LCD display
  lcd.print(Current_Value); // Write the calculated Current_Value on the LCD display
  lcd.print(" mA");      // Write "mA" on the LCD display
  delay(1000);           // Wait for 1 second
}