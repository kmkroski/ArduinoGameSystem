#include <Arduino.h>
#include "Avalanche.h"

void Avalanche::restart() {
  pX = 3;
  speed = 24;
  score = 1;

  resetLevel();

  for (int i = 0; i < 8; i++) {
    enemies[i][0] = random(0, 8);
    enemies[i][1] = random(-8, 0);
  }

  enemies[0][1] = 0;
  enemies[1][1] = 0;
  enemies[2][1] = 1;
  enemies[3][1] = 1;

  movePlayer(NONE);
  moveEnemies();
}

void Avalanche::resetLevel() {  
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      level[i][j] = 'E';
    }  
  }
}

void Avalanche::play() {
  moveEnemies();
  checkCollision();

  speed = 24 - floor(score / 8);
}

void Avalanche::moveEnemies() {
  for (int i = 0; i < 8; i++) {
    enemies[i][1]++;

    if (enemies[i][1] >= 0 && enemies[i][1] < 8) {
      level[ enemies[i][1] ][ enemies[i][0] ] = 'B';
    }

    if (enemies[i][1] > 0) {
      level[ enemies[i][1] - 1 ][ enemies[i][0] ] = 'E';
    }

    if (enemies[i][1] > 7) {
      enemies[i][0] = random(0, 8);
      enemies[i][1] = random(-4, 0);

      score++;
    }
  }
}

void Avalanche::movePlayer(int controls) {
  level[7][pX] = 'E';
  
  switch (controls) {
    case LEFT:
      pX -= 1;
      if (pX < 0) {
        pX = 0;
      }
      break;
    case RIGHT:
      pX += 1;
      if (pX > 7) {
        pX = 7;
      }
      break;
  }

  level[7][pX] = 'P';

  checkCollision();
}

void Avalanche::checkCollision() {
  for (int i = 0; i < 8; i++) {
    if (enemies[i][0] == pX && enemies[i][1] == 7) {
      score = 0;
      return;
    }
  }
}

