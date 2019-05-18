class Drive {  
  void moveLines();
  void drawLines();
  void checkCollision();
  void resetLevel();

  public:
  int pX;
  char level[8][8];
  char lines[8];
  int speed;
  int score;
  enum {LEFT, RIGHT, NONE} controls = NONE;
  
  void restart();
  void play();
  void movePlayer(int controls);
};
