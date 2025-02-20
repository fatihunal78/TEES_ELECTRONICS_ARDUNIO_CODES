//S39 - Smart light
#define LDR_PIN 0          //Define the pin to which the LDR is connected
#define MAX_ADC_READING 1023    //When the value applied to the ADC is 5V, we see a maximum value of 1023 in the ADC. 
                                //That's why we specified the maximum ADC reading as 1023
#define ADC_REFERENCE_VOLTAGE 5.0    //Reference voltage values on Arduino UNO Analog pins are 5 Volts. We've outlined 
                                    //this for the calculations 
#define REFERENCE_RESISTANCE 10000    //We defined that the resistance connected from the input of LDR and Analog pin 
                                    //to ground is 10K 

//The values of the two variables below are the fixed values required to calculate the LUX value.
#define LUX_CONSTANT 12518931
#define LUX_CONSTANT_CURVILINEAR_CONSTANT -1.405

int LEDPin = 3;    //Define the digital pin number to which the LED is connected

//Required variable definitions have been made for calculations 
int readValue;
float resistorVoltage, LDRVoltage;
float LDRResistance;
float LDRLux;
int proportion;
  
void setup(void) {
    pinMode(LEDPin, OUTPUT);
}

void loop(void) {  
    readValue = analogRead(LDR_PIN);    //Save the value read from the analog pin to the readValue variable 
    
    //Use the formula (readValue * 5/1023) to find the voltage equivalent of the readValue
    //and keep it at resistorVoltage variable
    resistorVoltage = (float)readValue / MAX_ADC_READING * ADC_REFERENCE_VOLTAGE;
                                                                                      
    //To find the voltage falling on the LDR. Calculate reference voltage - Resistor voltage
    LDRVoltage = ADC_REFERENCE_VOLTAGE - resistorVoltage;
    
    //We know that the resistance of LDR changes depending on the light
    //Let's find the resistance value on the LDR so that we can find the amount of light
    //For LDR resistance, we calculated it with the formula (Voltage read from LDR)/(Voltage read from analog pin * 5)
    LDRResistance = LDRVoltage / resistorVoltage * REFERENCE_RESISTANCE;
    
    //After doing the mathematical operation to find the LUX value, we found the LUX value
    LDRLux = LUX_CONSTANT * pow(LDRResistance, LUX_CONSTANT_CURVILINEAR_CONSTANT);

    //Proportion the values between 0 and 300 read from the LDRLux variable to the values between 255 and 0
    proportion = map(LDRLux, 0, 300, 255, 0);
    
    if(LDRLux > 300) {    //If LDRLux is greater than 300 
        proportion = 0;    //Set variable proportion to 0 
    }
    
    analogWrite(LEDPin, proportion);    //Send the proportion value to the LED with analogWrite command as a PWM signal
    delay(100);    //Wait for 100ms 
}
