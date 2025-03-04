//SA76 - Electronic periodic table

#include <LiquidCrystal_I2C.h>    //Add I2C LCD library
#include <Keypad.h>               //Add Keypad Library
#include <stdlib.h>               //Library to use the itoa function required for the integer-to-character transformation

LiquidCrystal_I2C lcd(0x27, 16, 2);    //Define 1602 LCD display

const byte ROW = 4;                     //Specify how many rows the keypad consists of 
const byte COLUMN = 4;                  //Specify how many columns the keypad consists of 

//Define the position and order of the keys in the row and column
char pressedKeys[ROW][COLUMN] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

//Define the pins to which the row and column pins of the keypad are connected
byte rowPins[ROW] = { 7, 6, 5, 4 }; 
byte columnPins[COLUMN] = { 3, 2, 1, 0 }; 

//Start the keypad
Keypad key_pad = Keypad(makeKeymap(pressedKeys), rowPins, columnPins, ROW, COLUMN); 

char pressedKey;                        //Define the variable to store the key pressed on the keypad 
char Atomic_Number_char[4] = {};        //Define the variable to keep the atomic number as a character
int Atomic_Number;                      //Define the variable that will keep the atomic number as an integer
int i = 0;
int looping = 1;

void setup() {
  lcd.begin();                          //Start the LCD display
  lcd.backlight();                      //Turn ON the LCD backlights
  lcd.clear();                          //Clear the LCD display
  lcd.setCursor(0, 0);                  //Switch to the first row 
  lcd.print("   ELECTRONIC ");          //Write "ELECTRONIC" on the first row 
  lcd.setCursor(0, 1);                  //Switch to lower row
  lcd.print("PERIODIC TABLE");          //Write "PERIODIC TABLE" on the LCD display
  delay(2000);                          //Wait for 2 seconds
  lcd.clear();                          //Clear the LCD display
  lcd.print("Enter Atomic");            //Print "Atomic Number" on the LCD display
  lcd.setCursor(0, 1);                  //Switch to the lower row
  lcd.print("Number and Press #");      //Print the message to the LCD display
  delay(2000);                          //Wait for 2 seconds 
  lcd.clear();                          //Clear the LCD display 
}

void loop() {
  if(looping == 1) {
    lcd.clear();
    while(1) {                          //Enter infinite loop 
      char pressedKey = key_pad.getKey();   //Save the key pressed from the keypad to the pressedKey character.
      if(pressedKey) {                      //If any key is pressed
        Atomic_Number_char[i]=pressedKey;    //Save the pressed key to the Atomic_Number_char[i] variable
        lcd.setCursor(0,0);                  //Go to the first row on the LCD display
        lcd.print("Atomic Number: ");        //Write "Atomic Number:" on the LCD display 
        //Go to column 9+i on first row of LCD display. If i=0 go to column 9, if i=1 go to column 10
        lcd.setCursor(9+i, 0);              
        lcd.print(Atomic_Number_char[i]);    //Print the values entered from the keypad to the LCD display.
        if(i > 2) i = 0;                     //If i is greater than 2, set i to 0
        i++;                                 //Increment i value by one
        
        Atomic_Number = atoi(Atomic_Number_char);    //Convert variable in char format to integer format
        
        if(pressedKey == '#') {             //If # is pressed, clear screen, reset variables and end infinite loop
          lcd.clear(); 
          i = 0; 
          looping = 0; 
          break;
        }
      }
    }
  }
  
  lcd.clear();                              //Clear the LCD display 
  pressedKey = key_pad.getKey();            //Save the key pressed from the keypad to the pressedKey character
  if(pressedKey == '*') { looping = 1; }       //If * key is pressed, make the loop variable 1 
  
  //Perform the following operations according to the atomic number entered
  if(Atomic_Number == 0) { lcd.print("ATOMIC NUMBER > 0"); }
  else if(Atomic_Number == 1) { lcd.print("Hydrogen (H)"); printValue(1.007); }
  else if(Atomic_Number == 2) { lcd.print("Helium (He)"); printValue(4.002); }
  else if(Atomic_Number == 3) { lcd.print("Lithium (Li)"); printValue(6.941); }
  else if(Atomic_Number == 4) { lcd.print("Beryllium (Be)"); printValue(9.012); }
  else if(Atomic_Number == 5) { lcd.print("Boron (B)"); printValue(10.811); }
  else if(Atomic_Number == 6) { lcd.print("Carbon (C)"); printValue(12.011); }
  else if(Atomic_Number == 7) { lcd.print("Nitrogen (N)"); printValue(14.006); }
  else if(Atomic_Number == 8) { lcd.print("Oxygen (O)"); printValue(15.999); }
  else if(Atomic_Number == 9) { lcd.print("Fluor (F)"); printValue(18.998); }
  else if(Atomic_Number == 10) { lcd.print("Neon (Ne)"); printValue(20.179); }
  else if(Atomic_Number == 11) { lcd.print("Sodium (Na)"); printValue(22.989); }
  else if(Atomic_Number == 12) { lcd.print("Magnesium (Mg)"); printValue(24.305); }
  else if(Atomic_Number == 13) { lcd.print("Aluminum (Al)"); printValue(26.981); }
  else if(Atomic_Number == 14) { lcd.print("Silicon (Si)"); printValue(28.085); }
  else if(Atomic_Number == 15) { lcd.print("Phosphorus (P)"); printValue(30.973); }
  else if(Atomic_Number == 16) { lcd.print("Sulphur (S)"); printValue(32.060); }
  else if(Atomic_Number == 17) { lcd.print("Chlorine (Cl)"); printValue(35.452); } 
  else if(Atomic_Number == 18) { lcd.print("Argon (Ar)"); printValue(39.948); }
  else if(Atomic_Number == 19) { lcd.print("Potassium (K)"); printValue(39.098); }
  else if(Atomic_Number == 20) { lcd.print("Calcium (Ca)"); printValue(40.078); }
  else if(Atomic_Number == 21) { lcd.print("Scandium (Sc)"); printValue(44.955); }
  else if(Atomic_Number == 22) { lcd.print("Titanium (Ti)"); printValue(47.880); }
  else if(Atomic_Number == 23) { lcd.print("Vanadium (V)"); printValue(50.941); }
  else if(Atomic_Number == 24) { lcd.print("Chromium (Cr)"); printValue(51.996); }
  else if(Atomic_Number == 25) { lcd.print("Manganese (Mn)"); printValue(54.938); }
  else if(Atomic_Number == 26) { lcd.print("Iron (Fe)"); printValue(55.847); }
  else if(Atomic_Number == 27) { lcd.print("Cobalt (Co)"); printValue(58.933); }
  else if(Atomic_Number == 28) { lcd.print("Nickel (Ni)"); printValue(58.695); }
  else if(Atomic_Number == 29) { lcd.print("Copper (Cu)"); printValue(63.546); }
  else if(Atomic_Number == 30) { lcd.print("Zinc (Zn)"); printValue(65.390); }
  else if(Atomic_Number == 31) { lcd.print("Gallium (Ga)"); printValue(69.723); }
  else if(Atomic_Number == 32) { lcd.print("Germanium (Ge)"); printValue(72.610); }
  else if(Atomic_Number == 33) { lcd.print("Arsenic (As)"); printValue(74.921); }
  else if(Atomic_Number == 34) { lcd.print("Selenium (Se)"); printValue(78.960); }
  else if(Atomic_Number == 35) { lcd.print("Brom (Br)"); printValue(79.904); }
  else if(Atomic_Number == 36) { lcd.print("Krypton (Kr)"); printValue(83.800); }
  else if(Atomic_Number == 37) { lcd.print("Rubidium (Rb)"); printValue(85.467); }
  else if(Atomic_Number == 38) { lcd.print("Strontium (Sr)"); printValue(87.620); }
  else if(Atomic_Number == 39) { lcd.print("Yttrium (Y)"); printValue(88.905); }
  else if(Atomic_Number == 40) { lcd.print("Zirconium (Zr)"); printValue(91.224); }
  else if(Atomic_Number == 41) { lcd.print("Niobium (Nb)"); printValue(92.906); }
  else if(Atomic_Number == 42) { lcd.print("Molybdenum (Mo)"); printValue(95.940); }
  else if(Atomic_Number == 43) { lcd.print("Technetium (Tc)"); printValue(98.000); }
  else if(Atomic_Number == 44) { lcd.print("Ruthenium (Ru)"); printValue(101.070); }
  else if(Atomic_Number == 45) { lcd.print("Rhodium (Rh)"); printValue(102.905); }  
  else if(Atomic_Number == 46) { lcd.print("Palladium (Pd)"); printValue(106.420); }
  else if(Atomic_Number == 47) { lcd.print("Silver (Ag)"); printValue(107.868); }
  else if(Atomic_Number == 48) { lcd.print("Cadmium (Cd)"); printValue(112.411); }
  else if(Atomic_Number == 49) { lcd.print("Indium (In)"); printValue(114.820); }
  else if(Atomic_Number == 50) { lcd.print("Tin (Sn)"); printValue(118.710); }
  else if(Atomic_Number == 51) { lcd.print("Antimony (Sb)"); printValue(121.757); }
  else if(Atomic_Number == 52) { lcd.print("Tellur (Te)"); printValue(127.600); }
  else if(Atomic_Number == 53) { lcd.print("Iodine (I)"); printValue(126.904); }
  else if(Atomic_Number == 54) { lcd.print("Xenon (Xe)"); printValue(131.290); }
  else if(Atomic_Number == 55) { lcd.print("Cesium (Cs)"); printValue(132.905); }
  else if(Atomic_Number == 56) { lcd.print("Barium (Ba)"); printValue(137.327); }
  else if(Atomic_Number == 57) { lcd.print("Lanthanum (La)"); printValue(138.905); }
  else if(Atomic_Number == 58) { lcd.print("Cerium (Ce)"); printValue(140.115); }
  else if(Atomic_Number == 59) { lcd.print("Praseodim (Pr)"); printValue(140.907); }
  else if(Atomic_Number == 60) { lcd.print("Neodymium (Nd)"); printValue(144.240); }
  else if(Atomic_Number == 61) { lcd.print("Promethium (Pm)"); printValue(145.000); }
  else if(Atomic_Number == 62) { lcd.print("Samarium (Sm)"); printValue(150.360); }
  else if(Atomic_Number == 63) { lcd.print("Evropium (Eu)"); printValue(151.965); }
  else if(Atomic_Number == 64) { lcd.print("Gadolinium (Gd)"); printValue(157.250); }
  else if(Atomic_Number == 65) { lcd.print("Terbium (Tb)"); printValue(158.925); }
  else if(Atomic_Number == 66) { lcd.print("Dysprosium (Dy)"); printValue(162.500); }
  else if(Atomic_Number == 67) { lcd.print("Holmium (Ho)"); printValue(164.930); }
  else if(Atomic_Number == 68) { lcd.print("Erbium (Er)"); printValue(167.260); }
  else if(Atomic_Number == 69) { lcd.print("Thulium (Tm)"); printValue(168.934); }
  else if(Atomic_Number == 70) { lcd.print("Ytterbium (Yb)"); printValue(173.040); }
  else if(Atomic_Number == 71) { lcd.print("Lutetium (Lu)"); printValue(174.967); }
  else if(Atomic_Number == 72) { lcd.print("Hafnium (Hf)"); printValue(178.490); }
  else if(Atomic_Number == 73) { lcd.print("Tantalum (Ta)"); printValue(180.947); }
  else if(Atomic_Number == 74) { lcd.print("Tungsten (W)"); printValue(183.850); }
  else if(Atomic_Number == 75) { lcd.print("Rhenium (Re)"); printValue(186.207); }
  else if(Atomic_Number == 76) { lcd.print("Osmium (Os)"); printValue(190.200); }
  else if(Atomic_Number == 77) { lcd.print("Iridium (Ir)"); printValue(192.220); }
  else if(Atomic_Number == 78) { lcd.print("Platinum (Pt)"); printValue(195.080); }
  else if(Atomic_Number == 79) { lcd.print("Gold (Au)"); printValue(196.966); }
  else if(Atomic_Number == 80) { lcd.print("Mercury (Hg)"); printValue(200.590); }
  else if(Atomic_Number == 81) { lcd.print("Thallium (Tl)"); printValue(204.383); }
  else if(Atomic_Number == 82) { lcd.print("Lead (Pb)"); printValue(207.200); }
  else if(Atomic_Number == 83) { lcd.print("Bismuth (Bi)"); printValue(208.980); }
  else if(Atomic_Number == 84) { lcd.print("Polonium (Po)"); printValue(209); }
  else if(Atomic_Number == 85) { lcd.print("Astatine (At)"); printValue(210); }
  else if(Atomic_Number == 86) { lcd.print("Radon (Rn)"); printValue(222); }
  else if(Atomic_Number == 87) { lcd.print("Francium (Fr)"); printValue(223); }
  else if(Atomic_Number == 88) { lcd.print("Radium (Ra)"); printValue(226.025); }
  else if(Atomic_Number == 89) { lcd.print("Actinium (Ac)"); printValue(227); }
  else if(Atomic_Number == 90) { lcd.print("Thorium (Th)"); printValue(232.038); }
  else if(Atomic_Number == 91) { lcd.print("Protactinium(Pa)"); printValue(231.035); }
  else if(Atomic_Number == 92) { lcd.print("Uranium (U)"); printValue(238.028); }
  else if(Atomic_Number == 93) { lcd.print("Neptunium (Np)"); printValue(237.048); }
  else if(Atomic_Number == 94) { lcd.print("Plutonium (Pu)"); printValue(244); }
  else if(Atomic_Number == 95) { lcd.print("Americium (Am)"); printValue(243); }
  else if(Atomic_Number == 96) { lcd.print("Curium (Cm)"); printValue(247); }
  else if(Atomic_Number == 97) { lcd.print("Berkelium (Bk)"); printValue(247); }
  else if(Atomic_Number == 98) { lcd.print("Californium (Cf)"); printValue(251); } 
  else if(Atomic_Number == 99) { lcd.print("Einsteinium (Es)"); printValue(252); }
  else if(Atomic_Number == 100) { lcd.print("Fermium (Fm)"); printValue(257); }
  else if(Atomic_Number == 101) { lcd.print("Mendelevium (Md)"); printValue(258); }
  else if(Atomic_Number == 102) { lcd.print("Nobelium (No)"); printValue(259); }
  else if(Atomic_Number == 103) { lcd.print("Lavrensium (Lr)"); printValue(260); }
  /*
   * THESE ELEMENTS WERE DISCOVERED IN THE LABORATORY AND LATER ADDED TO THE PERIODIC TABLE
   * 
  else if(Atomic_Number == 104) { lcd.print("Rutherfordium(Rf)"); printValue(261); }
  else if(Atomic_Number == 105) { lcd.print("Dubnium (Db)"); printValue(262); }
  else if(Atomic_Number == 106) { lcd.print("Seaborgium (Sg)"); printValue(263); }
  else if(Atomic_Number == 107) { lcd.print("Bohrium (Bh)"); printValue(262); }
  else if(Atomic_Number == 108) { lcd.print("Hassiyum (Hs)"); printValue(265); }
  else if(Atomic_Number == 109) { lcd.print("Meitnerium (Mt)"); printValue(266); }
  else if(Atomic_Number == 110) { lcd.print("Darmstadtium(Ds)"); printValue(271); }
  else if(Atomic_Number == 111) { lcd.print("Rontgenium (Rg)"); printValue(272); }
  else if(Atomic_Number == 112) { lcd.print("Ununbium (Uub)"); printValue(277); }
  else if(Atomic_Number == 113) { lcd.print("Ununtriyum (Uut)"); printValue(284); } 
  */
  else { lcd.print("Atomic No. WRONG"); }
  delay(200);
}

void printValue(double massNumber) {
  lcd.setCursor(0, 1);
  lcd.print("AN:");
  lcd.print(Atomic_Number);
  lcd.print(" KN:");
  lcd.print(massNumber);
}
