#include "clientGame.h"
#include "textureManager.h"

clientGame* clientGame::instance = nullptr;

void clientGame::running(SDL_Renderer *renderer)
{
  SDL_RenderClear(renderer);
  textureManager::Instance() -> draw(renderer, areaBackGround, "data/image/Client.jpg");
  SDL_RenderPresent(renderer);
}
