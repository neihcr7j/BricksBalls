#ifndef SETTING_H
#define SETTING_H

#include <parameter.h>
#include <sound.h>

struct SelectButton{
  SDL_Rect area;
  bool isLeft;
  std::string contentLeft, contentRight;
  const SDL_Color lightColor = {240, 230, 140}, darkColor = {255, 215, 0, 255};

  SelectButton(SDL_Rect _area = {0, 0, 0, 0}, bool _isLeft = 1, std::string _contentLeft = "", std::string _contentRight = "") :
  area(_area), isLeft(_isLeft), contentLeft(_contentLeft), contentRight(_contentRight)
  {};

  void Clicked(SDL_MouseButtonEvent e);
  SDL_Rect getRect(bool isLeft);
  void Show(SDL_Renderer *renderer);
};

class Setting{
public:
  const SDL_Rect areaBackClient = {0, HEIGHT - HEIGHT / 10, WIDTH / 6, HEIGHT / 10};

  SelectButton
    selectButtonFPS = SelectButton({290, 190, 150, 25}, 1, "Low", "High"),
    selectButtonSoundEffects = SelectButton({290, 265, 150, 25}, 1, "Yes", "No"),
    selectButtonColorBall = SelectButton({290, 340, 150, 25}, 1, "White", "Violet"),
    selectButtonMode = SelectButton({290, 415, 150, 25}, 1, "Classic", "Custom");

  Setting() {};
  static Setting* Instance()
	{
		if (instance == nullptr) instance = new Setting();
		return instance;
	}

  void running(SDL_Renderer *renderer);

private:
  static Setting* instance;
};

#endif // SETTING_H
