//SA29 - Wireless transmission

int sensorPin = A5;       // Define the pin number to which the infrared sensor is connected
int LEDs[] = {2, 3, 4, 5, 6}; // Define the pin numbers to which the LEDs are connected
int readValue;            // Define the variable to save the read value from ADC
int averageValue;         // Define the variable to store the average of the 10 values read from the ADC
int sensorValue;          // Define the variable in which the values read from the infrared receiver sensor will be stored

void setup() {
  pinMode(sensorPin, INPUT); // Set the pin to which the infrared sensor is connected as input
  for (int i = 0; i < 5; i++) { // Use for loop 
    pinMode(LEDs[i], OUTPUT); // Set LEDs as output pin 
  }
  
  // The sensor was initially calibrated with the following operations
  // Values at the analog pin may vary according to variable factors such as temperature, light, sound and location
  // That's why calibration is done at the beginning
  
  for (int i = 0; i < 10; i++) { // Loop from 0 to 10 to get 10 values from ADC initially 
    readValue = analogRead(sensorPin); // Save read values from ADC to readValue variable
    averageValue = averageValue + readValue; // Add the new value to the readValue variable with the previous value 
                                             // and save it
    delay(50); // Wait for 50ms 
  }
  averageValue = averageValue / 10; // Average of 10 measured values
}

void loop() {
  sensorValue = analogRead(sensorPin); // Read analog values from infrared sensor and save them to sensorValue variable
  int proportion = map(sensorValue, averageValue, 1024, 0, 6); // Proportion the value in the sensorValue variable 
                                                               // between 0 and 6

  switch (proportion) { // Based on the data returned from the proportion variable, use the switch case structure 
    case 0: // In case 0 
      for (int i = 0; i < 5; i++) { // Using for loop 
        digitalWrite(LEDs[i], LOW); // Turn OFF all LEDs 
      }
      break; // End case 0 
      
    case 1: // In case 1 
      for (int i = 0; i < 5; i++) { // Using for loop 
        digitalWrite(LEDs[i], LOW); // Turn OFF all LEDs 
      }
      digitalWrite(LEDs[0], HIGH); // Turn ON 1st Yellow LED
      break; // End case 1 
      
    case 2: // In case 2 
      for (int i = 0; i < 5; i++) { // Using for loop 
        digitalWrite(LEDs[i], LOW); // Turn OFF all LEDs 
      }
      // Turn ON the 1st and 2nd Green LEDs 
      digitalWrite(LEDs[0], HIGH);
      digitalWrite(LEDs[1], HIGH);
      break; // End case 2 
      
    case 3: // In case 3 
      for (int i = 0; i < 5; i++) { // Using for loop 
        digitalWrite(LEDs[i], LOW); // Turn OFF all LEDs 
      }
      // Turn ON the 1st and 2nd Green LED and Yellow LED 
      digitalWrite(LEDs[0], HIGH);
      digitalWrite(LEDs[1], HIGH);
      digitalWrite(LEDs[2], HIGH);
      break; // End case 3 
      
    case 4: // In case 4 
      for (int i = 0; i < 5; i++) { // Using for loop 
        digitalWrite(LEDs[i], LOW); // Turn OFF all LEDs 
      }
      // Turn ON the 1st and 2nd Green LED, Yellow LED and 1st Red LED 
      digitalWrite(LEDs[0], HIGH);
      digitalWrite(LEDs[1], HIGH);
      digitalWrite(LEDs[2], HIGH);
      digitalWrite(LEDs[3], HIGH);
      break; // End case 4 
      
    case 5: // In case 5 
      // Turn ON all LEDs 
      digitalWrite(LEDs[0], HIGH);
      digitalWrite(LEDs[1], HIGH);
      digitalWrite(LEDs[2], HIGH);
      digitalWrite(LEDs[3], HIGH);
      digitalWrite(LEDs[4], HIGH); 
      break; // End case 5 
  }
  
  delay(100);
}
