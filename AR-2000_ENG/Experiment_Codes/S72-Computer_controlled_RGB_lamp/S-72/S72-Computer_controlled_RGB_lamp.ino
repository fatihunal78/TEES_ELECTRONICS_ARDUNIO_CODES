//S72 - Computer controlled RGB lamp

//Define the digital pin numbers to which the LEDs are connected
int redLEDPin = 6;
int greenLEDPin = 5;
int blueLEDPin = 3;

//Define the variables to keep the status of the LEDs
int redStatus = 0;
int greenStatus = 0;
int blueStatus = 0;

//Define the variable queryStatus to store the query status
int queryStatus = 0;

//Sorting out the second one
int secondRank = 0;
int dummy = 0;

void setup() {
    //Set the pin to which the LEDs are connected as output
    pinMode(redLEDPin, OUTPUT);
    pinMode(greenLEDPin, OUTPUT);
    pinMode(blueLEDPin, OUTPUT);
    
    //Initially turn OFF all LEDs.
    digitalWrite(redLEDPin, HIGH);
    digitalWrite(greenLEDPin, HIGH);
    digitalWrite(blueLEDPin, HIGH);

    //Set serial communication settings
    Serial.begin(9600); //Start serial communication with 9600 baud rate
  
    //Send message to serial communication screen
    Serial.println("Welcome to RGB colour adjustment app!");
    Serial.println("Enter colour values between 0-255.");
    Serial.println("----------------------------------------");
}

void loop() {
    switch(queryStatus) //Create switch case structure
    {
        case 0: //In case 0 
            Serial.println("Enter Red LED colour value."); //Write on the serial screen
            queryStatus = 1; //Set the queryStatus variable to 1 
            break; //End case 0
            
        case 1: //In case 1 
            if(Serial.available() > 0) //If serial communication is open 
            {
                redStatus = Serial.parseInt(); //Save the entered value to redStatus variable 
                dummy = Serial.parseInt(); //If there is a value that we did not write or that is not wanted on the serial port screen, save it to the dummy variable.
                Serial.print("Red Value -- >  "); 
                Serial.println(redStatus); //Print the red value entered on the Serial port screen
                Serial.println("----------------------------------------"); //Write to serial port screen
                Serial.println("Enter Green LED colour value."); //Write to serial port screen
                queryStatus = 2; //Set the queryStatus variable to 2 
            }
            break; //End case 1 
            
        case 2: //In case 2 
            if(Serial.available() > 0) //If serial communication is open 
            {
                greenStatus = Serial.parseInt(); //Save the entered value to greenStatus variable 
                dummy = Serial.parseInt(); //If there is a value that we did not write or that is not wanted on the serial port screen, save it to the dummy variable.
                Serial.print("Green Value -- >  "); 
                Serial.println(greenStatus); //Print the green value entered on the Serial port screen.
                Serial.println("----------------------------------------"); //Write to serial port screen
                Serial.println("Enter Blue LED colour value."); //Write to serial port screen
                queryStatus = 3; //Set the queryStatus variable to 3 
            }
            break; //End case 2 
            
        case 3: //In case 3 
            if(Serial.available() > 0) //If serial communication is open 
            {
                blueStatus = Serial.parseInt(); //Save the entered value to blueStatus variable 
                dummy = Serial.parseInt(); //If there is a value that we did not write or that is not wanted on the serial port screen, save it to the dummy variable.
                Serial.print("Blue Value -- >  "); 
                Serial.println(blueStatus); //Print the blue value entered on the Serial port screen.
                queryStatus = 4; //Set the queryStatus variable to 4 
            }
            break; //End case 3 
            
        case 4: //In case 4 
            //Turn ON the RGB LED according to the levels of the status variables
            //Since the RGB used is a common Anode, the values should be transferred as "255 - Value".
            analogWrite(redLEDPin, (255 - redStatus));
            analogWrite(greenLEDPin, (255 - greenStatus));
            analogWrite(blueLEDPin, (255 - blueStatus));
            
            redStatus = 0;
            greenStatus = 0;
            blueStatus = 0;
            
            Serial.println(" "); 
            Serial.println("The colour you want is set.");
            Serial.println("You May Enter New Values");
            Serial.println("----------------------------------------"); //Write to serial port screen
            
            delay(500); //Wait for 500ms
            Serial.println("");
            queryStatus = 0;
            break; //End case 4 
    }
}
