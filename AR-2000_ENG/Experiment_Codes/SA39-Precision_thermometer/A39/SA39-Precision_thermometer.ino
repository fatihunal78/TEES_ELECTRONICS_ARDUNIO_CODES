//SA39 - Precision thermometer

#include <LiquidCrystal_I2C.h> // Add I2C LCD library
#include <DHT.h> // Add DHT library

#define DHTPIN 2 // Define DHT pin number
#define DHTTYPE DHT11 // Define DHT model

DHT dht(DHTPIN, DHTTYPE); // Create a sensor named DHT

// Define Turkish characters for LCD
byte characterdot[8] = {0x02, 0x05, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00}; // Dot for degree symbol
byte characteri[8] = {0x0, 0x0, 0x4, 0x4, 0x4, 0x4, 0x0}; // ı

LiquidCrystal_I2C lcd(0x27, 16, 2); // Define 1602 LCD display

void setup() {
  dht.begin(); // Start DHT sensor

  lcd.begin(); // Start the LCD display
  lcd.backlight(); // Turn ON the LCD backlights
  // Define added characters
  lcd.createChar(2, characterdot); // Create degree symbol
  lcd.clear(); // Clear the LCD display
  lcd.setCursor(0, 0); // Go to the first row, first character on the LCD display
  lcd.print("TEES Electronics"); // Write "TEES Electronics" on the LCD display
  lcd.setCursor(0, 1); // Go to the lower row, first character on the LCD display
  lcd.print("DHT11 Temperature"); // Write to the LCD display

  delay(3000); // Wait for 3 seconds
  lcd.clear(); // Clear the LCD display 
}

void loop() {
  // Query DHT temperature
  float temperature = dht.readTemperature();

  lcd.setCursor(0, 0); // Go to the first row, first character on the LCD display
  lcd.print("Temperature:"); // Write to the LCD display

  lcd.setCursor(12, 0); // Move cursor to next position for temperature value
  lcd.print(temperature); // Write temperature variable to the LCD display
  lcd.write(byte(2)); // Write the degree symbol to the LCD display
  lcd.print("C"); // Write to the LCD display

  delay(2000); // Wait for 2 seconds before updating the display
}
