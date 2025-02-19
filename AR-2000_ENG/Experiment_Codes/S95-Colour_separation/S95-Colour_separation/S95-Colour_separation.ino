//S95 - Colour separation

//Define the digital pin numbers to which the LEDs are connected
int RGB_Red = 6;
int RGB_Green = 5;
int RGB_Blue = 3;
int Red_LED = 11;
int Green_LED = 10;
int Blue_LED = 9;

int potPin = A0;    //Define the analog pin number to which the Potentiometer is connected
int potValue = 0;   //Define the variable to store the Potentiometer value

void setup() {
    //Set the pin to which the RGB LEDs are connected as output
    pinMode(RGB_Red, OUTPUT);
    pinMode(RGB_Green, OUTPUT);
    pinMode(RGB_Blue, OUTPUT);

    //Set the pins to which the LED Modules are connected as output
    pinMode(Red_LED, OUTPUT);
    pinMode(Green_LED, OUTPUT);
    pinMode(Blue_LED, OUTPUT);
     
    //Initially turn OFF all LEDs.
    analogWrite(RGB_Red, 255);
    analogWrite(RGB_Green, 255);
    analogWrite(RGB_Blue, 255);

    analogWrite(Red_LED, 0);
    analogWrite(Green_LED, 0);
    analogWrite(Blue_LED, 0);
}

void loop() {
    //Read the Potentiometer value and assign it to the potStatus variable
    potValue = analogRead(potPin);
    //Change the colour of the LEDs according to the potValue

    if(potValue >= 0 && potValue < 150) {    //If the reading from the Potentiometer is between 0 and 150 Turn ON the Red LED
        //Turn ON the Red LED on the RGB module according to the Potentiometer value 
        analogWrite(RGB_Red, 255 - potValue);
        analogWrite(RGB_Green, 255);
        analogWrite(RGB_Blue, 255);

        //Turn ON the Red LED module according to the Potentiometer value
        analogWrite(Red_LED, potValue);
        analogWrite(Green_LED, 0);
        analogWrite(Blue_LED, 0);
    }
    else if(potValue >= 150 && potValue < 300) {    //If the reading from the Potentiometer is between 150 and 300 
                                                    //Turn ON the Green LED
        //Proportion to the maximum value 255 that LEDs can be adjusted with PWM
        int proportion = map(potValue, 150, 300, 0, 255);
    
        //Turn ON the Green LED on the RGB module according to the potentiometer value 
        analogWrite(RGB_Red, 255);
        analogWrite(RGB_Green, 255 - proportion);
        analogWrite(RGB_Blue, 255);
        //Turn ON the Green LED module according to the Potentiometer value
        analogWrite(Red_LED, 0);
        analogWrite(Green_LED, proportion);
        analogWrite(Blue_LED, 0);
    }
    else if(potValue >= 300 && potValue < 450) {    //If the reading from the Potentiometer is between 300 and 450 
                                                    //Turn ON the Blue LED
        //Proportion to the maximum value 255 that LEDs can be adjusted with PWM
        int proportion = map(potValue, 300, 450, 0, 255);
    
        //Turn ON the Blue LED on the RGB module according to the Potentiometer value 
        analogWrite(RGB_Red, 255);
        analogWrite(RGB_Green, 255);
        analogWrite(RGB_Blue, 255 - proportion);

        //Turn ON the Blue LED module according to the Potentiometer value 
        analogWrite(Red_LED, 0);
        analogWrite(Green_LED, 0);
        analogWrite(Blue_LED, proportion);
    }
    else if(potValue >= 450 && potValue < 600) {    //If the reading from the Potentiometer is between 450 and 600 
                                                    //Turn ON the magenta colour with LEDs
        //Proportion to the maximum value 255 that LEDs can be adjusted with PWM
        int proportion = map(potValue, 450, 600, 0, 255);
   
        //Adjust the magenta colour with the Red and Blue colour LEDs on the RGB module according to the 
        //Potentiometer value.
        analogWrite(RGB_Red, 255-proportion);
        analogWrite(RGB_Green, 255);
        analogWrite(RGB_Blue, 255 - proportion);
    
        //Adjust the magenta colour with the Red and Blue LED modules according to the Potentiometer value
        analogWrite(Red_LED, proportion);
        analogWrite(Green_LED, 0);
        analogWrite(Blue_LED, proportion);
    }
    else if(potValue >= 600 && potValue < 750) {    //If the reading from the Potentiometer is between 600 and 750 
                                                    //Turn ON the yellow colour with LEDs
        //Proportion to the maximum value 255 that LEDs can be adjusted with PWM
        int proportion = map(potValue, 600, 750, 0, 255);

        //Adjust the yellow colour with the Red and Green colour LEDs in the RGB module according to the 
        //Potentiometer value
        analogWrite(RGB_Red, 255-proportion);
        analogWrite(RGB_Green, 255 - proportion);
        analogWrite(RGB_Blue, 255);

        //Set the yellow colour with Red and Green LED modules according to the potentiometer value
        analogWrite(Red_LED, proportion);
        analogWrite(Green_LED, proportion);
        analogWrite(Blue_LED, 0);
    }
    else if(potValue >= 750 && potValue < 900) {    //If the reading from the Potentiometer is between 750 and 900 
                                                    //Turn ON the Cyan colour with LEDs
        //Proportion to the maximum value 255 that LEDs can be adjusted with PWM
        int proportion = map(potValue, 750, 900, 0, 255);

        //Adjust the Cyan colour with the Green and Blue colour LEDs in the RGB module according to the 
        //Potentiometer value
        analogWrite(RGB_Red, 255);
        analogWrite(RGB_Green, 255 - proportion);
        analogWrite(RGB_Blue, 255 - proportion);

        //Set the Cyan colour with Green and Blue LED modules according to the Potentiometer value
        analogWrite(Red_LED, 0);
        analogWrite(Green_LED, proportion);
        analogWrite(Blue_LED, proportion);
    }
    else if(potValue >= 900) {    //If the reading from the Potentiometer is greater than 900 Turn ON the white colour 
                                 //with LEDs
        //Adjust the white colour with the Red, Green and Blue colour LEDs in the RGB module according to the 
        //Potentiometer value
        analogWrite(RGB_Red, 255 - potValue + 900);
        analogWrite(RGB_Green, 255 - potValue + 900);
        analogWrite(RGB_Blue, 255 - potValue + 900);

        //Adjust the white colour with Red, Green and Blue LED modules according to the Potentiometer value
        analogWrite(Red_LED, potValue - 900);
        analogWrite(Green_LED, potValue - 900);    //Fixed variable name from Yesil_LED to Green_LED
        analogWrite(Blue_LED, potValue - 900);
    }
}
