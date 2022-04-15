#include "custom.h"
#include "textureManager.h"
#include <fstream>

Custom* Custom::instance = nullptr;
int xMouseDown = 0, yMouseDown = 0;

void Custom::saveMouseDown(int x, int y)
{
  xMouseDown = x;
  yMouseDown = y;
  clicked = 1;
}

void Custom::saveMouseUp(int x, int y)
{
  x = std::min(x, WIDTH - 1);
  x = std::max(x, 0);
  y = std::min(y, WIDTH - 1);
  y = std::max(y, 0);
  clicked = 0;

  changeCell(xMouseDown, yMouseDown, x, y, indexCell + '0');
}

void Custom::incIndexCell()
{
  indexCell = (indexCell + 1) % numbersCell;
}

void Custom::decIndexCell()
{
  indexCell = (indexCell + numbersCell - 1) % numbersCell;
}

void Custom::saveData()
{
  std::string path = "data/level/custom.txt";

  std::ofstream out(path.c_str());

  for (int i = 0; i < HEIGHT / lengthCell; ++i)
    for (int j = 0; j < WIDTH / lengthCell; ++j)
      out << a[j][i] << (j + 1 == WIDTH / lengthCell ? "\n" : "");
}

void Custom::showCell(SDL_Renderer *renderer)
{
  for (int i = 0; i < WIDTH / lengthCell; ++i)
    for (int j = 0; j < WIDTH / lengthCell; ++j)
    {
      SDL_Rect r = {i * lengthCell, j * lengthCell, lengthCell, lengthCell};
      Draw::Rect(renderer, r, boderColor, 0);
      Draw::Cell(renderer, r, convertCharToColor(a[i][j]));
    }
}

void Custom::changeCell(int xBegin, int yBegin, int xEnd, int yEnd, char ch)
{
  if (xBegin > xEnd) std::swap(xBegin, xEnd);
  if (yBegin > yEnd) std::swap(yBegin, yEnd);

  for (int i = xBegin / lengthCell; i <= xEnd / lengthCell; ++i)
    for (int j = yBegin / lengthCell; j <= yEnd / lengthCell; ++j)
      a[i][j] = ch;
}

void Custom::showLightCell(SDL_Renderer *renderer, int xBegin, int yBegin, int xEnd, int yEnd)
{
  if (xBegin > xEnd) std::swap(xBegin, xEnd);
  if (yBegin > yEnd) std::swap(yBegin, yEnd);
  xEnd = std::min(xEnd, WIDTH - 1);
  xEnd = std::max(xEnd, 0);
  yEnd = std::min(yEnd, WIDTH - 1);
  yEnd = std::max(yEnd, 0);

  xBegin /= lengthCell;
  xEnd /= lengthCell;
  yBegin /= lengthCell;
  yEnd /= lengthCell;

  for (int i = xBegin; i <= xEnd; ++i)
    for (int j = yBegin; j <= yEnd; ++j)
    {
      SDL_Rect r = {i * lengthCell, j * lengthCell, lengthCell, lengthCell};
      Draw::Cell(renderer, r, convertCharToColor(indexCell + '0'));
    }

  Draw::Text(renderer, areaSize, std::to_string(yEnd - yBegin + 1) + " x " + std::to_string(xEnd - xBegin + 1), "data/ttf/arialRegular.ttf", 20, WHITE);
}

void Custom::running(SDL_Renderer *renderer)
{
  SDL_RenderClear(renderer);

  Draw::Rect(renderer, areaBackGround, backGroundColor);
  textureManager::Instance() -> draw(renderer, areaDecCell, "data/image/Icon_dec.png");
  textureManager::Instance() -> draw(renderer, areaIncCell, "data/image/Icon_inc.png");

  textureManager::Instance() -> draw(renderer, areaBackClient, "data/image/Icon_back.png");
  textureManager::Instance() -> draw(renderer, areaSave, "data/image/Icon_save.png");

  Draw::Rect(renderer, areaCell, convertCharToColor(indexCell + '0'));
  Draw::Rect(renderer, areaCell, WHITE, 0);

  showCell(renderer);

  if (clicked)
  {
    int x, y;
    SDL_GetMouseState(&x, &y);
    showLightCell(renderer, xMouseDown, yMouseDown, x, y);
  }

  SDL_RenderPresent(renderer);
}
