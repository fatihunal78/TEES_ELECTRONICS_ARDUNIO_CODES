//S19 - NPN transistor test device

int BasePin = 2;    //The pin number to which the Base leg of the transistor is connected is defined

void setup() {
    pinMode(BasePin, OUTPUT);    //Base pin is set as output 
}

void loop() {
    digitalWrite(BasePin, HIGH);    //We sent signal to BasePin (we made it HIGH) 
    delay(1000);
    digitalWrite(BasePin, LOW);     //We sent signal to BasePin (we made it LOW) 
    delay(1000); 
}