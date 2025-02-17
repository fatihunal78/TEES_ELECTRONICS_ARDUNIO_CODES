//Define the pin numbers to which the LEDs are connected
int left = 4;
int right = 3;
int up = 5;
int down = 2;

int Joystick_VRX = A4;  //Define the pin to which the x-axis of the joystick is connected
int Joystick_VRY = A5;  //Define the pin to which the y-axis of the joystick is connected

int xPosition = 0;      //Define the variable that will store the position of the Joystick X axis
int yPosition = 0;      //Define the variable that will store the position of the Joystick Y axis

void setup() {
    //Set the pins to which the LEDs are connected as output
    pinMode(left, OUTPUT);
    pinMode(right, OUTPUT);
    pinMode(up, OUTPUT);
    pinMode(down, OUTPUT);
    
    pinMode(Joystick_VRX, INPUT);  //Set the pin to which the Joystick VRX axis is connected as input
    pinMode(Joystick_VRY, INPUT);  //Set the pin to which the Joystick VRY axis is connected as input
}

void loop() {
    //Read the position of the Joystick X axis and save it to the xPosition variable
    xPosition = analogRead(Joystick_VRX);
    //Read the position of the Joystick Y axis and save it to the yPosition variable
    yPosition = analogRead(Joystick_VRY);

    if(xPosition > 900 && yPosition > 120) {  //If the direction is right
        //Turn ON the LED representing the right, turn OFF the others.
        digitalWrite(right, HIGH);
        digitalWrite(left, LOW);
        digitalWrite(up, LOW);
        digitalWrite(down, LOW);
    }
    else if(xPosition < 120 && yPosition > 120) {  //If the direction is left
        //Turn ON the LED representing the left, turn OFF the others.
        digitalWrite(right, LOW);
        digitalWrite(left, HIGH);
        digitalWrite(up, LOW);
        digitalWrite(down, LOW);
    }
    else if(xPosition > 120 && yPosition < 120) {  //If the direction is up
        //Turn ON the LED representing the up, turn OFF the others.
        digitalWrite(right, LOW);
        digitalWrite(left, LOW);
        digitalWrite(up, HIGH);
        digitalWrite(down, LOW);
    }
    else if(xPosition > 120 && yPosition > 900) {  //If the direction is down
        //Turn ON the LED representing the down, turn OFF the others.
        digitalWrite(right, LOW);
        digitalWrite(left, LOW);
        digitalWrite(up, LOW);
        digitalWrite(down, HIGH);
    }
    else {  //If the Joystick is in the middle
        //Turn OFF all LEDs
        digitalWrite(right, LOW);
        digitalWrite(left, LOW);
        digitalWrite(up, LOW);
        digitalWrite(down, LOW);
    }
}
