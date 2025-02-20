//S100 - Graphical user interface

//Define the pin numbers to which the LEDs are connected
int rpin = 6;
int gpin = 5;
int bpin = 3;

float h = 0;  //Define the variable to store the hue (tone) value
int red = 0, green = 0, blue = 0;  //Define variables to store colour values 
int status = 1;  //Define the variable to store the state for the switch case structure
int incoming = 0;  //Define the variable to store incoming data for values to be read from Processing

void setup() {
    Serial.begin(9600);  //Start serial communication with Processing
}

void loop() {
    while(Serial.available() > 0) {  //If there is information coming from the serial communication port
        incoming = Serial.read();  //Save values read from serial port to the incoming variable
        switch(status) {  //Construct switch case structure
            case 1:  //When the case status is 1
                if(incoming == 'R') {  //If the incoming variable is R
                    status = 2;  //Switch to status 2
                }
                break;  //End case 1

            case 2:  //When the case status is 2
                red = incoming;  //Save incoming value to the red variable
                status = 3;  //Switch to status 3
                break;  //End case 2

            case 3:  //When the case status is 3
                green = incoming;  //Save incoming value to the green variable
                status = 4;  //Switch to status 4
                break;  //End case 3

            case 4:  //When the case status is 4
                blue = incoming;  //Save incoming value to the blue variable
                status = 1;  //Switch to status 1
                break;  //End case 4
        }
    }

    //Turn ON the LEDs using PWM signal for common cathode RGB LED
    analogWrite(rpin, 255 - red);  //Turn ON the red LED according to the incoming value
    analogWrite(gpin, 255 - green);  //Turn ON the green LED according to the incoming value
    analogWrite(bpin, 255 - blue);  //Turn ON the blue LED according to the incoming value

    delay(20);  //Wait for 20ms
}
