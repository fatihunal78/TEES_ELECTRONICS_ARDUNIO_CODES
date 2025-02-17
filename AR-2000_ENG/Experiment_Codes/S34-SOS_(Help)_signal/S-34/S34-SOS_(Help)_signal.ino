//S34 - SOS (Help) signal

int LEDPin = 3;      //Define the pin number to which the LED is connected
int buzzerPin = 5;   //Define the pin to which the Buzzer is connected
int buttonPin = 2;   //Define the pin to which the Button is connected

void setup() {
    pinMode(LEDPin, OUTPUT);     //The LED pin is set as output
    pinMode(buzzerPin, OUTPUT);  //The Buzzer pin is set as output
    pinMode(buttonPin, INPUT);   //The Button pin is defined as input
}

void loop() {
    if(digitalRead(buttonPin) == HIGH) {  //If the Button is pressed
        flash(100); flash(100); flash(100);  //S
        delay(300);                          //Wait for 300 milliseconds
        flash(200); flash(200); flash(200);  //O
        delay(300);                          //Wait for 300 milliseconds
        flash(100); flash(100); flash(100);  //S
    }
    delay(300);  //Wait for 300 milliseconds
}

void flash(int delayTime) {
    digitalWrite(LEDPin, HIGH);     //Turn ON the LED
    digitalWrite(buzzerPin, HIGH);  //Make a sound from the Buzzer
    delay(delayTime);
    digitalWrite(LEDPin, LOW);      //Turn OFF the LED
    digitalWrite(buzzerPin, LOW);   //Mute the Buzzer
    delay(delayTime);
}
