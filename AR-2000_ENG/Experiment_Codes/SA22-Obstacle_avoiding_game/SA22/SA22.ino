//SA22 - Obstacle avoiding game

//Add I2C LCD library
#include <LiquidCrystal_I2C.h>

volatile int difficultyLevel;
volatile int difficultyLevelCounter;

int PIN_SELECTION_BUTTON = 2;
int PIN_BUTTON = 3;
#define SPEAKER_PIN 4
#define PIN_AUTOPLAY 1
#define PIN_READWRITE 10
#define PIN_CONTRAST 12
#define FAST_RUN1 1
#define FAST_RUN2 2
#define FAST_JUMP 3
#define FAST_JUMP_UPPER '.'
#define FAST_JUMP_LOWER 4
#define SPRITE_TERRAIN_EMPTY ' '
#define SPRITE_TERRAIN_SOLID 5
#define SPRITE_TERRAIN_SOLID_RIGHT 6
#define SPRITE_TERRAIN_SOLID_LEFT 7
#define HERO_HORIZONTAL_POSITION 1
#define TERRAIN_WIDTH 16
#define TERRAIN_EMPTY 0
#define TERRAIN_LOWER_BLOCK 1
#define TERRAIN_UPPER_BLOCK 2
#define HERO_POSITION_OFF 0
#define HERO_LOWER_RUN_POSITION_1 1
#define HERO_LOWER_RUN_POSITION_2 2
#define HERO_JUMP_POSITION_1 3
#define HERO_JUMP_POSITION_2 4
#define HERO_JUMP_POSITION_3 5
#define HERO_JUMP_POSITION_4 6
#define HERO_JUMP_POSITION_5 7
#define HERO_JUMP_POSITION_6 8
#define HERO_JUMP_POSITION_7 9
#define HERO_JUMP_POSITION_8 10
#define HERO_UPPER_RUN_POSITION_1 11
#define HERO_UPPER_RUN_POSITION_2 12

unsigned int Score;

//Define 1602 LCD display
LiquidCrystal_I2C lcd(0x27, 16, 2);
static char terrainUpper[TERRAIN_WIDTH + 1];
static char terrainLower[TERRAIN_WIDTH + 1];
static bool buttonPushed = false;

//Define graphics
void defineGraphics() {
    static byte graphics[] = {
        //Running position 1
        0x0C, 0x0C, 0x00, 0x0E, 0x1C, 0x0C, 0x1A, 0x13,
        //Running position 2
        0x0C, 0x0C, 0x00, 0x0C, 0x0C, 0x0C, 0x0C, 0x0E,
        //Jumping
        0x0C, 0x0C, 0x00, 0x1E, 0x0D, 0x1F, 0x10, 0x00,
        //Jumping from Lower
        0x1E, 0x0D, 0x1F, 0x10, 0x00, 0x00, 0x00, 0x00,
        //Base
        0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F,
        //Base right
        0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
        //Base left
        0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18,
    };

    int i;
    for(i = 0; i < 7; ++i) {
        lcd.createChar(i + 1, &graphics[i * 8]);
    }
    for(i = 0; i < TERRAIN_WIDTH; ++i) {
        terrainUpper[i] = SPRITE_TERRAIN_EMPTY;
        terrainLower[i] = SPRITE_TERRAIN_EMPTY;
    }
}

void advanceTerrain(char* terrain, byte newTerrain) {
    for(int i = 0; i < TERRAIN_WIDTH; ++i) {
        char current = terrain[i];
        char next = (i == TERRAIN_WIDTH-1) ? newTerrain : terrain[i+1];
        switch(current) {
            case SPRITE_TERRAIN_EMPTY:
                terrain[i] = (next == SPRITE_TERRAIN_SOLID) ? SPRITE_TERRAIN_SOLID_RIGHT : SPRITE_TERRAIN_EMPTY;
                break;
            case SPRITE_TERRAIN_SOLID:
                terrain[i] = (next == SPRITE_TERRAIN_EMPTY) ? SPRITE_TERRAIN_SOLID_LEFT : SPRITE_TERRAIN_SOLID;
                break;
            case SPRITE_TERRAIN_SOLID_RIGHT:
                terrain[i] = SPRITE_TERRAIN_SOLID;
                break;
            case SPRITE_TERRAIN_SOLID_LEFT:
                terrain[i] = SPRITE_TERRAIN_EMPTY;
                break;
        }
    }
}

//Define the playNote function
void playNote(int wait, int Tone) { 
    tone(SPEAKER_PIN, Tone);
    delay(wait);
    noTone(SPEAKER_PIN);
}

//Define heroDraw function
bool heroDraw(byte position, char* terrainUpper, char* terrainLower, unsigned int score) {
    bool collide = false;
    char upperSave = terrainUpper[HERO_HORIZONTAL_POSITION];
    char lowerSave = terrainLower[HERO_HORIZONTAL_POSITION];
    byte upper, lower;
    switch(position) {
        case HERO_POSITION_OFF:
            upper = lower = SPRITE_TERRAIN_EMPTY;
            break;
        case HERO_LOWER_RUN_POSITION_1:
            upper = SPRITE_TERRAIN_EMPTY;
            lower = FAST_RUN1;
            break;
        case HERO_LOWER_RUN_POSITION_2:
            upper = SPRITE_TERRAIN_EMPTY;
            lower = FAST_RUN2;
            break;
        case HERO_JUMP_POSITION_1:
        case HERO_JUMP_POSITION_8:
            upper = SPRITE_TERRAIN_EMPTY;
            lower = FAST_JUMP;
            break;
        case HERO_JUMP_POSITION_2:
        case HERO_JUMP_POSITION_7:
            upper = FAST_JUMP_UPPER;
            lower = FAST_JUMP_LOWER;
            break;
        case HERO_JUMP_POSITION_3:
        case HERO_JUMP_POSITION_4:
        case HERO_JUMP_POSITION_5:
        case HERO_JUMP_POSITION_6:
            upper = FAST_JUMP;
            lower = SPRITE_TERRAIN_EMPTY;
            break;
        case HERO_UPPER_RUN_POSITION_1:
            upper = FAST_RUN1;
            lower = SPRITE_TERRAIN_EMPTY;
            break;
        case HERO_UPPER_RUN_POSITION_2:
            upper = FAST_RUN2;
            lower = SPRITE_TERRAIN_EMPTY;
            break;
    }
    if(upper != ' ') {
        terrainUpper[HERO_HORIZONTAL_POSITION] = upper;
        collide = (upperSave == SPRITE_TERRAIN_EMPTY) ? false : true;
    }
    if(lower != ' ') {
        terrainLower[HERO_HORIZONTAL_POSITION] = lower;
        collide |= (lowerSave == SPRITE_TERRAIN_EMPTY) ? false : true;
    }

    byte digits = (score > 9999) ? 5 : (score > 999) ? 4 : (score > 99) ? 3 : (score > 9) ? 2 : 1;

    terrainUpper[TERRAIN_WIDTH] = '\0';
    terrainLower[TERRAIN_WIDTH] = '\0';
    char temp = terrainUpper[16 - digits];
    terrainUpper[16-digits] = '\0';
    lcd.setCursor(0, 0);
    lcd.print(terrainUpper);
    terrainUpper[16-digits] = temp;
    lcd.setCursor(0, 1);
    lcd.print(terrainLower);

    lcd.setCursor(16 - digits, 0);
    lcd.print(score);
    Score = score;
    terrainUpper[HERO_HORIZONTAL_POSITION] = upperSave;
    terrainLower[HERO_HORIZONTAL_POSITION] = lowerSave;
    return collide;
}

//Function to call on button press interrupt
void buttonPressed() {
    buttonPushed = true;
}

void createObstacle(int waitTime) {
    static byte heroPos = HERO_LOWER_RUN_POSITION_1;
    static byte newTerrainType = TERRAIN_EMPTY;
    static byte newTerrainDuration = 1;
    static bool playing = false;
    static bool blink = false;
    static unsigned int distance = 0;
    
    if(!playing) {
        heroDraw((blink) ? HERO_POSITION_OFF : heroPos, terrainUpper, terrainLower, distance >> 3);
        if(blink) {
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("You Lost!");
            lcd.setCursor(0, 1);
            lcd.print("Score: ");
            lcd.print(Score);
            delay(2000);

            while(digitalRead(2)) {
                lcd.setCursor(0, 0);
                lcd.print("To Replay the Game");
                lcd.setCursor(0, 1);
                lcd.print("Press PB1 Button");
            }
        }
        delay(250);
        blink = !blink;
        if(buttonPushed) {
            playNote(100, 400);
            playNote(100, 600);
            playNote(100, 400);
            defineGraphics();
            heroPos = HERO_LOWER_RUN_POSITION_1;
            playing = true;
            buttonPushed = false;
            distance = 0;
        }
        return;
    }

    //Slide obstacles to the left
    advanceTerrain(terrainLower, newTerrainType == TERRAIN_LOWER_BLOCK ? SPRITE_TERRAIN_SOLID : SPRITE_TERRAIN_EMPTY);
    advanceTerrain(terrainUpper, newTerrainType == TERRAIN_UPPER_BLOCK ? SPRITE_TERRAIN_SOLID : SPRITE_TERRAIN_EMPTY);

    //Define a new obstacle and insert into the screen from the right
    if(--newTerrainDuration == 0) {
        if(newTerrainType == TERRAIN_EMPTY) {
            newTerrainType = (random(3) == 0) ? TERRAIN_UPPER_BLOCK : TERRAIN_LOWER_BLOCK;
            newTerrainDuration = 2 + random(10);
        } else {
            newTerrainType = TERRAIN_EMPTY;
            newTerrainDuration = 10 + random(10);
        }
    }

    if(buttonPushed) {
        if(heroPos <= HERO_LOWER_RUN_POSITION_2)
            playNote(100, 300);
        heroPos = HERO_JUMP_POSITION_1;
        buttonPushed = false;
    }

    if(heroDraw(heroPos, terrainUpper, terrainLower, distance >> 3)) {
        playing = false; // The hero collided with something. Too bad.
        playNote(100, 500);
        playNote(100, 400);
        playNote(120, 300);
        playNote(160, 400);
        lcd.clear();
    } else {
        if(heroPos == HERO_LOWER_RUN_POSITION_2 || heroPos == HERO_JUMP_POSITION_8) {
            heroPos = HERO_LOWER_RUN_POSITION_1;
        } else if((heroPos >= HERO_JUMP_POSITION_3 && heroPos <= HERO_JUMP_POSITION_5) && terrainLower[HERO_HORIZONTAL_POSITION] != SPRITE_TERRAIN_EMPTY) {
            heroPos = HERO_UPPER_RUN_POSITION_1;
        } else if(heroPos >= HERO_UPPER_RUN_POSITION_1 && terrainLower[HERO_HORIZONTAL_POSITION] == SPRITE_TERRAIN_EMPTY) {
            heroPos = HERO_JUMP_POSITION_5;
        } else if(heroPos == HERO_UPPER_RUN_POSITION_2) {
            heroPos = HERO_UPPER_RUN_POSITION_1;
        } else {
            ++heroPos;
        }
        ++distance;

        digitalWrite(PIN_AUTOPLAY, terrainLower[HERO_HORIZONTAL_POSITION + 2] == SPRITE_TERRAIN_EMPTY ? HIGH : LOW);
    }
    delay(waitTime);
}

void setup() {
    //Set difficulty select button as input
    pinMode(PIN_SELECTION_BUTTON, INPUT_PULLUP);
    //Set jump button as input
    pinMode(PIN_BUTTON, INPUT_PULLUP);
    //Set the pin to which the Speaker is connected as output
    pinMode(SPEAKER_PIN, OUTPUT);
    difficultyLevelCounter = 1;

    //Define interrupt for PIN_BUTTON leg
    //For pin number 2, interrupt 0 is written, if pin number 3 is used, interrupt 1 is written.
    attachInterrupt(0/*PIN_BUTTON*/, buttonPressed, FALLING);

    defineGraphics();

    lcd.begin();
    lcd.setCursor(6, 0);
    lcd.print("Escape");
    lcd.setCursor(3, 3);
    lcd.print("And Jump!");
    //Play game starting notes
    playNote(100, 400);
    playNote(100, 300);
    playNote(100, 200);
    playNote(100, 300);
    playNote(100, 400);
    playNote(100, 600);
    delay(1000); //Wait for 1 second
    lcd.clear(); //Clear the LCD display
    //Call the menu() function until the jump key is pressed
    do {
        menu();
    } while(digitalRead(PIN_BUTTON) == HIGH);
}

void loop() {
    switch(difficultyLevel) {
        case 1:
            createObstacle(70);
            break;
        case 2:
            createObstacle(50);
            break;
        case 3:
            createObstacle(15);
            break;
    }
}

void menu() {
    if(difficultyLevelCounter > 3 || difficultyLevelCounter < 0) {
        difficultyLevelCounter = 0;
    }

    if(digitalRead(PIN_SELECTION_BUTTON) == LOW) {
        difficultyLevelCounter++;
    }
    switch(difficultyLevelCounter) {
        case 1:
            lcd.setCursor(0, 0);
            lcd.print("Select Difficulty:");
            lcd.print(":");
            lcd.setCursor(0, 1);
            lcd.print("<    Easy     >");
            delay(250);

            if(digitalRead(PIN_BUTTON) == LOW) {
                difficultyLevel = 1;
            }
            break;
        case 2:
            lcd.setCursor(0, 0);
            lcd.print("Select Difficulty:");
            lcd.print(":");
            lcd.setCursor(0, 1);
            lcd.print("<    Medium    >");
            delay(250);
            if(digitalRead(PIN_BUTTON) == LOW) {
                difficultyLevel = 2;
            }
            break;
        case 3:
            lcd.setCursor(0, 0);
            lcd.print("Select Difficulty:");
            lcd.print(":");
            lcd.setCursor(0, 1);
            lcd.print("<    Difficult    >");
            delay(250);
            if(digitalRead(PIN_BUTTON) == LOW) {
                difficultyLevel = 3;
            }
            break;
        default:
            difficultyLevelCounter = 0;
            break;
    }
}
