//S27 - LED delaying with light

//Define the pin numbers to which the LEDs are connected
int RedLED = 3;
int GreenLED = 4;
int YellowLED = 5;

//Define the pin to which the LDR is connected
int LDRPin = A0;

int readValue;   //Define the variable to store the value read from the LDR
int proportion;  //Define the variable to store the value that we proportionate with map function

void setup() {
    //Set LED pins as output
    pinMode(RedLED, OUTPUT);
    pinMode(YellowLED, OUTPUT);
    pinMode(GreenLED, OUTPUT);
}

void loop() {
    readValue = analogRead(LDRPin);                    //Assign reading from LDR to readValue variable
    proportion = map(readValue, 0, 1023, 0, 1000);     //Proportion the value read between 0 and 1000 and assign it to the 
                                                       //proportion variable.
    
    digitalWrite(RedLED, HIGH);      //Turn ON the Red LED
    delay(proportion);               //Wait by the proportion value
    digitalWrite(RedLED, LOW);       //Turn OFF the Red LED
    
    digitalWrite(YellowLED, HIGH);   //Turn ON the Yellow LED
    delay(proportion);               //Wait by the proportion value
    digitalWrite(YellowLED, LOW);    //Turn OFF the Yellow LED
    
    digitalWrite(GreenLED, HIGH);    //Turn ON the Green LED
    delay(proportion);               //Wait by the proportion value
    digitalWrite(GreenLED, LOW);     //Turn OFF the Green LED
}
