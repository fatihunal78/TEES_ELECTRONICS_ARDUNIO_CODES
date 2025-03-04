//SA60 - Snake game

//Add libraries
#include <LedControl.h> 
#include <MaxMatrix.h>

//Define LED Matrix connections
#define CLK  8   //Define CLK pin
#define CS   9   //Define CS pin
#define DIN  10  //Define DIN pin
int LED_Matrix_Count = 1;  //LED matrices can be connected in series
                          //If more than one matrix is to be connected, you can change the number here
MaxMatrix m(DIN, CS, CLK, LED_Matrix_Count);      //Define matrix m with matrix pin connections 
LedControl lc = LedControl(DIN, CLK, CS, 1);      //Create LedControl object named lc

//Define joystick connections
#define VRX  A4          //Define the pin to which the Joystick's VRX leg is connected
#define VRY  A5          //Define the pin to which the Joystick's VRY leg is connected
#define SW   2           //Define the pin to which the Joystick's SW leg is connected
#define speakerPin  4    //Define the pin number to which the Speaker is connected

char string1[] = "   GAME OVER   ";  //Write the text you want to slide on the screen in the double quotes

#define Size  8
#define Delay_Time 20

byte buffer[10];
int snake[Size*Size][2]; 
int length;
int food[2], v[2];
bool game_over = false;
long current_time;
long last_time;
int blink_count;
const short message_speed = 5;
int score = 0;

void start_game() {
    last_time = current_time = 0;  //Reset last_time and current_time variables
    blink_count = 3;
    int half = Size / 2;
    length = Size / 3;

    for(int i=0; i<length; i++) {
        snake[i][0] = half - 1;
        snake[i][1] = half + i;
    }

    food[0] = half + 1;
    food[1] = half - 1;

    v[0] = 0;
    v[1] = -1;
}

void render() {
    for(int i=0; i<length; i++) {
        lc.setLed(0, snake[i][0], snake[i][1], 1);
    }
    lc.setLed(0, food[0], food[1], 1);
}

void clear_screen() { 
    for(int x=0; x<Size; x++) {
        for(int y=0; y<Size; y++) {
            lc.setLed(0, x, y, 0);
        }
    }
}

bool advance() {
    int head[2] = {snake[0][0] + v[0], snake[0][1] + v[1]};

    // Check X boundary
    if(head[0] < 0 || head[0] >= Size) {
        delay(1000);
        game_over_message();
        return true;
    }

    // Check Y boundary
    if(head[1] < 0 || head[1] >= Size) {
        delay(1000);
        game_over_message();
        return true;
    }

    for(int i=0; i<length; i++) {
        if(snake[i][0] == head[0] && snake[i][1] == head[1]) {
            delay(1000); 
            game_over_message();
            return true;
        }
    }

    bool grow = (head[0] == food[0] && head[1] == food[1]);
    if(grow) {
        tone(speakerPin, 500);
        length++;
        score = score + 5; 
        randomSeed(current_time); 
        food[0] = random(Size);
        food[1] = random(Size);
        delay(50);
        noTone(speakerPin);
    }

    for(int i=length-1; i >= 0; i--) {
        snake[i + 1][0] = snake[i][0];
        snake[i + 1][1] = snake[i][1];
    }
    snake[0][0] += v[0];
    snake[0][1] += v[1];
    return false;
}

void setup() {
    pinMode(SW, INPUT_PULLUP);      //Set Joystick SW pin as input 
    pinMode(VRX, INPUT);            //Set Joystick VRX pin as input 
    pinMode(VRY, INPUT);            //Set Joystick VRY pin as input 
    pinMode(speakerPin, OUTPUT);    //Set the pin to which speaker is connected as output
  
    //Enable interrupt. Interrupt is defined on the pin connected to the Joystick button and it is defined on 
    //the restart function
    attachInterrupt(digitalPinToInterrupt(SW), restart, RISING);
                                                                      
    lc.shutdown(0, false); 
    lc.setIntensity(0, 8);         //Brightness is adjustable from 0 to 15
    m.init();                      //Start the LED matrix
    m.setIntensity(8);             //Brightness is adjustable from 0 to 15
    start_game();                  //Call the start_game function
    render();                      //Call render function 
}

void loop() {
    if(!game_over) {
        clear_screen();
        render();

        if(current_time - last_time > Delay_Time) {
            game_over = advance();
            last_time = current_time; 
        }
    } 
    else {
        while(blink_count > 0) {
            clear_screen();
            delay(300);
            render();
            delay(300);
            blink_count--; 
        }
    }
    Snake_Control();
    current_time++;
}

void restart() { 
    start_game();
    game_over = false;
}

void Snake_Control () {
    //Read the value on the Analog 1 pin connected to the X axis of the joystick and proportion the value 
    //between 0 and 906 to 2 and -2.
    int VRX_Read = map(analogRead(VRX), 0, 906, -2, 2);
    
    //Read the value on the Analog 2 pin connected to the Y axis of the joystick and convert the value 
    //between 0 and 906 into a ratio of 2 to -2.
    int VRY_Read = map(analogRead(VRY), 0, 906, 2, -2);
  
    if(VRX_Read != 0) {  //If the value read is non-zero 
        //divide the data received by the VRX_Read variable by its own absolute value
        //And save the result to the VRX_Read variable
        VRX_Read = VRX_Read/abs(VRX_Read);
    }  
  
    if(VRX_Read != 0) {  //If the value read is non-zero 
        //divide the data received by the VRY_Read variable by its own absolute value
        //And save the result to the VRY_Read variable
        VRY_Read = VRY_Read/abs(VRY_Read);
    }

    if(VRY_Read != 0 && v[0] != 0) {
        v[0] = 0;
        v[1] = VRY_Read; 
    }

    if(VRX_Read != 0 && v[1] != 0) {
        v[0] = VRX_Read;
        v[1] = 0;
    }
}

void game_over_message() {
    for(int i=0; i<3; i++) {
        tone(speakerPin, 500);
        delay(50);
        noTone(speakerPin);
        delay(50);
    }
    
    m.shiftLeft(false, true);
    printStringWithShift("Score: ", 80);
    char score2[4];
    itoa(score, score2, 10);  //Convert integer number to char, convert score integer number to score2 char
    printStringWithShift(score2, 80);
    printStringWithShift("   ", 80);
    score = 0;
}

//Binary format of letters, numbers and symbols
PROGMEM const unsigned char CH[] = {
    3, 8, B00000000, B00000000, B00000000, B00000000, B00000000,  // space
    1, 8, B01011111, B00000000, B00000000, B00000000, B00000000,  // !
    3, 8, B00000011, B00000000, B00000011, B00000000, B00000000,  // "
    5, 8, B00010100, B00111110, B00010100, B00111110, B00010100,  // #
    4, 8, B00100100, B01101010, B00101011, B00010010, B00000000,  // $
    5, 8, B01100011, B00010011, B00001000, B01100100, B01100011,  // %
    5, 8, B00110110, B01001001, B01010110, B00100000, B01010000,  // &
    1, 8, B00000011, B00000000, B00000000, B00000000, B00000000,  // '
    3, 8, B00011100, B00100010, B01000001, B00000000, B00000000,  // (
    3, 8, B01000001, B00100010, B00011100, B00000000, B00000000,  // )
    5, 8, B00101000, B00011000, B00001110, B00011000, B00101000,  // *
    5, 8, B00001000, B00001000, B00111110, B00001000, B00001000,  // +
    2, 8, B10110000, B01110000, B00000000, B00000000, B00000000,  // ,
    4, 8, B00001000, B00001000, B00001000, B00001000, B00000000,  // -
    2, 8, B01100000, B01100000, B00000000, B00000000, B00000000,  // .
    4, 8, B01100000, B00011000, B00000110, B00000001, B00000000,  // /
    4, 8, B00111110, B01000001, B01000001, B00111110, B00000000,  // 0
    3, 8, B01000010, B01111111, B01000000, B00000000, B00000000,  // 1
    4, 8, B01100010, B01010001, B01001001, B01000110, B00000000,  // 2
    4, 8, B00100010, B01000001, B01001001, B00110110, B00000000,  // 3
    4, 8, B00011000, B00010100, B00010010, B01111111, B00000000,  // 4
    4, 8, B00100111, B01000101, B01000101, B00111001, B00000000,  // 5
    4, 8, B00111110, B01001001, B01001001, B00110000, B00000000,  // 6
    4, 8, B01100001, B00010001, B00001001, B00000111, B00000000,  // 7
    4, 8, B00110110, B01001001, B01001001, B00110110, B00000000,  // 8
    4, 8, B00000110, B01001001, B01001001, B00111110, B00000000,  // 9
    2, 8, B01010000, B00000000, B00000000, B00000000, B00000000,  // :
    2, 8, B10000000, B01010000, B00000000, B00000000, B00000000,  // ;
    3, 8, B00010000, B00101000, B01000100, B00000000, B00000000,  // <
    3, 8, B00010100, B00010100, B00010100, B00000000, B00000000,  // =
    3, 8, B01000100, B00101000, B00010000, B00000000, B00000000,  // >
    4, 8, B00000010, B01011001, B00001001, B00000110, B00000000,  // ?
    5, 8, B00111110, B01001001, B01010101, B01011101, B00001110,  // @
    4, 8, B01111110, B00010001, B00010001, B01111110, B00000000,  // A
    4, 8, B01111111, B01001001, B01001001, B00110110, B00000000,  // B
    4, 8, B00111110, B01000001, B01000001, B00100010, B00000000,  // C
    4, 8, B01111111, B01000001, B01000001, B00111110, B00000000,  // D
    4, 8, B01111111, B01001001, B01001001, B01000001, B00000000,  // E
    4, 8, B01111111, B00001001, B00001001, B00000001, B00000000,  // F
    4, 8, B00111110, B01000001, B01001001, B01111010, B00000000,  // G
    4, 8, B01111111, B00001000, B00001000, B01111111, B00000000,  // H
    3, 8, B01000001, B01111111, B01000001, B00000000, B00000000,  // I
    4, 8, B00110000, B01000000, B01000001, B00111111, B00000000,  // J
    4, 8, B01111111, B00001000, B00010100, B01100011, B00000000,  // K
    4, 8, B01111111, B01000000, B01000000, B01000000, B00000000,  // L
    5, 8, B01111111, B00000010, B00001100, B00000010, B01111111,  // M
    5, 8, B01111111, B00000100, B00001000, B00010000, B01111111,  // N
    4, 8, B00111110, B01000001, B01000001, B00111110, B00000000,  // O
    4, 8, B01111111, B00001001, B00001001, B00000110, B00000000,  // P
    4, 8, B00111110, B01000001, B01000001, B10111110, B00000000,  // Q
    4, 8, B01111111, B00001001, B00001001, B01110110, B00000000,  // R
    4, 8, B01000110, B01001001, B01001001, B00110010, B00000000,  // S
    5, 8, B00000001, B00000001, B01111111, B00000001, B00000001,  // T
    4, 8, B00111111, B01000000, B01000000, B00111111, B00000000,  // U
    5, 8, B00001111, B00110000, B01000000, B00110000, B00001111,  // V
    5, 8, B00111111, B01000000, B00111000, B01000000, B00111111,  // W
    5, 8, B01100011, B00010100, B00001000, B00010100, B01100011,  // X
    5, 8, B00000111, B00001000, B01110000, B00001000, B00000111,  // Y
    4, 8, B01110001, B01001001, B01001001, B01000111, B00000000,  // Z
    2, 8, B01111111, B01000001, B00000000, B00000000, B00000000,  // [
    4, 8, B00000001, B00000110, B00011000, B01100000, B00000000,  // \ backslash
    2, 8, B01000001, B01111111, B00000000, B00000000, B00000000,  // ]
    3, 8, B00000010, B00000001, B00000010, B00000000, B00000000,  // hat
    4, 8, B01000000, B01000000, B01000000, B01000000, B00000000,  // _
    2, 8, B00000001, B00000010, B00000000, B00000000, B00000000,  // `
    4, 8, B00100000, B01010100, B01010100, B01111000, B00000000,  // a
    4, 8, B01111111, B01000100, B01000100, B00111000, B00000000,  // b
    4, 8, B00111000, B01000100, B01000100, B00101000, B00000000,  // c
    4, 8, B00111000, B01000100, B01000100, B01111111, B00000000,  // d
    4, 8, B00111000, B01010100, B01010100, B00011000, B00000000,  // e
    3, 8, B00000100, B01111110, B00000101, B00000000, B00000000,  // f
    4, 8, B10011000, B10100100, B10100100, B01111000, B00000000,  // g
    4, 8, B01111111, B00000100, B00000100, B01111000, B00000000,  // h
    3, 8, B01000100, B01111101, B01000000, B00000000, B00000000,  // i
    4, 8, B01000000, B10000000, B10000100, B01111101, B00000000,  // j
    4, 8, B01111111, B00010000, B00101000, B01000100, B00000000,  // k
    3, 8, B01000001, B01111111, B01000000, B00000000, B00000000,  // l
    5, 8, B01111100, B00000100, B01111100, B00000100, B01111000,  // m
    4, 8, B01111100, B00000100, B00000100, B01111000, B00000000,  // n
    4, 8, B00111000, B01000100, B01000100, B00111000, B00000000,  // o
    4, 8, B11111100, B00100100, B00100100, B00011000, B00000000,  // p
    4, 8, B00011000, B00100100, B00100100, B11111100, B00000000,  // q
    4, 8, B01111100, B00001000, B00000100, B00000100, B00000000,  // r
    4, 8, B01001000, B01010100, B01010100, B00100100, B00000000,  // s
    3, 8, B00000100, B00111111, B01000100, B00000000, B00000000,  // t
    4, 8, B00111100, B01000000, B01000000, B01111100, B00000000,  // u
    5, 8, B00011100, B00100000, B01000000, B00100000, B00011100,  // v
    5, 8, B00111100, B01000000, B00111100, B01000000, B00111100,  // w
    5, 8, B01000100, B00101000, B00010000, B00101000, B01000100,  // x
    4, 8, B10011100, B10100000, B10100000, B01111100, B00000000,  // y
    3, 8, B01100100, B01010100, B01001100, B00000000, B00000000,  // z
    3, 8, B00001000, B00110110, B01000001, B00000000, B00000000,  // {
    1, 8, B01111111, B00000000, B00000000, B00000000, B00000000,  // |
    3, 8, B01000001, B00110110, B00001000, B00000000, B00000000,  // }
    4, 8, B00001000, B00000100, B00001000, B00000100, B00000000,  // ~
};

//Define the function required to print characters
void printCharWithShift(char c, int shift_speed) {
    if(c < 32) return;
    c -= 32;
    memcpy_P(buffer, CH + 7*c, 7);
    m.writeSprite(LED_Matrix_Count * 8, 0, buffer);
    m.setColumn(LED_Matrix_Count * 8 + buffer[0], 0);
   
    for(int i=0; i<buffer[0]+1; i++) {
        delay(shift_speed);
        m.shiftLeft(false, false);
    }
}
  
//Function required to print string
void printStringWithShift(char* s, int shift_speed) {
    while (*s != 0) {
        printCharWithShift(*s, shift_speed);
        s++;
    }
}
