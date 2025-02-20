//S48 - Capacitance meter

//Define charging pin
int chargePin = 8;
//Define discharging pin 
int dischargePin = 9;
//Define the pin to measure the voltage on the capacitor
int analogPin = A0;
//Define the pin to which the Button is connected
int buttonPin = 2;
//Define variables to store the start, end and elapsed times
unsigned long startTime = 0;
unsigned long endTime = 0;
unsigned long elapsedTime = 0;
//Define the variable to store the voltage value
float voltageValue = 3;
//Define the variable to store the capacity value
float capacityValue = 0.0;
//Define the measurement function
int measure(void);

void setup() {
    Serial.begin(9600);
    Serial.println("TEES ELECTRONICS ");
    Serial.println("CAPACITANCE METER");
    Serial.println("PLUG THE CAPACITOR TO MEASURE");
    Serial.println("----------------------------------- ");
    delay(3000);    //Wait for 3 seconds
    //Set discharging pin as input
    pinMode(dischargePin, INPUT);
    //Set charging pin as output
    pinMode(chargePin, OUTPUT);
    //Set button pin as input
    pinMode(buttonPin, INPUT);
    digitalWrite(chargePin, HIGH);    //Open charging pin
}

void loop() {
    //Discharge it
    //Set charging pin as input
    pinMode(chargePin, INPUT);
    //Set discharge pin as output
    pinMode(dischargePin, OUTPUT);
    //Close discharge pin
    digitalWrite(dischargePin, LOW);
    
    while(voltageValue > 2.0) {
        Serial.println("DISCHARGING...");
        voltageValue = measure();    //Measure the voltage value
        delay(100);
        capacityValue = voltageValue * (99.0/1023.0);
        Serial.print(99 - capacityValue); 
        Serial.println("  %");
        delay(50);
    }
    
    delay(1000); 
    Serial.println("CHARGING...");
  
    //Charge it
    //Set discharging pin as input
    pinMode(dischargePin, INPUT);
    //Set charging pin as output
    pinMode(chargePin, OUTPUT);
    //Open charging pin
    digitalWrite(chargePin, HIGH);
    startTime = micros();    //Save start time
    
    while(measure() < 648) {    //If the measurement value is less than 648
        Serial.print("%"); 
        Serial.println(measure()*(100.0/1023.0),1);    //Print percentages on the Serial port screen
    }
    
    endTime = micros();    //Save end time
    elapsedTime = endTime - startTime;    //Calculate elapsed time
    capacityValue = elapsedTime / 10000;    //Calculate capacity value
    Serial.print(" ***             VALUE :"); 
    Serial.print(capacityValue); 
    Serial.println("  uF           ***"); 
    delay(3000);
    
    while(1) {
        //Discharge it
        //Set charging pin as input
        pinMode(chargePin, INPUT);
        //Set discharge pin as output
        pinMode(dischargePin, OUTPUT);
        //Close discharging pin
        digitalWrite(dischargePin, LOW); 
        delay(1500);
        //Charge it
        //Set discharging pin as input
        pinMode(dischargePin, INPUT);
        //Set charging pin as output
        pinMode(chargePin, OUTPUT);
        //Open charging pin
        digitalWrite(chargePin, HIGH);
        break; 
    }
}

//Define measurement function
int measure(void) {
    int value;
    value = analogRead(analogPin);
    return value;
}
