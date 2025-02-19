//SA106 - Pulse monitor

#define USE_ARDUINO_INTERRUPTS true    //Activate the interruptions required for Heart Rhythm measurement 
#include <PulseSensorPlayground.h>     //Add Pulse Sensor library
#include <LiquidCrystal_I2C.h>        //Add I2C LCD library

LiquidCrystal_I2C lcd(0x27, 16, 2);   //Define 1602 LCD display

const int PulseSensor = A0;           //Define the pin number to which the sensor is connected
const int LEDPin = 3;                 //Define the pin number to which the LED is connected
const int speakerPin = 6;             //Define the pin number to which the Speaker is connected

int Threshold = 200;                  //This value can be adjusted for the sensor to read properly
                                 
uint8_t character0[8] = {
    0x0, 0x0, 0xA, 0x1F, 
    0x1F, 0xE, 0x4, 0x0
};                                    //Heart symbol
                             
PulseSensorPlayground pulseSensor;    //Create an object named pulseSensor

void setup() { 
    Serial.begin(9600); 
    pinMode(speakerPin, OUTPUT);      //Set the pin to which the Speaker is connected as output
  
    lcd.begin();                      //Start the LCD display
    lcd.backlight();                  //Turn ON the LCD backlights
    lcd.clear();                      //Clear the LCD display
  
    lcd.createChar(0, character0);    //Create the heart symbol and define it to address 0
  
    pulseSensor.analogInput(PulseSensor);  //Read from the analog pin for pulseSensor 
    pulseSensor.blinkOnPulse(LEDPin);      //For each pulse to turn ON the LED
    pulseSensor.setThreshold(Threshold); 

    if(pulseSensor.begin()) { 
        lcd.clear();
        lcd.print("BPM:");            //Heartbeat per minute
    }
  
    lcd.setCursor(0, 0);              //Switch to the first row
    lcd.print("TEES ELECTRONICS");     //Write "TEES ELECTRONICS" on the first row
    lcd.setCursor(0, 1);              //Switch to the second row
    lcd.print("HEART RHYTHM MEASURE"); //Write "HEART RHYTHM MEASURE" on the LCD display
    delay(2000);                      //Wait for 2 seconds
    lcd.clear();
    lcd.setCursor(0, 0);              //Switch to the first row
    lcd.print("For Measurement");      //Write "For Measurement" on the first row
    lcd.setCursor(0, 1);              //Switch to the second row
    lcd.print("Put Your Finger");      //Write "Put Your Finger" on the LCD display
    delay(2000);                      //Wait for 2 seconds
}

void loop() {
    int myBPM = pulseSensor.getBeatsPerMinute();  //Call getBeatsPerMinute() from the library to read values
         
    if(pulseSensor.sawStartOfBeat()) {            //Start sensor if there is heartbeat
        tone(speakerPin, 1047);
        lcd.clear(); 
        lcd.print((char)0);                       //Print the heart symbol on the LCD display
        lcd.print(" BPM:");
        lcd.print(myBPM); 
    }
    else {
        noTone(speakerPin);
    }
    delay(10); 
}
