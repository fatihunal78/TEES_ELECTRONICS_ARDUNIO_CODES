//SA40 - Hygrometer

#include <LiquidCrystal_I2C.h> // Add I2C LCD library
#include <DHT.h> // Add DHT library

#define DHTPIN 2 // Define DHT pin number
#define DHTTYPE DHT11 // Define DHT model

DHT dht(DHTPIN, DHTTYPE); // Create a sensor named DHT

// Define 1602 LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  dht.begin(); // Start DHT sensor

  lcd.begin(); // Start the LCD display
  lcd.backlight(); // Turn ON the LCD backlights
  
  lcd.clear(); // Clear the LCD display
  lcd.setCursor(0, 0); // Go to the first row, first character on the LCD display
  lcd.print("TEES Electronics"); // Write "TEES Electronics" on the LCD display
  lcd.setCursor(0, 1); // Go to the lower row, first character on the LCD display
  lcd.print(" Hygrometer "); // Write to the LCD display
  delay(3000); // Wait for 3 seconds
  lcd.clear(); // Clear the LCD display
}

void loop() {
  // Query DHT humidity status
  float humidity = dht.readHumidity();

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity)) {
    lcd.setCursor(0, 0); // Switch to the first row on the LCD
    lcd.print("Failed to read"); // Write error message to the LCD display
    lcd.setCursor(0, 1); // Switch to the second row on the LCD
    lcd.print("from DHT sensor");
    delay(2000);
    return;
  }
  
  lcd.setCursor(0, 0); // Switch to the first row on the LCD
  lcd.print("Humidity: "); // Write to the LCD display
  lcd.print(humidity); // Write humidity value variable to the LCD display
  lcd.print("% RH"); // Write to the LCD display

  delay(2000); // Wait for 2 seconds before updating the display
}