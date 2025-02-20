//S14 - LED lighting with button

/*
* As in the LED Lighting experiment, we named the digital pins to which the LED and Button are connected.
* This naming allows us not to confuse to which pin the Button or LED is connected while coding the program.
* int LEDPin=3; and the name of digital pin number 3 is LEDPin now.
* int buttonPin =2; and the name of the digital pin number 2 is buttonPin now.
*/
int LEDPin = 3;    //Define the digital pin number to which the LED is connected. 

int buttonPin = 2; //Define the digital pin number to which the Button is connected

int buttonStatus = 0; //Similar to what we did in the pin definition, we created a variable called buttonStatus
                     //and we set the buttonStatus variable to zero.
                     //We have defined the variable to keep track of whether the Button is pressed or not.

void setup() { 
  /*
  * As we saw in the LED Lighting experiment, one-time events are performed under the setup function.
  * And here the input and output settings of the LED, sensor or button are done.
  * We set our LED as output and our button as input.
  */
  pinMode(LEDPin, OUTPUT);    //Set the pin to which the LED is connected as output 
  pinMode(buttonPin, INPUT);  //Set the pin to which the Button is connected as input
}

void loop() {
  /*
  * dijitalRead(pinNumber); this command reads the value on any digital pin.
  * When we make the connections in the assembly plan, if the Button is pressed, our buttonPin, namely pin 2, will be HIGH. 
  * This HIGH status will be saved as 1 in the buttonStatus variable.
  * In short, check the value on the pin to which the Button is connected with the digitalRead(buttonPin) command.
  * If the Button is pressed, save the buttonStatus variable as 1 (HIGH)
  * Save it as 0 (LOW) when the Button is not pressed
  */
  buttonStatus = digitalRead(buttonPin); //Query the Button status and assign it to the buttonStatus variable

  /*
  * As we explained in the if else loop, if this event happened do this and if it didn't happen, do that.
  * In the example below, the buttonStatus variable changes to HIGH or LOW, depending on whether the Button is pressed or not.
  * if(buttonStatus==HIGH) If the Button is pressed { do the operations in curly brackets 
  *  
  * else if(buttonStatus==LOW) If the Button is not pressed { do the operations in curly brackets 
  *  
  */
  if(buttonStatus == HIGH) //If the Button is pressed
  {
    digitalWrite(LEDPin, HIGH); //Turn ON the LED 
    delay(50);                  //Wait for 50ms(milliseconds) 
  }
  else if(buttonStatus == LOW) { //If the Button is not pressed 
    digitalWrite(LEDPin, LOW);   //Turn OFF the LED 
    delay(50);                   //Wait for 50ms(milliseconds) 
  }

  /*
  * ------ Sample description for if else -----
  * 
  * Let's imagine that a dice is thrown, the LED turns ON when the dice comes 1-2 and 3, and the LED turns OFF in other cases. 
  * The dice is thrown and the variable to hold the dice value is diceValue.
  * 
  * if(diceValue == 1) //If the dice value is 1 
  * {
  * digitalWrite(LEDPin, HIGH); //Turn ON the LED 
  * }
  *  
  * else if(diceValue == 2) //If the dice value is 2 
  * {
  * digitalWrite(LEDPin, HIGH); //Turn ON the LED 
  * }
  * 
  * else if(diceValue == 3) //If the dice value is 3 
  * {
  * digitalWrite(LEDPin, HIGH); //Turn ON the LED 
  * }
  * 
  * else //If the dice value does not meet the conditions above (1,2 and 3), namely 4-5-6 
  * {
  * digitalWrite(LEDPin, LOW); //Turn OFF the LED 
  * }
  */

  
}