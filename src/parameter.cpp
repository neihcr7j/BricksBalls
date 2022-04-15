#include "parameter.h"
#include <math.h>

void unitize(double &x, double &y)
{
  double l = sqrt(x * x + y * y);
  x /= l;
  y /= l;
}

SDL_Color convertCharToColor(char ch)
{
  switch (ch)
  {
    case '0':
    {
      return backGroundColor;
    }
    case '1':
    {
      return wallColor;
    }
    case '2':
    {
      return GREEN;
    }
    case '3':
    {
      return BLUE;
    }
    case '4':
    {
      return ORANGE;
    }
    case '5':
    {
      return PINK;
    }
  }

  return backGroundColor;
}

//=========================================LOG===========================================================================//

void Log::Notification(std::ostream& os, const std::string &msg)
{
  os << msg << std::endl;
}

void Log::SDLError(std::ostream& os, const std::string &msg)
{
  os << msg << " Error: " << SDL_GetError() << std::endl;
}

void Log::Warning(std::ostream& os, const std::string &msg)
{
  os << "Warning: " << msg << std::endl;
}

//=========================================GET===========================================================================//

int Get::xMiddleBar()
{
  SDL_PumpEvents();
  int x, y;
  SDL_GetMouseState(&x, &y);
  x = std::max(x, widthBar / 2);
  x = std::min(x, WIDTH - widthBar / 2);
  return x;
}

SDL_Rect Get::Bar(double x)
{
  SDL_Rect r = {x - widthBar / 2, yBar, widthBar, heightBar};
  r.x = std::max(r.x, 0);
  r.x = std::min(r.x, WIDTH - widthBar);
  return r;
}

double Get::Angle(double x, double y)
{
  double alpha = atan(y / x);
  if (y == 0)
    alpha = (x >= 0 ? 0 : PI);
  else
  if (y > 0)
    alpha = (alpha > 0 ? alpha : alpha + PI);
  else
    alpha = (alpha > 0 ? alpha + PI : alpha);

  return alpha;
}

double Get::Distance(double x, double y, double a, double b)
{
  return sqrt((x - a) * (x - a) + (y - b) * (y - b));
}

int Get::Rand(int x)
{
  return (rand() % x + 1) * rand() % x;
}

//============================================CHECK=======================================================================//

bool Check::clickInRect(SDL_MouseButtonEvent e, const SDL_Rect& r)
{
  return e.x >= r.x && e.y >= r.y && e.x <= r.x + r.w && e.y <= r.y + r.h;
}

bool Check::rightAngle(double alpha)
{
  return abs(int(alpha / (PI / 2)) - (alpha / (PI / 2))) < 0.4;
}

//==============================================DRAW=======================================================================//

void Draw::Rect(SDL_Renderer *renderer, SDL_Rect r, SDL_Color c, bool filled)
{
  SDL_SetRenderDrawColor(renderer, detailColor(c));
  if (filled)
    SDL_RenderFillRect(renderer, &r);
  else
    SDL_RenderDrawRect(renderer, &r);
}

void Draw::Cell(SDL_Renderer *renderer, SDL_Rect r, SDL_Color c)
{
  int d = r.w / 10;
  r.x += d; r.y += d;
  r.w -= 3 * d; r.h -= 3 * d;
  Rect(renderer, r, c);
}

void Draw::Text(SDL_Renderer *renderer, SDL_Rect r, std::string sentence, std::string path, int fontSize, SDL_Color c)
{
  TTF_Font *font = TTF_OpenFont(path.c_str(), fontSize);

  SDL_Surface *surface = TTF_RenderText_Solid(font, sentence.c_str(), c);
  SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

  int w, h;
  SDL_QueryTexture(texture, NULL, NULL, &w, &h);
  int x = r.x + r.w / 2 - w / 2, y = r.y + r.h / 2 - h / 2;
  SDL_Rect rText = {x, y, w, h};

  SDL_FreeSurface(surface);
  SDL_RenderCopy(renderer, texture, NULL, &rText);

  TTF_CloseFont(font);
}

void Draw::Bar(SDL_Renderer *renderer, double x)
{
  Rect(renderer, Get::Bar(x), ORANGE);
}

void Draw::Circle(SDL_Renderer *renderer, double x, double y, double radius, SDL_Color c)
{
  SDL_SetRenderDrawColor(renderer, detailColor(c));
  for (double i = x - radius; i <= x + radius; i++)
    for (double j = y - radius; j <= y + radius; j++)
      if (Get::Distance(x, y, i, j) <= radius)
        SDL_RenderDrawPoint(renderer, i, j);
}

