//S92 - Illuminated warning sign

int LEDs[] = {2,3,4,5,6,7,8};    //Define the pin numbers to which the LEDs are connected
int LDRPin = A5;                 //Define the analog pin number to which the LDR is connected
int speed = 200;                 //Define the variable of the navigation speed of the LEDs, you can change it as you wish

void setup() 
{
    //With for loop, set the pin to which the LEDs are connected as output
    for(int i=0; i<7; i++)
    {
        pinMode(LEDs[i], OUTPUT);
    }
    pinMode(LDRPin, INPUT_PULLUP);    //Set the pin to which LDR is connected as input, activate the pull up resistance
}

void loop() 
{
    //Check LDR status 
    if(analogRead(LDRPin) > 600)    //If the light intensity value is greater than 600 
    {
        //Turn ON the LEDs in turn
        for(int i=0; i<5; i++)    //By using for loop Turn ON the LEDs on digital pins 2, 3, 4, 5, 6 defined in the LEDs[i]
                                  //variable.
        {
            digitalWrite(LEDs[i], HIGH);
            delay(speed);
        }  
   
        digitalWrite(LEDs[5], HIGH);    //Turn ON the LED number LEDs[5]
        delay(speed);                   //Wait until the speed variable
    
        digitalWrite(LEDs[6], HIGH);    //Turn ON the LED number LEDs[6]
        delay(speed);                   //Wait until the speed variable
    
        //Initially turn OFF all LEDs.
        for(int l=0; l<7; l++)    //Turn OFF the LEDs defined in the variable LEDs[l] using a for loop
        {
            digitalWrite(LEDs[l], LOW); 
        }
        delay(speed);
    
        for(int i=0; i<3; i++)    //repeat 3 times 
        {
            //Turn ON all LEDs
            for(int l=0; l<7 ; l++)
            {
                digitalWrite(LEDs[l], HIGH);
            }
            delay(speed);
            
            //Initially turn OFF all LEDs.
            for(int l=0; l<7; l++)
            {
                digitalWrite(LEDs[l], LOW); 
            }
            delay(speed);
        }
    }
}
