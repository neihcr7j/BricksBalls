#ifndef CLIENTGAME_H
#define CLIENTGAME_H

#include <parameter.h>

class clientGame{
public:
  const SDL_Rect
    areaPlay = {75, 350, 300, 70},
    areaLevel = {75, 550, 137, 52},
    areaSetting = {237, 550, 137, 52},
    areaCustom = {75, 450, 300, 70};

  clientGame() {};
  static clientGame* Instance()
	{
		if (instance == nullptr) instance = new clientGame();
		return instance;
	}

  void running(SDL_Renderer *rendnerer);

private:
  static clientGame* instance;
};

#endif // CLIENTGAME_H
