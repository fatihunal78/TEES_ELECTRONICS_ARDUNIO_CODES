//S13 - Flashing LED

/* When a connection is made to any digital pin, to give a name to the sensor, button or LED connected to that pin 
 * int LEDPin=3; command is used. Here this command indicates that we have assigned the name of pin number 3 as LEDPin.
 * After making this definition, we will use the LEDPin variable name to turn on and turn off the LED 
 * 
 */
int LEDPin = 3; //Define the digital pin number to which the LED is connected. Now the pin number 3 is called LEDPin.

/*
 * void setup(): This loop returns only once and the necessary definitions are made here. 
 * The input or output settings of our LED, sensor or button are made in this section.
 * setup() function is the first place the Arduino reads when the code starts running. 
 * After reading this part, Arduino starts to read the other parts. 
 * This section is read only once and is not read again while the program is running. 
 * In this area, important settings such as the operating modes of the pins are made, which only need to be done once.
 */

void setup() {  
  /*
   * To set the digital pin that we assigned the name at the top as input or output 
   * we use the command pinMode(pinNumber, status).
   * Here pinNumber indicates the pin number to which the LED is connected. So in this example we can write 3 or LEDPin instead of pinNumber
   * Status indicates whether the connected LED, button or sensor will be used as input or output.
   * In this example, since we will use our LED as an output, we set it as OUTPUT. 
   * 
   * pinMode(LEDPin, OUTPUT);
   * pinMode(3, OUTPUT);
   * In the commands written in this way, we have shown that pin number 3, the pin named LEDPin, is set as output.
   */
  pinMode(LEDPin, OUTPUT); //Set the pin to which the LED is connected as output
}

/*
 * The loop function is executed after the setup function is executed. 
 * This is a main function and the tasks you want to be done are written here. 
 * The loop function is an infinite loop, which means that when the tasks here are completed, 
 * The program goes back to the beginning and performs the operations again. 
 * This loop continues as long as Arduino is running.
 * It is an endless cycle. The program flow will do what is defined in the loop continuously from top to bottom.
 */

void loop() {  
  
  /* digitalWrite(pinNumber, status); with this command, we can energize or de-energize a pin.
   * pinNumber represents the digital pin to which the LED is connected or the name assigned to it.
   * Status allows us to set the specified digital pin to HIGH (+5V) or LOW (0V). 
   * 
   */

  /* We can wait using the delay(milliseconds) function. When we write the number 1000 in the millisecond variable, it represents 1 second.
   * 500 ms (milliseconds) represents half a second. 
   */
  digitalWrite(LEDPin, HIGH); //We called the pin number 3 to which the LED is connected with the LEDPin name we defined before and set its status to HIGH, that is, ON. 
                             //We turned ON the LED
  delay(1000);               //Wait for 1 second 
                            //LED will stay on for 1 second
               
  digitalWrite(LEDPin, LOW); //We called the pin number 3 to which the LED is connected with the LEDPin name we defined before and set its status to LOW, that is, OFF. 
                            //We turned OFF the LED
  delay(1000);              //Wait for 1 second 
                           //The LED will stay OFF for 1 second 
  /*
   * Our LED named LEDPin connected to pin 3 will stay ON for 1 second and OFF for 1 second.
   * Since we are in a loop, this process will repeat continuously.
   */          
}
