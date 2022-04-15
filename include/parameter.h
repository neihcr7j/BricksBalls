#ifndef PARAMETER_H
#define PARAMETER_H

#include <iostream>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define detailColor(c) c.r, c.g, c.b, c.a

const double PI = 3.1415926535;

const std::string TITLE = "Bricks&Balls";
const int WIDTH = 450;
const int HEIGHT = 700;

const int lengthCell = 10;

const int radiusBall = lengthCell / 2 - 1;

const int radiusGift = lengthCell;

const int widthBar = WIDTH / 4;
const int heightBar = radiusBall * 5;
const int yBar = HEIGHT - HEIGHT / 20 + radiusBall;

const SDL_Rect areaBackGround = {0, 0, WIDTH, HEIGHT};

const SDL_Color backGroundColor = {14, 24, 51, 255};
const SDL_Color wallColor = {80, 79, 76, 255};
const SDL_Color boderColor = {100, 100, 100, 255};
const SDL_Color WHITE = {255, 255, 255, 255};
const SDL_Color BLACK = {0, 0, 0, 255};
const SDL_Color GREEN = {68, 236, 1, 255};
const SDL_Color BLUE = {20, 224, 252, 255};
const SDL_Color ORANGE = {251, 177, 0, 255};
const SDL_Color VIOLET = {219, 112, 147, 255};
const SDL_Color PINK = {240, 128, 128, 255};

void unitize(double &x, double &y);
SDL_Color convertCharToColor(char ch);

namespace Log{
  void Notification(std::ostream& os, const std::string &msg);
  void SDLError(std::ostream& os, const std::string &msg);
  void Warning(std::ostream& os, const std::string &msg);
};

namespace Get{
  int xMiddleBar();
  SDL_Rect Bar(double x);
  double Angle(double x, double y);
  double Distance(double x, double y, double a, double b);
  int Rand(int x);
}

namespace Check{
  bool clickInRect(SDL_MouseButtonEvent e, const SDL_Rect& r);
  bool rightAngle(double alpha);
}

namespace Draw{
  void Rect(SDL_Renderer *renderer, SDL_Rect r, SDL_Color c, bool filled = 1);
  void Circle(SDL_Renderer *renderer, double x, double y, double radius, SDL_Color c);
  void Cell(SDL_Renderer *renderer, SDL_Rect r, SDL_Color c);
  void Text(SDL_Renderer *renderer, SDL_Rect r, std::string sentence, std::string path, int fontSize, SDL_Color c);
  void Bar(SDL_Renderer *renderer, double x);
}

#endif // PARAMETER_H_INCLUDED
