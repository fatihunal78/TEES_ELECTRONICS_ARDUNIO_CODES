// SA76 - Elektronik Periyotik Cetvel

#include <LiquidCrystal_I2C.h>    //I2C LCD kütüphanesini ekle
#include <Keypad.h>               //Keypad kütüphanesi eklendi
#include <stdlib.h>               //integer'dan karaktere dönüşüm için gerekli itoa fonksiyonunu kullanmak için 
                                 //gerekli kütüphane

LiquidCrystal_I2C lcd(0x27, 16, 2);  //1602 LCD ekranı tanımla

const byte SATIR = 4;                 //Tuş takımının kaç satırdan oluştuğunu belirt 
const byte SUTUN = 4;                 //Tuş takımının kaç sütundan oluştuğunu belirt 

//Satır ve sütundaki tuşların yerini ve sırasını tanımla
char Basilan_tuslar[SATIR][SUTUN] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

//Tuş takımının satır ve sütun pinlerinin bağlandığı pinleri tanımla
byte satirPinleri[SATIR] = {7, 6, 5, 4}; 
byte sutunPinleri[SUTUN] = {3, 2, 1, 0}; 

//Tuş takımını başlat
Keypad Tus_Takimi = Keypad(makeKeymap(Basilan_tuslar), satirPinleri, sutunPinleri, SATIR, SUTUN);

char Basilan_tus;                    //Tuş takımından basılan tuşun kaydedileceği değişkeni tanımla                                                                                   
char Atom_No_char[4] = {};           //Atom numarası değişkenini karakter olarak tutacağı değişkeni tanımla
int Atom_No;                         //Atom numarasının tamsayı olarak tutulmasını sağlayacak değişkeni tanımla
int i = 0;
int dongu = 1;

void setup() {
    lcd.begin();                     //LCD'yi başlat
    lcd.backlight();                 //LCD arka ışıklarını aç
    lcd.clear();                     //LCD'yi temizle
    lcd.setCursor(0, 0);             //İlk satıra geç 
    lcd.print("   ELEKTRONIK");      //ELEKTRONIK yaz     
    lcd.setCursor(0, 1);             //Alt satıra geç
    lcd.print("PERIYODIK CETVEL ");  //PERIYODIK CETVEL yaz
    delay(2000);                     //2 saniye bekle
    lcd.clear();                     //LCD'yi temizle
    lcd.print("Atom Numarasi");      //LCD Ekrana Atom Numarasi yazdır
    lcd.setCursor(0, 1);             //Alt satıra geç
    lcd.print("Girin ve # basin");   //LCD Ekrana Girin ve # basin yazdır
    delay(2000);                     //2 saniye bekle 
    lcd.clear();                     //LCD'yi temizle 
}

void loop() {
    if (dongu == 1) {
        lcd.clear();
        while (1) {                  //Sonsuz döngüye gir 
            Basilan_tus = Tus_Takimi.getKey();  //Keypad'den basılan tuşu Basilan_tus karakterine kaydet
            
            if (Basilan_tus) {       //Eğer tuşa basıldı ise
                Atom_No_char[i] = Basilan_tus;  //Atom_No_char[i] değişkenine basilan tuşu kaydet
                lcd.setCursor(0, 0);
                lcd.print("Atom No:");          //LCD ekranın ilk satırına git ve Atom No: yaz            
                lcd.setCursor(9 + i, 0);        //LCD Ekranın ilk satırında 9+i. sütüna git
                lcd.print(Atom_No_char[i]);     //Tuş takımından basılan değerleri LCD ekrana yazdır
                
                if (i > 2) i = 0;              //Eğer i değeri 2'den büyük ise i değerini 0 yap
                i++;                           //i değerini bir arttır
                
                Atom_No = atoi(Atom_No_char);  //char formatındaki değişkeni tam sayı formatına çevir
                
                if (Basilan_tus == '#') {      //Eğer #'ye basıldı ise
                    lcd.clear();
                    i = 0;
                    dongu = 0;
                    break;                      //sonsuz döngüyü bitir
                }
            }
        }
    }

    lcd.clear();                               //LCD'yi temizle 
    Basilan_tus = Tus_Takimi.getKey();        //Keypad'den basılan tuşu Basilan_tus karakterine kaydet
    if (Basilan_tus == '*') {
        dongu = 1;
    }

    //Girilen atom numarasına göre aşağıdaki işlemleri gerçekleştir
    if (Atom_No == 0) {
        lcd.print("ATOM NO>0 OLMALI");
    }
    else if (Atom_No == 1) {
        lcd.print("Hidrojen (H)");
        degeryaz(1.007);
    }
    else if (Atom_No == 2) {
        lcd.print("Helyum (He)");
        degeryaz(4.002);
    }
    else if (Atom_No == 3) {
        lcd.print("Lityum (Li)");
        degeryaz(6.941);
    }
    else if (Atom_No == 4) {
        lcd.print("Berilyum (Be)");
        degeryaz(9.012);
    }
    else if (Atom_No == 5) {
        lcd.print("Bor (B)");
        degeryaz(10.811);
    }
    else if (Atom_No == 6) {
        lcd.print("Karbon (C)");
        degeryaz(12.011);
    }
    else if (Atom_No == 7) {
        lcd.print("Azot (N)");
        degeryaz(14.006);
    }
    else if (Atom_No == 8) {
        lcd.print("Oksijen (O)");
        degeryaz(15.999);
    }
    else if (Atom_No == 9) {
        lcd.print("Flor (F)");
        degeryaz(18.998);
    }
    else if (Atom_No == 10) {
        lcd.print("Neon (Ne)");
        degeryaz(20.179);
    }
    else if (Atom_No == 11) {
        lcd.print("Sodyum (Na)");
        degeryaz(22.989);
    }
    else if (Atom_No == 12) {
        lcd.print("Magnezyum (Mg)");
        degeryaz(24.305);
    }
    else if (Atom_No == 13) {
        lcd.print("Aluminyum (Al)");
        degeryaz(26.981);
    }
    else if (Atom_No == 14) {
        lcd.print("Silisyum (Si)");
        degeryaz(28.085);
    }
    else if (Atom_No == 15) {
        lcd.print("Fosfor (P)");
        degeryaz(30.973);
    }
    else if (Atom_No == 16) {
        lcd.print("Kukurt (S)");
        degeryaz(32.060);
    }
    else if (Atom_No == 17) {
        lcd.print("Klor (Cl)");
        degeryaz(35.452);
    }
    else if (Atom_No == 18) {
        lcd.print("Argon (Ar)");
        degeryaz(39.948);
    }
    else if (Atom_No == 19) {
        lcd.print("Potasyum (K)");
        degeryaz(39.098);
    }
    else if (Atom_No == 20) {
        lcd.print("Kalsiyum (Ca)");
        degeryaz(40.078);
    }
    else if (Atom_No == 21) {
        lcd.print("Skandiyum (Sc)");
        degeryaz(44.955);
    }
    else if (Atom_No == 22) {
        lcd.print("Titanyum (Ti)");
        degeryaz(47.880);
    }
    else if (Atom_No == 23) {
        lcd.print("Vanadyum (V)");
        degeryaz(50.941);
    }
    else if (Atom_No == 24) {
        lcd.print("Krom (Cr)");
        degeryaz(51.996);
    }
    else if (Atom_No == 25) {
        lcd.print("Manganez (Mn)");
        degeryaz(54.938);
    }
    else if (Atom_No == 26) {
        lcd.print("Demir (Fe)");
        degeryaz(55.847);
    }
    else if (Atom_No == 27) {
        lcd.print("Kobalt (Co)");
        degeryaz(58.933);
    }
    else if (Atom_No == 28) {
        lcd.print("Nikel (Ni)");
        degeryaz(58.695);
    }
    else if (Atom_No == 29) {
        lcd.print("Bakir (Cu)");
        degeryaz(63.546);
    }
    else if (Atom_No == 30) {
        lcd.print("Cinko (Zn)");
        degeryaz(65.390);
    }
    else if (Atom_No == 31) {
        lcd.print("Galyum (Ga)");
        degeryaz(69.723);
    }
    else if (Atom_No == 32) {
        lcd.print("Germanyum (Ge)");
        degeryaz(72.610);
    }
    else if (Atom_No == 33) {
        lcd.print("Arsenik (As)");
        degeryaz(74.921);
    }
    else if (Atom_No == 34) {
        lcd.print("Selenyum (Se)");
        degeryaz(78.960);
    }
    else if (Atom_No == 35) {
        lcd.print("Brom (Br)");
        degeryaz(79.904);
    }
    else if (Atom_No == 36) {
        lcd.print("Kripton (Kr)");
        degeryaz(83.800);
    }
    else if (Atom_No == 37) {
        lcd.print("Rubidyum (Rb)");
        degeryaz(85.467);
    }
    else if (Atom_No == 38) {
        lcd.print("Stronsiyum (Sr)");
        degeryaz(87.620);
    }
    else if (Atom_No == 39) {
        lcd.print("itriyum (Y)");
        degeryaz(88.905);
    }
    else if (Atom_No == 40) {
        lcd.print("Zirkonyum (Zr)");
        degeryaz(91.224);
    }
    else if (Atom_No == 41) {
        lcd.print("Niyobyum (Nb)");
        degeryaz(92.906);
    }
    else if (Atom_No == 42) {
        lcd.print("Molibden (Mo)");
        degeryaz(95.940);
    }
    else if (Atom_No == 43) {
        lcd.print("Teknesyum (Tc)");
        degeryaz(98.000);
    }
    else if (Atom_No == 44) {
        lcd.print("Rutenyum (Ru)");
        degeryaz(101.070);
    }
    else if (Atom_No == 45) {
        lcd.print("Rodyum (Rh)");
        degeryaz(102.905);
    }
    else if (Atom_No == 46) {
        lcd.print("Palladyum (Pd)");
        degeryaz(106.420);
    }
    else if (Atom_No == 47) {
        lcd.print("Gumus (Ag)");
        degeryaz(107.868);
    }
    else if (Atom_No == 48) {
        lcd.print("Kadmiyum (Cd)");
        degeryaz(112.411);
    }
    else if (Atom_No == 49) {
        lcd.print("indiyum (In)");
        degeryaz(114.820);
    }
    else if (Atom_No == 50) {
        lcd.print("Kalay (Sn)");
        degeryaz(118.710);
    }
    else if (Atom_No == 51) {
        lcd.print("Antimon (Sb)");
        degeryaz(121.757);
    }
    else if (Atom_No == 52) {
        lcd.print("Tellur (Te)");
        degeryaz(127.600);
    }
    else if (Atom_No == 53) {
        lcd.print("iyot (I)");
        degeryaz(126.904);
    }
    else if (Atom_No == 54) {
        lcd.print("Ksenon (Xe)");
        degeryaz(131.290);
    }
    else if (Atom_No == 55) {
        lcd.print("Sezyum (Cs)");
        degeryaz(132.905);
    }
    else if (Atom_No == 56) {
        lcd.print("Baryum (Ba)");
        degeryaz(137.327);
    }
    else if (Atom_No == 57) {
        lcd.print("Lantan (La)");
        degeryaz(138.905);
    }
    else if (Atom_No == 58) {
        lcd.print("Seryum (Ce)");
        degeryaz(140.115);
    }
    else if (Atom_No == 59) {
        lcd.print("Praseodim (Pr)");
        degeryaz(140.907);
    }
    else if (Atom_No == 60) {
        lcd.print("Neodim (Nd)");
        degeryaz(144.240);
    }
    else if (Atom_No == 61) {
        lcd.print("Prometyum (Pm)");
        degeryaz(145.000);
    }
    else if (Atom_No == 62) {
        lcd.print("Samaryum (Sm)");
        degeryaz(150.360);
    }
    else if (Atom_No == 63) {
        lcd.print("Evropyum (Eu)");
        degeryaz(151.965);
    }
    else if (Atom_No == 64) {
        lcd.print("Gadolinyum (Gd)");
        degeryaz(157.250);
    }
    else if (Atom_No == 65) {
        lcd.print("Terbiyum (Tb)");
        degeryaz(158.925);
    }
    else if (Atom_No == 66) {
        lcd.print("Disprosiyum (Dy)");
        degeryaz(162.500);
    }
    else if (Atom_No == 67) {
        lcd.print("Holmiyum (Ho)");
        degeryaz(164.930);
    }
    else if (Atom_No == 68) {
        lcd.print("Erbiyum (Er)");
        degeryaz(167.260);
    }
    else if (Atom_No == 69) {
        lcd.print("Tulyum (Tm)");
        degeryaz(168.934);
    }
    else if (Atom_No == 70) {
        lcd.print("iterbiyum (Yb)");
        degeryaz(173.040);
    }
    else if (Atom_No == 71) {
        lcd.print("Lutesyum (Lu)");
        degeryaz(174.967);
    }
    else if (Atom_No == 72) {
        lcd.print("Hafniyum (Hf)");
        degeryaz(178.490);
    }
    else if (Atom_No == 73) {
        lcd.print("Tantal (Ta)");
        degeryaz(180.947);
    }
    else if (Atom_No == 74) {
        lcd.print("Tungsten (W)");
        degeryaz(183.850);
    }
    else if (Atom_No == 75) {
        lcd.print("Renyum (Re)");
        degeryaz(186.207);
    }
    else if (Atom_No == 76) {
        lcd.print("Osmiyum (Os)");
        degeryaz(190.200);
    }
    else if (Atom_No == 77) {
        lcd.print("iridyum (Ir)");
        degeryaz(192.220);
    }
    else if (Atom_No == 78) {
        lcd.print("Platin (Pt)");
        degeryaz(195.080);
    }
    else if (Atom_No == 79) {
        lcd.print("Altin (Au)");
        degeryaz(196.966);
    }
    else if (Atom_No == 80) {
        lcd.print("Civa (Hg)");
        degeryaz(200.590);
    }
    else if (Atom_No == 81) {
        lcd.print("Talyum (Tl)");
        degeryaz(204.383);
    }
    else if (Atom_No == 82) {
        lcd.print("Kursun (Pb)");
        degeryaz(207.200);
    }
    else if (Atom_No == 83) {
        lcd.print("Bizmut (Bi)");
        degeryaz(208.980);
    }
    else if (Atom_No == 84) {
        lcd.print("Polonyum (Po)");
        degeryaz(209);
    }
    else if (Atom_No == 85) {
        lcd.print("Astatin (At)");
        degeryaz(210);
    }
    else if (Atom_No == 86) {
        lcd.print("Radon (Rn)");
        degeryaz(222);
    }
    else if (Atom_No == 87) {
        lcd.print("Fransiyum (Fr)");
        degeryaz(223);
    }
    else if (Atom_No == 88) {
        lcd.print("Radyum (Ra)");
        degeryaz(226.025);
    }
    else if (Atom_No == 89) {
        lcd.print("Aktinyum (Ac)");
        degeryaz(227);
    }
    else if (Atom_No == 90) {
        lcd.print("Toryum (Th)");
        degeryaz(232.038);
    }
    else if (Atom_No == 91) {
        lcd.print("Protaktinyum(Pa)");
        degeryaz(231.035);
    }
    else if (Atom_No == 92) {
        lcd.print("Uranyum (U)");
        degeryaz(238.028);
    }
    else if (Atom_No == 93) {
        lcd.print("Neptunyum (Np)");
        degeryaz(237.048);
    }
    else if (Atom_No == 94) {
        lcd.print("Plutonyum (Pu)");
        degeryaz(244);
    }
    else if (Atom_No == 95) {
        lcd.print("Amerikyum (Am)");
        degeryaz(243);
    }
    else if (Atom_No == 96) {
        lcd.print("Kuriyum (Cm)");
        degeryaz(247);
    }
    else if (Atom_No == 97) {
        lcd.print("Berkelyum (Bk)");
        degeryaz(247);
    }
    else if (Atom_No == 98) {
        lcd.print("Kaliforniyum (Cf)");
        degeryaz(251);
    }
    else if (Atom_No == 99) {
        lcd.print("Aynstaynyum (Es)");
        degeryaz(252);
    }
    else if (Atom_No == 100) {
        lcd.print("Fermiyum (Fm)");
        degeryaz(257);
    }
    else if (Atom_No == 101) {
        lcd.print("Mendelevyum (Md)");
        degeryaz(258);
    }
    else if (Atom_No == 102) {
        lcd.print("Nobelyum (No)");
        degeryaz(259);
    }
    else if (Atom_No == 103) {
        lcd.print("Lavrensiyum (Lr)");
        degeryaz(260);
    }
    else {
        lcd.print("Atom No HATALI");
    }
    delay(200);
}

void degeryaz(double kutle_No) {
    lcd.setCursor(0, 1);
    lcd.print("AN:");
    lcd.print(Atom_No);
    lcd.print(" KN:");
    lcd.print(kutle_No);
}
