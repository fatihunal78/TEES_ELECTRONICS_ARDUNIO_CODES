// S16 - Adjusting LED brightness (Dimmer)
int LEDPin = 3;    //Define the digital pin number to which the LED is connected. 
                   //We state that the LED is connected to pin number 3
                
int potPin = A0;   //Define the analog pin number to which the Potentiometer is connected.
                   //We stated that the middle leg of the Potentiometer is connected to the analog 0 (A0) pin
                  
int brightness = 0; //Define the variable where we will store the brightness value of the LED.
                   //We did not define any pins here, we just set the initial value of a variable named brightness equal to zero.
                   
int potValue = 0;  //Define the variable where we will store the value of the Potentiometer.
                   //We did not define any pins here, we just set the initial value of a variable named potValue equal to zero

void setup() {
    //Since analog pins are input pins, you do not need to make any definition under setup.
    //Here we will only set our LED as output 
    pinMode(LEDPin, OUTPUT);    //Set the pin to which the LED is connected as output
}

void loop() {
    //Potentiometers are adjustable resistors. When you turn it, the resistance value increases or decreases.
    //According to this increase or decrease, the digital equivalents of the voltage values at the analog pin (A0 pin) are displayed.
    //For example, when the Potentiometer is in the middle position, it reads half of 5V from the analog pin.
    //This value corresponds to 512 in the digital system. 
  
    potValue = analogRead(potPin);    //Read the value of the Potentiometer and write it to the variable. $$
                                     //It reads a value between 0 and 1023 depending on the voltage on the 2nd leg of the Potentiometer.
                                   
    //map function is a tool for proportioning a variable from one range to another range
    //We can proportionate a number in the range 0-1023 to a number in the range 0-255.
    //newVariable = map(oldVariable, 0, 1023, 0, 255); We can do this with this command
    //LED brightness can be adjusted between 0-255. $$
    //map function brings the value read in the range of 0-1023 to the value of 0-255, which is where the LED brightness is adjusted. 
    //For example, if the reading is 1000, the map function converts it to 250
  
    brightness = map(potValue, 0, 1023, 0, 255);    //That is, the value between 0 and 1023 read from the potValue variable
                                                    //is proportionated between 0 and 255 and saved in the brightness variable

    /*
     * analogWrite(pinNumber,value) command can generate a PWM signal
     * With this PWM signal we can control the brightness of the LED, the rotation speed of the motor and so on.
     * PWM signal has an important role in Arduino coding.
     * analogWrite(pinNumber,value); where pinNumber represents the pin to which the LED is connected
     * The value variable specifies how much PWM signal should be sent to that pin.
     * The pins that provide PWM output on the Arduino are: pins 3, 5, 6, 9, 10 and 11.
     */

    analogWrite(LEDPin, brightness);    //We proportionated the value read from the Potentiometer with the map function and saved it in the brightness variable.
                                       //We assigned the value of the brightness variable to the LEDPin pin, that is, pin number 3 to which the LED is connected.
                                       //When this brightness variable varies from 0 to 255 depending on the rotation of the Potentiometer
                                       //Brightness of the LED will also change.
    delay(50);    //Wait for 50ms
}
