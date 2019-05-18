class Avalanche {  
  void moveEnemies();
  void checkCollision();
  void resetLevel();

  public:
  int pX;
  char level[8][8];
  int enemies[8][2];
  int speed;
  int score;
  enum {LEFT, RIGHT, NONE} controls = NONE;
  
  void restart();
  void play();
  void movePlayer(int controls);
};
