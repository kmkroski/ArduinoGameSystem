#include "Breakout.h"

void Breakout::restart() {
  bX = 3;
  bY = 6;
  bDX = 0;
  bDY = -1;

  pX = 2;

  speed = 10 - skill;
  bricks = 22;

  resetLevel();
  updatePaddle();
  
  level[bY][bX] = 'O';
}

void Breakout::resetLevel() {
  int bricksSetup = 0;
  
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (bricksSetup < bricks && !(i == 0 && j == 0) && !(i == 0 && j == 7)) {
        level[i][j] = 'B';
        bricksSetup++;
      } else {
        level[i][j] = 'E';
      }
    }  
  }
}

void Breakout::updatePaddle(){
  for (int i = 0; i < 8; i++) {
    level[7][i] = 'E';
  }
  
  for (int i = 0; i < 3; i++) {
    level[7][pX + i] = 'P';  
  }
}

void Breakout::play(){
  moveBall();
  checkCollision();
  
  level[bY][bX] = 'O';
}

void Breakout::movePaddle(int controls) {
  switch (controls) {
    case LEFT:
      pX -= 1;
      if (pX < 0) {
        pX = 0;
      }
      break;
    case RIGHT:
      pX += 1;
      if (pX > 5) {
        pX = 5;
      }
      break;
  }
  
  updatePaddle();
}

void Breakout::checkCollision() {
  if (level[bY][bX] == 'B') {     // if a brick is hit
    bricks--;
    bDY = -1 * bDY;
    // bDX = 0;
  } else if (bY >= 6) {
    if (level[bY][bX] == 'P') {   // if ball is in paddle, move above
      bY--;
    }
    
    if (level[bY + 1][bX] == 'P') {   // if the paddle is hit
      hitPaddle();
    }
  }

  checkSides();
}

void Breakout::hitPaddle() {
  bDY = -1;
  
  if (bX == pX + 1) {   // hit on middle
    bDX = 0;
  } else {
    if (bX == pX) {
      bDX = -1;
    } else if (bX == pX + 2) {
      bDX = 1;
    }
  }
}

void Breakout::checkSides() {
  if (bX == 0 || bX == 7) {
    bDX = -1 * bDX;
  }

  if (bY == 0) {
    bDY = 1;
  }
}


void Breakout::moveBall(){
  level[bY][bX] = 'E';

  bX = bX + bDX;
  bY = bY + bDY;
}
