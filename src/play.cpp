#include "play.h"
#include "textureManager.h"
#include <fstream>
#include <math.h>

int unit = 1;

Play* Play::instance = nullptr;

bool Play::destroyCell(int i, int j)
{
  if (a[i][j] == '0') return false;

  if (a[i][j] != '1')
  {
    a[i][j] = '0';
    numbersCell --;

    if (1 < i && i + 2 < WIDTH / lengthCell)
    {
      int r = Get::Rand((setBall.size() + setGift.size()) * 3);
      if (r == 1) setGift.push(Gift(i * lengthCell + lengthCell / 2, (j + 1) * lengthCell, 0));
      if (r == 2) setGift.push(Gift(i * lengthCell + lengthCell / 2, (j + 1) * lengthCell, 1));
    }
  }

  return true;
}

bool Play::checkInCell(double x, double y)
{
  int i = x / lengthCell, j = y / lengthCell;

  if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return 0;

  return destroyCell(i, j);
}

bool Play::checkX(double x, double y, bool ok)
{
  if (ok && x + radiusBall >= WIDTH) return 1;
  if (!ok && x - radiusBall <= 0) return 1;

  if (y >= yBar && y <= yBar + heightBar)
  {
    if (ok && x + radiusBall >= Get::xMiddleBar() - widthBar / 2 && x + radiusBall <= Get::xMiddleBar() - widthBar / 2 + unit) return 1;
    if (!ok && x - radiusBall <= Get::xMiddleBar() + widthBar / 2 && x - radiusBall >= Get::xMiddleBar() - widthBar / 2 - unit) return 1;
  }

  if (ok == 0)
  {
    return checkInCell(x - radiusBall, y);
  }
  else
  {
    return checkInCell(x + radiusBall, y);
  }
}

bool Play::checkY(double x, double y, bool ok)
{
  if (!ok && y - radiusBall <= 0) return 1;
  if (ok && y + radiusBall >= HEIGHT) return 0;

  if (ok == 0)
  {
    return checkInCell(x, y - radiusBall);
  }
  else
  {
    return checkInCell(x, y + radiusBall);
  }

  return 0;
}

void Play::readData(int level)
{
  std::string path = (Setting::Instance() -> selectButtonMode.isLeft ?  "data/level/" + std::to_string(level) + ".txt" : "data/level/custom.txt");

  std::ifstream inp(path.c_str());

  numbersCell = 0;

  for (int i = 0; i < HEIGHT / lengthCell; ++i)
    for (int j = 0; j < WIDTH / lengthCell; ++j)
    {
      inp >> a[j][i];
      if (a[j][i] != '0' && a[j][i] != '1') numbersCell ++;
    }
}

bool Play::nextBall(Ball &b)
{
  bool ok = 0;

  if (b.dirY > 0 && b.y + radiusBall >= yBar && b.y + radiusBall <= yBar + unit && abs(b.x - Get::xMiddleBar()) < widthBar / 2)
  {
    b.dirX = b.dirX;
    b.dirY = -b.dirY;

    double x = (b.x - Get::xMiddleBar()) / (widthBar / 2);
    double y = sqrt(1 - x * x);

    double alpha = Get::Angle(b.dirX, -b.dirY) + (Get::Angle(x, y) - PI / 2) / 2;

    if (alpha >= PI) alpha = PI - 0.1;
    if (alpha < 0) alpha = 0.1;

    b.dirX = cos(alpha);
    b.dirY = -sin(alpha);

    if (b.dirY >= -0.4)
    {
      b.dirY = -0.4;
      b.dirX = -b.dirX / abs(b.dirX) * sqrt(1 - b.dirY * b.dirY);
    }

    return 1;
  }

  if (checkX(b.x, b.y, (b.dirX > 0 ? 1 : 0)))
  {
    ok = 1;
    b.dirX = -b.dirX;
  }

  if (checkY(b.x, b.y, (b.dirY > 0 ? 1 : 0)))
  {
    ok = 1;
    b.dirY = -b.dirY;
  }

  b.x += b.dirX * unit;
  b.y += b.dirY * unit;

  return ok;
}

void Play::openGift(int type)
{
  if (setBall.size() >= limitNumbersBall) return;

  if (type == 0)
  {
    setBall.push(Ball(Get::xMiddleBar(), yBar - radiusBall, -sqrt(2) / 2, -sqrt(2) / 2));
    setBall.push(Ball(Get::xMiddleBar(), yBar - radiusBall, 0, -1));
    setBall.push(Ball(Get::xMiddleBar(), yBar - radiusBall, sqrt(2) / 2, -sqrt(2) / 2));
  }
  else
  {
    int cur = setBall.size();

    while (cur--)
    {
      Ball b = setBall.front();
      double alpha = Get::Angle(b.dirX, b.dirY);

      do
      {
        alpha = alpha + double(Get::Rand(360)) / 360 * 2 * PI;
      } while(Check::rightAngle(alpha) && Check::rightAngle(alpha + 2 * PI / 3) && Check::rightAngle(alpha + 4 * PI / 3));

      setBall.push(Ball(b.x, b.y, cos(alpha + 0 * PI / 3), sin(alpha + 0 * PI / 3)));
      setBall.push(Ball(b.x, b.y, cos(alpha + 2 * PI / 3), sin(alpha + 2 * PI / 3)));
      setBall.push(Ball(b.x, b.y, cos(alpha + 4 * PI / 3), sin(alpha + 4 * PI / 3)));

      setBall.pop();
    }
  }
}

void Play::updateBall()
{
  int cur = setBall.size();
  bool bOpenSound = 0;

  while (cur--)
  {
    Ball b = setBall.front();

    for (int i = 0; i < b.getSpeed(); ++i)
      bOpenSound |= nextBall(b);

    if (b.y - radiusBall < HEIGHT) setBall.push(b);

    setBall.pop();
  }

  if (bOpenSound)
    Sound::open("data/mixer/collision.wav", 0);
}

void Play::updateGift()
{
  int cur = setGift.size();

  while (cur--)
  {
    Gift g = setGift.front();
    setGift.pop();

    g.y += g.getSpeed();

    if (g.y - radiusGift >= HEIGHT) continue;

    if (abs(g.x - Get::xMiddleBar()) <= radiusGift + widthBar / 2 && g.y + radiusGift >= yBar && g.y - radiusGift <= yBar + heightBar)
      openGift(g.type);
    else
      setGift.push(g);
  }
}

void Play::keepingMouseInWindow(SDL_Window *window)
{
  SDL_PumpEvents();
  int x, y;
  SDL_GetMouseState(&x, &y);
  y = std::max(y, HEIGHT - HEIGHT / 3);
  y = std::min(y, HEIGHT / 3);
  x = std::max(x, widthBar / 2);
  x = std::min(x, WIDTH - widthBar / 2);
  SDL_WarpMouseInWindow(window, x, y);
}

void Play::showCell(SDL_Renderer *renderer)
{
  for (int i = 0; i < WIDTH / lengthCell; ++i)
    for (int j = 0; j < WIDTH / lengthCell; ++j)
    {
      SDL_Rect r = {i * lengthCell, j * lengthCell, lengthCell, lengthCell};
      Draw::Cell(renderer, r, convertCharToColor(a[i][j]));
    }
}

void Play::showBall(SDL_Renderer *renderer)
{
  int cur = setBall.size();
  while (cur--)
  {
    Ball b = setBall.front();
    Draw::Circle(renderer, b.x, b.y, radiusBall, (Setting::Instance() -> selectButtonColorBall.isLeft ? WHITE : VIOLET));
    setBall.pop();
    setBall.push(b);
  }
}

void Play::showGift(SDL_Renderer *renderer)
{
  int cur = setGift.size();
  while (cur--)
  {
    Gift g = setGift.front();
    textureManager::Instance() -> draw(renderer, {g.x - radiusGift, g.y - radiusGift, 2 * radiusGift, 2 * radiusGift}, (g.type ? "data/image/Gift2.png" : "data/image/Gift1.png"));
    setGift.pop();
    setGift.push(g);
  }

}

void Play::reset(SDL_Renderer *renderer)
{
  flag = 0;
  while (!setBall.empty()) setBall.pop();
  while (!setGift.empty()) setGift.pop();
  numbersCell = 0;
  Ball b(WIDTH / 2, yBar - radiusBall, 0, 0);
  setBall.push(b);
}

void Play::start(SDL_Renderer *renderer)
{
  if (flag == 0)
  {
    flag = 1;
    readData(Level::Instance() -> numberLevel);
  }

  SDL_RenderClear(renderer);
  Draw::Rect(renderer, areaBackGround, backGroundColor);

  showCell(renderer);
  showBall(renderer);
  Draw::Bar(renderer, WIDTH / 2);

  SDL_RenderPresent(renderer);
}

int Play::running(SDL_Window *window, SDL_Renderer *renderer)
{
  SDL_RenderClear(renderer);
  Draw::Rect(renderer, areaBackGround, backGroundColor);

  keepingMouseInWindow(window);

  updateBall();
  updateGift();

  showCell(renderer);
  showBall(renderer);
  showGift(renderer);

  Draw::Bar(renderer, Get::xMiddleBar());
  SDL_RenderPresent(renderer);

  if (numbersCell != 0)
  {
    if (setBall.empty())
      return 1;
    else
      return 0;
  }
  else
    return 2;
}

void Play::over(SDL_Renderer *renderer)
{
  SDL_RenderClear(renderer);
  textureManager::Instance() -> draw(renderer, areaBackGround, "data/image/Over.jpg");
  textureManager::Instance() -> draw(renderer, areaBackClient, "data/image/Icon_home.png");
  textureManager::Instance() -> draw(renderer, areaContinue, "data/image/Icon_replay.png");

  SDL_RenderPresent(renderer);
}

void Play::victory(SDL_Renderer *renderer)
{
  SDL_RenderClear(renderer);
  textureManager::Instance() -> draw(renderer, areaBackGround, "data/image/Victory.jpg");
  textureManager::Instance() -> draw(renderer, areaBackClient, "data/image/Icon_home.png");
  textureManager::Instance() -> draw(renderer, areaContinue, "data/image/Icon_next.png");

  SDL_RenderPresent(renderer);
}
