#ifndef PLAY_H
#define PLAY_H

#include "level.h"
#include "setting.h"
#include <queue>

struct Gift{
  int type;
  double x, y;

  double getSpeed()
  {
    return double(100) / (Setting::Instance() -> selectButtonFPS.isLeft ? 40 : 50);
  }

  Gift(double _x = 0, double _y = 0, bool _type = 0) : x(_x), y(_y), type(_type) {};
};

struct Ball{
  double x, y;
  double dirX, dirY;

  int getSpeed()
  {
    return 400 / (Setting::Instance() -> selectButtonFPS.isLeft ? 40 : 50);
  }

  Ball(double _x = 0, double _y = 0, double _dirX = 0, double _dirY = 0) : x(_x), y(_y), dirX(_dirX), dirY(_dirY) {};
};

class Play{
public:
  const SDL_Rect
    areaBackClient = {100, 260, 100, 100},
    areaContinue = {240, 260, 100, 100};

  bool flag;
  char a[WIDTH / lengthCell][HEIGHT / lengthCell];
  int numbersCell;
  const int static limitNumbersBall = 100;
  std::queue <Ball> setBall;
  std::queue <Gift> setGift;

  Play() : flag(0) {};

  void reset(SDL_Renderer *renderer);

  static Play* Instance()
	{
		if (instance == nullptr) instance = new Play();
		return instance;
	}

	static Play* instance;

	void start(SDL_Renderer *renderer);
  int running(SDL_Window *window, SDL_Renderer *renderer);
  void over(SDL_Renderer *renderer);
  void victory(SDL_Renderer *renderer);

private:
  bool destroyCell(int i, int j);
  bool checkInCell(double x, double y);
  bool checkX(double x, double y, bool ok);
  bool checkY(double x, double y, bool ok);

  void readData(int level);
  bool nextBall(Ball &b);
  void openGift(int type);
  void updateBall();
  void updateGift();
  void keepingMouseInWindow(SDL_Window *window);
  void showCell(SDL_Renderer *renderer);
  void showBall(SDL_Renderer *renderer);
  void showGift(SDL_Renderer *renderer);
};

#endif // PLAY_H
