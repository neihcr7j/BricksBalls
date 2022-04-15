#include "level.h"
#include "textureManager.h"

Level* Level::instance = nullptr;

void Level::decLevel()
{
  numberLevel = (numberLevel + levelMax - 1) % levelMax;
}
void Level::incLevel()
{
  numberLevel = (numberLevel + 1) % levelMax;
}
void Level::running(SDL_Renderer *renderer)
{
  SDL_RenderClear(renderer);

  textureManager::Instance() -> draw(renderer, areaBackGround,"data/image/Level.jpg");
  textureManager::Instance() -> draw(renderer, areaBackClient,"data/image/icon_back.png");
  textureManager::Instance() -> draw(renderer, areaDecLevel,"data/image/icon_dec.png");
  textureManager::Instance() -> draw(renderer, areaIncLevel,"data/image/icon_inc.png");

  Draw::Text(renderer, areaBackGround, std::to_string(numberLevel + 1), "data/ttf/arialRegular.ttf", 150, WHITE);

  SDL_RenderPresent(renderer);
}
