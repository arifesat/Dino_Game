#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUTTON_PIN 4
#define CROUCH_BUTTON_PIN 2
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

// #define SDA_PIN SDA
// #define SCL_PIN SCL

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const unsigned char dino_bitmap [] PROGMEM = {
0x21, 0xFE, 
0x23, 0x1F, 
0x23, 0x1F, 
0x03, 0x1F, 
0x21, 0xF0, 
0x01, 0xFC, 
0x83, 0xE7, 
0x87, 0xE0, 
0xCF, 0xFC, 
0xFF, 0xE0, 
0x7F, 0xE0, 
0x3F, 0xC0, 
0x1F, 0x80, 
0x09, 0x00, 
0x09, 0x00, 
0x00, 0x00
};

const unsigned char dino_right_foot_bitmap [] PROGMEM = {
0x01, 0xFE, 
0x03, 0xFF, 
0x03, 0xBF, 
0x03, 0xFF, 
0x01, 0xF0, 
0x81, 0xFE, 
0x83, 0xE0, 
0xC7, 0xFC, 
0xEF, 0xE8, 
0x7F, 0xE0, 
0x3F, 0xE0, 
0x1F, 0xC0, 
0x1F, 0x80, 
0x0B, 0x00, 
0x09, 0x80, 
0x0C, 0x00
};

const unsigned char dino_left_foot_bitmap [] PROGMEM = {
0x01, 0xFE, 
0x03, 0xFF, 
0x03, 0x7F, 
0x03, 0xFF, 
0x01, 0xF0, 
0x01, 0xFE, 
0x83, 0xE0, 
0x87, 0xFC, 
0xCF, 0xE4, 
0xFF, 0xE0, 
0x7F, 0xE0, 
0x3F, 0xC0, 
0x1F, 0x80, 
0x19, 0x00, 
0x0D, 0x00, 
0x01, 0x80
};

const unsigned char cactus_bitmap [] PROGMEM = {
0x18, 0x18, 
0x18, 0x38, 
0x3C, 0x7C, 
0x7C, 0x7C, 
0x7C, 0x78, 
0x18, 0x18, 
0x18, 0x18, 
0x18, 0x18
};

// Height: 11
const unsigned char dino_crouch_bitmap [] PROGMEM = {
0x00, 0x00, 
0x00, 0x00, 
0x00, 0x00, 
0x00, 0x00, 
0x00, 0x00, 
0x00, 0xFE, 
0x01, 0xFF, 
0x07, 0xFF, 
0x0F, 0xFD, 
0x1F, 0xF5, 
0x1F, 0xF5, 
0x0F, 0xE5, 
0x06, 0x67, 
0x02, 0x20, 
0x02, 0x20, 
0x03, 0x30
};

const unsigned char dino_crouch_right_foot_bitmap [] PROGMEM = {
0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 
0x00, 0xFE, 0xFE, 
0x83, 0xFF, 0xDF, 
0xC7, 0xFF, 0xFF, 
0xFF, 0xFF, 0xFF, 
0x7F, 0xFF, 0xFF, 
0x3F, 0xFF, 0x70, 
0x1F, 0xFE, 0x3E, 
0x03, 0x23, 0x00, 
0x02, 0x31, 0x00, 
0x03, 0x00, 0x00
};

const unsigned char dino_crouch_left_foot_bitmap [] PROGMEM = {
0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 
0x80, 0xFE, 0xFE, 
0xE3, 0xFF, 0xEF, 
0xFF, 0xFF, 0xFF, 
0x7F, 0xFF, 0xFF, 
0x3F, 0xFF, 0xFF, 
0x1F, 0xFF, 0x70, 
0x0F, 0xFE, 0x3E, 
0x02, 0x63, 0x00, 
0x03, 0x20, 0x00, 
0x00, 0x30, 0x00
};

const unsigned char bird_up_bitmap [] PROGMEM = {
// Pterodactyl - Height 9
0x00, 0x40, 
0x00, 0x60, 
0x0C, 0x70, 
0x1E, 0x78, 
0x3F, 0xFE, 
0x03, 0xF8, 
0x01, 0xFE, 
0x00, 0x00, 
0x00, 0x00, 
0x00, 0x00, 
0x00, 0x00, 
0x00, 0x00, 
0x00, 0x00, 
0x00, 0x00, 
0x00, 0x00, 
0x00, 0x00
};

const unsigned char bird_down_bitmap [] PROGMEM = {
  // Pterodactyl - Height 9
0x00, 0x00, 
0x00, 0x00, 
0x0C, 0x00, 
0x1E, 0x00, 
0x3F, 0xFE, 
0x03, 0xF8, 
0x01, 0xFE, 
0x00, 0x60, 
0x00, 0x40, 
0x00, 0x00, 
0x00, 0x00, 
0x00, 0x00, 
0x00, 0x00, 
0x00, 0x00, 
0x00, 0x00, 
0x00, 0x00
};

const int GROUND_Y = 60;
const int GRAVITY = 1;
const int JUMP_STRENGTH = -8;

const int DINO_STAND_HEIGHT = 16;
const int DINO_CROUCH_HEIGHT = 11;
const int BIRD_VISUAL_Y = 40;  // Where the bird sprite is drawn
const int BIRD_COLLISION_Y = 10;  // Top of collision box (catches jumping dino)
const int BIRD_COLLISION_HEIGHT = 39;  // Collision spans Y=10 to Y=49 (above crouching dino at 49)

const int BASE_CACTUS_SPEED = 4;
const int BASE_BIRD_SPEED = 5;
const int SPEED_INCREASE_THRESHOLD = 20;  // Start increasing speed at this score
const int SPEED_INCREASE_INTERVAL = 10;   // Increase speed every N points after threshold

unsigned int score = 0;
unsigned int highScore = 0;

bool isCrouching = false;
bool isBirdObstacle = false;
bool birdWingUp = true;
unsigned long birdAnimTime = 0;
const int birdAnimDelay = 150;  // Wing flap speed in ms

bool dinoRightFoot = true;  // Toggle between left/right foot
unsigned long dinoAnimTime = 0;
const int dinoAnimDelay = 100;  // Foot step speed in ms

typedef struct {
  int x;
  int y;
  int vel_y;
  bool isJumping;
  int width;
  int height;
} Dino;

typedef struct {
  int x;
  int y;
  int width;
  int height;
} Cactus;

typedef struct {
  int x;
  int y;
  int width;
  int height;
} Bird;

Dino tRex;
Cactus obstacle;
Bird bird;

unsigned long prevTime = 0;
const int frameDelay = 30;

void resetGame(){
  tRex.height = DINO_STAND_HEIGHT;
  tRex.y = GROUND_Y - tRex.height;
  tRex.vel_y = 0;
  tRex.isJumping = false;
  isCrouching = false;

  obstacle.x = 128;
  isBirdObstacle = false;
  bird.x = 128;
  score = 0;
}

void spawnObstacle() {
  if (score >= 10 && random(0, 100) < 40) {
    // 40% chance to spawn bird after score 10
    isBirdObstacle = true;
    bird.x = 128 + random(0, 100);
    bird.y = BIRD_COLLISION_Y;
    bird.width = 16;
    bird.height = BIRD_COLLISION_HEIGHT;
  } else {
    // Spawn cactus
    isBirdObstacle = false;
    obstacle.x = 128 + random(0, 100);
  }
}

void setup(){
  Serial.begin(115200);

  Wire.begin();
  Wire.setClock(400000);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)){
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(CROUCH_BUTTON_PIN, INPUT_PULLUP);

  tRex.width = 16;
  tRex.height = 16;
  tRex.x = 10;

  obstacle.width = 8;
  obstacle.height = 16;
  obstacle.y = GROUND_Y - obstacle.height;

  bird.width = 16;
  bird.height = BIRD_COLLISION_HEIGHT;
  bird.y = BIRD_COLLISION_Y;
  bird.x = 128;

  resetGame();
}

void loop(){
  unsigned long currentTime = millis();
  if(currentTime - prevTime >= frameDelay){
    prevTime = currentTime;
    
    display.clearDisplay();
    
    // Handle crouch input
    if(digitalRead(CROUCH_BUTTON_PIN) == LOW && !tRex.isJumping){
      if(!isCrouching){
        isCrouching = true;
        tRex.height = DINO_CROUCH_HEIGHT;
        tRex.y = GROUND_Y - tRex.height;
      }
    } else if(!tRex.isJumping) {
      if(isCrouching){
        isCrouching = false;
        tRex.height = DINO_STAND_HEIGHT;
        tRex.y = GROUND_Y - tRex.height;
      }
    }

    // Handle jump input (only when not crouching)
    if(digitalRead(BUTTON_PIN) == LOW && !tRex.isJumping && !isCrouching){
      tRex.vel_y = JUMP_STRENGTH;
      tRex.isJumping = true;
    }

    tRex.y += tRex.vel_y;

    if(tRex.y < (GROUND_Y - tRex.height)) {
      tRex.vel_y += GRAVITY;
    }else{
      tRex.vel_y = 0;
      tRex.y = GROUND_Y - tRex.height;
      tRex.isJumping = false;
    }

    // Calculate speed bonus based on score
    int speedBonus = 0;
    if(score >= SPEED_INCREASE_THRESHOLD) {
      speedBonus = 1 + (score - SPEED_INCREASE_THRESHOLD) / SPEED_INCREASE_INTERVAL;
    }

    // Move obstacle
    if(isBirdObstacle) {
      bird.x -= (BASE_BIRD_SPEED + speedBonus);
      
      // Animate bird wings
      if(currentTime - birdAnimTime >= birdAnimDelay) {
        birdAnimTime = currentTime;
        birdWingUp = !birdWingUp;
      }
      
      if(bird.x < -20){
        score++;
        spawnObstacle();
      }
    } else {
      obstacle.x -= (BASE_CACTUS_SPEED + speedBonus);
      if(obstacle.x < -10){
        score++;
        spawnObstacle();
      }
    }

    bool collision = false;
    
    if(isBirdObstacle) {
      // Bird collision: check if dino's top is below bird's bottom
      bool collisionX = (tRex.x + tRex.width >= bird.x) && (bird.x + bird.width >= tRex.x);
      bool collisionY = (tRex.y < bird.y + bird.height) && (tRex.y + tRex.height > bird.y);
      collision = collisionX && collisionY;
    } else {
      // Cactus collision
      bool collisionX = (tRex.x + tRex.width >= obstacle.x) && (obstacle.x + obstacle.width >= tRex.x);
      bool collisionY = (tRex.y + tRex.height >= obstacle.y);
      collision = collisionX && collisionY;
    }

    if(collision){
      if(score > highScore) {
        highScore = score;
      }

      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(35, 20);
      display.println(F("GAME OVER"));

      display.setCursor(35, 30);
      display.print(F("Score: "));
      display.print(score);

      display.setCursor(35, 42);
      display.print(F("Best: "));
      display.print(highScore);

      display.display();

      delay(250);

      while(digitalRead(BUTTON_PIN) == HIGH){
        delay(10);
      }

      if(digitalRead(BUTTON_PIN) == LOW){  
        delay(500);
        resetGame();
      }
    }

    display.drawLine(0, GROUND_Y, 128, GROUND_Y, SSD1306_WHITE);

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(70, 0);
    display.print(F("Score: "));
    display.print(score);

    // Animate dino feet (only when on ground)
    if(!tRex.isJumping && currentTime - dinoAnimTime >= dinoAnimDelay) {
      dinoAnimTime = currentTime;
      dinoRightFoot = !dinoRightFoot;
    }

    // Calculate draw Y position (offset by empty rows in bitmap)
    // Bitmap is 16px tall, but content height varies. Empty rows are at top.
    int drawY = tRex.y - (16 - tRex.height);

    // Draw dino (standing or crouching, with foot animation)
    if(tRex.isJumping) {
      // Static pose when jumping (standing bitmap has 2 empty rows at top)
      display.drawBitmap(tRex.x, tRex.y - 2, dino_bitmap, tRex.width, 16, SSD1306_WHITE);
    } else if(isCrouching) {
      if(dinoRightFoot) {
        display.drawBitmap(tRex.x, drawY, dino_crouch_right_foot_bitmap, 24, 16, SSD1306_WHITE);
      } else {
        display.drawBitmap(tRex.x, drawY, dino_crouch_left_foot_bitmap, 24, 16, SSD1306_WHITE);
      }
    } else {
      if(dinoRightFoot) {
        display.drawBitmap(tRex.x, drawY, dino_right_foot_bitmap, tRex.width, 16, SSD1306_WHITE);
      } else {
        display.drawBitmap(tRex.x, drawY, dino_left_foot_bitmap, tRex.width, 16, SSD1306_WHITE);
      }
    }
    
    // Draw obstacle (bird or cactus)
    if(isBirdObstacle) {
      if(birdWingUp) {
        display.drawBitmap(bird.x, BIRD_VISUAL_Y, bird_up_bitmap, bird.width, 16, SSD1306_WHITE);
      } else {
        display.drawBitmap(bird.x, BIRD_VISUAL_Y, bird_down_bitmap, bird.width, 16, SSD1306_WHITE);
      }
    } else {
      display.drawBitmap(obstacle.x, obstacle.y, cactus_bitmap, obstacle.width, obstacle.height, SSD1306_WHITE);
    }

    display.display();
  }
}