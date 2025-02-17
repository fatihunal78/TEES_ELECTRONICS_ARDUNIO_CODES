//S17 - Adjustable tone generator
int speakerPin = 3;    //The speaker is defined to be connected to pin number 3.
int proportion;        //A variable named proportion is created
int potPin = A0;      //The pin to which the Potentiometer is connected is defined as Analog 0 pin
int potValue;         //The variable to store the value of the Potentiometer is defined

void setup() {
    pinMode(speakerPin, OUTPUT);    //Speaker is set as output 
    Serial.begin(9600);             //Serial communication is started
                                   //9600 should be selected in the lower right corner of the serial port screen 
}

void loop() {
    potValue = analogRead(potPin);                      //Read value from the Potentiometer and save it to potValue variable 
    proportion = map(potValue, 0, 1023, 0, 2000);      //Proportionate the values between 0 and 1023 read from the Potentiometer to between 0 and 2000. 

    //tone() function is a tool for creating sounds with the help of Arduino digital pins 
    //You can use it as: tone(pin_number, sound_frequency_value)
    //You can create suitable sounds in your projects with the tone function.
    tone(speakerPin, proportion);                       //Transfer the proportional value to the Speaker
    delay(100);                                         //Wait for 100ms
    noTone(speakerPin);                                //Mute the Speaker
    delay(100);                                         //Wait for 100ms 

    Serial.print("Frequency Value:"); 
    Serial.print(proportion);                           //Print the value held in the proportion variable to the serial screen.
    Serial.println(" Hz (Hertz)");

    while(proportion <= 20) {                          //Mute the Speaker as long as the proportion value is less than 20
        noTone(speakerPin);                           //Mute the Speaker
        potValue = analogRead(potPin);                //Read the value from Potentiometer 
        proportion = map(potValue, 0, 1023, 0, 2000); //Proportionate the value read from the Potentiometer 
    }
}
