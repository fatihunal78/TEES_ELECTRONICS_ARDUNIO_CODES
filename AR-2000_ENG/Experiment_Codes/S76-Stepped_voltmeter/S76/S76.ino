//S76 - Stepped voltmeter

//Define the digital pin numbers to which the LEDs are connected
int LEDs[] = {2, 3, 4, 5, 6};

//Define the digital pin number to which the Potentiometer is connected
int potPin = A0;

//Define the variable to store the Potentiometer value
int potValue = 0;

void setup() {
    //Start serial port with 9600 baud rate
    Serial.begin(9600);
    
    //Set the pins to which the LEDs are connected as output
    //With for loop, set the pin to which the LEDs are connected as output
    for(int i = 0; i < 5; i++) {
        pinMode(LEDs[i], OUTPUT);
    }
}

void loop() {
    //Read the value of the Potentiometer and assign it to the potValue variable
    potValue = analogRead(potPin);
    Serial.print("Read Voltage : ");
    Serial.print((float)potValue * 5/1023);
    Serial.println(" V");
    
    if(975 < potValue) { //If the measured value is 5V 
        for(int i = 0; i < 5; i++) {
            digitalWrite(LEDs[i], HIGH);
        }
    }
    else if(820 < potValue) { //If measured value is 4V or above 
        for(int i = 0; i < 4; i++) {
            digitalWrite(LEDs[i], HIGH);
        }
        for(int i = 4; i < 5; i++) {
            digitalWrite(LEDs[i], LOW);
        }
    }
    else if(615 < potValue) { //If measured value is 3V or above 
        for(int i = 0; i < 3; i++) {
            digitalWrite(LEDs[i], HIGH);
        }
        for(int i = 3; i < 5; i++) {
            digitalWrite(LEDs[i], LOW);
        }
    }
    else if(410 < potValue) { //If measured value is 2V or above 
        for(int i = 0; i < 2; i++) {
            digitalWrite(LEDs[i], HIGH);
        }
        for(int i = 2; i < 5; i++) {
            digitalWrite(LEDs[i], LOW);
        }
    }
    else if(205 < potValue) { //If measured value is 1V or above 
        digitalWrite(LEDs[0], HIGH);
        for(int i = 1; i < 5; i++) {
            digitalWrite(LEDs[i], LOW);
        }
    }
    else if(0 <= potValue) { //If measured value is 1V or below 
        for(int i = 0; i < 5; i++) {
            digitalWrite(LEDs[i], LOW);
        }
    }
    delay(250);
}
