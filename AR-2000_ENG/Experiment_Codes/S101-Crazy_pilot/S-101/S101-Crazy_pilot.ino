//S101 - Crazy pilot

int echoPin = 3;      //Define the pin to which the HC-SR04 Echo leg is connected
int triggerPin = 2;   //Define the pin to which the HC-SR04 Trigger leg is connected
//Define time, distance, and old_distance variables
unsigned long time = 0;
unsigned distance = 0;
unsigned old_distance = 0;

void setup() {
    pinMode(echoPin, INPUT);      //Set the pin to which the Echo leg is connected as input
    pinMode(triggerPin, OUTPUT);   //Set the pin to which the trigger leg is connected as output
    Serial.begin(9600);           //Start serial communication with Processing
}

void loop() {
    digitalWrite(triggerPin, LOW);    //Pull the trigger pin to LOW
    delayMicroseconds(100);           //Wait for 100 microseconds
    digitalWrite(triggerPin, HIGH);    //Pull the trigger pin to HIGH
    delayMicroseconds(100);           //Wait for 100 microseconds
    digitalWrite(triggerPin, LOW);     //Pull the trigger pin to LOW
    time = pulseIn(echoPin, HIGH);    //Calculate time and save it to time variable
    distance = time / 58;             //Divide time variable by 58 to calculate distance
    delay(10);                        //Wait for 10 milliseconds

    if(old_distance != distance) {     //If the old_distance variable is different from the distance variable
        Serial.println(distance);      //Print serial to send the distance variable to Processing application
        old_distance = distance;       //Save the value in the distance variable to the old_distance variable
    }
    delay(50);                        //Wait for 50ms
}
