//S103 - Processing_Alarm_Clock

import processing.serial.*;    // Add serial communication library to communicate with Arduino
import ddf.minim.*;           // Add minim library for playing sounds


Serial myPort;                // Create an object named myPort for reading values from serial port
Minim minim;                 // Create a minim object

// Create objects to store the sounds
AudioPlayer player;          // Rooster sound
AudioPlayer clock;          // Clock sound
AudioPlayer zero;           // Number sounds
AudioPlayer one;
AudioPlayer two;
AudioPlayer three;
AudioPlayer four;
AudioPlayer five;
AudioPlayer six;
AudioPlayer seven;
AudioPlayer eight;
AudioPlayer nine;
AudioPlayer ten;
AudioPlayer eleven;
AudioPlayer twelve;
AudioPlayer thirteen;
AudioPlayer fourteen;
AudioPlayer fifteen;
AudioPlayer sixteen;
AudioPlayer seventeen;
AudioPlayer eighteen;
AudioPlayer nineteen;
AudioPlayer twenty;
AudioPlayer twentyOne;
AudioPlayer twentyTwo;
AudioPlayer twentyThree;
AudioPlayer thirty;
AudioPlayer forty;
AudioPlayer fifty;
AudioPlayer wakeUpTime;

float incoming_data;          // Define variable to store values read from serial port
int quotient, remainder;
int fontSize = 40;
int h, m, s;
int Alarmh, Alarmm, Alarms;

void setup() {
    minim = new Minim(this);  // Setup for Minim
    
    // Load alarm clock sounds
    player = minim.loadFile("rooster.mp3");         // Store the rooster.mp3 sound effect from the data folder
    clock = minim.loadFile("clock.mp3");
    zero = minim.loadFile("zero.mp3");
    one = minim.loadFile("one.mp3");
    two = minim.loadFile("two.mp3");
    three = minim.loadFile("three.mp3");
    four = minim.loadFile("four.mp3");
    five = minim.loadFile("five.mp3");
    six = minim.loadFile("six.mp3");
    seven = minim.loadFile("seven.mp3");
    eight = minim.loadFile("eight.mp3");
    nine = minim.loadFile("nine.mp3");
    ten = minim.loadFile("ten.mp3");
    eleven = minim.loadFile("eleven.mp3");
    twelve = minim.loadFile("twelve.mp3");
    thirteen = minim.loadFile("thirteen.mp3");
    fourteen = minim.loadFile("fourteen.mp3");
    fifteen = minim.loadFile("fifteen.mp3");
    sixteen = minim.loadFile("sixteen.mp3");
    seventeen = minim.loadFile("seventeen.mp3");
    eighteen = minim.loadFile("eighteen.mp3");
    nineteen = minim.loadFile("nineteen.mp3");
    twenty = minim.loadFile("twenty.mp3");
    twentyOne = minim.loadFile("twentyOne.mp3");
    twentyTwo = minim.loadFile("twentyTwo.mp3");
    twentyThree = minim.loadFile("twentyThree.mp3");
    thirty = minim.loadFile("thirty.mp3");
    forty = minim.loadFile("forty.mp3");
    fifty = minim.loadFile("fifty.mp3");
    wakeUpTime = minim.loadFile("wakeUpTime.mp3");
  
    myPort = new Serial(this, "COM5", 9600);        // Use COM5 port for Arduino connection in serial port screen
    myPort.bufferUntil('\n');                       // Get data from Arduino until end of line
    size(240, 240);
}

void serialEvent(Serial myPort) {
    incoming_data = float(myPort.readStringUntil('\n'));    // Save incoming data from Arduino to incoming_data variable
    println(incoming_data);                                  // Show incoming_data in serial monitor
}

void draw() {
    background(204);
    displayTime();
    displayAlarm();
  
    if (incoming_data == 1) {                               // If incoming data is 1
        Alarmh++;
        delay(100);
        if (Alarmh > 23) {
            Alarmh = 0;
        }
    }
  
    if (incoming_data == 2) {                               // If incoming data is 2
        Alarmm++;
        delay(100);
        if (Alarmm > 59) {
            Alarmm = 0;
        }
    }
  
    if (Alarmh == h && Alarmm == m && Alarms == s) {
        while (Alarmh == h && Alarmm == m) {
            displayTime();
            displayAlarm();
            player.rewind();                                // To repeat when sound ends
            player.play();                                  // Play rooster sound
            delay(2000);
            clock.rewind();                                // To repeat when sound ends
            clock.play();
            delay(1000);
    
            if (h == 0)        { zero.rewind();         zero.play(); }
            else if (h == 1)   { one.rewind();          one.play(); }
            else if (h == 2)   { two.rewind();          two.play(); }
            else if (h == 3)   { three.rewind();        three.play(); }
            else if (h == 4)   { four.rewind();         four.play(); }
            else if (h == 5)   { five.rewind();         five.play(); }
            else if (h == 6)   { six.rewind();          six.play(); }
            else if (h == 7)   { seven.rewind();        seven.play(); }
            else if (h == 8)   { eight.rewind();        eight.play(); }
            else if (h == 9)   { nine.rewind();         nine.play(); }
            else if (h == 10)  { ten.rewind();          ten.play(); }
            else if (h == 11)  { eleven.rewind();       eleven.play(); }
            else if (h == 12)  { twelve.rewind();       twelve.play(); }
            else if (h == 13)  { thirteen.rewind();     thirteen.play(); }
            else if (h == 14)  { fourteen.rewind();     fourteen.play(); }
            else if (h == 15)  { fifteen.rewind();      fifteen.play(); }
            else if (h == 16)  { sixteen.rewind();      sixteen.play(); }
            else if (h == 17)  { seventeen.rewind();    seventeen.play(); }
            else if (h == 18)  { eighteen.rewind();     eighteen.play(); }
            else if (h == 19)  { nineteen.rewind();     nineteen.play(); }
            else if (h == 20)  { twenty.rewind();       twenty.play(); }
            else if (h == 21)  { twentyOne.rewind();    twentyOne.play(); }
            else if (h == 22)  { twentyTwo.rewind();    twentyTwo.play(); }
            else if (h == 23)  { twentyThree.rewind();  twentyThree.play(); }
            delay(1000);
    
            if (m == 0)        { zero.rewind();         zero.play(); }
            else if (m == 1)   { one.rewind();          one.play(); }
            else if (m == 2)   { two.rewind();          two.play(); }
            else if (m == 3)   { three.rewind();        three.play(); }
            else if (m == 4)   { four.rewind();         four.play(); }
            else if (m == 5)   { five.rewind();         five.play(); }
            else if (m == 6)   { six.rewind();          six.play(); }
            else if (m == 7)   { seven.rewind();        seven.play(); }
            else if (m == 8)   { eight.rewind();        eight.play(); }
            else if (m == 9)   { nine.rewind();         nine.play(); }
            else if (m == 10)  { ten.rewind();          ten.play(); }
            delay(1000);
            
            if (m >= 10) {
                quotient = m / 10;
                remainder = m % 10;
                println(quotient);
                
                if (quotient == 1)      { ten.rewind();      ten.play(); }
                else if (quotient == 2) { twenty.rewind();    twenty.play(); }
                else if (quotient == 3) { thirty.rewind();    thirty.play(); }
                else if (quotient == 4) { forty.rewind();     forty.play(); }
                else if (quotient == 5) { fifty.rewind();     fifty.play(); }
                delay(1000);
      
                if (remainder == 1)      { one.rewind();      one.play(); }
                else if (remainder == 2) { two.rewind();      two.play(); }
                else if (remainder == 3) { three.rewind();    three.play(); }
                else if (remainder == 4) { four.rewind();     four.play(); }
                else if (remainder == 5) { five.rewind();     five.play(); }
                else if (remainder == 6) { six.rewind();      six.play(); }
                else if (remainder == 7) { seven.rewind();    seven.play(); }
                else if (remainder == 8) { eight.rewind();    eight.play(); }
                else if (remainder == 9) { nine.rewind();     nine.play(); }
                delay(1000);
            }
    
            wakeUpTime.rewind();
            wakeUpTime.play();
    
            for (int i = 0; i < 100; i++) {
                delay(20);
            }
        }
    } else {
        player.pause();
    }
}

void displayTime() {
    h = hour();
    m = minute();
    s = second();
    fill(0, 102, 153);
    text("TIME", 120, 40);
    textSize(fontSize);
    textAlign(CENTER);
    text(h + ":" + nf(m, 2) + ":" + nf(s, 2), 120, 80);
}

void displayAlarm() {
    fill(0, 102, 153);
    text("ALARM", 120, 150);
    textSize(fontSize);
    textAlign(CENTER);
    text(Alarmh + ":" + nf(Alarmm, 2) + ":" + nf(Alarms, 2), 120, 190);
}
