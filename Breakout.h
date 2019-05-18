class Breakout {  
  void moveBall();
  void checkCollision();
  void resetLevel();
  void checkSides();
  void hitPaddle();

  public:
  int bX, bY, bDX, bDY, pX;
  char level[8][8];
  int speed = 10;
  int skill = 1;
  int bricks = 24;
  enum {LEFT, RIGHT, NONE} controls = NONE;
  
  void restart();
  void updatePaddle();
  void play();
  void movePaddle(int controls);
};
