#include "event.h"

Event* Event::instance = nullptr;

std::string Event::changeType(std::string s, SDL_Renderer *renderer)
{
  if (type != "play" && s == "play")
  {
    SDL_ShowCursor(SDL_DISABLE);
  }

  if (type == "play" && s != "play")
  {
    SDL_ShowCursor(SDL_ENABLE);
  }

  if (type != "start" && s == "start")
  {
    Play::Instance() -> reset(renderer);
  }
  return type = s;
}

std::string Event::updating(SDL_Renderer *renderer)
{
  SDL_Event e;
  SDL_PollEvent(&e);

  if (e.type == SDL_QUIT)
  {
    return Event::Instance() -> changeType("quit", renderer);
  }

  if (e.type == SDL_MOUSEBUTTONDOWN)
  {
//-------------------------------------------CLIENT---------------------------------------------//
    if (Event::Instance() -> type == "client")
    {
      if (Check::clickInRect(e.button, clientGame::Instance() -> areaPlay))
      {
        return Event::Instance() -> changeType("start", renderer);
      }
      if (Check::clickInRect(e.button, clientGame::Instance() -> areaLevel))
      {
        return Event::Instance() -> changeType("level", renderer);
      }
      if (Check::clickInRect(e.button, clientGame::Instance() -> areaSetting))
      {
        return Event::Instance() -> changeType("setting", renderer);
      }
      if (Check::clickInRect(e.button, clientGame::Instance() -> areaCustom))
      {
        return Event::Instance() -> changeType("custom", renderer);
      }
    }
    else
//-------------------------------------------START---------------------------------------------//
    if (Event::Instance() -> type == "start")
    {
      double x = e.button.x - WIDTH / 2, y = e.button.y - (yBar - radiusBall);

      unitize(x, y);
      Ball b = Play::Instance() -> setBall.front();
      Play::Instance() -> setBall.pop();

      b.dirX = x;
      b.dirY = y;

      Play::Instance() -> setBall.push(b);
      return Event::Instance() -> changeType("play", renderer);
    }
    else
//-------------------------------------------OVER---------------------------------------------//
    if (Event::Instance() -> type == "over")
    {
      if (Check::clickInRect(e.button, Play::Instance() -> areaBackClient))
      {
        return Event::Instance() -> changeType("client", renderer);
      }
      if (Check::clickInRect(e.button, Play::Instance() -> areaContinue))
      {
        return Event::Instance() -> changeType("start", renderer);
      }
    }
    else
//-------------------------------------------VICTORY---------------------------------------------//
    if (Event::Instance() -> type == "victory")
    {
      if (Check::clickInRect(e.button, Play::Instance() -> areaBackClient))
      {
        return Event::Instance() -> changeType("client", renderer);
      }
      if (Check::clickInRect(e.button, Play::Instance() -> areaContinue))
      {
        return Event::Instance() -> changeType("start", renderer);
      }
    }
    else
//-------------------------------------------LEVEL---------------------------------------------//
    if (Event::Instance() -> type == "level")
    {
      if (Check::clickInRect(e.button, Level::Instance() -> areaBackClient))
      {
        return Event::Instance() -> changeType("client", renderer);
      }
      if (Check::clickInRect(e.button, Level::Instance() -> areaDecLevel))
      {
        Level::Instance() -> decLevel();
        return Event::Instance() -> type;
      }
      if (Check::clickInRect(e.button, Level::Instance() -> areaIncLevel))
      {
        Level::Instance() -> incLevel();
        return Event::Instance() -> type;
      }
    }
    else
//-------------------------------------------SETTINGS---------------------------------------------//
    if (Event::Instance() -> type == "setting")
    {
      if (Check::clickInRect(e.button, Setting::Instance() -> areaBackClient))
      {
        return Event::Instance() -> changeType("client", renderer);
      }

      Setting::Instance() -> selectButtonFPS.Clicked(e.button);

      Setting::Instance() -> selectButtonSoundEffects.Clicked(e.button);
      if (Setting::Instance() -> selectButtonSoundEffects.isLeft)
        Sound::on();
      else
        Sound::off();

      Setting::Instance() -> selectButtonColorBall.Clicked(e.button);
      Setting::Instance() -> selectButtonMode.Clicked(e.button);
    }
    else
//-------------------------------------------CUSTOM---------------------------------------------//
    if (Event::Instance() -> type == "custom")
    {
      if (Check::clickInRect(e.button, Custom::Instance() -> areaBackClient))
      {
        return Event::Instance() -> changeType("client", renderer);
      }
      if (Check::clickInRect(e.button, Custom::Instance() -> areaSave))
      {
        Custom::Instance() -> saveData();
        return Event::Instance() -> changeType("client", renderer);
      }
      if (Check::clickInRect(e.button, {0, 0, WIDTH, WIDTH}))
      {
        Custom::Instance() -> saveMouseDown(e.button.x, e.button.y);
      //  Custom::Instance() -> changeCell(e.button.x, e.button.y, Custom::Instance() -> indexCell + '0');
      }
      if (Check::clickInRect(e.button, Custom::Instance() -> areaIncCell))
      {
        Custom::Instance() -> incIndexCell();
      }
      if (Check::clickInRect(e.button, Custom::Instance() -> areaDecCell))
      {
        Custom::Instance() -> decIndexCell();
      }
    }
  }

  if (Event::Instance() -> type == "custom" && Custom::Instance() -> clicked == 1)
  {
    if (e.type == SDL_MOUSEBUTTONUP)
    {
      Custom::Instance() -> saveMouseUp(e.button.x, e.button.y);
    }
  }


  return Event::Instance() -> type;
}
