//S100 - Processing_Fire_Alarm

import processing.serial.*;    //Add serial communication library to communicate with Arduino
import ddf.minim.*;           //Add minim library for playing sounds
Serial myPort;                //Create an object named myPort to read values from Serial port
Minim minim;                 //Create a minim object
AudioPlayer player;          //Create an object to store sounds
float incoming_data;         //Variable defined to hold values read from Serial port

void setup() {
    minim = new Minim(this);                          //Setup for Minim
    player = minim.loadFile("firetruck.mp3");         //Hold the firetruck.mp3 sound effect from the data folder in player file
    myPort = new Serial(this, "COM4", 9600);          //Enter required Port and BoundRate values for Arduino communication
                                                      //You can change COM value according to your Arduino
    myPort.bufferUntil('\n');                        //Get data from Arduino until end of line
}

void serialEvent(Serial myPort) {
    incoming_data = float(myPort.readStringUntil('\n'));    //Save data coming from Arduino to incoming_data variable
    println(incoming_data);                                 //Show incoming_data on serial monitor
}

void draw() {
    println(incoming_data);                //Show incoming_data on serial monitor
    
    if (incoming_data == 0) {             //If incoming data is 0
        player.pause();                    //Stop playing sound
    }

    if (incoming_data == 1) {             //If incoming data is 1
        player.rewind();                   //To repeat when sound ends
        player.play();                     //Play firetruck sound
        
        for (int i = 0; i < 100; i++) {
            delay(50);
            if (incoming_data == 0) {      //If incoming data is 0
                player.pause();            //Stop playing sound
            }
        }
    }
} 