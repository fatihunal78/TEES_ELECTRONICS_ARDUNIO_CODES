//S59 - Needle & thread game (Time limited)

int red_LED = 3;      //Define the pin number to which the LED on the panel is connected
int green_LED = 7;    //Define the pin number to which the Green LED is connected
int speakerPin = 5;   //Define the pin number to which the Speaker is connected
int buttonPin = 2;    //Define the pin number to which the Button is connected
int sensorPin = 4;    //Define the connection coming from the 10K resistor as sensor pin

int buttonPressed = 0;        //Define the variable that will hold the value of how many times the button is pressed
unsigned long time;          //Define the variable to store the time value
unsigned long startTime;     //Define the variable that will store the time when the system starts

void setup() {
    pinMode(green_LED, OUTPUT);       //Set the pin to which the Green LED is connected as output
    pinMode(red_LED, OUTPUT);         //Set the pin to which the Red LED is connected as output
    pinMode(speakerPin, OUTPUT);      //Set the pin to which the Speaker is connected as output 
    pinMode(buttonPin, INPUT_PULLUP); //Set the pin to which the Button is connected as input, activate the pull up resistor
    pinMode(sensorPin, INPUT);        //Set the pin to which the Sensor is connected as input 
}

void loop() {
    if(digitalRead(buttonPin) == LOW) {   //If the Button is pressed 
        buttonPressed++;                   //Increment the buttonPressed variable by one
        time = 0;                         //Reset the time variable
        while(digitalRead(buttonPin) == LOW);  //Wait as long as the Button is pressed
    }
    
    if(buttonPressed == 1) {   //If buttonPressed is 1 
        digitalWrite(green_LED, HIGH);     //Turn ON the Green LED
        //If the probe tip touches the ring, that is, if the needle thread game is unsuccessful or if the time value is 
        //greater than 15000 (15 seconds have passed). That is, if HIGH value comes from sensorPin (pin no. 4) or more 
        //than 15 seconds have passed
        if(digitalRead(sensorPin) == HIGH || time > 15000) {
            while(1) {                     //Enter infinite loop 
                digitalWrite(red_LED, HIGH);    //Turn ON the Red LED on the panel 
                tone(speakerPin, 200);         //Play audio from the Speaker 
                if(digitalRead(buttonPin) == LOW) 
                    break;                     //If the Button is pressed, exit the infinite loop
            }
        }
        time = time + 100;                //Increase time variable by 100
    }
    else {                              //If buttonPressed is 0 
        digitalWrite(green_LED, LOW);    //Turn OFF the Green LED
        noTone(speakerPin);             //Mute the Speaker 
        buttonPressed = 0;              //Set buttonPressed value to 0
    }
  
    //Free mode settings 
    if(digitalRead(sensorPin) == HIGH) {    //If the value read from the sensor is 1, that is, if the needle and thread touch each other 
        digitalWrite(red_LED, HIGH);         //Turn ON the Red LED on the panel 
        tone(speakerPin, 700);              //Play audio from the Speaker 
    }
    else {
        digitalWrite(red_LED, LOW);          //Turn OFF the RED LED 
        noTone(speakerPin);                 //Mute the Speaker 
    }
    delay(100);
}
