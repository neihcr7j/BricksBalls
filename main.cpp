#include "game.h"

int main( int argc, char * argv[] )
{
  int frameStart, frameTime;
  Log::Notification(std::cout, "Game init attempt....");

  if (Game::Instance() -> init(TITLE, WIDTH, HEIGHT))
  {
    Log::Notification(std::cout, "Game init success!");
    while(Game::Instance() -> running())
    {
      frameStart = SDL_GetTicks();

      std::string type = Event::Instance() -> updating(Game::Instance() -> getRenderer());

      if (type == "client")
      {
        clientGame::Instance() -> running(Game::Instance() -> getRenderer());
      }
      else
      if (type == "quit")
      {
        Game::Instance() -> quit();
      }
      else
      if (type == "start")
      {
        Play::Instance() -> start(Game::Instance() -> getRenderer());
      }
      else
      if (type == "play")
      {
        int state =  Play::Instance() -> running(Game::Instance() -> getWindow(), Game::Instance() -> getRenderer());
        if (state == 1) Event::Instance() -> changeType("over", Game::Instance() -> getRenderer());
        if (state == 2)
        {
          Level::Instance() -> incLevel();
          Event::Instance() -> changeType("victory", Game::Instance() -> getRenderer());
        }
      }
      else
      if (type == "over")
      {
        Play::Instance() -> over(Game::Instance() -> getRenderer());
      }
      else
      if (type == "victory")
      {
        Play::Instance() -> victory(Game::Instance() -> getRenderer());
      }
      else
      if (type == "level")
      {
        Level::Instance() -> running(Game::Instance() -> getRenderer());
      }
      else
      if (type == "setting")
      {
        Setting::Instance() -> running(Game::Instance() -> getRenderer());
      }
      else
      if (type == "custom")
      {
        Custom::Instance() -> running(Game::Instance() -> getRenderer());
      }

      frameTime = SDL_GetTicks() - frameStart;

      if (frameTime < Game::Instance() -> timeForOneFrame())
      {
        SDL_Delay(int(Game::Instance() -> timeForOneFrame() - frameTime));
      }
    }
  }

  Game::Instance() -> cleaner();
  Log::Notification(std::cout, "game closing.....");

  return 0;
}

