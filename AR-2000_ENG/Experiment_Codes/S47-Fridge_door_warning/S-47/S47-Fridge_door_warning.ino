//S47 - Fridge door warning

int speakerPin = 3;    //Define the pin number to which the Speaker is connected
int LDRPin = A5;    //Define the pin number to which the LDR is connected
int LEDPin = 2;    //Define the pin number to which the LED is connected
int readValue = 0;    //Define variable to store the value read from LDR
int averageValue = 0;    //Define the variable to store the average value
unsigned long time = 0;    //Define the variable to store time

void setup() {
    pinMode(speakerPin, OUTPUT);    //Set the pin to which the Speaker is connected as output 
    pinMode(LDRPin, INPUT);    //Set the pin to which the LDR is connected as the input
    pinMode(LEDPin, OUTPUT);    //Set the pin to which the LED is connected as output

    //Read 10 different values for calibration
    for(int i = 0; i < 10; i++) {    //Get 10 different values with for loop
        averageValue = averageValue + analogRead(LDRPin);    //Read the values and save the sum of the values to 
                                                            //the average value variable
    }
    //To find the average of the values, divide the sum in the average value variable by 10.
    averageValue = averageValue / 10;
}

void loop() {
    readValue = analogRead(LDRPin);    //read the value from the LDR

    //If the value in the readValue variable is 100 more than the value in the averageValue variable
    //In this case, your fridge door is opened and the light ON will increase the LDR value.
    if(readValue > averageValue + 100) {
        delay(10);    //Wait for 10ms
        time += 10;    //increase the time variable by 10.

        //If the time variable is greater than 10000, i.e. the fridge door was left open for more than 10 seconds
        if(time >= 10000) {
            tone(speakerPin, 1000);    //Play audio from the Speaker
            digitalWrite(LEDPin, HIGH);    //Turn ON the LED 
            delay(250);    //Wait for 250ms
            digitalWrite(LEDPin, LOW);    //Turn OFF the LED 
            noTone(speakerPin);    //Mute the Speaker
            delay(250);    //Wait for 250ms
        }
    }
    else {    //If the door is closed
        time = 0;    //Reset the time variable
        noTone(speakerPin);    //Mute the Speaker
        digitalWrite(LEDPin, LOW);    //Turn OFF the LED
    }
}
