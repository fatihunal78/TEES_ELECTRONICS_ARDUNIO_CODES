//SA105 - ECG graph

int LEDPin = 3;      //Define the pin number to which the LED is connected
int speakerPin = 6;  //Define the pin number to which the Speaker is connected

void setup() {
    Serial.begin(9600);           //Start serial communication
    pinMode(LEDPin, OUTPUT);      //Set the pin to which the LED is connected as output
    pinMode(speakerPin, OUTPUT);  //Set the pin to which the Speaker is connected as output 
}

void loop() {
    Serial.println(analogRead(A5));  //Read value from analog (A5) pin and write it to serial port
    
    if(analogRead(A5) >= 200) {     //If the reading is greater than or equal to 200 
        digitalWrite(LEDPin, HIGH);  //Turn ON the LED
        tone(speakerPin, 1047);     //Play audio from the Speaker 
    }
    else {                          //If the value read from analog pin 5 is less than 200
        digitalWrite(LEDPin, LOW);   //Turn OFF the LED
        noTone(speakerPin);         //Mute the Speaker
    }
    
    delay(10);                      //10 ms delay
}
