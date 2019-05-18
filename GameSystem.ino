#include <FastLED.h>
#include "Avalanche.h"
#include "Breakout.h"
#include "Drive.h"

#define DATA_PIN 10
#define L_PIN 7
#define R_PIN 6
#define NUM_LEDS 64
#define BRIGHTNESS 5
#define SLIDE_STEP 5

const CRGB color_array[8] = {
  CRGB::Red,
  CRGB::Orange,
  CRGB::Yellow,
  CRGB::Chartreuse,
  CRGB::Green,
  CRGB::CornflowerBlue,
  CRGB::Blue,
  CRGB::Purple,
};

enum {RAINBOW, AVALANCHE, BREAKOUT, DRIVE} game = BREAKOUT;
enum {START, WON, LOST, PLAY, SETUP} state = SETUP;
enum {LEFT, RIGHT, NONE} controls = NONE;

int count = 0;
int stepCount = 0;

CRGB screen[NUM_LEDS];
Avalanche avalanche;
Breakout breakout;
Drive drive;

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  pinMode(L_PIN, INPUT_PULLUP);
  pinMode(R_PIN, INPUT_PULLUP);
  
  FastLED.addLeds<NEOPIXEL,DATA_PIN>(screen, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  if (!digitalRead(L_PIN) && !digitalRead(R_PIN)) {
    game = RAINBOW;
  } else if (!digitalRead(L_PIN)) {
    game = AVALANCHE;
  } else if (!digitalRead(R_PIN)) {
    game = DRIVE;
  }

  endScreen(color_array[random(0, 9)]);
  FastLED.clear();
  delay(600);
}

void loop() {
  switch (game) {
    case AVALANCHE:
      loopAvalanche();
      break;
    case BREAKOUT:
      loopBreakout();
      break;
    case DRIVE:
      loopDrive();
      break;
    case RAINBOW:
    default:
      loopRainbow();
      break;
  }

  FastLED.show();
}

void loopAvalanche() {
  switch(state){
    case SETUP:
      avalanche.restart();
      state = START;
      break;
      
    case START:
      checkControls();
      if (controls != NONE) {
        state = PLAY;
      }
      break;
      
    case LOST:
      avalanche.restart();
      endScreen(CRGB::Red);
      state = START;
      break;

    case WON:
      avalanche.restart();
      endScreen(CRGB::Green);
      state = START;
      break;
      
    case PLAY:
      if (stepCount >= SLIDE_STEP) {
        checkControls();
        avalanche.movePlayer(controls);
        
        stepCount = 0;
      }
      
      if (count >= avalanche.speed) {
        avalanche.play();
        count = 0;
        
        if (avalanche.speed <= 4) {   // Harder?
          state = WON;
        }
               
        if (avalanche.score == 0) {
          state = LOST;
        }
      }
        
      delay(10);
      
      count++;
      stepCount++;
  }
  
  delay(10);
  
  avalancheDraw();
}

void avalancheDraw() {
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      switch (avalanche.level[y][x]) {
        case 'E':
          screen[y * 8 + x] = CRGB::Black;
          break;
        case 'P':
          screen[y * 8 + x] = CRGB::Orange;
          break;
        case 'B':
          screen[y * 8 + x] = CRGB::CornflowerBlue;
          break;
      }
    }
  }
}

void loopBreakout() {
  switch(state){
    case SETUP:
      breakout.restart();
      state = START;
      break;
      
    case START:
      checkControls();
      if (controls != NONE) {
        state = PLAY;
      }
      break;
      
    case LOST:
      breakout.skill = 1;
      breakout.restart();
      endScreen(CRGB::Red);
      state = START;
      break;

    case WON:
      breakout.skill += 1;
      breakout.restart();
      endScreen(CRGB::Green);
      state = START;
      break;
      
    case PLAY:
      if (stepCount >= SLIDE_STEP) {
        checkControls();
        breakout.movePaddle(controls);
        
        stepCount = 0;
      }
      
      if (count >= breakout.speed) {
        breakout.play();
        count = 0;
        
        if (breakout.bricks == 0) {
          state = WON;
        }
        
        if (breakout.bY > 7) {
          state = LOST;
        }
      }
        
      delay(10);
      
      count++;
      stepCount++;
  }
  
  delay(10);
  
  breakoutDraw();
}

void breakoutDraw() {
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      switch (breakout.level[y][x]) {
        case 'E':
          screen[y * 8 + x] = CRGB::Black;
          break;
        case 'P':
          screen[y * 8 + x] = CRGB::CornflowerBlue;
          break;
        case 'B':
          screen[y * 8 + x] = CRGB::Purple;
          break;
        case 'O':
          screen[y * 8 + x] = CRGB::Yellow;
          break;
      }
    }
  }
}



void loopDrive() {
  switch(state){
    case SETUP:
      drive.restart();
      state = START;
      break;
      
    case START:
      checkControls();
      if (controls != NONE) {
        state = PLAY;
      }
      break;
      
    case LOST:
      drive.restart();
      endScreen(CRGB::Red);
      state = START;
      break;

    case WON:
      drive.restart();
      endScreen(CRGB::Green);
      state = START;
      break;
      
    case PLAY:
      if (stepCount >= SLIDE_STEP) {
        checkControls();
        drive.movePlayer(controls);
        
        stepCount = 0;
      }
      
      if (count >= drive.speed) {
        drive.play();
        count = 0;
        
        if (drive.speed <= 4) {   // Harder?
          state = WON;
        }
               
        if (drive.score == 0) {
          state = LOST;
        }
      }
        
      delay(10);
      
      count++;
      stepCount++;
  }
  
  delay(10);
  
  driveDraw();
}

void driveDraw() {
  for (int y = 0; y < 8; y++) {
    for (int x = 0; x < 8; x++) {
      switch (drive.level[y][x]) {
        case 'E':
          screen[y * 8 + x] = CRGB::Black;
          break;
        case 'L':
          screen[y * 8 + x] = CRGB::Yellow;
          break;
        case 'P':
          screen[y * 8 + x] = CRGB::Blue;
          break;
      }
    }
  }
}

int hue = 0;
void loopRainbow() {
  checkControls();
  
  if (controls == LEFT) {
    hue++;
  } else if (controls == RIGHT) {
    hue--;
  }

  if (hue >= 8) {
    hue = 0;
  } else if (hue < 0) {
    hue = 7;
  }

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      screen[j * 8 + i] = color_array[(hue + i) % 8];
    }
  }

  FastLED.show();

  delay(75);  
}

void checkControls() {
  int count = 0;
  int threshold = 5;
  
  while(count < threshold && !digitalRead(L_PIN) && digitalRead(R_PIN)){
    count++;
  }
  
  if(count >= threshold * 0.9){
    controls = LEFT;
    return;
  }
  
  count = 0;
  
  while(count < threshold && !digitalRead(R_PIN) && digitalRead(L_PIN)){
    count++;
  }
  
  if(count >= threshold * 0.9){
    controls = RIGHT;
    return;
  }
  
  controls = NONE;
}

void endScreen(CRGB color) {
  for (int l = 0; l < 4; l++) {
    for (int y = 0; y < 8; y++) {
      for (int x = 0; x < 8; x++) {
        if (y == l || x == l || y + l == 7 || x + l == 7) {
          screen[y * 8 + x] = color;
        }
      }
    }

    FastLED.show();
    delay(100);
  }

  delay(600);
}
