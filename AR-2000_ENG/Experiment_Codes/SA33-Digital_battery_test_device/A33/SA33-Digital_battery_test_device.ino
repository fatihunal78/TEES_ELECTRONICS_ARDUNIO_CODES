//SA33 - Digital battery test device

#include <LiquidCrystal_I2C.h> // Add I2C LCD library

LiquidCrystal_I2C lcd(0x27, 16, 2); // Define 1602 LCD display

// Define the characters required for the creation of the battery symbol on the LCD display
uint8_t characters1[8] = {0x3, 0x2, 0x2, 0xE, 0x10, 0x1F, 0x1F, 0x1F}; 
uint8_t characters2[8] = {0x18, 0x8, 0x8, 0xE, 0x1, 0x1F, 0x1F, 0x1F}; 
uint8_t characters3[8] = {0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F}; 
uint8_t characters4[8] = {0x3, 0x2, 0x2, 0xE, 0x10, 0x10, 0x10, 0x10}; 
uint8_t characters5[8] = {0x18, 0x8, 0x8, 0xE, 0x1, 0x1, 0x1, 0x1}; 
uint8_t characters6[8] = {0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x1F, 0x1F}; 
uint8_t characters7[8] = {0x1, 0x1, 0x1, 0x1, 0x1, 0x1F, 0x1F, 0x1F}; 
uint8_t characters8[8] = {0xA, 0x0, 0xE, 0x11, 0x11, 0x11, 0x11, 0xE}; // letter Ö

int ADCPin = 0; // Define the pin to be used for reading values
// Define the variables to store the voltage read
float Vout = 0.0; 
float Voltage = 0.0;
float R1 = 100000.0; // Define the value of the resistor connected to the + end of the probe is 100K
float R2 = 10000.0;  // Define the value of the resistor connected to the probe-end is 10K
int readValue = 0;

void setup() {
  lcd.begin();      // Start the LCD display
  lcd.backlight();  // Turn ON LCD backlights 
  
  // Create the characters to be used for the battery symbol
  lcd.createChar(1, characters1); 
  lcd.createChar(2, characters2); 
  lcd.createChar(3, characters3); 
  lcd.createChar(4, characters4); 
  lcd.createChar(5, characters5); 
  lcd.createChar(6, characters6); 
  lcd.createChar(7, characters7); 
  lcd.createChar(8, characters8); 
   
  pinMode(ADCPin, INPUT); // Define ADC pin as input
   
  lcd.clear();            // Clear the LCD display
  lcd.setCursor(0, 0);    // Go to the first row, first character on the LCD display
  lcd.print("TEES ELECTRONICS"); // Write "TEES ELECTRONICS" on the LCD display
  lcd.setCursor(2, 1);    // Select LCD lower row third character
  lcd.print("Battery Tester"); // Write to the LCD display
  lcd.print(char(8));     // Ö
  lcd.print("lcer");
    
  delay(3000);            // Wait for 3 seconds
  lcd.clear();            // Clear the LCD display
}

void loop() {
  readValue = analogRead(ADCPin); // Read the value on ADCPin and save it to the readValue variable.
  Vout = (readValue * 5.0) / 1024.0; // Multiply the readValue by 5 and divide by 1024 to find the voltage equivalent 
                                     // of the measured value 
  Voltage = Vout / (R2 / (R1 + R2)); // Find the Voltage value you want to measure by proportioning the voltages 
                                     // on the resistors with the voltages corresponding to the voltage
  
  if (Voltage < 0.09) { // If the Voltage value is less than 0.09 
    Voltage = 0.0;      // Set the Voltage value to zero. 
  } 

  // Show half-charged battery character on the LCD display. 
  lcd.setCursor(0, 0);
  lcd.print(char(1));
  lcd.print(char(2));
  lcd.setCursor(0, 1); // Switch to 2nd row (lower row) on the LCD display 
  lcd.print(char(3));
  lcd.print(char(3));
  
  lcd.setCursor(3, 0);
  lcd.print("Battery: ");
  lcd.print(Voltage); // Write the calculated Voltage value on the LCD display
  lcd.print(" V");    // Write "V" on the LCD display 
  
  if (Voltage == 0) { // If voltage is 0
    // Display the dead battery character on the LCD display. 
    lcd.setCursor(0, 0);
    lcd.print(char(4));
    lcd.print(char(5));
    lcd.setCursor(0, 1); // Switch to 2nd row (lower row) on the LCD display 
    lcd.print(char(6));
    lcd.print(char(7));
  }
  delay(500);
}