#include "game.h"
#include "textureManager.h"

Game* Game::instance = nullptr;

bool Game::init(std::string TITLE, int width, int height)
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    Log::SDLError(std::cout, "SDL init fail");
    return 0;
  }

  window = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, 0);

  if (window == nullptr)
  {
    Log::SDLError(std::cout, "window init fail");
    return 0;
  }

  renderer = SDL_CreateRenderer(window, -1, 0);

  if (renderer == nullptr)
  {
    Log::SDLError(std::cout, "renderer init fail");
    return 0;
  }

  if (!TTF_Init())
    Log::Notification(std::cout, "TTF init fail");

  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
    Log::Notification(std::cout, "Mixer init fail");
  bRunning = 1;

  return 1;
}

bool Game::running()
{
  return bRunning;
}

int Game::getFPS()
{
  return (Setting::Instance() -> selectButtonFPS.isLeft ? 40 : 50);
}

double Game::timeForOneFrame()
{
  return (double)1000 / getFPS();
}

void Game::quit()
{
  bRunning = 0;
}

void Game::cleaner()
{
  Log::Notification(std::cout, "Cleaning game....");
  textureManager::Instance() -> clearAllTexture();
  SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
