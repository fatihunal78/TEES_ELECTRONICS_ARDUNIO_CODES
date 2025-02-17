//S73 - Ultrasonic meter

//Define the pin to which the HC-SR04 Trigger leg is connected
#define triggerPin 2
//Define the pin to which the HC-SR04 Echo pin is connected  
#define echoPin 3
//Define time and distance variables
long time, distance;

void setup() {
    //Activate serial port
    Serial.begin(9600);
    //Set the pin to which the trigger leg is connected as output
    pinMode(triggerPin, OUTPUT);
    //Set the pin to which the echo leg is connected as input
    pinMode(echoPin, INPUT);
}

void loop() {
    //Pull the trigger leg to zero
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);  //Wait for 2 microseconds
    //Pull the trigger leg to 5V
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);  //Wait for 10 microseconds
    //Pull the trigger leg to zero
    digitalWrite(triggerPin, LOW);
    //Measure the return time of the audio signal from the echo pin
    time = pulseIn(echoPin, HIGH);
    //Calculate the distance in cm by multiplying the measured time by the speed of sound
    distance = (time/2) * 0.034;

    if(distance > 2000 || distance < 0) {  //If the distance is greater than 2000 cm and less than 0
        Serial.println("Out of Range");  //Print "Out of Range" from the serial port screen
    }
    else {  //If the distance is between 0 and 2000 cm
        Serial.print("Distance: ");  //Print "Distance: " on the serial port screen
        Serial.print(distance);  //Print the distance variable on the serial port screen
        Serial.println(" cm");  //Print the unit of distance as cm
    }
    delay(500);  //Wait for 500ms
}
