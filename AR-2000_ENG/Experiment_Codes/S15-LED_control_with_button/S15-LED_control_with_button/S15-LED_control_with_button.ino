//S15 - LED control with button
int LEDPin = 3;    //Define the digital pin number to which the LED is connected. 
                   //We introduced that our LED is connected to digital pin number 3 and named it LEDPin.
                
int buttonPin = 2; //Define the digital pin number to which the Button is connected
                   //We introduced that our Button is connected to digital pin number 2 and named it buttonPin.

int buttonStatus = 0; //Define the variable to store the Button state
                     //With this variable we will store the status whether the Button is pressed or not.
                    
int LEDStatus = 0;   //Define variable to store the LED status
                     //With this variable we will store the LED status, i.e. whether it is ON or OFF.

void setup() {
    pinMode(LEDPin, OUTPUT);    //Set the pin to which the LED is connected as output
    pinMode(buttonPin, INPUT);  //Set the pin to which the Button is connected as input
}

void loop() {
  
    buttonStatus = digitalRead(buttonPin); //Query the Button status and assign it to the buttonStatus variable
                                         //As we have seen before, we will store the status whether the Button is pressed or not in the buttonStatus variable with the digitalRead command.
                                         //If the Button is pressed, the buttonStatus variable will have the value HIGH, that is, 1
                                       
    //Set the status of the LED according to the status of the Button
    if(buttonStatus == HIGH) //If the Button is pressed
    {
        if(LEDStatus == 0) //If the LEDStatus variable is 0, that is, the LED is OFF 
        {
            digitalWrite(LEDPin, HIGH); //Turn ON the LED 
            LEDStatus = 1;             //Save the LED status as ON
                                      //Since the LED is currently ON, we set the LEDStatus variable to 1.
                    
            delay(500);               //Wait for 500ms(milliseconds) 
                                     //In circuits with button circuits, a delay of about half a second is usually added. 
                                     //This is because when the Button is pressed, it behaves as if it was pressed many times rather than just once. 
                                     //If you make the delay 100 ms, the LED may flash more than once when you press the Button.
                                     //This state of the Button is called button crackling or debounce. This situation is usually prevented by adding a delay. 
        }
        else //If the LEDStatus variable is 1, that is, if the LED is ON 
        {
            digitalWrite(LEDPin, LOW); //Turn OFF the LED 
            LEDStatus = 0;            //Save LED status as OFF
                                     //Since the LED is currently OFF, we set the LEDStatus variable to 0.
            delay(500);              //Wait for 500ms(milliseconds) 
                                    //In circuits with button circuits, a delay of about half a second is usually added. 
                                    //This is because when the Button is pressed, it behaves as if it was pressed many times rather than just once. 
                                    //If you make the delay 100 ms, the LED may flash more than once when you press the Button.
                                    //This state of the Button is called button crackling or debounce. This situation is usually prevented by adding a delay. 
        }
    }
}

/*  --- The program code under void loop() is written as follows using the && (and) operator.
 *   The and (&&) operator is used when both conditions are checked, as described in the explanations.
 *   So in the example below, if the Button is pressed and LEDStatus=0, that is, the LED is OFF, do the following operation 
 *   Here, checking whether the Button is pressed or not is the 1st event, checking whether the LED is ON or OFF is the 2nd event.
    
  void loop() {  
  buttonStatus = digitalRead(buttonPin); //Query the Button status and assign it to the buttonStatus variable 
                                       
  //Set the status of the LED according to the status of the Button
  f(buttonStatus == HIGH && LEDStatus == 0) //If Button is pressed and LEDStatus =0,  that is, LED is OFF
  {
      digitalWrite(LEDPin, HIGH); //Turn ON the LED 
      LEDStatus = 1; //Save the LED status as ON
                    //Since the LED is currently ON, we set the LEDStatus variable to 1.
                    
      delay(500); //Wait for 500ms(milliseconds) 
  }
  else if(buttonStatus == HIGH && LEDStatus == 1) //If Button is pressed and LEDStatus =1, that is, LED is ON 
  {      
    digitalWrite(LEDPin, LOW); //Turn OFF the LED
    LEDStatus = 0; //Save LED status as OFF
                  //Since the LED is currently OFF, we set the LEDStatus variable to 0.
    delay(500); //Wait for 500ms(milliseconds) 
  }
}
 */
