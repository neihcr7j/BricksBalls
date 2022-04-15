#ifndef CUSTOM_H
#define CUSTOM_H

#include <parameter.h>

class Custom{
public:
  const SDL_Rect areaBackClient = {0, HEIGHT - HEIGHT / 10, WIDTH / 6, HEIGHT / 10},
                 areaSave = {WIDTH - WIDTH / 7, HEIGHT - HEIGHT / 10, WIDTH / 7, HEIGHT / 10},
                 areaDecCell = {100, 500, 50, 50},
                 areaIncCell = {300, 500, 50, 50},
                 areaCell = {200, 500, 50, 50},
                 areaSize = {390, 460, 50, 10};

  int clicked;
  int indexCell, numbersCell;
  char a[WIDTH / lengthCell][HEIGHT / lengthCell];

  Custom()
  {
    clicked = 0;
    indexCell = 0;
    numbersCell = 6;

    for (int i = 0; i < WIDTH / lengthCell; ++i)
      for (int j = 0; j < HEIGHT / lengthCell; ++j)
        a[i][j] = '0';
  };

  static Custom* Instance()
	{
		if (instance == nullptr) instance = new Custom();
		return instance;
	}

  void saveMouseDown(int x, int y);
  void saveMouseUp(int x, int y);
  void incIndexCell();
  void decIndexCell();
	void saveData();
	void changeCell(int xBegin, int yBegin, int xEnd, int yEnd, char ch);
  void showLightCell(SDL_Renderer *renderer, int xBegin, int yBegin, int xEnd, int yEnd);
  void running(SDL_Renderer *renderer);

private:
  static Custom* instance;
  void showCell(SDL_Renderer *renderer);
};

#endif // CUSTOM_H
