//SA87 - Fruit piano

#include <CapacitiveSensor.h>                                //Add capacitive sensor library 
 
#define speakerPin 11                                       //Define the pin number to which the Speaker is connected

//Define musical notes and frequency values
#define do       262                                        //do
#define re       294                                        //re
#define mi       330                                        //mi
#define fa       349                                        //fa
#define so       392                                        //so
#define la       440                                        //la
#define ti       494                                        //ti
#define soft_do  512                                        //soft do

//Define the pin numbers to which the fruits are connected to the capacitive sensor library
CapacitiveSensor cs_2_3  = CapacitiveSensor(2, 3); 
CapacitiveSensor cs_2_4  = CapacitiveSensor(2, 4); 
CapacitiveSensor cs_2_5  = CapacitiveSensor(2, 5); 
CapacitiveSensor cs_2_6  = CapacitiveSensor(2, 6); 
CapacitiveSensor cs_2_7  = CapacitiveSensor(2, 7); 
CapacitiveSensor cs_2_8  = CapacitiveSensor(2, 8); 
CapacitiveSensor cs_2_9  = CapacitiveSensor(2, 9); 
CapacitiveSensor cs_2_10 = CapacitiveSensor(2, 10); 

void setup() {
    pinMode(speakerPin, OUTPUT);                           //Set the pin to which the Speaker is connected as output
}

void loop() {
    //Set the touch sensitivity of the fruits to be used as sensors
    //And when the fruits are touched, save the read values to the fruit variables
    long fruit1 = cs_2_3.capacitiveSensor(10000);
    long fruit2 = cs_2_4.capacitiveSensor(10000);
    long fruit3 = cs_2_5.capacitiveSensor(10000);
    long fruit4 = cs_2_6.capacitiveSensor(10000);
    long fruit5 = cs_2_7.capacitiveSensor(10000);
    long fruit6 = cs_2_8.capacitiveSensor(10000);
    long fruit7 = cs_2_9.capacitiveSensor(10000);
    long fruit8 = cs_2_10.capacitiveSensor(10000);

    //When the fruits are touched, the corresponding note is played from the speaker
    if (fruit1 > 300) {
        tone(speakerPin, do);
        delay(200);
    } else if (fruit2 > 300) {
        tone(speakerPin, re);
        delay(200);
    } else if (fruit3 > 300) {
        tone(speakerPin, mi);
        delay(200);
    } else if (fruit4 > 300) {
        tone(speakerPin, fa);
        delay(200);
    } else if (fruit5 > 300) {
        tone(speakerPin, so);
        delay(200);
    } else if (fruit6 > 300) {
        tone(speakerPin, la);
        delay(200);
    } else if (fruit7 > 300) {
        tone(speakerPin, ti);
        delay(200);
    } else if (fruit8 > 300) {
        tone(speakerPin, soft_do);
        delay(200);
    } else {
        noTone(speakerPin);
    }
}
