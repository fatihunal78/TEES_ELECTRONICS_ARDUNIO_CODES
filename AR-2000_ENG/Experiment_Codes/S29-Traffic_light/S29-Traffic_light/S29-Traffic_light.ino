//S29 - Traffic light

//Define the pin number to which the Red LED is connected
int redPin = 4;
//Define the pin number to which the yellow LED is connected
int yellowPin = 3;
//Define the pin number to which the Green LED is connected
int greenPin = 2;

void setup() {
    //Set the pin to which the Red LED is connected as output
    pinMode(redPin, OUTPUT);
    //Set the pin to which the yellow LED is connected as output 
    pinMode(yellowPin, OUTPUT);
    //Set the pin to which the Green LED is connected as output
    pinMode(greenPin, OUTPUT);
}

void loop() {
    //Turn ON the Red LED
    digitalWrite(redPin, HIGH);
    delay(5000);                    //Wait for 5 seconds

    //Turn ON the yellow LED
    digitalWrite(yellowPin, HIGH);
    delay(2000);                    //Wait for 2 seconds

    //Turn OFF the Red LED
    digitalWrite(redPin, LOW);
    //Turn OFF the yellow LED
    digitalWrite(yellowPin, LOW);
    //Turn ON the Green LED
    digitalWrite(greenPin, HIGH);
    delay(5000);                    //Wait for 5 seconds

    //Turn OFF the Green LED and Turn ON the yellow LED
    digitalWrite(greenPin, LOW);
    digitalWrite(yellowPin, HIGH);
    delay(2000);                    //Wait for 2 seconds

    //Turn OFF the Green LED
    digitalWrite(greenPin, LOW);
    //Turn OFF the yellow LED
    digitalWrite(yellowPin, LOW);
}
