//S41 - Lie detector

int redLED = 2;    //Define the pin number to which the Red LED is connected
int buzzerPin = 4;    //Define the pin to which the Buzzer is connected 
int sensorPin = A5;    //Define the pin to which the sensor is connected for force measurement

int sensorValue;    //Define the variable to store the data read from the probe tips
int readValue;    //Define the variable to store the calibration operation
int total = 0;    //Define the variable to store the sum of the values in the calibration process and set 
                  //the initial value to zero

void setup() {
    pinMode(sensorPin, INPUT);    //Set the A5 pin to which the sensor is connected for force measurement as input
    pinMode(redLED, OUTPUT);    //Set the red LED pin as output
    pinMode(buzzerPin, OUTPUT);    //Set the Buzzer pin as output

    //Calibration setting
    for(int i = 0; i < 10; i++) {    //Get 10 different values with for loop
        readValue = analogRead(sensorPin);    //Read the analog values from probes connected to sensor pin
        total = total + readValue;    //Sum the analogue value read with the previous sum
        delay(100);    //Wait for 100ms
    }
    total = total/10;    //Average the values read from the analog pin
}

void loop() {
    sensorValue = analogRead(sensorPin);    //Read the value in the analog pin and save it to the sensorValue variable
    if(sensorValue > readValue + 10) {    //If the sensor value is 10 greater than the initial calibration value
                                         //So if he/she is lying
        digitalWrite(buzzerPin, HIGH);    //Make a sound from the Buzzer
        digitalWrite(redLED, HIGH);    //Turn ON the Red LED
        delay(1000);    //Wait for 1 second
    }
    else {    //If not
        digitalWrite(buzzerPin, LOW);    //Mute the Buzzer
        digitalWrite(redLED, LOW);    //Turn OFF the Red LED
    }
    delay(50);    //Wait for 50ms
}
