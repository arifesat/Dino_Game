#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define BUTTON_PIN 4
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

#define SDA_PIN 21
#define SCL_PIN 22

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const unsigned char dino_bitmap [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x07, 0xFE, 0x07, 0xFF, 
  0x07, 0x07, 0x07, 0x3F, 0x06, 0x20, 0x07, 0xF0, 
  0x1F, 0xF8, 0x1F, 0xFC, 0x1F, 0xF0, 0x1F, 0xE0, 
  0x0E, 0x40, 0x02, 0x20, 0x02, 0x20, 0x03, 0x30
};

const unsigned char cactus_bitmap [] PROGMEM = {
  0x18, 0x18, 0x18, 0x58, 0x58, 0xD8, 0xD8, 0xD8, 
  0xD8, 0xD8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18
};

// Width: 24, Height: 14
const unsigned char dino_crouch_bitmap [] PROGMEM = {
0x00, 0x00, // Satır 0 (Boş)
0x00, 0x00, // Satır 1
0x00, 0x00, // Satır 2
0x00, 0x00, // Satır 3
0x00, 0x00, // Satır 4
0x00, 0x00, // Satır 5
0x00, 0x00, // Satır 6
0x00, 0x00, // Satır 7 (Üstteki 8 satır tamamen boş, hitbox küçüldü)
0x00, 0xF8, // Satır 8: Kafa
0x00, 0xFC, // Satır 9: Kafa
0x00, 0xCC, // Satır 10: Boyun
0x3F, 0xFE, // Satır 11: Uzun gövde
0x3F, 0xFC, // Satır 12: Gövde altı
0x0F, 0x30, // Satır 13: Bacaklar
0x0C, 0x30, // Satır 14: Ayaklar
0x0C, 0x30  // Satır 15: Ayaklar (Yerde)
};

const unsigned char bird_up_bitmap [] PROGMEM = {
// Pterodactyl - Kare 1 (Kanat Yukarı)
0x00, 0x00, // Boş
0x00, 0x00, // Boş
0x20, 0x00, // Kanat ucu
0x30, 0x00, // Kanat
0x38, 0x00, // Kanat
0x3C, 0x0C, // Kanat + Kafa arkası
0x27, 0xFE, // Gövde + Gaga (Çarpışma bölgesi burası)
0x20, 0x04, // Gövde altı
0x00, 0x00, // Boş
0x00, 0x00, // Boş... (Alt satırlar boş)
0x00, 0x00,
0x00, 0x00,
0x00, 0x00,
0x00, 0x00,
0x00, 0x00,
0x00, 0x00
};

const unsigned char bird_down_bitmap [] PROGMEM = {
  // Pterodactyl - Kare 2 (Kanat Aşağı)
0x00, 0x00, // Boş
0x00, 0x00, // Boş
0x00, 0x0C, // Kafa arkası
0x07, 0xFE, // Gövde + Gaga (Çarpışma bölgesi burası)
0x3E, 0x04, // Kanat başlangıcı
0x1C, 0x00, // Kanat ortası
0x08, 0x00, // Kanat ucu
0x00, 0x00, // Boş
0x00, 0x00,
0x00, 0x00,
0x00, 0x00,
0x00, 0x00,
0x00, 0x00,
0x00, 0x00,
0x00, 0x00,
0x00, 0x00
};

const int GROUND_Y = 50;
const int GRAVITY = 1;
const int JUMP_STRENGTH = -8;

unsigned int score = 0;
// unsigned int highScore = 0;

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

Dino tRex;
Cactus obstacle;

unsigned long prevTime = 0;
const int frameDelay = 30;

void resetGame(){
  tRex.y = GROUND_Y - tRex.height;
  tRex.vel_y = 0;
  tRex.isJumping = false;

  obstacle.x = 128;
  score = 0;
}

void setup(){
  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(400000);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c)){
    Serial.println("SSD1306 allocation failed");
    for(;;);
  }

  pinMode(BUTTON_PIN, INPUT_PULLUP);

  tRex.width = 16;
  tRex.height = 16;
  tRex.x = 10;

  obstacle.width = 8;
  obstacle.height = 16;
  obstacle.y = GROUND_Y - obstacle.height;

  resetGame();
}

void loop(){
  unsigned long currentTime = millis();
  if(currentTime - prevTime >= frameDelay){
    prevTime = currentTime;
    
    display.clearDisplay();
    
    if(digitalRead(BUTTON_PIN) == LOW && tRex.isJumping == false){
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

    obstacle.x -= 4;
    if(obstacle.x < -10){
      obstacle.x = 128 + random(0, 100);

      score++;
    }

    bool collisionX = (tRex.x + tRex.width >= obstacle.x) && (obstacle.x + obstacle.width >= tRex.x);

    bool collisionY = (tRex.y + tRex.height >= obstacle.y);

    if(collisionX && collisionY){
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(35, 20);
      display.println(F("GAME OVER"));

      display.setCursor(35, 35);
      display.print(F("Score: "));
      display.print(score);

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

    // if((tRex.x + tRex.width) > obstacle.x && (tRex.x) < (obstacle.x + obstacle.width) && (tRex.height + tRex.y) >= obstacle.height){
    //   while(1){
    //     Serial.println("GAME OVER");
    //     display.display();
    //     yield();
    //   }
    // }

    display.drawLine(0, GROUND_Y, 128, GROUND_Y, SSD1306_WHITE);

    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(70, 0);
    display.print(F("Score: "));
    display.print(score);

    display.drawBitmap(tRex.x, tRex.y, dino_bitmap, tRex.width, tRex.height, SSD1306_WHITE);
    display.drawBitmap(obstacle.x, obstacle.y, cactus_bitmap, obstacle.width, obstacle.height, SSD1306_WHITE);

    display.display();
  }
}