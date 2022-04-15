#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL.h>
#include <SDL_image.h>
#include <map>

class textureManager{
public:
  bool load(SDL_Renderer *renderer, std::string path);
  void draw(SDL_Renderer *renderer, SDL_Rect r, std::string path);
  void clearTexture(std::string path);
  void clearAllTexture();

  textureManager() {};
  static textureManager* Instance()
	{
		if (instance == nullptr) instance = new textureManager();
		return instance;
	}

private:
  static textureManager* instance;
  std::map<std::string, SDL_Texture*> textureMap;
};

#endif // TEXTUREMANAGER_H
