//S70 - Turkish National Anthem

const int speakerPin = 3; //Define the pin number to which the Speaker is connected 
int buttonPin = 2; //Define the pin number to which the Button is connected
//Define the pin numbers to which the LEDs are connected
int redLED = 6;
int whiteLED = 7;

//Define the notes to use
int a, ad, b, c, cd, d, dd, e, f, fd, g, gd, a2, ad2, b2, c2, cd2, d2, dd2, e2, f2, fd2, g2, gd2, a3;

void setup() 
{  
  pinMode(speakerPin, OUTPUT); //Set the pin to which the Speaker is connected as output 
  pinMode(redLED, OUTPUT); //Set the pin to which the Red LED is connected as output 
  pinMode(whiteLED, OUTPUT); //Set the pin to which the White LED is connected as output 
  pinMode(buttonPin, INPUT); //Set the pin to which the Button is connected as input 

  //////////////////////  
  //c  = do
  //cd = do sharp
  //d = re
 //dd = re sharp
  //e = mi
  //f = fa
  //fd = fa sharp
  //g = so
  //gd = so sharp
  //a = la
  //ad = la sharp
  //b = ti
  ///////////////////////
  
  //Frequency values corresponding to the musical notes
  a=440;
  ad=466;
  b=494;
  c=523;
  cd=554;
  d=587;
  dd=622;
  e=659;
  f = 698;
  fd = 740;
  g = 784;
  gd = 830;
  a2 = 880;
  ad2 = 932;
  b2 = 988;
  c2 = 1046;
  cd2 = 1108;
  d2 = 1174;
  dd2 = 1244;
  e2 = 1318;
  f2 = 1396;
  fd2 = 1480;
  g2 = 1568;
  gd2 = 1660;
  a3 = 1760;
}  

/**/
// Turkish National Anthem: English lyrics
// Fear not! The scarlet flag rippling at dawns shall not wither
// While my country's last smoking hearth is yet aflicker.
// She is the star of my nation: she is meant to blaze and shine;
// She belongs to none but my nation alone, she is mine.

// Do not frown, I beseech you, oh coy crescent!
// But smile at my valiant race… Why this angry, why violent?
// Lest our blood spilt for you be unblessed and worthless.
// For my nation, who worships God, has the right to independence!

/**/
// Turkish national anthem: Turkish lyrics
// Korkma! Sönmez bu şafaklarda yüzen al sancak,
// Sönmeden yurdumun üstünde tüten en son ocak.
// O benim milletimin yıldızıdır, parlayacak;
// O benimdir, o benim milletimindir ancak.

// Çatma, kurban olayım, çehreni ey nazlı hilal!
// Kahraman ırkıma bir gül; ne bu şiddet, bu celal?
// Sana olmaz dökülen kanlarımız sonra helal...
// Hakkıdır, Hakk'a tapan milletimin istiklal!

void loop()
{  
  if(digitalRead(buttonPin) == HIGH) { //If the Button is pressed 
    while(1) 
    {
      //Turkish National Anthem: 
      //*** First Verse ***
      //Korkma Sönmez Bu Şafak  
      tone(speakerPin, c);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(800); 
         
      tone(speakerPin, f);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(800);
      
      tone(speakerPin, g);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(800);
      
      digitalWrite(whiteLED, LOW); 
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(800);
      
      tone(speakerPin, e);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400);
      
      tone(speakerPin, g);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
        delay(200); 
      
      tone(speakerPin, f);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(1600); 
           
      noTone(speakerPin);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(300);
      
      //Larda Yüzden Al Sancak
      tone(speakerPin, f);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(800); 
  
      tone(speakerPin, ad2);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(800); 
  
      tone(speakerPin, c2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(800); 
  
      tone(speakerPin, cd2);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(800);
  
      tone(speakerPin, a2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400);
  
      tone(speakerPin, c2);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, ad2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(1600); 
  
      //Sönmeden Yurdumun Üstünde Tüten En Son Ocak O Be
      tone(speakerPin, c2);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
        delay(200); 
  
      tone(speakerPin, ad2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
        delay(200); 
  
      tone(speakerPin, c2);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
        delay(200); 
  
      tone(speakerPin, g);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400); 
  
      noTone(speakerPin);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(100); 
  
      tone(speakerPin, g);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400); 
  
      tone(speakerPin, ad);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, gd);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW); 
      delay(400); 
  
      tone(speakerPin, e);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, f);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400); 
      
      tone(speakerPin, g);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, gd);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400); 
  
      tone(speakerPin, ad);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
        delay(200); 
  
      tone(speakerPin, c2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400); 
  
      tone(speakerPin, cd2);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
        delay(200); 
  
      tone(speakerPin, dd2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400); 
  
      tone(speakerPin, f2);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
        delay(200); 
  
      tone(speakerPin, dd2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400); 
  
      //Nim Milletimin
      tone(speakerPin, dd);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, d);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(200);
  
      tone(speakerPin, dd);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, c2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(800);
  
      tone(speakerPin, ad);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(800);
  
      tone(speakerPin, gd);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(1600);
  
      //Yıldızıdır Parlayacak O Benim
      tone(speakerPin, c);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH); 
      delay(200);
  
      tone(speakerPin, b);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(200);
  
      tone(speakerPin, c);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, g);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(800);
  
      tone(speakerPin, c);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(800);
  
      tone(speakerPin, c2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(800);
  
      tone(speakerPin, ad);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, gd);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(200);
  
      tone(speakerPin, g);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(400);
  
      tone(speakerPin, gd);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(200);
  
      tone(speakerPin, f);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(800);
  
      //Dir O Benim Milletimindir Ancak
      tone(speakerPin, f2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(800);
  
      tone(speakerPin, dd2);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, cd2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400);
  
      tone(speakerPin, c2);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, ad);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400);
  
      tone(speakerPin, gd);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, g);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400);
  
      tone(speakerPin, f);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, c2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400);
  
      tone(speakerPin, c);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(800);
  
      tone(speakerPin, f);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(1600);
  
      //*** Second Verse ***
      //Çatma Kurban Olayım
      tone(speakerPin, c);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(800);
  
      tone(speakerPin, f);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(800);
  
      tone(speakerPin, g);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(800);
  
      tone(speakerPin, gd);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(800);
      
      tone(speakerPin, e);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(400);
  
      tone(speakerPin, g);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
        delay(200); 
  
      tone(speakerPin, f);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(1600); 
  
      noTone(speakerPin);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(300);
  
      //Çehreni Ey Nazlı Hilal
      tone(speakerPin, f);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(800); 
  
      tone(speakerPin, ad2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(800); 
  
      tone(speakerPin, c2);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(800); 
  
      tone(speakerPin, cd2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400);
  
      tone(speakerPin, ad2);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(400);
  
      tone(speakerPin, a2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400);
  
      tone(speakerPin, c2);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(400);
  
      tone(speakerPin, ad2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(800); 
  
      //Kahraman Irkıma Bir Gül Ne Bu Şiddet Bu Celal Sana
      tone(speakerPin, c2);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
        delay(200); 
  
      tone(speakerPin, ad2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
        delay(200); 
  
      tone(speakerPin, c2);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
        delay(200); 
  
      tone(speakerPin, g);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400); 
  
      noTone(speakerPin);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(100); 
  
      tone(speakerPin, g);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400); 
  
      tone(speakerPin, ad);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, gd);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400); 
  
      tone(speakerPin, e);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, f);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400); 
  
      tone(speakerPin, g);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, gd);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400); 
  
      tone(speakerPin, ad);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
        delay(200); 
  
      tone(speakerPin, c2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400); 
  
      tone(speakerPin, cd2);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
        delay(200); 
  
      tone(speakerPin, dd2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400); 
  
      tone(speakerPin, f2);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
        delay(200); 
  
      tone(speakerPin, dd2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400); 
  
      //Olmaz Dökülen
      tone(speakerPin, dd);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, d);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(200);
  
      tone(speakerPin, dd);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, c2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(800);
  
      tone(speakerPin, ad);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(800);
  
      tone(speakerPin, gd);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(1600);
  
      //Kanlarımız Sonra Helal Hakkıdır
      tone(speakerPin, c);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, b);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(200);
  
      tone(speakerPin, c);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, g);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(800);
  
      tone(speakerPin, c);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(800);
  
      tone(speakerPin, c2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(800);
  
      tone(speakerPin, ad);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, gd);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(200);
  
      tone(speakerPin, g);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(400);
  
      tone(speakerPin, gd);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(200);
  
      tone(speakerPin, f);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(800);
  
      //Hakk'a Tapan Milletimin İstiklal
      tone(speakerPin, f2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(800);
  
      tone(speakerPin, dd2);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, cd2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400);
  
      tone(speakerPin, c2);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, ad);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400);
  
      tone(speakerPin, gd);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, g);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400);
  
      tone(speakerPin, f);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(200);
  
      tone(speakerPin, c2);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(400);
  
      tone(speakerPin, c);
      digitalWrite(redLED, LOW);
      digitalWrite(whiteLED, HIGH);
      delay(800);
  
      tone(speakerPin, f);
      digitalWrite(redLED, HIGH);
      digitalWrite(whiteLED, LOW);
      delay(1600);
      break;
    }    
  }
  //Penned By   : Mehmet Akif Ersoy
  //Composed By : Osman Zeki Üngör
  
  else
  {
    noTone(speakerPin);
    delay(300);
  }
}
