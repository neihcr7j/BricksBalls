#include "setting.h"
#include "textureManager.h"

void SelectButton::Clicked(SDL_MouseButtonEvent e)
{
  if (Check::clickInRect(e, getRect(0))) isLeft = 1;
  if (Check::clickInRect(e, getRect(1))) isLeft = 0;
}

SDL_Rect SelectButton::getRect(bool isLeft)
{
  return {area.x + (isLeft ? area.w / 2 : 0), area.y, area.w / 2, area.h};
}

void SelectButton::Show(SDL_Renderer *renderer)
{
  Draw::Rect(renderer, getRect(0), (isLeft ? darkColor : lightColor));
  Draw::Rect(renderer, getRect(1), (isLeft ? lightColor : darkColor));

  Draw::Text(renderer, getRect(0), contentLeft, "data/ttf/arialBold.ttf", 20, BLACK);
  Draw::Text(renderer, getRect(1), contentRight, "data/ttf/arialBold.ttf", 20, BLACK);
}

Setting* Setting::instance = nullptr;

void Setting::running(SDL_Renderer *renderer)
{
  SDL_RenderClear(renderer);

  textureManager::Instance() -> draw(renderer, areaBackGround, "data/image/Setting.jpg");
  textureManager::Instance() -> draw(renderer, areaBackClient, "data/image/Icon_back.png");

  selectButtonFPS.Show(renderer);
  selectButtonSoundEffects.Show(renderer);
  selectButtonColorBall.Show(renderer);
  selectButtonMode.Show(renderer);

  SDL_RenderPresent(renderer);
}
