//S83 - Liquid level meter

//Define the pin numbers to which the LEDs are connected
int GreenLED1  = 5;
int GreenLED2  = 6;
int YellowLED  = 7;
int RedLED1    = 8;
int RedLED2    = 9;

int buzzerPin  = 4;    //Define the pin number to which the Buzzer is connected 

#define triggerPin 2    //Define the pin to which the HC-SR04 Trigger leg is connected
#define echoPin 3       //Define the pin to which the HC-SR04 Echo pin is connected

int beepTime   = 300;   //Define the variable to store the warning sound duration 
 
//Define duration, distance, container_depth, proportion variables
long duration, distance, container_depth, proportion;    

void measureDistance()   //Create measureDistance() function to measure distance
{
    digitalWrite(triggerPin, LOW);      //Pull the Trigger leg to zero
    delayMicroseconds(2);              //Wait for 2 microseconds
    digitalWrite(triggerPin, HIGH);     //Pull the Trigger leg to 5V
    delayMicroseconds(10);             //Wait for 10 microseconds
    digitalWrite(triggerPin, LOW);      //Pull the Trigger leg to zero
  
    duration = pulseIn(echoPin, HIGH);  //Measure the return time of the audio signal from the Echo pin
    distance = (duration/2) * 0.034;    //Calculate distance in cm by multiplying the measured time by the speed of sound
}

void setup()
{
    //Set LEDs as output
    pinMode(GreenLED1, OUTPUT);
    pinMode(GreenLED2, OUTPUT);
    pinMode(YellowLED, OUTPUT); 
    pinMode(RedLED1, OUTPUT);
    pinMode(RedLED2, OUTPUT);
  
    pinMode(buzzerPin, OUTPUT);         //Set the pin to which the Buzzer is connected as output
    pinMode(triggerPin, OUTPUT);        //Set the pin to which the trigger leg is connected as output 
    pinMode(echoPin, INPUT);            //Set the pin to which the echo leg is connected as input

    //To measure the depth of the container to which the ultrasonic sensor is connected (the container in which 
    //the water level will be measured). After the circuit is installed and the software is loaded, the depth 
    //of the container will be measured with the help of an ultrasonic sensor. And our reference will be the 
    //depth of the container. 
 
    measureDistance();                  //Call the measureDistance() function and measure the distance
    container_depth = distance;         //Length of the distance variable in which the distance is stored in the 
                                      //measureDistance() function. Save it to container_depth variable
    delay(1000);                       //Wait for 1 second 
}

void loop()
{
    measureDistance();    //Measure distance with the measureDistance() function
  
    //Proportion the distance to the number of LEDs with the map() function and save it to the proportion variable
    proportion = map(distance, 0, container_depth, 5, 0); 
  
    //Show the result of distance calculation on LEDs
    switch(proportion)
    {
        case 5: 
        {
            //Turn ON all LEDs
            digitalWrite(GreenLED1, HIGH);
            digitalWrite(GreenLED2, HIGH);
            digitalWrite(YellowLED, HIGH);
            digitalWrite(RedLED1, HIGH);
            digitalWrite(RedLED2, HIGH);
            digitalWrite(buzzerPin, LOW);   //Mute the Buzzer
            break;
        }
        case 4: 
        {
            digitalWrite(GreenLED1, LOW);   //Turn OFF the first warning LED
            //Turn ON all other LEDs 
            digitalWrite(GreenLED2, HIGH);
            digitalWrite(YellowLED, HIGH);
            digitalWrite(RedLED1, HIGH);
            digitalWrite(RedLED2, HIGH);
            digitalWrite(buzzerPin, LOW);   //Mute the Buzzer
            break;
        }
        case 3: 
        {
            //Turn OFF the first two LEDs
            digitalWrite(GreenLED1, LOW);
            digitalWrite(GreenLED2, LOW);
            //Turn ON the other LEDs
            digitalWrite(YellowLED, HIGH);
            digitalWrite(RedLED1, HIGH);
            digitalWrite(RedLED2, HIGH); 
            digitalWrite(buzzerPin, LOW);   //Mute the Buzzer 
            break;
        }
        case 2: 
        {
            //Turn OFF the first three LEDs
            digitalWrite(GreenLED1, LOW);
            digitalWrite(GreenLED2, LOW);
            digitalWrite(YellowLED, LOW);
            //Turn ON the other LEDs 
            digitalWrite(RedLED1, HIGH);
            digitalWrite(RedLED2, HIGH);
            digitalWrite(buzzerPin, LOW);   //Mute the Buzzer
            break;
        }
        case 1: 
        {
            //Turn OFF the first four LEDs
            digitalWrite(GreenLED1, LOW);
            digitalWrite(GreenLED2, LOW);
            digitalWrite(YellowLED, LOW);
            digitalWrite(RedLED1, LOW);
            digitalWrite(buzzerPin, LOW);   //Mute the Buzzer
            digitalWrite(RedLED2, HIGH);    //Turn ON the other LEDs 
            break;
        }
        case 0: 
        {
            //Turn OFF the first four LEDs
            digitalWrite(GreenLED1, LOW);
            digitalWrite(GreenLED2, LOW);
            digitalWrite(YellowLED, LOW);
            digitalWrite(RedLED1, LOW);
      
            digitalWrite(RedLED2, HIGH);
            digitalWrite(buzzerPin, HIGH);
            delay(200);
            digitalWrite(buzzerPin, LOW);
            digitalWrite(RedLED2, LOW);
            delay(200);
            break;
        }
    }
}
