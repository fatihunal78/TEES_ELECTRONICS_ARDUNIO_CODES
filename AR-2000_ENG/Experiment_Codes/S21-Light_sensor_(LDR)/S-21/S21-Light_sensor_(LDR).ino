//S21 - Light sensor (LDR)

int LdrPin = A5;    //Pin number to which LDR is connected is defined
                    //LDR is connected to analog pin number 5 (A5) and the name of that pin is LdrPin now 

int analogPin_ReadValue;    //To save the data to be read from the LDR 
                           //We created a variable named analogPin_ReadValue
                           
void setup() {
    pinMode(LdrPin, INPUT);    //To read the analog A5 pin named LdrPin 
                               //It is set as input pin
    Serial.begin(9600);        //We activated the Serial Port Screen to see the values read from the LDR.
                              //9600 should be selected in the lower right corner of the serial port screen 
}

void loop() {
    analogPin_ReadValue = analogRead(LdrPin);    //With analogRead(LdrPin) command
                                                 //Read analog values on A5 pin to which LDR is connected
                                                 //And store these values in the analogPin_ReadValue variable.

    Serial.println(analogPin_ReadValue);    //Print the LDR value held in analogPin_ReadValue variable
                                           //With the Serial.println command.

    delay(400);    //To read the values at 400 ms intervals
                   //We created a 400ms delay with the delay command 

    /* After clicking on Tools, you can see the values on the LDR when you click on "Serial Port Screen". 
     * These values are between 0 and 1023 
     * They do not fall below 0 and they do not rise above 1023 
     * This is related to the fact that the ADC (Analog to Digital Converter) where the reading from the analog pin is performed is 10 bits.
     */
}
