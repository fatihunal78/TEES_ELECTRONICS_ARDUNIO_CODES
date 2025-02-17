//SA79 - Fan with advanced thermostat

#include <DHT.h>                                  //Add DHT library
#include <LiquidCrystal_I2C.h>                   //Add I2C LCD library

LiquidCrystal_I2C lcd(0x27, 16, 2);             //Define 1602 LCD display

uint8_t character0[8] = {
    0xC, 0x12, 0x12, 0xC, 0x0, 0x0, 0x0, 0x0    //Character to show degree symbol
};

int potPin = A0;                                 //Define the digital pin number to which the Potentiometer is connected
int potValue = 0;                                //Define the variable to store the Potentiometer value
int setTemperature = 0;                          //Define the variable to store the set temperature value
int temperature;                                 //Define the variable to store the temperature value
int fanStatus = 0;                               //Define the variable to store the fan status

int buttonPin = 2;                               //Define the pin number to which the Button is connected
int LEDPin = 5;                                  //Define the pin number to which the LED is connected
int motorPin = 4;                                //Define the pin number to which the transistor is connected

#define DHTPIN 3                                 //Define DHT pin number
#define DHTTYPE DHT11                            //Define DHT model
DHT dht(DHTPIN, DHTTYPE);                        //Create a sensor named dht

void setup() {
    dht.begin();                                 //Start DHT sensor
    pinMode(motorPin, OUTPUT);                   //Set the pin to which the transistor is connected as output
    pinMode(LEDPin, OUTPUT);                     //Set the pin to which the LED is connected as output
    pinMode(buttonPin, INPUT_PULLUP);            //Set the pin to which the button is connected as input
    
    lcd.begin();                                 //Start the LCD display
    lcd.backlight();                            //Turn ON the LCD backlights
    lcd.clear();                                //Clear the LCD display
    
    lcd.createChar(0, character0);              //Create the degree symbol and define it to address 0
    
    lcd.setCursor(0, 0);                        //Switch to the first row on the LCD display 
    lcd.print("   Fan with");                   //Write "Fan with Thermostat" on the LCD display 
    lcd.setCursor(0, 1);                        //Switch to the lower row
    lcd.print("   Thermostat");
    delay(2000);                                //Wait for 2 seconds 
    lcd.clear();                                //Clear the LCD display 
}

void loop() {
    if(digitalRead(buttonPin) == LOW) {         //If the Button is pressed
        while(digitalRead(buttonPin) == LOW);    //Wait as long as the button is pressed
        if(fanStatus == 1)                      //If the fan is running
            fanStatus = 0;                      //Save fan state as OFF
        else                                    //If the fan is not working
            fanStatus = 1;                      //Save fan state as ON
    }
    
    potValue = analogRead(potPin);              //Read the value of the potentiometer and save it to the variable
    setTemperature = map(potValue, 0, 1023, 15, 50);  //Proportion the read value to the range of 15-50 and save it
    temperature = dht.readTemperature();        //Query DHT temperature
    
    lcd.setCursor(0, 0);
    lcd.print("Set Temp: ");
    lcd.print(setTemperature);
    lcd.print((char)0);                        //Print the degree symbol on the LCD display
    lcd.print("C");
    
    lcd.setCursor(0, 1);
    lcd.print("Measured: ");
    lcd.print(temperature);
    lcd.print((char)0);                        //Print the degree symbol on the LCD display
    lcd.print("C");
    
    if(temperature > setTemperature || fanStatus == 1) {  //If measured temperature higher than set or fan is ON
        digitalWrite(motorPin, HIGH);           //Switch the transistor to conduction state
        digitalWrite(LEDPin, HIGH);             //Turn ON the LED
    } else {
        digitalWrite(motorPin, LOW);            //Switch the transistor to cut-off state
        digitalWrite(LEDPin, LOW);              //Turn OFF the LED
    }
    
    delay(50);                                 //Wait for 50ms
}
