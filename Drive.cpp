#include <Arduino.h>
#import "Drive.h"

void Drive::restart() {
  pX = 3;
  score = 1;
  speed = 30 - score;

  resetLevel();
  movePlayer(NONE);
  drawLines();
}

void Drive::resetLevel() {
  lines[7] = pX;
  
  for (int i = 6; i >= 0; i--) {
    int lineBelow = lines[i + 1];
    int newLine = random(lineBelow - 1, lineBelow + 2);
    lines[i] = constrain(newLine, 1, 6);
  }
}

void Drive::play() {
  moveLines();
}

void Drive::movePlayer(int controls) {
  level[7][pX] = 'E';
  
  switch (controls) {
    case LEFT:
      pX--;
      if (pX < 0) {
        pX = 0;
      }
      break;
    case RIGHT:
      pX++;
      if (pX > 7) {
        pX = 7;
      }
      break;
  }

  level[7][pX] = 'P';

  checkCollision();
}

void Drive::checkCollision() {
  if (pX < lines[7] - 1 || pX > lines[7] + 1) {
    score = 0;
  }
}

void Drive::moveLines() {
  for (int i = 7; i >= 1; i--) {
    lines[i] = lines[i - 1];
  }

  int newLine = random(lines[1] - 1, lines[1] + 2);
  lines[0] = constrain(newLine, 1, 6);
  score++;

  speed = 30 - floor(score / 10);

  drawLines();
  checkCollision();
}

void Drive::drawLines() {
  for (int i = 0; i < 8; i++) {  
    for (int j = 0; j < 8; j++) {
      if (j == lines[i] || j == lines[i] + 1 || j == lines[i] - 1) {
        level[i][j] = 'E';
      } else {
        level[i][j] = 'L';
      }
    }
  }

  level[7][pX] = 'P';
}

