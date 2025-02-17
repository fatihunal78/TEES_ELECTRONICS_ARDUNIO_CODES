//S38 - Luxmeter

/* The formula required for measuring light level with LDR is as follows. 
 * Lux=500/R(LDR)   The light level is equal to 500 divided by the LDR resistance
 * RLDR= (10*Vout)/(5-Vout)  LDR resistance calculation formula in kohm
 * 
 * If we replace the RLDR formula in the formula above
 * We will find Lux= (2500/Vout-500)/10)
 * 
 * It will be equal to Vout= ADC_readValue * (5/1024).
 */
double Light(int ADC_readValue) {  //We created a function called Light
    double Vout = ADC_readValue * 0.0048828125;  //We multiplied the value read from ADC by 5/1024, which is 0.0048828125.
    int lux = (2500/Vout-500)/10;  //We made the necessary calculations to find the lux value, which is the unit of light intensity. 
    return lux;  //We sent the calculated lux value into the loop function with the return command.
}

void setup() {
    Serial.begin(9600);  //Start serial communication
}

void loop() {
    int readValue = analogRead(0);  //Define the readValue variable and store the value read from Analog 0 pin in the readValue variable 
    Serial.print("Light Brightness:");  //Write the light brightness value to the serial screen (Characters other than English alphabet may not appear on the serial port screen.)
    Serial.print(int(Light(analogRead(0))));  //Return the value calculated with the Light function on the serial screen
    Serial.println("  LUX  ");
    delay(1000);  //Wait for 1 second 
}
