//S40 - Ohmmeter

//Define pin numbers
int ADCPin = A0;
//Define variables
int readValue = 0;
int Vin = 5;
float Vout = 0;
int R1 = 10000;    //Known resistance value can be changed for calibration
double R2 = 0;
float buffer = 0;

void setup() {
    Serial.begin(9600);
    Serial.println("CONNECT THE RESISTOR TO MEASURE");    //Print to serial port screen
}

void loop() {
    readValue = analogRead(ADCPin);    //Save value read from ADC pin to readValue variable
    if(readValue) {    //If readValue is defined
        //Make the necessary calculations for the measurement
        buffer = readValue * Vin;
        Vout = (buffer)/1024.0;
        buffer = (Vin/Vout) - 1;
        R2 = R1 * buffer;
        
        if(R2 >= 10000000) {    //If the result is greater than 10000000 (Ten Million)
            Serial.println("Connect a Resistor.. ");
        }
        else if(R2 >= 1000 && R2 < 1000000) {    //If the result is greater than 1000 and less than 1000000, 
                                                 //to print K OHMS
            R2 = R2/1000;
            Serial.print("Resistance Value: ");
            Serial.print(R2);
            Serial.println("  K OHMS");
        }
        else if(R2 >= 1000000 && R2 < 10000000) {    //If the result is greater than 1000000 and less than 
                                                     //10000000, then to print M OHMS
            R2 = R2/1000000;
            Serial.print("Resistance Value: ");
            Serial.print(R2);
            Serial.println("  M OHMS");
        }
        else if(R2 < 1000) {    //To print OHMS if the result is less than 1000
            Serial.print("Resistance Value: ");
            Serial.print(R2);
            Serial.println("  OHMS");
        }
        delay(1000);
    }
}
