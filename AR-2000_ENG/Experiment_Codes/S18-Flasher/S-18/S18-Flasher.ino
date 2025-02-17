//S18 - Flasher

int LEDPin = 2;    //The pin number to which the LED is connected is defined
int potPin = A0;   //The pin number to which the Potentiometer is connected is defined
int delayTime;     //The variable to hold the value to be proportioned is defined
int readValue;     //The variable to store the value read in the Potentiometer is defined

void setup() {
    pinMode(LEDPin, OUTPUT);    //LED is set as output
}

void loop() {
    readValue = analogRead(potPin);    //Value is read from the Potentiometer and saved to readValue variable
    delayTime = map(readValue, 0, 1023, 1000, 100);    //Value read from the Potentiometer between 0 and 1023 
                                                       //is proportionated between 1000 and 100ms for the delay of the LED
    digitalWrite(LEDPin, HIGH);    //Turn ON the LED 
    delay(delayTime);             //Delay by proportioned value 
    digitalWrite(LEDPin, LOW);     //Turn OFF the LED 
    delay(delayTime);             //Delay by proportioned value 
}
