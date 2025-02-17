//S22 - Street lamp
int lampPin = 2;      //Define the pin number to which the street lamp is connected
int LDRPin = A5;      //Define the analog pin number to which the LDR is connected
int light_value;      //Define the variable in which the measured light value will be stored
int lampStatus = 0;   //Define the variable in which the lamp status will be stored

void setup() {
    pinMode(lampPin, OUTPUT);    //Set the pin to which the street lamp is connected as the output pin
    pinMode(LDRPin, INPUT);      //Set the pin to which the LDR is connected as the input pin
}

void loop() {
    //Read the measured light value from the analog pin
    //and assign to light_value variable
    //Light value is read between 0-1023
    //The value is low in the dark,
    //High in light. You may change the value 300 
    //according to the brightness level you want.

    light_value = analogRead(LDRPin);

    if (light_value < 300) {     //If the value read from the LDR is lower than 300, that is, if the weather is dark
        digitalWrite(lampPin, HIGH);    //Turn on the lamp
        lampStatus = 1;                 //Save the lamp status as ON
    }
  
    if (lampStatus == 1) {       //If the lamp is ON
        if (light_value > 300) { //If the ambient light value is HIGH, wait for 5s
            delay(5000);         //Wait for 5 seconds
            if (light_value > 300) {    //After 5 seconds if the ambient light value is still HIGH, turn OFF the light
                digitalWrite(lampPin, LOW);    //Turn OFF the lamp
                lampStatus = 0;               //Save the lamp status as OFF
            }
        }
    }
}
