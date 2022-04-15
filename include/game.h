#ifndef GAME_H
#define GAME_H

#include <event.h>

class Game{
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  TTF_Font *font;

  bool bRunning;

  Game(): bRunning(false), window(nullptr), renderer(nullptr) {}

  static Game* instance;

public:
  static Game* Instance()
	{
		if (instance == nullptr) instance = new Game();
		return instance;
	}

	SDL_Renderer *getRenderer() {return renderer;}
	SDL_Window *getWindow() {return window;}

  bool init(std::string TITLE, int width, int height);
  bool running();

  int getFPS();
  double timeForOneFrame();

  void quit();
  void cleaner();
};

#endif // GAMELIB_H_INCLUDED
