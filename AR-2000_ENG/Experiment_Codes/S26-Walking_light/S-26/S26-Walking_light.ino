//S26 - Walking light

//Define the pin numbers to which the LEDs are connected
int LEDs[] = {3,4,5,6,7};
//Navigation speed of LEDs 
int speed;
int potPin = A0; //The pin to which the Potentiometer is connected
int potValue; //value read from the Potentiometer
int proportion; //The variable that we will convert the value read from the Potentiometer to delay

void setup() {
    //By means of the for loop set the pins to which the LEDs are connected
    //as output
    for(int i=0; i<5; i++) {
        pinMode(LEDs[i], OUTPUT);
    }
}

void loop() {
    potValue = analogRead(potPin); //Read the value on the analog pin 0 and save it to the potValue variable
    proportion = map(potValue, 0, 1023, 500, 20); //Change the value stored in potValue to between 20 and 500.
                                                 //This stored value is between 0 and 1023 
                                                 //because the right and left ends of the Potentiometer are connected to + and -. 
                                                 //(These values are the values we will use when making delays.)
                                                 //So the value read as 1023 will correspond to 500 ms, and the value 0 will correspond to 20 ms.
    
    //Turn the LEDs ON and OFF in order from left to right
    //The LEDs defined as an array with the variable i are turned ON and OFF in sequence.
    for(int i=0; i<5; i++) {
        digitalWrite(LEDs[i], HIGH); //Turn ON the next LED
        delay(proportion); //Wait by the proportion value
        digitalWrite(LEDs[i], LOW); //Turn OFF the next LED
    }
    
    //Turn the LEDs ON and OFF in order from right to left
    //The LEDs defined as an array with the variable j are turned ON and OFF in sequence.
    for(int j=4; j>0; j--) {
        digitalWrite(LEDs[j], HIGH); //Turn ON the next LED
        delay(proportion); //Wait by the proportion value
        digitalWrite(LEDs[j], LOW); //Turn OFF the next LED
    }
}
