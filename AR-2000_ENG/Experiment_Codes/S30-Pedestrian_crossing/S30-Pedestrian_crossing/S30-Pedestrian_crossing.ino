//S30 - Pedestrian crossing

//Define the pin numbers to which the traffic light module is connected
//Define the pin number to which the Red LED is connected
int redPin = 4;
//Define the pin number to which the yellow LED is connected
int yellowPin = 3;
//Define the pin number to which the Green LED is connected
int greenPin = 2;

//Define the pin numbers to which the Crosswalk light is connected
int pedestrianRed = 7;    //Define the pin number of Red LED for pedestrian light 
int pedestrianGreen = 6;  //Define the pin number of Green LED for pedestrian light 

void setup() {
    //Set the pins to which the traffic light module is connected as output
    //Set the pin to which the Red LED is connected as output
    pinMode(redPin, OUTPUT);
    //Set the pin to which the yellow LED is connected as output
    pinMode(yellowPin, OUTPUT);
    //Set the pin to which the Green LED is connected as output
    pinMode(greenPin, OUTPUT);
    //Set the pins to which the crosswalk light is connected as output
    pinMode(pedestrianRed, OUTPUT);    //Set the pin to which the pedestrian Red light LED is connected as output
    pinMode(pedestrianGreen, OUTPUT);  //Set the pin to which the pedestrian Green light LED is connected as output
}

void loop() {
    digitalWrite(redPin, HIGH);         //Turn ON the Red LED for Vehicles
    digitalWrite(greenPin, LOW);        //Turn OFF the Green LED for Vehicles
    digitalWrite(yellowPin, LOW);       //Turn OFF the Yellow LED for Vehicles
    delay(2000);                        //Wait for 2 seconds
    digitalWrite(pedestrianGreen, HIGH); //Turn ON the Green LED for Pedestrians
    digitalWrite(pedestrianRed, LOW);    //Turn OFF the Red LED for Pedestrians
    delay(10000);                       //Wait for 10 seconds
    digitalWrite(yellowPin, HIGH);       //Turn ON the Yellow LED for Vehicles
    
    for(int i = 0; i < 5; i++) {
        digitalWrite(pedestrianGreen, LOW);  //Turn OFF the Green LED for Pedestrians
        digitalWrite(pedestrianRed, LOW);    //Turn OFF the Red LED for Pedestrians
        delay(400);                          //Wait for 400ms
        digitalWrite(pedestrianRed, HIGH);   //Turn ON the Red LED for Pedestrians
        delay(400);                          //Wait for 400ms
    }

    digitalWrite(pedestrianRed, HIGH);   //Turn ON the Red LED for Pedestrians
    digitalWrite(pedestrianGreen, LOW);  //Turn OFF the Green LED for Pedestrians
    delay(2000);                         //Wait for 2 seconds
    digitalWrite(redPin, LOW);           //Turn OFF the Red LED for Vehicles
    digitalWrite(yellowPin, LOW);        //Turn OFF the Yellow LED for Vehicles
    digitalWrite(greenPin, HIGH);        //Turn ON the Green LED for Vehicles
    delay(10000);                        //Wait for 10 seconds
    digitalWrite(yellowPin, HIGH);       //Turn ON the Yellow LED for Vehicles
    delay(2000);                         //Wait for 2 seconds
}
