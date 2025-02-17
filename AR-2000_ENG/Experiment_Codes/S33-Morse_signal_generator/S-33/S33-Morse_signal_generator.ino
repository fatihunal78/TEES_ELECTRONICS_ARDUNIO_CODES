//S33 - Morse signal generator

int LEDPin = 3;      //Define the digital pin number to which the LED is connected
int buzzerPin = 5;   //Define the pin to which the Buzzer is connected

char* letters[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",    //Letters between A and I
    ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",  //Letters between J and R
    "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."          //Letters between S and Z
};

char* numbers[] = {
    "-----", ".----", "..---", "...--", "....-", ".....", "-....", 
    "--...", "---..", "----."
};

int delayTime = 85;  //Define the delay value

void setup() {
    pinMode(LEDPin, OUTPUT);     //Set the pin to which the LED is connected as output
    pinMode(buzzerPin, OUTPUT);  //Set the pin to which the buzzer is connected as output
    Serial.begin(9600);         //Serial communication is started
}

void loop() {
    char ch;  //Define the variable ch as a character
    
    if(Serial.available()) {  //If any data came from the serial port screen
        ch = Serial.read();   //Store the read text in ch.
        
        if(ch >= 'a' && ch <= 'z') {  //If ch is between a and z and it is lowercase
            flashSequence(letters[ch - 'a']);  //Create Morse sound
        }
        else if(ch >= 'A' && ch <= 'Z') {  //If ch is between A and Z and it is uppercase
            flashSequence(letters[ch - 'A']);
        }
        else if(ch >= '0' && ch <= '9') {  //If ch is a number
            flashSequence(numbers[ch - '0']);
        }
        else if(ch == ' ') {  //If ch is a whitespace
            delay(delayTime * 4);  //Wait time between characters
        }
    }
    delay(delayTime * 8);
}

void flashSequence(char* sequence) {
    int i = 0;
    while(sequence[i] != NULL) {
        dotOrHyphen(sequence[i]);
        i++;
    }
    delay(delayTime * 3);  //Wait time between characters
}

void dotOrHyphen(char DotHyphen) {
    digitalWrite(LEDPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    
    if(DotHyphen == '.') {  //If it is dot(.)
        delay(delayTime);
    }
    else {  //If it is hyphen(-)
        delay(delayTime * 3);
    }
    
    digitalWrite(LEDPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(delayTime);  //Wait time between characters
}
