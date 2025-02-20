//S82 - Rainbow

int LEDs[] = {3,4,5,6,7};    //Define the pin numbers to which the LEDs are connected
                             //LEDs are connected to digital pins 3,4,5,6,7 
                            
void setup()
{
    //With for loop, set the pin to which the LEDs are connected as output
    for(int i=0; i<5; i++)
    {
        pinMode(LEDs[i], OUTPUT);    //Set the pin to which the LED is connected as output
    } 
}

void loop()
{
    //1st Animation: Turn ON LEDs from right to left
    for(int i=0; i<5; i++)    //By using for loop 
    {  
        digitalWrite(LEDs[i], HIGH);    //Turn ON LEDs one by one 
        delay(350);                     //Wait for 350ms
    }
    for(int i=0; i<5; i++)    //By using for loop 
    {  
        digitalWrite(LEDs[i], LOW);     //Turn OFF LEDs one by one
        delay(350);                     //Wait for 350ms
    }

    //2nd Animation: Turn ON LEDs from left to right
    for(int i=4; i>=0; i--)    //By using for loop 
    {
        digitalWrite(LEDs[i], HIGH);    //Turn ON LEDs one by one 
        delay(350);                     //Wait for 350ms
    }
    for(int i=4; i>=0; i--)    //By using for loop 
    {
        digitalWrite(LEDs[i], LOW);     //Turn OFF LEDs one by one
        delay(350);                     //Wait for 350ms 
    }

    //3rd Animation: Connect the LEDs coming from left and right to the middle
    digitalWrite(LEDs[4], HIGH);    //Turn ON the LED corresponding to the LEDs[4] variable
    digitalWrite(LEDs[0], HIGH);    //Turn ON the LED corresponding to the LEDs[0] variable
    delay(350);
  
    digitalWrite(LEDs[3], HIGH);    //Turn ON the LED corresponding to the LEDs[3] variable
    digitalWrite(LEDs[1], HIGH);    //Turn ON the LED corresponding to the LEDs[1] variable 
    delay(350);
 
    digitalWrite(LEDs[2], HIGH);    //Turn ON the LED corresponding to the LEDs[2] variable 
    delay(350);
    
    //4th Animation: Flash all animation LEDs 3 times
    for(int i=0; i<3; i++)    //Repeat 3 times 
    {
        for(int j=0; j<5; j++)
        {
            digitalWrite(LEDs[j], HIGH);    //Turn ON all LEDs 
        }
        delay(150);                         //Wait for 150ms 
        
        for(int j=4; j>=0; j--)
        {
            digitalWrite(LEDs[j], LOW);     //Turn OFF all LEDs 
        }
        delay(150);                         //Wait for 150ms 
    }
}
