//S71 - Water tank level alarm

//Define the digital pin number to which the LEDs are connected
int redPin = 6;
int greenPin = 5;

//Define the pin number to which the liquid sensors are connected 
int minimumSensorPin = A5;
int maximumSensorPin = A4;

//Define the pin number to which the Speaker is connected
int speakerPin = 2;

//Define the variables to store the status of liquid sensors
int minimumLevelStatus = 0;
int maximumLevelStatus = 0;

void setup() {
  //Set the pin to which the LED is connected as output
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  
  //Set the pin to which the Speaker is connected as output
  pinMode(speakerPin, OUTPUT);
  
  //Set the pin to which the liquid sensors are connected as input
  pinMode(minimumSensorPin, INPUT);
  pinMode(maximumSensorPin, INPUT);
}

void loop() {
  //Query liquid level states and assign them to variables
  minimumLevelStatus = analogRead(minimumSensorPin);
  maximumLevelStatus = analogRead(maximumSensorPin);

  //Check the status of the liquid sensor
  //If both sensors are active, the container is full; if both sensors are inactive, the container is empty.
  
  //If the variables minimumLevelStatus and maximumLevelStatus are greater than or equal to the analog value 200 
  //Then the water container is full
  //Green LED lights up as a warning
  if(minimumLevelStatus >= 200 && maximumLevelStatus >= 200) {
    //Turn OFF the Red LED
    digitalWrite(redPin, LOW);
    //Turn ON the Green LED
    digitalWrite(greenPin, HIGH);
  }
  
  //If minimumLevelStatus is greater than or equal to 200 and maximumLevelStatus is less than 200
  //Then the container is half full and half empty
  //Green LED flashes as a warning
  else if(minimumLevelStatus >= 200 && maximumLevelStatus < 200) {
    //Turn OFF the Red LED
    digitalWrite(redPin, LOW);
    //Turn ON the Green LED
    digitalWrite(greenPin, HIGH);
    delay(250); //Wait for 250ms
    //Turn OFF the Green LED
    digitalWrite(greenPin, LOW);
    delay(250); //Wait for 250ms
  }
  
  //If minimumLevelStatus and maximumLevelStatus variables are less than 200
  //Then it means, water container is empty
  //The Red LED flashes and a tone sounds from the Speaker.
  else if(minimumLevelStatus <= 200 && maximumLevelStatus <= 200 || minimumLevelStatus <= 200) {
    //Turn OFF the Green LED
    digitalWrite(greenPin, LOW);
    //Turn ON the Red LED
    digitalWrite(redPin, HIGH);
    
    for(int i=0; i<2; i++) {
      //Activate the Speaker
      tone(speakerPin, 500);
      delay(50); //Wait for 50ms
      //Mute the Speaker
      noTone(speakerPin);
      delay(50); //Wait for 50ms
    }
    
    //Mute the Speaker
    noTone(speakerPin);
    delay(150); //Wait for 150ms
    //Turn OFF the Red LED
    digitalWrite(redPin, LOW);
    
    for(int i=0; i<2; i++) {
      //Activate the Speaker
      tone(speakerPin, 500);
      delay(50); //Wait for 50ms
      //Mute the Speaker
      noTone(speakerPin);
      delay(50); //Wait for 50ms
    }
    
    //Mute the Speaker
    noTone(speakerPin);
    delay(150); //Wait for 150ms
  }
}
