// SA58 - Meteorological station

#include <LiquidCrystal_I2C.h> // Add I2C LCD library
#include <DHT.h>               // Add DHT library

#define DHTPIN 2     // Define DHT pin number
#define DHTTYPE DHT11 // Define DHT model

DHT dht(DHTPIN, DHTTYPE); // Create a sensor named DHT

// Define custom characters for LCD
byte characterdot[8] = {0x02, 0x05, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00}; // Dot for degree symbol
byte characterThermometer[8] = {0x0E, 0x0A, 0x0A, 0x0E, 0x1F, 0x1F, 0x1F, 0x0E}; // Thermometer symbol
byte characterWaterdrop1[8] = {0x04, 0x0E, 0x1F, 0x1F, 0x1F, 0x0E, 0x00, 0x00};   // Water drop symbol 1
byte characterWaterdrop2[8] = {0x00, 0x00, 0x04, 0x0E, 0x1F, 0x1F, 0x1F, 0x0E};   // Water drop symbol 2

// Define 1602 LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  dht.begin(); // Start DHT sensor

  lcd.begin();      // Start the LCD display
  lcd.backlight();  // Turn ON the LCD backlights

  // Define added characters
  lcd.createChar(1, characterdot);         // Create degree symbol
  lcd.createChar(2, characterThermometer); // Create thermometer character
  lcd.createChar(3, characterWaterdrop1);  // Create water drop 1 character
  lcd.createChar(4, characterWaterdrop2);  // Create water drop 2 character

  lcd.clear();      // Clear the LCD display
  lcd.setCursor(0, 0); // Go to the first row, first character on the LCD display
  lcd.print("TEES Electronics"); // Write "TEES Electronics" on the LCD display
  lcd.setCursor(0, 1); // Go to the lower row, first character on the LCD display
  lcd.print("  Meteorology  ");  // Write to the LCD display
  delay(3000); // Wait for 3 seconds
  lcd.clear(); // Clear the LCD display
}

void loop() {
  // Query DHT temperature
  int temperature = dht.readTemperature();
  // Query DHT humidity status
  int humidity = dht.readHumidity();

  lcd.setCursor(0, 0); // Go to the first row, first character on the LCD display
  lcd.write(byte(2));  // Write thermometer symbol to the LCD display
  lcd.print("Temperature:"); // Write to the LCD display
  lcd.print(temperature);    // Write temperature variable to the LCD display
  lcd.write(byte(1));        // Write the degree symbol to the LCD display
  lcd.print("C");            // Write to the LCD display

  lcd.setCursor(0, 1); // Switch to the lower row
  lcd.write(byte(3));  // Write the water drop 1 symbol on the LCD display
  lcd.write(byte(4));  // Write the water drop 2 symbol on the LCD display
  lcd.print("Humidity: "); // Write to the LCD display
  lcd.print(humidity);     // Write humidity value variable to the LCD display
  lcd.print("% RH");       // Write to the LCD display
}